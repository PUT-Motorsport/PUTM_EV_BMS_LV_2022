/*
 * ltc_task.hpp
 *
 *  Created on: May 1, 2022
 *      Author: max
 */

#ifndef INC_LTC_TASK_HPP_
#define INC_LTC_TASK_HPP_

#include <main.h>
#include <cmsis_os.h>

float temperature_calculations(uint16_t value);

void get_temperatures();

void start_ltc_function(void *argument);



#endif /* INC_LTC_TASK_HPP_ */
