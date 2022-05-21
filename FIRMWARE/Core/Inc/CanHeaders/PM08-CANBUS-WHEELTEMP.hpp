//Generated on Sat Apr 30 12:45:15 2022
#ifndef WHEELTEMP
#define WHEELTEMP

#include <cstdint>
#include "message_abstraction.hpp"

enum struct WheelTemp_states: uint8_t {
	Power_up,
	Normal_operation,
	Sensor_impossibility,
};

struct __attribute__ ((packed)) WheelTemp_main{
	uint8_t wheelTemp; 
	WheelTemp_states device_state; // 
};


const uint16_t WHEELTEMP_MAIN_CAN_ID = 0x69;
const uint8_t WHEELTEMP_MAIN_CAN_DLC = sizeof(WheelTemp_main);
const uint8_t WHEELTEMP_MAIN_FREQUENCY = 1;

const CAN_TxHeaderTypeDef can_tx_header_WHEELTEMP_MAIN{
WHEELTEMP_MAIN_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, WHEELTEMP_MAIN_CAN_DLC, DISABLE};

#endif

