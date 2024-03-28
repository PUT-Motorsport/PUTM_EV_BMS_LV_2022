//Generated on Wed Jun 15 10:27:29 2022
#ifndef BMS_LV
#define BMS_LV

#include <cstdint>

namespace PUTM_CAN {

enum struct BMS_LV_states: uint8_t {
	Normal,
	Charging,	// warning
	Unbalanced,	// warning
	Temp_warning,	// warning
	Voltage_low,	// shut down
	Voltage_high,	// shut down
	Temp_high,	// shut down
	Current_high,	// shut down
	Sleep,	// shut down
};

struct __attribute__ ((packed)) BMS_LV_main{
	uint16_t voltage_sum; // eg 2500 means 25.00V
	uint8_t soc; // state of charge
	uint8_t temp_avg; // in Celsius
	uint8_t current; 
	BMS_LV_states device_state; 
};

struct __attribute__ ((packed)) BMS_LV_temperature{
	uint8_t temp_1; // in Celsius
	uint8_t temp_2; // in Celsius
	uint8_t temp_3; // in Celsius
	uint8_t temp_4; // in Celsius
	uint8_t temp_5; // in Celsius
	uint8_t temp_6; // in Celsius
	uint8_t temp_7; // in Celsius
	uint8_t temp_8; // in Celsius
};


const uint16_t BMS_LV_MAIN_CAN_ID = 0xf;
const uint8_t BMS_LV_MAIN_CAN_DLC = sizeof(BMS_LV_main);
const uint8_t BMS_LV_MAIN_FREQUENCY = 100;
const uint16_t BMS_LV_TEMPERATURE_CAN_ID = 0x14;
const uint8_t BMS_LV_TEMPERATURE_CAN_DLC = sizeof(BMS_LV_temperature);
const uint8_t BMS_LV_TEMPERATURE_FREQUENCY = 1;

const CAN_TxHeaderTypeDef can_tx_header_BMS_LV_MAIN{
BMS_LV_MAIN_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, BMS_LV_MAIN_CAN_DLC, DISABLE};

const CAN_TxHeaderTypeDef can_tx_header_BMS_LV_TEMPERATURE{
BMS_LV_TEMPERATURE_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, BMS_LV_TEMPERATURE_CAN_DLC, DISABLE};

} // namespace can

#endif

