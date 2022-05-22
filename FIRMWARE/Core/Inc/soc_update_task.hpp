/*
 * soc_update_task.hpp
 *
 *  Created on: May 22, 2022
 *      Author: Maks
 */

#ifndef INC_SOC_UPDATE_TASK_HPP_
#define INC_SOC_UPDATE_TASK_HPP_

#include <main.h>
#include <cmsis_os.h>
#include <global_variables.hpp>

void calculate_current();

void start_soc_function(void *argument);

#endif /* INC_SOC_UPDATE_TASK_HPP_ */
