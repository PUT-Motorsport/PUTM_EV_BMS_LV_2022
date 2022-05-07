/*
 * ltc_task.cpp
 *
 *  Created on: May 1, 2022
 *      Author: max
 */
#include <ltc_task.hpp>
#include <ltc_library.hpp>

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
		data.temperatures.values[i] = (uint16_t)temperature_calculations(data.temperatures.adc[i]);
		data.temperatures.average += data.temperatures.values[i];
	}
	data.temperatures.average = data.temperatures.average / 6;
}

/**
 * Brief:	ltc_task main function
 * Param:	None
 * Retval:	None
 */
void start_ltc_function(void *argument){
	for(;;){

		osDelay(1);
		LTC_start_cell_adc();
		osDelay(30);

		LTC_get_values_adc(data.voltages.cells, data.voltages.total, data.voltages.cells_can);

		get_temperatures();
	}
}
