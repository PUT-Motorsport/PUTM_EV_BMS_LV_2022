//Generated on Sat Apr 30 12:45:18 2022
#ifndef LAP_TIMER
#define LAP_TIMER

#include <cstdint>
#include "message_abstraction.hpp"

enum struct Lap_timer_states: uint8_t {
	Power_up,
	Error,
};

struct __attribute__ ((packed)) Lap_timer_Main{
	Lap_timer_states device_state; 
};

struct __attribute__ ((packed)) Lap_timer_Pass{
	uint8_t Sector; // "0x00 - default
	Lap_timer_states device_state; // 
};


const uint16_t LAP_TIMER_MAIN_CAN_ID = 0x78;
const uint8_t LAP_TIMER_MAIN_CAN_DLC = sizeof(Lap_timer_Main);
const uint8_t LAP_TIMER_MAIN_FREQUENCY = 5;
const uint16_t LAP_TIMER_PASS_CAN_ID = 0x3c;
const uint8_t LAP_TIMER_PASS_CAN_DLC = sizeof(Lap_timer_Pass);
const uint8_t LAP_TIMER_PASS_FREQUENCY = 0;

const CAN_TxHeaderTypeDef can_tx_header_LAP_TIMER_MAIN{
LAP_TIMER_MAIN_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, LAP_TIMER_MAIN_CAN_DLC, DISABLE};

const CAN_TxHeaderTypeDef can_tx_header_LAP_TIMER_PASS{
LAP_TIMER_PASS_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, LAP_TIMER_PASS_CAN_DLC, DISABLE};

#endif

