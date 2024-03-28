//Generated on Wed Jun 15 10:27:28 2022
#ifndef YAWPROBE
#define YAWPROBE

#include <cstdint>

namespace PUTM_CAN {

enum struct YawProbe_states: uint8_t {
	Power_up,
	Normal_operation,
	Sensor_impossibility,
};

struct __attribute__ ((packed)) YawProbe_air_flow{
	uint16_t air_flow_velocity; // rotation wheel speed rpm
	YawProbe_states device_state; // 
};


const uint16_t YAWPROBE_AIR_FLOW_CAN_ID = 0x6e;
const uint8_t YAWPROBE_AIR_FLOW_CAN_DLC = sizeof(YawProbe_air_flow);
const uint8_t YAWPROBE_AIR_FLOW_FREQUENCY = 1;

const CAN_TxHeaderTypeDef can_tx_header_YAWPROBE_AIR_FLOW{
YAWPROBE_AIR_FLOW_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, YAWPROBE_AIR_FLOW_CAN_DLC, DISABLE};

} //namespace can

#endif

