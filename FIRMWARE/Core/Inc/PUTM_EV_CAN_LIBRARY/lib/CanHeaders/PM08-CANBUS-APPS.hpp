//Generated on Wed Jun 15 10:27:21 2022
#ifndef APPS
#define APPS

#include <cstdint>

namespace PUTM_CAN {

enum struct Apps_states: uint8_t {
	Normal_operation,
	Power_up,
	Sensor_Implausiblity,
	Left_sensor_out_of_range_lower_bound,
	Left_sensor_out_of_range_upper_bound,
	Right_sensor_out_of_range_lower_bound,
	Right_sensor_out_of_range_upper_bound,
};

struct __attribute__ ((packed)) Apps_main{
	uint16_t pedal_position; // pedal position form 0 – 1000 where 0 means pedal not pressed
	uint8_t counter; // counts from 0-255 to ensure all frames are recived
	int8_t position_diff; // pedal position derivative in [count / second]
	Apps_states device_state; // -----------------------------------------------------------------
};


const uint16_t APPS_MAIN_CAN_ID = 0x5;
const uint8_t APPS_MAIN_CAN_DLC = sizeof(Apps_main);
const uint8_t APPS_MAIN_FREQUENCY = 100;

const CAN_TxHeaderTypeDef can_tx_header_APPS_MAIN{
APPS_MAIN_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, APPS_MAIN_CAN_DLC, DISABLE};

} //namespace can
#endif

