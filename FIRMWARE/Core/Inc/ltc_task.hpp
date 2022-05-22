/*
 * ltc_task.hpp
 *
 *  Created on: May 22, 2022
 *      Author: Maks
 */

#ifndef INC_LTC_TASK_HPP_
#define INC_LTC_TASK_HPP_

#include <main.h>
#include <cmsis_os.h>

float temperature_calculations(uint16_t value);

void get_temperatures();

void min_max_voltage();

void min_max_temperature();

void voltage_can_calc();

void start_ltc_function(void *argument);

#endif /* INC_LTC_TASK_HPP_ */
