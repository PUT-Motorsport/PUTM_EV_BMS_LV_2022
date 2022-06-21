/*
 * soc_update_task.cpp
 *
 *  Created on: May 22, 2022
 *      Author: Maks
 */

#include <soc_update_task.hpp>



// define detail single cell dynamic model
const float ICR18650[] = {0.05016, 115.753797, 20.957554, 0.024685, 0.013414, 5.0};
const float Li_Ion_ocv[] = {418.7120, -1685.2339, 2773.2511, -2389.3256, 1135.4684,
		-277.8532, 22.4610, 3.9510, 2.7624};
const unsigned int Li_Ion_ocv_length = sizeof(Li_Ion_ocv) / sizeof(Li_Ion_ocv[0]);
static_assert(SOC_OCV_poli_coeff_lenght == Li_Ion_ocv_length, "update define soc-ocv curve");

float max_divided_current_sensor_output_voltage = ((float)(CS_MAX_OUTPUT_VOLTAGE * RESISTOR_2) / (float)(RESISTOR_1 + RESISTOR_2)) / 1000.0;
float current_sensor_volts_to_amper = ((float)(CS_MVOLT_TO_AMPER * RESISTOR_2) / (float)(RESISTOR_1 + RESISTOR_2)) / 1000.0;
float output_current_factor = max_divided_current_sensor_output_voltage / 4096.0 * (1.0 / current_sensor_volts_to_amper);

void calculate_current()
{
	float raw_sum = 0, raw_max = INT32_MIN, raw_min = INT32_MAX, avarage_adc;
	for(int i = 0; i < NUMBER_OF_CS_SAMPLES; i++)
	{
		int16_t raw_value = data.current.adc[i];
		raw_sum += raw_value;
		if(raw_value > raw_max) raw_max = raw_value;
		if(raw_value < raw_min) raw_min = raw_value;
	}
	avarage_adc = raw_sum / NUMBER_OF_CS_SAMPLES;

	avarage_adc -= NEUTRAL_CURRENT_SENSOR;
	raw_max -= NEUTRAL_CURRENT_SENSOR;
	raw_min -= NEUTRAL_CURRENT_SENSOR;

	data.current.value = avarage_adc * output_current_factor;
	data.current.value_max = (float)raw_max * output_current_factor;
	data.current.value_min = (float)raw_min * output_current_factor;

	/*if(outputCurrent < -NEUTRAL_CURRENT_CAR)
	{
		chargingState = 1;
	}else if (outputCurrent >= 0 || HAL_GPIO_ReadPin(LED_2_GPIO_Port, LED_2_Pin) == 1){
		chargingState = 0;
	}*/

}

void start_soc_function(void *argument){
	data.soc.main.set_single_cell_equivalent_model(ICR18650);
	data.soc.main.set_single_cell_ocv_polinomial(Li_Ion_ocv, Li_Ion_ocv_length);
	data.soc.main.set_battery_configuration(1, 2);
	data.soc.main.set_time_sampling(0.03f);
	data.soc.main.set_update_matrix();
	data.soc.main.set_initial_SoC(0.5);

	osDelay(100);

	float temp_voltage = (float)data.voltages.cells[0] / 10'000.0f;
	data.soc.main.update_SoC_based_on_voltage(temp_voltage);

	for(;;){
		osDelay(30);

		calculate_current();

		float temp_voltage = (float)data.voltages.cells[0] / 10'000.0f;
		data.soc.main.update(data.current.value, temp_voltage);
		data.soc.value = data.soc.main.get_SoC();
		data.soc.value_can = (uint8_t)(data.soc.value * 100);

	}
}

