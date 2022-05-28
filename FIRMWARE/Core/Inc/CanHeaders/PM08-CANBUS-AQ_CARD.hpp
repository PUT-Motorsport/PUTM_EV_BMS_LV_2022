//Generated on Tue May 24 17:28:32 2022
#ifndef AQ
#define AQ

#include <cstdint>

namespace PUTM_CAN {

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

struct __attribute__ ((packed)) AQ_acceleration{
	int16_t acc_x; // acceleration in X axis
	int16_t acc_y; // acceleration in Y axis
	int16_t acc_z; // acceleration in Z axis
};

struct __attribute__ ((packed)) AQ_gyroscope{
	int16_t speed_x; // rotary speed x
	int16_t speed_y; // rotary speed y
	int16_t speed_z; // rotary speed z
};


const uint16_t AQ_MAIN_CAN_ID = 0x5f;
const uint8_t AQ_MAIN_CAN_DLC = sizeof(AQ_main);
const uint8_t AQ_MAIN_FREQUENCY = 100;
const uint16_t AQ_ACCELERATION_CAN_ID = 0x82;
const uint8_t AQ_ACCELERATION_CAN_DLC = sizeof(AQ_acceleration);
const uint8_t AQ_ACCELERATION_FREQUENCY = 100;
const uint16_t AQ_GYROSCOPE_CAN_ID = 0x87;
const uint8_t AQ_GYROSCOPE_CAN_DLC = sizeof(AQ_gyroscope);
const uint8_t AQ_GYROSCOPE_FREQUENCY = 100;

const CAN_TxHeaderTypeDef can_tx_header_AQ_MAIN{
AQ_MAIN_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, AQ_MAIN_CAN_DLC, DISABLE};

const CAN_TxHeaderTypeDef can_tx_header_AQ_ACCELERATION{
AQ_ACCELERATION_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, AQ_ACCELERATION_CAN_DLC, DISABLE};

const CAN_TxHeaderTypeDef can_tx_header_AQ_GYROSCOPE{
AQ_GYROSCOPE_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, AQ_GYROSCOPE_CAN_DLC, DISABLE};

} //namespace can

#endif

