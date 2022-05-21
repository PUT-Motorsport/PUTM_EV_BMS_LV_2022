//Generated on Wed May 11 12:18:57 2022
#ifndef DASH
#define DASH

#include <cstdint>

enum struct Dash_states: uint8_t {
	Power_up,
	Normal_operation,
	Driverless,
};

struct __attribute__ ((packed)) Dash_Main{
	Dash_states device_state; 
};

struct __attribute__ ((packed)) Dash_TCS{
	uint8_t on; // TC- ON - OFF
	uint8_t max_slip_ratio; // 0-100%
	uint8_t algorithm; // "PI (PID
	uint8_t max_power; // 0-100%
	uint8_t apps_curve; // "0 - Linear
	uint8_t regen_power; // 0-100%
	uint8_t sensivity; // 0-100% [100% - no wheel slip]
	uint8_t CRC_byte; 
};

struct __attribute__ ((packed)) Dash_Smart_Fuses_FAN_speed{
	uint8_t fan_2; // 0-100% []
	uint8_t water_pump; // on off
};

struct __attribute__ ((packed)) Dash_steering_wheel_request{
};

struct __attribute__ ((packed)) Dash_lap_finished{
	uint32_t time; // total lap time (all sectors) in microseconds
};


const uint16_t DASH_MAIN_CAN_ID = 0x64;
const uint8_t DASH_MAIN_CAN_DLC = sizeof(Dash_Main);
const uint8_t DASH_MAIN_FREQUENCY = 10;
const uint16_t DASH_TCS_CAN_ID = 0x19;
const uint8_t DASH_TCS_CAN_DLC = sizeof(Dash_TCS);
const uint8_t DASH_TCS_FREQUENCY = 0;
const uint16_t DASH_SMART_FUSES_FAN_SPEED_CAN_ID = 0x32;
const uint8_t DASH_SMART_FUSES_FAN_SPEED_CAN_DLC = sizeof(Dash_Smart_Fuses_FAN_speed);
const uint8_t DASH_SMART_FUSES_FAN_SPEED_FREQUENCY = 0;
const uint16_t DASH_STEERING_WHEEL_REQUEST_CAN_ID = 0x37;
const uint8_t DASH_STEERING_WHEEL_REQUEST_CAN_DLC = sizeof(Dash_steering_wheel_request);
const uint8_t DASH_STEERING_WHEEL_REQUEST_FREQUENCY = 0;
const uint16_t DASH_LAP_FINISHED_CAN_ID = 0x7d;
const uint8_t DASH_LAP_FINISHED_CAN_DLC = sizeof(Dash_lap_finished);
const uint8_t DASH_LAP_FINISHED_FREQUENCY = 0;

const CAN_TxHeaderTypeDef can_tx_header_DASH_MAIN{
DASH_MAIN_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, DASH_MAIN_CAN_DLC, DISABLE};

const CAN_TxHeaderTypeDef can_tx_header_DASH_TCS{
DASH_TCS_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, DASH_TCS_CAN_DLC, DISABLE};

const CAN_TxHeaderTypeDef can_tx_header_DASH_SMART_FUSES_FAN_SPEED{
DASH_SMART_FUSES_FAN_SPEED_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, DASH_SMART_FUSES_FAN_SPEED_CAN_DLC, DISABLE};

const CAN_TxHeaderTypeDef can_tx_header_DASH_STEERING_WHEEL_REQUEST{
DASH_STEERING_WHEEL_REQUEST_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, DASH_STEERING_WHEEL_REQUEST_CAN_DLC, DISABLE};

const CAN_TxHeaderTypeDef can_tx_header_DASH_LAP_FINISHED{
DASH_LAP_FINISHED_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, DASH_LAP_FINISHED_CAN_DLC, DISABLE};

#endif
