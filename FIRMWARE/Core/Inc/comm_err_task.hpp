/*
 * comm_err_task.hpp
 *
 *  Created on: May 22, 2022
 *      Author: Maks
 */

#ifndef INC_COMM_ERR_TASK_HPP_
#define INC_COMM_ERR_TASK_HPP_

#include "main.h"
#include "cmsis_os.h"
#include "global_variables.hpp"
#include "etl/vector.h"
#include "usbd_cdc_if.h"
#include "etl/algorithm.h"
#include "Embedded_Json/embedded_json.hpp"

#include "PUTM_EV_CAN_LIBRARY/include/can_driver.hpp"
#include "PUTM_EV_CAN_LIBRARY/database/generated/PUTM_CAN_M.h"

void error_check();

void error_execute();

void serialPrint();

extern "C" void start_comm_err_function(void *argument);

#endif /* INC_COMM_ERR_TASK_HPP_ */