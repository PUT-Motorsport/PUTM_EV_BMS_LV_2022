/*
 * comm_err_task.cpp
 *
 *  Created on: May 6, 2022
 *      Author: Maks
 */
#include <comm_err_task.hpp>
#include <etl/vector.h>

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
	float value;
	const uint32_t error_time;
	uint32_t timer;
	bool flag;
};


// error if value is in range <min, max>
Error_and_connditions error_conditions[7] = {
		{Error_condition::UNBALANCE,2000,50000,(float)(data.voltages.highest_cell_voltage-data.voltages.lowest_cell_voltage),500},
		{Error_condition::VOLTAGE_LOW,0,30000,(float)data.voltages.lowest_cell_voltage,500},
		{Error_condition::VOLTAGE_HIGH,42200,500000,(float)data.voltages.highest_cell_voltage,500},
		{Error_condition::TEMPERATURE_WARNING,48,55,(float)data.temperatures.highest_temperature,1000},
		{Error_condition::TEMPERATURE_HIGH,55,120,(float)data.temperatures.highest_temperature,500},
		{Error_condition::CURRENT_HIGH,20,100,data.current.value,500},
		{Error_condition::NEUTRAL_CURRENT_CAR,0,0.3,data.current.value,1200000} //to check
};



void error_check(){


	etl::vector<Error_condition, 10> errors_vector;

	for(auto& error : error_conditions){
		if(error.min <= error.value && error.value <= error.max){

			if(false == error.flag)
			{
				errors_vector.emplace_back(error.error);
				error.timer = HAL_GetTick() + error.error_time;
				error.flag = true;
				//acu state
			}
		}
		else{
			error.timer = HAL_GetTick() + error.error_time;
			error.flag = false;
			//acu state
		}
	}

	for (auto error : errors_vector){
		// do sth
	}


}


/*
	if(timer <= HAL_GetTick())
	{
		// warning/shut down
		// acu state
		// led
	}
 */

void start_comm_function(void *argument){

	for(;;){

		osDelay(1);
	}
}



