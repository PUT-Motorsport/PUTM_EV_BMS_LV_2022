//Generated on Sat Apr 30 12:45:21 2022
#ifndef AQ
#define AQ

#include <cstdint>
#include "message_abstraction.hpp"

enum struct AQ_states: uint8_t {
	Power_up,
	Normal_operation,
	Sensor_impossibility,
};

struct __attribute__ ((packed)) AQ_main{
	uint16_t adc_susp_right; 
	uint16_t adc_susp_left; // i brake balance
	uint8_t brake_pressure_front; // pressure of braking lquid front in %
	uint8_t brake_pressure_back; // pressure of braking lquid back in %
};


const uint16_t AQ_MAIN_CAN_ID = 0x5f;
const uint8_t AQ_MAIN_CAN_DLC = sizeof(AQ_main);
const uint8_t AQ_MAIN_FREQUENCY = 100;

const CAN_TxHeaderTypeDef can_tx_header_AQ_MAIN{
AQ_MAIN_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, AQ_MAIN_CAN_DLC, DISABLE};

#endif

