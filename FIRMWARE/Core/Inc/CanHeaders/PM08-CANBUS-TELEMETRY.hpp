//Generated on Sat Apr 30 12:45:19 2022
#ifndef TELEMETRY
#define TELEMETRY

#include <cstdint>
#include "message_abstraction.hpp"

enum struct Telemetry_states: uint8_t {
	Power_up,
	Gathering_Data,
	Transmitting,
};

struct __attribute__ ((packed)) Telemetry_Main{
	Telemetry_states device_state; // 
};


const uint16_t TELEMETRY_MAIN_CAN_ID = 0x0;
const uint8_t TELEMETRY_MAIN_CAN_DLC = sizeof(Telemetry_Main);
const uint8_t TELEMETRY_MAIN_FREQUENCY = 1;

const CAN_TxHeaderTypeDef can_tx_header_TELEMETRY_MAIN{
TELEMETRY_MAIN_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, TELEMETRY_MAIN_CAN_DLC, DISABLE};

#endif

