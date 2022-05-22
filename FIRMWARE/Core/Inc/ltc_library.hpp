/*
 * ltc_library.hpp
 *
 *  Created on: May 22, 2022
 *      Author: Maks
 */

#ifndef INC_LTC_LIBRARY_HPP_
#define INC_LTC_LIBRARY_HPP_

#include <main.h>

void init_PEC15_Table();

uint16_t pec15(char *data , int len);

void LTC_wake_up();

void LTC_start_cell_adc();

void LTC_get_values_adc(uint16_t *cell_values);

void mute_dis();

void unmute_dis();

void LTC_turn_on_discharge(int cell, bool *cellDischarge);

void LTC_turn_off_discharge();

#endif /* INC_LTC_LIBRARY_HPP_ */
