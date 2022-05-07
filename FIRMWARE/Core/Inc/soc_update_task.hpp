/*
 * soc_update.hpp
 *
 *  Created on: May 6, 2022
 *      Author: Maks
 */

#ifndef INC_SOC_UPDATE_TASK_HPP_
#define INC_SOC_UPDATE_TASK_HPP_

#include <main.h>
#include <cmsis_os.h>

void calculate_current();

void start_soc_function(void *argument);


#endif /* INC_SOC_UPDATE_TASK_HPP_ */
