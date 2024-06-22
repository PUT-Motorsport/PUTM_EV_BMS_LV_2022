/*
 * ltc_task.cpp
 *
 *  Created on: May 22, 2022
 *      Author: Maks
 */

#include <ltc_task.hpp>
#include <ltc_library.hpp>
#include <global_variables.hpp>


const int temperature_map[26][2] = {
//	  adc value ,  temperature *C
		{4096	,	-50} ,
		{3713	,	-20} ,
		{3602	,	-15} ,
		{3469	,	-10} ,
		{3313	,	-5}	,
		{3136	,	0}	,
		{2939	,	5}	,
		{2726	,	10}	,
		{2503	,	15}	,
		{2275	,	20}	,
		{2048	,	25}	,
		{1828	,	30}	,
		{1618	,	35}	,
		{1424	,	40}	,
		{1245	,	45}	,
		{1085	,	50}	,
		{942	,	55}	,
		{816	,	60}	,
		{706	,	65}	,
		{611	,	70}	,
		{528	,	75}	,
		{458	,	80}	,
		{397	,	85}	,
		{344	,	90}	,
		{299	,	95}	,
		{261	,	100}

};

/**
 * Brief:	Calculation of temperature, from value of measured voltage
 * Param:	value:	Value of voltage, LSB -> 0.1 mV
 * Retval:	Temperature in *C
 */
float temperature_calculations(uint16_t value)
{
	float retval = 0.0;
	for(unsigned int i = 1; i < 28; i++)
	{
		if(value >= (uint16_t)temperature_map[i][0])
		{
			// approximation
			retval = (float)temperature_map[i][1] - 5.0 * ((float)value-(float)temperature_map[i][0]) / ((float)temperature_map[i-1][0] - (float)temperature_map[i][0]);
			break;
		}
	}
	return retval;
}

/**
 * Brief:	Getting proper values of temperatures on every cell in *C
 * Param:	None
 * Retval:	None
 */
void get_temperatures()
{
	data.temperatures.average = 0;
	for(unsigned int i = 0; i < NUMBER_OF_TEMPERATURES; i++)
	{
		data.temperatures.values[i] = (uint16_t)temperature_calculations(data.temperatures.adc[MAX_NUMBER_OF_TEMPERATURES-(i+1)]);
		data.temperatures.average += data.temperatures.values[i];
	}
	data.temperatures.average = data.temperatures.average / NUMBER_OF_TEMPERATURES;
}

/*
 * Brief:	Finding the highest and the lowest cell voltage and index of the highest one
 * Param:	None
 * Retval:	data.voltages.lowest_cell_voltage, data.voltages.highest_cell_voltage, data.voltages.highest_cell_voltage_index
 */
void min_max_voltage(){
	data.voltages.lowest_cell_voltage = data.voltages.cells[0];
	data.voltages.highest_cell_voltage = data.voltages.cells[0];
	data.voltages.highest_cell_voltage_index = 0;
	for(uint8_t i = 1; i < NUMBER_OF_CELLS; i++)
	{
		if(data.voltages.lowest_cell_voltage > data.voltages.cells[i])
		{
			data.voltages.lowest_cell_voltage = data.voltages.cells[i];
		}
		if(data.voltages.highest_cell_voltage < data.voltages.cells[i])
		{
			data.voltages.highest_cell_voltage = data.voltages.cells[i];
			data.voltages.highest_cell_voltage_index = i;
		}
	}
}

void min_max_temperature(){
	data.temperatures.lowest_temperature = data.temperatures.values[0];
	data.temperatures.highest_temperature = data.temperatures.values[0];
	for(unsigned int i = 1; i < NUMBER_OF_TEMPERATURES; i++)
	{
		if(data.temperatures.lowest_temperature > data.temperatures.values[i])
		{
			data.temperatures.lowest_temperature = data.temperatures.values[i];
		}
		if(data.temperatures.highest_temperature < data.temperatures.values[i])
		{
			data.temperatures.highest_temperature = data.temperatures.values[i];
		}
	}
}

void voltage_can_calc(){
	data.voltages.total = 0;
	//voltage calculations for CAN
	for(int i = 0; i < NUMBER_OF_CELLS; i++)
	{
		data.voltages.total += (uint32_t)data.voltages.cells[i];
		data.voltages.cells_can[i] = (uint8_t)(data.voltages.cells[i] / 1000);
	}

	data.voltages.total_can = data.voltages.total / 100;
}


/**
 * Brief:	ltc_task main function
 * Param:	None
 * Retval:	None
 */
void start_ltc_function(void *argument){
	  init_PEC15_Table();
	for(;;){

		osDelay(1);
		LTC_start_cell_adc();
		osDelay(30);

		LTC_get_values_adc(data.voltages.cells);

		min_max_voltage();

		voltage_can_calc();

		get_temperatures();

		min_max_temperature();

	}
}

