//Generated on Sat Apr 30 12:45:20 2022
#ifndef SF
#define SF

#include <cstdint>
#include "message_abstraction.hpp"

typedef struct { 
	uint16_t ok : 1; 
	uint16_t overheat : 1; 
	uint16_t undercurrent : 1; 
	uint16_t overcurrent : 1; 
	uint16_t current : 12; 
} FuseData;

enum struct SF_states: uint8_t {
	OK,
	CERROR,	// critical error
	WARNING_1,
	FUSE_0_FAILED,
	FUSE_1_FAILED,
	FUSE_2_FAILED,
	FUSE_3_FAILED,
};

struct __attribute__ ((packed)) SF_main{
	FuseData fuses_overall_state; // combined states + sum of all currenst
	SF_states device_state; // -----------------------------------------------------------------
};

struct __attribute__ ((packed)) SF_FrontBox{
	FuseData fuse_0_inverter; // state + mA read
	FuseData fuse_0_boxf_mb; // state + mA read
	FuseData fuse_0_apps; // state + mA read
	FuseData fuse_0_tsal_logic; // state + mA read
};

struct __attribute__ ((packed)) SF_CoolingAndVSafety{
	FuseData fuse_1_fan_l; // state + mA read
	FuseData fuse_1_fan_r; // state + mA read
	FuseData fuse_3_pump; // state + mA read
	FuseData fuse_2_v_safety; // state + mA read
};

struct __attribute__ ((packed)) SF_DV{
	FuseData fuse_0_box_dv; // state + mA read
	FuseData fuse_0_tsal_hv; // state + mA read
	FuseData fuse_2_wheel; // state + mA read
	FuseData fuse_1_dashboard; // state + mA read
};

struct __attribute__ ((packed)) SF_WS{
	FuseData fuse_1_ws_rl; // state + mA read
	FuseData fuse_1_ws_fl; // state + mA read
	FuseData fuse_1_ws_rr; // state + mA read
	FuseData fuse_2_ws_fr; // state + mA read
};

struct __attribute__ ((packed)) SF_NUCS{
	FuseData fuse_2_jetson; // state + mA read
	FuseData fuse_2_intel_nuc; // state + mA read
};


const uint16_t SF_MAIN_CAN_ID = 0x41;
const uint8_t SF_MAIN_CAN_DLC = sizeof(SF_main);
const uint8_t SF_MAIN_FREQUENCY = 100;
const uint16_t SF_FRONTBOX_CAN_ID = 0x46;
const uint8_t SF_FRONTBOX_CAN_DLC = sizeof(SF_FrontBox);
const uint8_t SF_FRONTBOX_FREQUENCY = 10;
const uint16_t SF_COOLINGANDVSAFETY_CAN_ID = 0x4b;
const uint8_t SF_COOLINGANDVSAFETY_CAN_DLC = sizeof(SF_CoolingAndVSafety);
const uint8_t SF_COOLINGANDVSAFETY_FREQUENCY = 10;
const uint16_t SF_DV_CAN_ID = 0x50;
const uint8_t SF_DV_CAN_DLC = sizeof(SF_DV);
const uint8_t SF_DV_FREQUENCY = 10;
const uint16_t SF_WS_CAN_ID = 0x55;
const uint8_t SF_WS_CAN_DLC = sizeof(SF_WS);
const uint8_t SF_WS_FREQUENCY = 10;
const uint16_t SF_NUCS_CAN_ID = 0x5a;
const uint8_t SF_NUCS_CAN_DLC = sizeof(SF_NUCS);
const uint8_t SF_NUCS_FREQUENCY = 10;

const CAN_TxHeaderTypeDef can_tx_header_SF_MAIN{
SF_MAIN_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, SF_MAIN_CAN_DLC, DISABLE};

const CAN_TxHeaderTypeDef can_tx_header_SF_FRONTBOX{
SF_FRONTBOX_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, SF_FRONTBOX_CAN_DLC, DISABLE};

const CAN_TxHeaderTypeDef can_tx_header_SF_COOLINGANDVSAFETY{
SF_COOLINGANDVSAFETY_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, SF_COOLINGANDVSAFETY_CAN_DLC, DISABLE};

const CAN_TxHeaderTypeDef can_tx_header_SF_DV{
SF_DV_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, SF_DV_CAN_DLC, DISABLE};

const CAN_TxHeaderTypeDef can_tx_header_SF_WS{
SF_WS_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, SF_WS_CAN_DLC, DISABLE};

const CAN_TxHeaderTypeDef can_tx_header_SF_NUCS{
SF_NUCS_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, SF_NUCS_CAN_DLC, DISABLE};

#endif

