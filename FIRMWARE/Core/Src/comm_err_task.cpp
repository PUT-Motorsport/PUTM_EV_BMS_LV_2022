/*
 * comm_err_task.cpp
 *
 *  Created on: May 22, 2022
 *      Author: Maks
 */

#include <comm_err_task.hpp>

extern FDCAN_HandleTypeDef hfdcan2;

putm_ev_can::CanDriver can_m;

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
		{Error_condition::TEMPERATURE_LOST,-1,1,(float)data.temperatures.lowest_temperature,ERROR_TIME_TEMPERATURES,6},
		{Error_condition::CURRENT_HIGH,20,100,data.current.value,ERROR_TIME,7}

};



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
	// Creating a JSON object with a buffer size of 1024 bytes
	    embeddedjson::Json<1024> json;

	    // Dodawanie danych do JSON
	    json.add("time", "TODO: Add time formatting");
	    json.add("battery_state", data.acu_state);
	    json.add("stack_voltage", (float)data.voltages.total / 10'000.0f);
	    json.add("state_of_charge", data.soc.value * 100.0f);
	    json.add("output_current", data.current.value);
	    json.add("efuse_state", HAL_GPIO_ReadPin(EFUSE_GPIO_Port, EFUSE_Pin));
	    json.add("balance_status", data.charging.balance_on);
	    json.add("error_detection", data.ErrorDetection);
	    json.add("can_error", data.CanError);

	    // Adding temperatures
	    std::array<float, 8> temperatures;
	    for (int i = 0; i < NUMBER_OF_TEMPERATURES; i++) {
	        temperatures[i] = data.temperatures.values[i];
	    }
	    json.add("temperatures", temperatures);

	    // Adding tensions
	    std::array<float, NUMBER_OF_CELLS> voltages;
	    for (int i = 0; i < NUMBER_OF_CELLS; i++) {
	        voltages[i] = (float)data.voltages.cells[i] / 10'000.0f;
	    }
	    json.add("voltages", voltages);

	    // Downloading JSON as a string
	    auto [json_data, json_size] = json.get_as_c_array();

	    // Send JSON from USB
	    CDC_Transmit_FS((uint8_t*)json_data, json_size);
}

extern "C" void start_comm_err_function(void *argument){

	//default error detection enabled
	data.ErrorDetection = true;

	if(!can_m.Init(&hfdcan2))
	{
		HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, GPIO_PIN_SET);
		Error_Handler();
	}


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

		PUTM_CAN_M_bms_lv_main_t can_message_main{
			.voltage_sum = (uint16_t)data.voltages.total_can,
			.soc = (uint8_t)data.soc.value_can,
			.temp_avg = (uint8_t)data.temperatures.average,
			.current = (uint8_t)data.current.value, 
			.device_state = (uint8_t)data.acu_state
		};

		PUTM_CAN_M_bms_lv_temperature_t can_message_temp{
			.temp_1 = data.temperatures.values[0],
			.temp_2 = data.temperatures.values[1],
			.temp_3 = data.temperatures.values[2],
			.temp_4 = data.temperatures.values[3],
			.temp_5 = data.temperatures.values[4],
			.temp_6 = data.temperatures.values[5],
			.temp_7 = data.temperatures.values[6],
			.temp_8 = data.temperatures.values[7]
		};

		if(can_main_tick < HAL_GetTick())
		{
			can_m.Send(PUTM_CAN_M_BMS_LV_MAIN_FRAME_ID, can_message_main);
			can_main_tick = HAL_GetTick() + 100; //0.1s
		}

		if(can_temp_tick < HAL_GetTick())
		{
			can_m.Send(PUTM_CAN_M_BMS_LV_TEMPERATURE_FRAME_ID, can_message_temp);
			can_temp_tick = HAL_GetTick() + 200; //0.2s
		}

		if(serial_tick < HAL_GetTick())
		{
			serialPrint();
			serial_tick = HAL_GetTick() + 500; //0.5s
		}

		


		//if error check shouldn't always be on, use this code (charging wire overwrites error)
	    // if(data.ErrorDetection) //error check is on
		// {
		// 	error_check();
		// 	error_execute();
		// }
		// else //error check is off
		// {
		// 	if(HAL_GPIO_ReadPin(EFUSE_GPIO_Port, EFUSE_Pin) == GPIO_PIN_RESET)
		// 	{
		// 		HAL_GPIO_WritePin(EFUSE_GPIO_Port, EFUSE_Pin, GPIO_PIN_SET);
		// 	}
		// }

		//if error check should always be on, use this code (charging wire doesn't overwrite error)
		error_check();
		error_execute();
	}
}