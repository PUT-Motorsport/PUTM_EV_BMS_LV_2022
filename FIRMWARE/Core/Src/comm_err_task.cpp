/*
 * comm_err_task.cpp
 *
 *  Created on: May 22, 2022
 *      Author: Maks
 */

#include <comm_err_task.hpp>

uint32_t serial_tick = 0;
uint32_t can_main_tick = 0;
uint32_t can_temp_tick = 0;

enum struct Error_condition{
	UNBALANCE,
	VOLTAGE_LOW,
	VOLTAGE_HIGH,
	TEMPERATURE_WARNING,
	TEMPERATURE_HIGH,
	TEMPERATURE_LOST,
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


Error_and_connditions error_conditions[8] = {
		{Error_condition::NEUTRAL_CURRENT_CAR,-0.3,0.3,data.current.value,TIME_TO_SLEEP,0}, //to check //acu_state 0 or 8?
		{Error_condition::UNBALANCE,2000,50000,(float)(data.voltages.highest_cell_voltage-data.voltages.lowest_cell_voltage),ERROR_TIME,2},
		{Error_condition::TEMPERATURE_WARNING,48,55,(float)data.temperatures.highest_temperature,ERROR_TIME_TEMPERATURES,3},
		{Error_condition::VOLTAGE_LOW,0,30000,(float)data.voltages.lowest_cell_voltage,ERROR_TIME,4},
		{Error_condition::VOLTAGE_HIGH,42200,500000,(float)data.voltages.highest_cell_voltage,ERROR_TIME,5},
		{Error_condition::TEMPERATURE_HIGH,55,120,(float)data.temperatures.highest_temperature,ERROR_TIME_TEMPERATURES,6},
		{Error_condition::TEMPERATURE_LOST,-1,1,data.temperatures.lowest_temperature,ERROR_TIME_TEMPERATURES,6},
		{Error_condition::CURRENT_HIGH,20,100,data.current.value,ERROR_TIME,7}

};

void can_init()
{
	CAN_FilterTypeDef filter;
	filter.FilterActivation = ENABLE;
	filter.FilterBank = 10;
	filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	filter.FilterIdHigh = 0x00;
	filter.FilterIdLow = 0x00;
	filter.FilterMaskIdHigh = 0x00;
	filter.FilterMaskIdLow = 0x00;
	filter.FilterMode = CAN_FILTERMODE_IDMASK;
	filter.FilterScale = CAN_FILTERSCALE_32BIT;
	filter.SlaveStartFilterBank = 10;

	HAL_CAN_ConfigFilter(&hcan1, &filter);
	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
	HAL_CAN_Start(&hcan1);

}

// error if value is in range <min, max>
void error_check(){
	etl::vector<Error_condition, 8> errors_vector;

	for(auto& error : error_conditions){
		if(error.min <= error.value && error.value <= error.max){
			errors_vector.emplace_back(error.error);
			data.acu_state=error.acu_state_code;
			if(false == error.flag)
			{
				error.timer = HAL_GetTick() + error.error_time;
				error.flag = true;
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
}

void error_execute(){
	uint32_t time = HAL_GetTick();
//	if(error_conditions[0].timer <= HAL_GetTick()) //shut down and sleep
//	{
//		HAL_GPIO_WritePin(EFUSE_GPIO_Port, EFUSE_Pin, GPIO_PIN_RESET);
//		HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
//	}
	for(unsigned int i = 3; i < 8; i++){
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

	data.EFUSE_state = HAL_GPIO_ReadPin(EFUSE_GPIO_Port, EFUSE_Pin);
}

void serialPrint()
{
	// FIXME count chars
	// or use {fmt}
	static char tab[1000];
	uint16_t n=0;

	RTC_DateTypeDef rtc_date;
	RTC_TimeTypeDef rtc_time;
	HAL_RTC_GetTime(&hrtc, &rtc_time, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &rtc_date, RTC_FORMAT_BIN);

	float cell_values_sum = (float)data.voltages.total / 10'000.0;
	n += sprintf(&tab[n], "%02d:%02d:%02d\r\n", rtc_time.Hours, rtc_time.Minutes, rtc_time.Seconds);
	n += sprintf(&tab[n], "*** Battery state: %d ***", data.acu_state);
	n += sprintf(&tab[n], "\r\n");
	n += sprintf(&tab[n], "LEGEND FOR BATTERY STATE:");
	n += sprintf(&tab[n], "\r\n");
	n += sprintf(&tab[n], "0- all good");
	n += sprintf(&tab[n], "\r\n");
	n += sprintf(&tab[n], "1- charging");
	n += sprintf(&tab[n], "\r\n");
	n += sprintf(&tab[n], "2- unbalanced(difference from lowest to highest >0.2V)");
	n += sprintf(&tab[n], "\r\n");
	n += sprintf(&tab[n], "3- highest temperature is more than 48C");
	n += sprintf(&tab[n], "\r\n");
	n += sprintf(&tab[n], "4- too low voltage");
	n += sprintf(&tab[n], "\r\n");
	n += sprintf(&tab[n], "5- too high voltage");
	n += sprintf(&tab[n], "\r\n");
	n += sprintf(&tab[n], "6- too high temperature");
	n += sprintf(&tab[n], "\r\n");
	n += sprintf(&tab[n], "7- too high current");
	n += sprintf(&tab[n], "\r\n");
	n += sprintf(&tab[n], "8- sleep mode");
	n += sprintf(&tab[n], "\r\n\n");
	n += sprintf(&tab[n], "*** Stack voltage:\t%3.2f V ***", cell_values_sum);
	n += sprintf(&tab[n], "\r\n");
	n += sprintf(&tab[n], "*** State of charge: %f ***", data.soc.value * 100);
	n += sprintf(&tab[n], "\r\n");

	for(int i = 0; i < NUMBER_OF_TEMPERATURES; i++)
	{
		n += sprintf(&tab[n], " -T.%d-\t", i);
		n += sprintf(&tab[n], "%d\t", data.temperatures.values[i]);
		if(i< NUMBER_OF_CELLS)
		{
			float cell_value = (float)data.voltages.cells[i] / 10'000.0;
			n += sprintf(&tab[n], "-V.%d-\t", i);
			n += sprintf(&tab[n], "%1.3f%c\t", cell_value, data.charging.cell_discharge[i] == 0 ? ' ' : '*');
		}
		n += sprintf(&tab[n], "\r\n");
	}

	n += sprintf(&tab[n], "\r\n");
	n += sprintf(&tab[n], "Output current:\t%3.2f\r\n", data.current.value);
	n += sprintf(&tab[n], "\r\n");

	n += sprintf(&tab[n], "EFUSE state:\t%d\r\n", HAL_GPIO_ReadPin(EFUSE_GPIO_Port, EFUSE_Pin));
	n += sprintf(&tab[n], "\r\n");

	CDC_Transmit_FS((uint8_t*)tab, n);
}

void start_comm_err_function(void *argument){

	//default error detection enabled
	data.ErrorDetection = true;

	can_init();
	for(;;){
		osDelay(20);

		error_conditions[0].value = data.current.value;
		error_conditions[1].value = (float)(data.voltages.highest_cell_voltage-data.voltages.lowest_cell_voltage);
		error_conditions[2].value = (float)data.temperatures.highest_temperature;
		error_conditions[3].value = (float)data.voltages.lowest_cell_voltage;
		error_conditions[4].value = (float)data.voltages.highest_cell_voltage;
		error_conditions[5].value = (float)data.temperatures.highest_temperature;
		error_conditions[6].value = data.temperatures.lowest_temperature;
		error_conditions[7].value = data.current.value;

		PUTM_CAN::BMS_LV_main can_message_main{
			.voltage_sum{data.voltages.total_can},
			.soc{data.soc.value_can},
			.temp_avg{data.temperatures.average},
			.current{(uint8_t)data.current.value},
			.device_state{static_cast<PUTM_CAN::BMS_LV_states>(data.acu_state)}
		};

		PUTM_CAN::BMS_LV_temperature can_message_temp{
			data.temperatures.values[0],
			data.temperatures.values[1],
			data.temperatures.values[2],
			data.temperatures.values[3],
			data.temperatures.values[4],
			data.temperatures.values[5],
			data.temperatures.values[6],
			data.temperatures.values[7]
		};

		if(serial_tick < HAL_GetTick())
		{
			serialPrint();
			serial_tick = HAL_GetTick() + 500; //0.5s
		}

		auto can_message_main_frame = PUTM_CAN::Can_tx_message<PUTM_CAN::BMS_LV_main>(can_message_main, PUTM_CAN::can_tx_header_BMS_LV_MAIN);
		auto can_message_temp_frame = PUTM_CAN::Can_tx_message<PUTM_CAN::BMS_LV_temperature>(can_message_temp, PUTM_CAN::can_tx_header_BMS_LV_TEMPERATURE);

		if(can_main_tick < HAL_GetTick())
		{
			auto status_main = can_message_main_frame.send(hcan1);
			can_main_tick = HAL_GetTick() + 40; //0.04s
		}

		if(can_temp_tick < HAL_GetTick())
		{
			auto status_temp = can_message_temp_frame.send(hcan1);
			can_temp_tick = HAL_GetTick() + 200; //0.2s
		}

		//if error check shouldn't always be on, use this code (charging wire overwrites error)
	    if(data.ErrorDetection) //error check is on
		{
			error_check();
			error_execute();
		}
		else //error check is off
		{
			if(HAL_GPIO_ReadPin(EFUSE_GPIO_Port, EFUSE_Pin) == GPIO_PIN_RESET)
			{
				HAL_GPIO_WritePin(EFUSE_GPIO_Port, EFUSE_Pin, GPIO_PIN_SET);
			}
		}

		//if error check should always be on, use this code (charging wire doesn't overwrite error)
		error_check();
		error_execute();
	}
}


