//Generated on Sat Apr 30 12:45:23 2022
#ifndef TS
#define TS

#include <cstdint>
#include "message_abstraction.hpp"

enum struct TS_states: uint8_t {
	NORMAL_OPERATION,
	Power_up,
	APPS_TIMEOUT,
	APPS_INVALID_VALUE,
	APPS_SKIP_FRAME,
	INV_TIMEOUT,
	INV_IPEAK,
};

struct __attribute__ ((packed)) TS_main{
	uint16_t vehicle_speed; // Estimated vehicele velocity [km/h * 100]
	uint8_t water_temp; // Water temperature at the radiator input [deg C]
	uint8_t water_pressure; // Water pressure at the radiator input [kPa]
	int8_t motor_current; // positive for normal operation negative for regen [A]
	bool tractive_system_on : 1; // Car is in ready to race state
	bool rtds_active : 1; // Rtds is making sound
	bool brake_light_active : 1; 
	bool traction_control_enable : 1; 
	bool  regen_enable : 1; // There is posible to produce negative torque
	bool regen_active : 1; 
	uint8_t traction_control_intensivity; // how much TC is limiting torque [%]
	TS_states device_state; // -------------------------
};

struct __attribute__ ((packed)) TS_rear_suspension{
	uint16_t adc_susp_right; 
	uint16_t adc_susp_left; 
	int16_t acc_lateral; 
	int16_t acc_longitunal; // 
};


const uint16_t TS_MAIN_CAN_ID = 0x1e;
const uint8_t TS_MAIN_CAN_DLC = sizeof(TS_main);
const uint8_t TS_MAIN_FREQUENCY = 50;
const uint16_t TS_REAR_SUSPENSION_CAN_ID = 0x23;
const uint8_t TS_REAR_SUSPENSION_CAN_DLC = sizeof(TS_rear_suspension);
const uint8_t TS_REAR_SUSPENSION_FREQUENCY = 50;

const CAN_TxHeaderTypeDef can_tx_header_TS_MAIN{
TS_MAIN_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, TS_MAIN_CAN_DLC, DISABLE};

const CAN_TxHeaderTypeDef can_tx_header_TS_REAR_SUSPENSION{
TS_REAR_SUSPENSION_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, TS_REAR_SUSPENSION_CAN_DLC, DISABLE};

#endif

