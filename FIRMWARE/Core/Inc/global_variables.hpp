/*
 * global_variables.hpp
 *
 *  Created on: May 22, 2022
 *      Author: Maks
 */

#ifndef INC_GLOBAL_VARIABLES_HPP_
#define INC_GLOBAL_VARIABLES_HPP_

#include <main.h>
#include <soc_ekf.h>

const static int NORMAL_STATE = 0;

const static int NUMBER_OF_CELLS = 6;
const static int MAX_NUMBER_OF_TEMPERATURES = 8;
const static int NUMBER_OF_TEMPERATURES = 8;
const static int NUMBER_OF_CS_SAMPLES = 100;
const static int NEUTRAL_CURRENT_SENSOR	= 2090;

const static int CS_MAX_OUTPUT_VOLTAGE = 4500;				//4,5V
const static int RESISTOR_1 = 1000;					//voltage divider up
const static int RESISTOR_2 = 2000;					//voltage divider down
const static int CS_MVOLT_TO_AMPER = 66;


const static int VOL_DOWN_OK = 36000; 				//3.6V

const static int VOL_UP_OVERCHARGE = 42100;
const static int VOL_UP_OK = 41995; 				//4.1995V
const static int VOL_DIS = 42010; 					//4.201V
const static int VOL_UP_NEARLY_OK = 41920;			//4.192V

const static int BALANCE_VALUE = 500; 				//0.05V
const static int BALANCE_TIME = 10000;   			//10s
const static int MAX_CELLS_DISCHARGE_AT_ONCE = 2;
const static float CHARGING_CUTOFF_CURRENT = 0.3f;

const static int TIME_TO_SLEEP = 1200000; 			//20 min = 1200000 = 20*60*1000 ms
const static int ERROR_TIME	= 500;   				//500ms
const static int ERROR_TIME_TEMPERATURES = 1000;  	//1000ms

const static int BALANCE_TICKS_AFTER_BALANCE = 30; //which means time = value*100ms

struct Voltages{
	uint16_t cells[NUMBER_OF_CELLS];	//eg. 34567 means 3.4567V
	uint8_t cells_can[NUMBER_OF_CELLS];
	uint8_t highest_cell_voltage_index;
	uint32_t total;
	uint16_t total_can;
	uint16_t lowest_cell_voltage;
	uint16_t highest_cell_voltage;
};

struct Temperatures{
	uint8_t values[NUMBER_OF_TEMPERATURES];
	uint8_t lowest_temperature;
	uint8_t highest_temperature;
	uint8_t average;
	volatile uint16_t adc[MAX_NUMBER_OF_TEMPERATURES];
};

struct Current_Sensor{
	uint32_t adc[NUMBER_OF_CS_SAMPLES];
	float value;
	float value_max;
	float value_min;

};

struct State_of_Charge{

	SoC_EKF main;
	float value;
	uint8_t value_can;
};

struct Charging{
	bool cell_discharge[NUMBER_OF_CELLS];
	bool charger_plugged;
	bool charging_state;
	bool discharge_activation;
	bool balance_on;
	uint32_t discharge_tick_end;
};

struct Data{
	// FIXME
	Voltages voltages;
	Temperatures temperatures;
	Current_Sensor current;
	State_of_Charge soc;
	Charging charging;
	uint8_t acu_state;
	bool EFUSE_state;
	bool ErrorDetection;
	bool CanError;
};

extern Data data;


#endif /* INC_GLOBAL_VARIABLES_HPP_ */
