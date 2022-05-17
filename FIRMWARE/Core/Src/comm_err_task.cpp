/*
 * comm_err_task.cpp
 *
 *  Created on: May 6, 2022
 *      Author: Maks
 */
#include <comm_err_task.hpp>
#include <etl/flat_map.h>

enum struct Error_condition{
	UNBALANCE,
	VOLTAGE_LOW,
	VOLTAGE_HIGH,
	TEMPERATURE_WARNING,
	TEMPERATURE_HIGH,
	CURRENT_HIGH,
	NEUTRAL_CURRENT_CAR
};


struct Error_and_connditions{
	Error_condition error;
	float min;
	float max;
	//const float &value;
};


// error if value is in range <min, max>
std::array< Error_and_connditions, 7> error_conditions = {
		Error_and_connditions{Error_condition::UNBALANCE,{2000,INT_MAX}},
		Error_and_connditions{Error_condition::VOLTAGE_LOW,{INT_MIN,30000}},
		Error_and_connditions{Error_condition::VOLTAGE_HIGH,{42200,INT_MAX}},
		Error_and_connditions{Error_condition::TEMPERATURE_WARNING,{48,55}},
		Error_and_connditions{Error_condition::TEMPERATURE_HIGH,{55,INT_MAX}},
		Error_and_connditions{Error_condition::CURRENT_HIGH,{20,INT_MAX}},
		Error_and_connditions{Error_condition::NEUTRAL_CURRENT_CAR,{0,1}} //float?  //to check
};



void error_values(){

//	Error_condition::UNBALANCE = data.voltages.cells[i] - data.voltages.lowest_cell_voltage;
//	Error_condition::VOLTAGE_LOW = data.voltages.lowest_cell_voltage;
//	Error_condition::VOLTAGE_LOW = data.voltages.highest_cell_voltage;
//	Error_condition::TEMPERATURE_WARNING = data.temperatures.highest_temperature;
//	Error_condition::TEMPERATURE_HIGH = data.temperatures.highest_temperature;
//	Error_condition::CURRENT_HIGH = data.current.value;
//	Error_condition::NEUTRAL_CURRENT_CAR = data.current.value;

	etl::vector<Error_condition, 10> errors;

	for( const auto& error : error_conditions){
		if(error.min <= error.value && error.value <= error.max){
			errors.emplace_back(error.error);
		}
	}

	for (auto error : errors){
		// do sth
	}


}



struct Timers{
	uint32_t balance_error[NUMBER_OF_CELLS];
	uint32_t low_voltage_error[NUMBER_OF_CELLS];
	uint32_t high_voltage_error[NUMBER_OF_CELLS];
	uint32_t high_temperature_error[NUMBER_OF_CELLS];
	uint32_t high_current_error[1];
	uint32_t sleep[1];

};

struct Flags{
	bool balance_error[NUMBER_OF_CELLS];
	bool low_voltage_error[NUMBER_OF_CELLS];
	bool high_voltage_error[NUMBER_OF_CELLS];
	bool high_temperature_error[NUMBER_OF_CELLS];
	bool high_current_error[1];
	bool sleep[1];
};

struct Error{
	Timers timers;
	Flags flags;
}error;

/*
	if(timer <= HAL_GetTick())
	{
		// warning/shut down
		// acu state
		// led
	}
 */

void if_error_occurs(uint32_t *timers, bool *flag, unsigned int *i, static const int condition, static const int error_time, uint16_t variable)
{
	switch (condition)
	{
	case 'UNBALANCE_LIMIT':
	case 'VOL_UP_LIMIT':
	case 'TOO_HIGH_CURRENT':
	case 'TEMPERATURE_LIMIT':
	case 'TEMPERATURE_WARNING':
		if(variable > condition)
		{
			if(false == flag[i])
			{
				timers[i] = HAL_GetTick() + error_time;
				flag[i] = true;
				//acu state
			}
		}else{
			timers[i] = HAL_GetTick() + error_time;
			flag[i] = false;
			//acu state
		}


		break;
	case 'VOL_DOWN_LIMIT':
	case 'NEUTRAL_CURRENT_CAR': //when the car is turned off, it causes counting to program sleep
		if(variable < condition)
		{
			if(false == flag[i])
			{
				timers[i] = HAL_GetTick() + error_time;
				flag[i] = true;
				//acu state
			}
		}else{
			timers[i] = HAL_GetTick() + error_time;
			flag[i] = false;
			//acu state
		}



		break;

	}
}

void error_check()
{
	for(unsigned int i = 0; i < NUMBER_OF_CELLS; i++)
	{
		uint16_t voltage_diff = data.voltages.cells[i] - data.voltages.lowest_cell_voltage;

		if_error_occurs(error.timers.balance_error, error.flags.balance_error, i, UNBALANCE_LIMIT, ERROR_TIME, voltage_diff);

		if_error_occurs(error.timers.low_voltage_error, error.flags.low_voltage_error, i, VOL_DOWN_LIMIT, ERROR_TIME, data.voltages.cells);

		if_error_occurs(error.timers.high_voltage_error, error.flags.high_voltage_error, i, VOL_UP_LIMIT, ERROR_TIME, data.voltages.cells);

		if(5 != i)
		{
			if_error_occurs(error.timers.high_temperature_error, error.flags.high_temperature_error, i, TEMPERATURE_LIMIT, ERROR_TIME_TEMPERATURES, data.temperatures.values);

			//should I add a warning for lower temperature?
			//if_error_occurs(error.timers.high_temperature_error, error.flags.high_temperature_error, i, TEMPERATURE_LIMIT, ERROR_TIME_TEMPERATURES, data.temperatures.values);
		}
	}

	if_error_occurs(error.timers.high_current_error, error.flags.high_current_error, 0, TOO_HIGH_CURRENT, ERROR_TIME, (uint16_t)data.current.value);


}

void start_comm_function(void *argument){

	for(;;){

		osDelay(1);
	}
}



