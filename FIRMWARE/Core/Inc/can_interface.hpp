#ifndef CAN_INTERFACE_HPP
#define CAN_INTERFACE_HPP

#include <array>
#include <cstdint>
#include <stdio.h>
#include <variant>

#ifdef UNIT_TESTS
#include "../hal_can.hpp"
#else
#include "main.h"
#endif

#include "message_abstraction.hpp"

// CanHeaders
#include "CanHeaders/PM08-CANBUS-APPS.hpp"
#include "CanHeaders/PM08-CANBUS-AQ_CARD.hpp"
#include "CanHeaders/PM08-CANBUS-BMS_HV.hpp"
#include "CanHeaders/PM08-CANBUS-BMS_LV.hpp"
#include "CanHeaders/PM08-CANBUS-DASH.hpp"
#include "CanHeaders/PM08-CANBUS-LAP_TIMER.hpp"
#include "CanHeaders/PM08-CANBUS-SF.hpp"
#include "CanHeaders/PM08-CANBUS-STEERING_WHEEL.hpp"
#include "CanHeaders/PM08-CANBUS-TC.hpp"
#include "CanHeaders/PM08-CANBUS-TELEMETRY.hpp"
#include "CanHeaders/PM08-CANBUS-WHEELTEMP.hpp"
#include "CanHeaders/PM08-CANBUS-YAWPROBE.hpp"

namespace PUTM_CAN {

class Can_interface {

  Device<Apps_main> apps{APPS_MAIN_CAN_ID};
  Device<AQ_main> aq_main{AQ_MAIN_CAN_ID};
  Device<AQ_acceleration> aq_acceleration{AQ_ACCELERATION_CAN_ID};
  Device<AQ_gyroscope> aq_gyroscope{AQ_GYROSCOPE_CAN_ID};
  Device<BMS_HV_main> bms_hv_main{BMS_HV_MAIN_CAN_ID};
  Device<BMS_LV_main> bms_lv_main{BMS_LV_MAIN_CAN_ID};
  Device<BMS_LV_temperature> bms_lv_temperature{BMS_LV_TEMPERATURE_CAN_ID};
  Device<Dash_Main> dash_main{DASH_MAIN_CAN_ID};
  Device<Dash_TCS> dash_TCS{DASH_TCS_CAN_ID};
  Device<Dash_Smart_Fuses_FAN_speed> dash_fan_speed{
      DASH_SMART_FUSES_FAN_SPEED_CAN_ID};
  Device<Dash_steering_wheel_request> dash_steering_request{DASH_STEERING_WHEEL_REQUEST_CAN_ID};
  Device<Dash_lap_finished> dash_lap_finished{DASH_LAP_FINISHED_CAN_ID};
  Device<Lap_timer_Main> laptimer_main{LAP_TIMER_MAIN_CAN_ID};
  Device<Lap_timer_Pass> laptimer_pass{LAP_TIMER_PASS_CAN_ID};
  Device<SF_main> sf_main{SF_MAIN_CAN_ID};
  Device<SF_FrontBox> sf_frontbox{SF_FRONTBOX_CAN_ID};
  Device<SF_CoolingAndVSafety> sf_coolingandvsafety{
      SF_COOLINGANDVSAFETY_CAN_ID};
  Device<SF_DV> sf_dv{SF_DV_CAN_ID};
  Device<SF_WS> sf_ws{SF_WS_CAN_ID};
  Device<SF_NUCS> sf_nucs{SF_NUCS_CAN_ID};
  Device<Steering_Wheel_main> steering_wheel_main{STEERING_WHEEL_MAIN_CAN_ID};
  Device<Steering_Wheel_event> steering_wheel_event{
      STEERING_WHEEL_EVENT_CAN_ID};
  Device<TC_main> tc_main{TC_MAIN_CAN_ID};
  Device<TC_rear_suspension> tc_rear_suspension{TC_REAR_SUSPENSION_CAN_ID};
  Device<TC_wheel_velocities> tc_wheel_velocities{TC_WHEEL_VELOCITIES_CAN_ID};
  Device<TC_temperatures> tc_temperatures{TC_TEMPERATURES_CAN_ID}; 
  Device<TC_imu_acc> tc_imu_acc{TC_IMU_ACC_CAN_ID};
  Device<TC_imu_gyro> tc_imu_gyro{TC_IMU_GYRO_CAN_ID};
  Device<Telemetry_Main> telemetry_main{TELEMETRY_MAIN_CAN_ID};
  Device<WheelTemp_main> wheel_temp_main{WHEELTEMP_MAIN_CAN_ID};
  Device<YawProbe_air_flow> yawprobe_air_flow{YAWPROBE_AIR_FLOW_CAN_ID};


  std::array<Device_base *, 31> device_array = {&apps,
                                                &aq_main,
                                                &aq_gyroscope,
                                                &aq_acceleration,
                                                &bms_hv_main,
                                                &bms_lv_main,
                                                &bms_lv_temperature,
                                                &dash_main,
                                                &dash_TCS,
                                                &dash_fan_speed,
                                                &dash_steering_request,
                                                &dash_lap_finished,
                                                &laptimer_main,
                                                &laptimer_pass,
                                                &sf_main,
                                                &sf_frontbox,
                                                &sf_coolingandvsafety,
                                                &sf_dv,
                                                &sf_ws,
                                                &sf_nucs,
                                                &steering_wheel_main,
                                                &steering_wheel_event,
                                                &tc_main,
                                                &tc_rear_suspension,
                                                &tc_wheel_velocities,
                                                &tc_temperatures,
                                                &tc_imu_acc,
                                                &tc_imu_gyro,
                                                &telemetry_main,
                                                &yawprobe_air_flow,
                                                &wheel_temp_main};

public:
  Can_interface() = default;

  bool parse_message(const Can_rx_message &m) {
    for (auto &device : device_array) {
      if (device->get_ID() == m.header.StdId) {
        device->set_data(m);
        return true;
      }
    }
    return false;
  }

  Apps_main get_apps_main() { return apps.data; }
  AQ_main get_aq_main() { return aq_main.data; }
  AQ_acceleration get_aq_acceleration() { return aq_acceleration.data; }
  AQ_gyroscope get_aq_gyroscope() { return aq_gyroscope.data; }
  BMS_HV_main get_bms_hv_main() { return bms_hv_main.data; }
  BMS_LV_main get_bms_lv_main() { return bms_lv_main.data; }
  BMS_LV_temperature get_bms_lv_temperature() {
    return bms_lv_temperature.data;
  }
  Dash_Main get_dash_main() { return dash_main.data; }
  Dash_TCS get_dash_TCS() { return dash_TCS.data; }
  Dash_Smart_Fuses_FAN_speed get_dash_fan_speed() {
    return dash_fan_speed.data;
  }
  Dash_steering_wheel_request get_dash_steering_wheel_request() {
    return dash_steering_request.data;
  }
  Dash_lap_finished get_dash_lap_finished() {
    return dash_lap_finished.data;
  }
  Lap_timer_Main get_laptimer_main() { return laptimer_main.data; };
  Lap_timer_Pass get_laptimer_pass() { return laptimer_pass.data; }
  SF_main get_sf_main() { return sf_main.data; }
  SF_FrontBox get_sf_frontbox() { return sf_frontbox.data; }
  SF_CoolingAndVSafety get_sf_cooling() { return sf_coolingandvsafety.data; }
  SF_DV get_sf_dv() { return sf_dv.data; }
  SF_WS get_sf_ws() { return sf_ws.data; }
  SF_NUCS get_sf_nucs() { return sf_nucs.data; }
  Steering_Wheel_main get_steering_wheel_main() {
    return steering_wheel_main.data;
  }
  Steering_Wheel_event get_steering_wheel_event() {
    return steering_wheel_event.data;
  }
  TC_main get_tc_main() { return tc_main.data; }
  TC_rear_suspension get_tc_rear() { return tc_rear_suspension.data; }
  TC_temperatures get_tc_temperatures() { return tc_temperatures.data; }
  TC_wheel_velocities get_tc_wheel_velocities() { return tc_wheel_velocities.data; }
  TC_imu_acc get_tc_imu_acc() { return tc_imu_acc.data; }
  TC_imu_gyro get_tc_imu_gyro() { return tc_imu_gyro.data; }
  Telemetry_Main get_telemetry_main() { return telemetry_main.data; }

  bool get_apps_main_new_data() { return apps.get_new_data(); }
  bool get_aq_main_new_data() { return aq_main.get_new_data(); }
  bool get_aq_acceleration_new_data() { return aq_acceleration.get_new_data();}
  bool get_aq_gryoscope_new_data() { return aq_gyroscope.get_new_data(); }
  bool get_bms_hv_main_new_data() { return bms_hv_main.get_new_data(); }
  bool get_bms_lv_main_new_data() { return bms_lv_main.get_new_data(); }
  bool get_bms_lv_temperature_new_data() {
    return bms_lv_temperature.get_new_data();
  }
  bool get_dash_main_new_data() { return dash_main.get_new_data(); }
  bool get_dash_TCS_new_data() { return dash_TCS.get_new_data(); }
  bool get_dash_fan_speed_new_data() { return dash_fan_speed.get_new_data(); }
  bool get_dash_steering_wheel_request_new_data() {
    return dash_steering_request.get_new_data();
  }
  bool get_dash_lap_finished_new_data() {
    return dash_lap_finished.get_new_data();
  }
  bool get_laptimer_main_new_data() { return laptimer_main.get_new_data(); }
  bool get_laptimer_pass_new_data() { return laptimer_pass.get_new_data(); }
  bool get_sf_main_new_data() { return sf_main.get_new_data(); }
  bool get_sf_frontbox_new_data() { return sf_frontbox.get_new_data(); }
  bool get_sf_cooling_new_data() { return sf_coolingandvsafety.get_new_data(); }
  bool get_sf_dv_new_data() { return sf_dv.get_new_data(); }
  bool get_sf_ws_new_data() { return sf_ws.get_new_data(); }
  bool get_sf_nucs_new_data() { return sf_nucs.get_new_data(); }
  bool get_steering_wheel_main_new_data() {
    return steering_wheel_main.get_new_data();
  }
  bool get_steering_wheel_event_new_data() {
    return steering_wheel_event.get_new_data();
  }
  bool get_tc_main_new_data() { return tc_main.get_new_data(); }
  bool get_tc_rear_suspension_new_data() {
    return tc_rear_suspension.get_new_data();
  }
  bool get_tc_temperatures_new_data() {return tc_temperatures.get_new_data(); }
  bool get_tc_wheel_velocities_new_data() {return tc_wheel_velocities.get_new_data();}
  bool get_tc_imu_gyro_new_data() {return tc_imu_gyro.get_new_data();}
  bool get_tc_imu_acc_new_data() {return tc_imu_acc.get_new_data();}
  
  bool get_telemetry_main_new_data() { return telemetry_main.get_new_data(); }
};

Can_interface can;

} // namespace PUTM_CAN

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
  PUTM_CAN::Can_rx_message rx{*hcan, 0};
  if (rx.status == HAL_StatusTypeDef::HAL_OK) {
    if (not PUTM_CAN::can.parse_message(rx)) {
      // Unknown message
      Error_Handler();
    }
  }
}

#endif
