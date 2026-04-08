/*
 * balance_task.hpp
 *
 *  Created on: May 22, 2022
 *      Author: Maks
 */

#ifndef INC_BALANCE_TASK_HPP_
#define INC_BALANCE_TASK_HPP_

#include <main.h>
#include <cmsis_os.h>
#include <ltc_library.hpp>
#include <global_variables.hpp>

int discharge_cells_tail(int i);

void set_discharge_cell(uint8_t &discharge_at_once, int &i);

void set_discharge_cell_max(uint8_t &discharge_at_once, int &i, bool &max_voltage_discharge_activation);

void balance_control();

void balance_activation_deactivation();

void start_balance_function(void *argument);

#endif /* INC_BALANCE_TASK_HPP_ */
