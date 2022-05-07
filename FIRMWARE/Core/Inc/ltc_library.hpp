/*
 * ltc_library.hpp
 *
 *  Created on: May 6, 2022
 *      Author: Maks
 */
#include <main.h>

#ifndef INC_LTC_LIBRARY_HPP_
#define INC_LTC_LIBRARY_HPP_

#define MAX_SUM_VOLTAGE 255

void init_PEC15_Table();

uint16_t pec15(char *data , int len);

void LTC_wake_up();

void LTC_start_cell_adc();

void LTC_get_values_adc(uint16_t *cellValues, uint32_t *cellValuesSum, uint8_t *cellValuesSumCAN);

void mute_dis();

void unmute_dis();

void LTC_turn_on_discharge(int cell, bool *cellDischarge);

void LTC_turn_off_discharge();


#endif /* INC_LTC_LIBRARY_HPP_ */
