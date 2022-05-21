//Generated on Sat Apr 30 12:45:15 2022
#ifndef BMS_HV
#define BMS_HV

#include <cstdint>
#include "message_abstraction.hpp"

enum struct BMS_HV_states: uint8_t {
	AIR_opened,	// normal
	AIR_closed,	// normal
	Precharge,	// normal
	Charger_connected,	// normal
	Unbalanced,	// warning
	Unbalanced_critical,	// shut down
	Voltage_low,	// shut down
	Voltage_high,	// shut down
	Temp_high,	// shut down
	Current_high,	// shut down
};

struct __attribute__ ((packed)) BMS_HV_main{
	int16_t voltage_sum; 
	int8_t soc; // state of charge
	int8_t temp_max; 
	int8_t temp_avg; // in Celsius
	int8_t current; 
	BMS_HV_states device_state; // 
};


const uint16_t BMS_HV_MAIN_CAN_ID = 0xa;
const uint8_t BMS_HV_MAIN_CAN_DLC = sizeof(BMS_HV_main);
const uint8_t BMS_HV_MAIN_FREQUENCY = 100;

const CAN_TxHeaderTypeDef can_tx_header_BMS_HV_MAIN{
BMS_HV_MAIN_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, BMS_HV_MAIN_CAN_DLC, DISABLE};

#endif

