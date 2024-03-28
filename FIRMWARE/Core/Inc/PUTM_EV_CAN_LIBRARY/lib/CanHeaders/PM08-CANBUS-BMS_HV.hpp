//Generated on Wed Jun 15 10:27:26 2022
#ifndef BMS_HV
#define BMS_HV

#include <cstdint>

namespace PUTM_CAN {

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
	uint16_t voltage_sum; 
	int16_t current; 
	uint8_t temp_max; 
	uint8_t temp_avg; // in Celsius
	uint16_t soc : 10; // state of charge
	BMS_HV_states device_state : 6; // 
};


const uint16_t BMS_HV_MAIN_CAN_ID = 0xa;
const uint8_t BMS_HV_MAIN_CAN_DLC = sizeof(BMS_HV_main);
const uint8_t BMS_HV_MAIN_FREQUENCY = 100;

const CAN_TxHeaderTypeDef can_tx_header_BMS_HV_MAIN{
BMS_HV_MAIN_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, BMS_HV_MAIN_CAN_DLC, DISABLE};

} // namespace can

#endif

