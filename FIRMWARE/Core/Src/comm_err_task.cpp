/*
 * comm_err_task.cpp
 *
 *  Created on: May 22, 2022
 *      Author: Maks
 */

#include <comm_err_task.hpp>



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
	const uint8_t acu_state_code;
	uint32_t timer;
	bool flag = false;
};



Error_and_connditions error_conditions[7] = {
		{Error_condition::NEUTRAL_CURRENT_CAR,0,0.3,data.current.value,1200000,8}, //to check //acu_state 0 or 8?
		{Error_condition::UNBALANCE,2000,50000,(float)(data.voltages.highest_cell_voltage-data.voltages.lowest_cell_voltage),500,2},
		{Error_condition::TEMPERATURE_WARNING,48,55,(float)data.temperatures.highest_temperature,1000,3},
		{Error_condition::VOLTAGE_LOW,0,30000,(float)data.voltages.lowest_cell_voltage,500,4},
		{Error_condition::VOLTAGE_HIGH,42200,500000,(float)data.voltages.highest_cell_voltage,500,5},
		{Error_condition::TEMPERATURE_HIGH,55,120,(float)data.temperatures.highest_temperature,500,6},
		{Error_condition::CURRENT_HIGH,20,100,data.current.value,500,7}

};


// error if value is in range <min, max>
void error_check(){
	etl::vector<Error_condition, 7> errors_vector;

	for(auto& error : error_conditions){
		if(error.min <= error.value && error.value <= error.max){

			if(false == error.flag)
			{
				errors_vector.emplace_back(error.error);
				error.timer = HAL_GetTick() + error.error_time;
				error.flag = true;
				data.acu_state=error.acu_state_code;
			}
		}
		else{
			error.timer = HAL_GetTick() + error.error_time;
			error.flag = false;
		}
	}

	if(errors_vector.empty())
	{
		data.acu_state = NORMAL_STATE;
	}

	/*for (auto error : errors_vector){
		// do sth
	}*/
}

void error_execute(){
	if(error_conditions[0].timer <= HAL_GetTick()) //shut down and sleep
	{
		HAL_GPIO_WritePin(EFUSE_GPIO_Port, EFUSE_Pin, GPIO_PIN_RESET);
		HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
	}
	for(unsigned int i = 3; i < 7; i++){
		{
			if(error_conditions[i].timer <= HAL_GetTick()) //shut down
			{

				HAL_GPIO_WritePin(EFUSE_GPIO_Port, EFUSE_Pin, GPIO_PIN_RESET);

				/*char tab[1];
				uint32_t n=1;
				//wait for key through USB
				auto status = CDC_Receive_FS((uint8_t*)tab,n);
				if(USBD_OK == status){
					break;
				}*/
			}
		}
	}
}

void serialPrint()
{
	static char tab[3500];
	uint16_t n=0;

	RTC_DateTypeDef rtc_date;
	RTC_TimeTypeDef rtc_time;
	HAL_RTC_GetTime(&hrtc, &rtc_time, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &rtc_date, RTC_FORMAT_BIN);

	float cell_values_sum = (float)data.voltages.total / 10000;
	n += sprintf(&tab[n], "%02d:%02d:%02d\r\n", rtc_time.Hours, rtc_time.Minutes, rtc_time.Seconds);
	n += sprintf(&tab[n], "*** Battery state: %d ***", data.acu_state);
	n += sprintf(&tab[n], "\n");
	n += sprintf(&tab[n], "LEGEND FOR BATTERY STATE:");
	n += sprintf(&tab[n], "\n");
	n += sprintf(&tab[n], "0- all good");
	n += sprintf(&tab[n], "\n");
	n += sprintf(&tab[n], "1- charging");
	n += sprintf(&tab[n], "\n");
	n += sprintf(&tab[n], "2- unbalanced(difference from lowest to highest >0.2V)");
	n += sprintf(&tab[n], "\n");
	n += sprintf(&tab[n], "3- highest temperature is more than 48C");
	n += sprintf(&tab[n], "\n");
	n += sprintf(&tab[n], "4- too low voltage");
	n += sprintf(&tab[n], "\n");
	n += sprintf(&tab[n], "5- too high voltage");
	n += sprintf(&tab[n], "\n");
	n += sprintf(&tab[n], "6- too high temperature");
	n += sprintf(&tab[n], "\n");
	n += sprintf(&tab[n], "7- too high current");
	n += sprintf(&tab[n], "\n");
	n += sprintf(&tab[n], "8- sleep mode");
	n += sprintf(&tab[n], "\r\n\n");
	n += sprintf(&tab[n], "*** Stack voltage:\t%3.2f V ***", cell_values_sum);
	n += sprintf(&tab[n], "\n");
	n += sprintf(&tab[n], "*** State of charge: %f ***", data.soc.value * 100);
	n += sprintf(&tab[n], "\r\n");

	for(int i = 0; i < NUMBER_OF_CELLS; i++)
	{
		float cell_value = (float)data.voltages.cells[i] / 10000;
		n += sprintf(&tab[n], "-V.%d-\t", i+1);
		n += sprintf(&tab[n], "%1.3f%c\t", cell_value, data.charging.cell_discharge[i] == 0 ? ' ' : '*');
		n += sprintf(&tab[n], " -T.%d-\t", i+1);
		if(i != 5)
		n += sprintf(&tab[n], "%d\t", data.temperatures.values[i]);
		n += sprintf(&tab[n], "\r\n");
	}

	n += sprintf(&tab[n], "\r\n");
	n += sprintf(&tab[n], "Output current:\t%3.2f\r\n", data.current.value);
	//n += sprintf(&tab[n], "Max current:\t%3.2f\r\n", data.current.value_max);
	//n += sprintf(&tab[n], "Min current:\t%3.2f\r\n", data.current.value_min);
	n += sprintf(&tab[n], "\r\n");

	n += sprintf(&tab[n], "EFUSE state:\t%d\r\n", HAL_GPIO_ReadPin(EFUSE_GPIO_Port, EFUSE_Pin));
	n += sprintf(&tab[n], "\r\n");

	CDC_Transmit_FS((uint8_t*)tab, n);
}

void start_comm_err_function(void *argument){

	for(;;){
		osDelay(20);

		BMS_LV_main can_message_main{
			data.voltages.total_can,
			data.soc.value_can,
			data.temperatures.average,
			(uint8_t)data.current.value,
			static_cast<BMS_LV_states>(data.acu_state)
		};

		BMS_LV_temperature can_message_temp{
			data.temperatures.values[0],
			data.temperatures.values[1],
			data.temperatures.values[2],
			data.temperatures.values[3],
			data.temperatures.values[4],
			0,//data.temperatures.values[5],
			0,//data.temperatures.values[6],
			0//data.temperatures.values[7]
		};

		//serialPrint();

		auto can_message_main_frame = PUTM_CAN::Can_tx_message<BMS_LV_main>(can_message_main, can_tx_header_BMS_LV_MAIN);
		auto can_message_temp_frame = PUTM_CAN::Can_tx_message<BMS_LV_temperature>(can_message_temp, can_tx_header_BMS_LV_TEMPERATURE);

		auto status_main = can_message_main_frame.send(hcan1);
		auto status_temp = can_message_temp_frame.send(hcan1);

		error_check();

		error_execute();
	}
}


