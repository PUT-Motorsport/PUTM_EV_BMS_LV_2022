//Generated on Wed Jun 15 10:27:28 2022
#ifndef TS
#define TS

#include <cstdint>

namespace PUTM_CAN {

enum struct TS_states: uint8_t {
	NORMAL_OPERATION,
	Power_up,
	APPS_TIMEOUT,
	APPS_INVALID_VALUE,
	APPS_SKIP_FRAME,
	INV_TIMEOUT,
	INV_IPEAK,
};

struct __attribute__ ((packed)) TC_main{
	uint16_t vehicle_speed; // Estimated vehicele velocity [km/h * 100]
	uint16_t engine_speed; 
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

struct __attribute__ ((packed)) TC_rear_suspension{
	uint16_t adc_susp_right; 
	uint16_t adc_susp_left; 
};

struct __attribute__ ((packed)) TC_wheel_velocities{
	uint16_t left_front; 
	uint16_t right_front; 
	uint16_t left_rear; 
	uint16_t right_rear; 
};

struct __attribute__ ((packed)) TC_temperatures{
	uint8_t inverter; 
	uint8_t engine; 
	uint8_t water_temp_in; // Water temperature at the radiator input [deg C]
	uint8_t water_pressure_in; // Water pressure at the radiator input [kPa]
	uint8_t water_temp_out; // Water temperature at the radiator output [deg C]
	uint8_t water_pressure_out; // Water pressure at the radiator output [kPa]
};

struct __attribute__ ((packed)) TC_imu_gyro{
	int16_t gyro_x; 
	int16_t gyro_y; 
	int16_t gyro_z; 
};

struct __attribute__ ((packed)) TC_imu_acc{
	int16_t acc_x; 
	int16_t acc_y; 
	int16_t acc_z; // 
};


const uint16_t TC_MAIN_CAN_ID = 0x1e;
const uint8_t TC_MAIN_CAN_DLC = sizeof(TC_main);
const uint8_t TC_MAIN_FREQUENCY = 50;
const uint16_t TC_REAR_SUSPENSION_CAN_ID = 0x23;
const uint8_t TC_REAR_SUSPENSION_CAN_DLC = sizeof(TC_rear_suspension);
const uint8_t TC_REAR_SUSPENSION_FREQUENCY = 50;
const uint16_t TC_WHEEL_VELOCITIES_CAN_ID = 0x24;
const uint8_t TC_WHEEL_VELOCITIES_CAN_DLC = sizeof(TC_wheel_velocities);
const uint8_t TC_WHEEL_VELOCITIES_FREQUENCY = 50;
const uint16_t TC_TEMPERATURES_CAN_ID = 0x25;
const uint8_t TC_TEMPERATURES_CAN_DLC = sizeof(TC_temperatures);
const uint8_t TC_TEMPERATURES_FREQUENCY = 10;
const uint16_t TC_IMU_GYRO_CAN_ID = 0x26;
const uint8_t TC_IMU_GYRO_CAN_DLC = sizeof(TC_imu_gyro);
const uint8_t TC_IMU_GYRO_FREQUENCY = 50;
const uint16_t TC_IMU_ACC_CAN_ID = 0x27;
const uint8_t TC_IMU_ACC_CAN_DLC = sizeof(TC_imu_acc);
const uint8_t TC_IMU_ACC_FREQUENCY = 50;

const CAN_TxHeaderTypeDef can_tx_header_TS_MAIN{
TC_MAIN_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, TC_MAIN_CAN_DLC, DISABLE};

const CAN_TxHeaderTypeDef can_tx_header_TS_REAR_SUSPENSION{
TC_REAR_SUSPENSION_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, TC_REAR_SUSPENSION_CAN_DLC, DISABLE};

const CAN_TxHeaderTypeDef can_tx_header_TS_WHEEL_VELOCITIES{
TC_WHEEL_VELOCITIES_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, TC_WHEEL_VELOCITIES_CAN_DLC, DISABLE};

const CAN_TxHeaderTypeDef can_tx_header_TS_TEMPERATURES{
TC_TEMPERATURES_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, TC_TEMPERATURES_CAN_DLC, DISABLE};

const CAN_TxHeaderTypeDef can_tx_header_TS_IMU_GYRO{
TC_IMU_GYRO_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, TC_IMU_GYRO_CAN_DLC, DISABLE};

const CAN_TxHeaderTypeDef can_tx_header_TS_IMU_ACC{
TC_IMU_ACC_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, TC_IMU_ACC_CAN_DLC, DISABLE};

} //namespace can

#endif

