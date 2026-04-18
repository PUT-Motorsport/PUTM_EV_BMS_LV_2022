/*
 * comm_err_task.cpp
 * Updated for PUTM_EV_CAN_LIBRARY
 */

#include <comm_err_task.hpp>
#include "can_driver.hpp"       // Main API class
#include "PUTM_CAN_M.h"         // Generated DBC headers

// Handle for the CAN peripheral from CubeMX
extern "C" FDCAN_HandleTypeDef hfdcan2; 

extern "C" {
    #include "usbd_cdc_if.h"  
    #include "stm32g4xx_hal.h"
}

// Global instance of the CAN driver
putm_ev_can::CanDriver can_m;

uint32_t serial_tick = 0;
uint32_t can_main_tick = 0;
uint32_t can_temp_tick = 0;

enum struct Error_condition {
    UNBALANCE,
    VOLTAGE_LOW,
    VOLTAGE_HIGH,
    TEMPERATURE_WARNING,
    TEMPERATURE_HIGH,
    TEMPERATURE_LOST,
    CURRENT_HIGH,
    NEUTRAL_CURRENT_CAR
};

struct Error_and_connditions {
    Error_condition error;
    float min;
    float max;
    float value;
    const uint32_t error_time;
    const uint8_t acu_state_code;
    uint32_t timer;
    bool flag = false;
};

Error_and_connditions error_conditions[8] = {
    {Error_condition::NEUTRAL_CURRENT_CAR, -0.3f, 0.3f, data.current.value, TIME_TO_SLEEP, 0},
    {Error_condition::UNBALANCE, 2000, 50000, (float)(data.voltages.highest_cell_voltage - data.voltages.lowest_cell_voltage), ERROR_TIME, 2},
    {Error_condition::TEMPERATURE_WARNING, 48, 55, (float)data.temperatures.highest_temperature, ERROR_TIME_TEMPERATURES, 3},
    {Error_condition::VOLTAGE_LOW, 0, 30000, (float)data.voltages.lowest_cell_voltage, ERROR_TIME, 4},
    {Error_condition::VOLTAGE_HIGH, 42200, 500000, (float)data.voltages.highest_cell_voltage, ERROR_TIME, 5},
    {Error_condition::TEMPERATURE_HIGH, 55, 120, (float)data.temperatures.highest_temperature, ERROR_TIME_TEMPERATURES, 6},
    {Error_condition::TEMPERATURE_LOST, -1, 1, (float)data.temperatures.lowest_temperature, ERROR_TIME_TEMPERATURES, 6},
    {Error_condition::CURRENT_HIGH, 20, 100, data.current.value, ERROR_TIME, 7}
};

void error_check() {
    etl::vector<Error_condition, 8> errors_vector;

    for (auto& error : error_conditions) {
        if (error.min <= error.value && error.value <= error.max) {
            errors_vector.emplace_back(error.error);
            data.acu_state = error.acu_state_code;
            if (false == error.flag) {
                error.timer = HAL_GetTick() + error.error_time;
                error.flag = true;
            }
        } else {
            error.timer = HAL_GetTick() + error.error_time;
            error.flag = false;
        }
    }

    if (errors_vector.empty()) {
        data.acu_state = NORMAL_STATE;
    }
}

void error_execute() {
    for (unsigned int i = 3; i < 8; i++) {
        if (error_conditions[i].timer <= HAL_GetTick()) {
            HAL_GPIO_WritePin(EFUSE_GPIO_Port, EFUSE_Pin, GPIO_PIN_RESET);
        }
    }
    data.EFUSE_state = HAL_GPIO_ReadPin(EFUSE_GPIO_Port, EFUSE_Pin);
}

void serialPrint() {
    embeddedjson::Json<1024> json;
    json.add("battery_state", data.acu_state);
    json.add("stack_voltage", (float)data.voltages.total / 10'000.0f);
    json.add("state_of_charge", data.soc.value * 100);
    json.add("output_current", data.current.value);
    json.add("efuse_state", HAL_GPIO_ReadPin(EFUSE_GPIO_Port, EFUSE_Pin));

    std::array<float, 8> temperatures;
    for (int i = 0; i < NUMBER_OF_TEMPERATURES; i++) {
        temperatures[i] = data.temperatures.values[i];
    }
    json.add("temperatures", temperatures);

    std::array<float, NUMBER_OF_CELLS> voltages;
    for (int i = 0; i < NUMBER_OF_CELLS; i++) {
        voltages[i] = (float)data.voltages.cells[i] / 10'000.0f;
    }
    json.add("voltages", voltages);

    auto [json_data, json_size] = json.get_as_c_array();
    // Use USB CDC to transmit data
    CDC_Transmit_FS((uint8_t*)json_data, json_size);
}

void start_comm_err_function(void *argument) {
    data.ErrorDetection = true;

    // Initialize the library driver
    if (!can_m.Init(&hfdcan2)) {
        Error_Handler();
    }

    for (;;) {
        osDelay(20);

        error_conditions[0].value = data.current.value;
        error_conditions[1].value = (float)(data.voltages.highest_cell_voltage - data.voltages.lowest_cell_voltage);
        error_conditions[2].value = (float)data.temperatures.highest_temperature;
        error_conditions[3].value = (float)data.voltages.lowest_cell_voltage;
        error_conditions[4].value = (float)data.voltages.highest_cell_voltage;
        error_conditions[5].value = (float)data.temperatures.highest_temperature;
        error_conditions[6].value = (float)data.temperatures.lowest_temperature;
        error_conditions[7].value = data.current.value;

        // Prepare BMS_LV_MAIN message using explicit casting to satisfy C++ types
        PUTM_CAN_M_bms_lv_main_t can_msg_main = {
            .voltage_sum = static_cast<uint16_t>(data.voltages.total_can),
            .soc         = static_cast<uint8_t>(data.soc.value_can),
            .temp_avg    = static_cast<uint8_t>(data.temperatures.average),
            .current     = static_cast<uint8_t>(data.current.value),
            .device_state = static_cast<uint8_t>(data.acu_state)
        };

        // Prepare BMS_LV_TEMPERATURE message
        PUTM_CAN_M_bms_lv_temperature_t can_msg_temp = {
            .temp_1 = static_cast<uint8_t>(data.temperatures.values[0]),
            .temp_2 = static_cast<uint8_t>(data.temperatures.values[1]),
            .temp_3 = static_cast<uint8_t>(data.temperatures.values[2]),
            .temp_4 = static_cast<uint8_t>(data.temperatures.values[3]),
            .temp_5 = static_cast<uint8_t>(data.temperatures.values[4]),
            .temp_6 = static_cast<uint8_t>(data.temperatures.values[5]),
            .temp_7 = static_cast<uint8_t>(data.temperatures.values[6]),
            .temp_8 = static_cast<uint8_t>(data.temperatures.values[7])
        };

        if (serial_tick < HAL_GetTick()) {
            serialPrint();
            serial_tick = HAL_GetTick() + 500;
        }

        // Periodic transmission using the new API
        if (can_main_tick < HAL_GetTick()) {
            bool ok = can_m.Send(PUTM_CAN_M_BMS_LV_MAIN_FRAME_ID, can_msg_main);
            can_main_tick = HAL_GetTick() + 40;
            data.CanError = ok ? 0 : 1;
        }

        if (can_temp_tick < HAL_GetTick()) {
            bool ok = can_m.Send(PUTM_CAN_M_BMS_LV_TEMPERATURE_FRAME_ID, can_msg_temp);
            can_temp_tick = HAL_GetTick() + 200;
            data.CanError = ok ? 0 : 1;
        }

        if (data.ErrorDetection) {
            error_check();
            error_execute();
        } else {
            if (HAL_GPIO_ReadPin(EFUSE_GPIO_Port, EFUSE_Pin) == GPIO_PIN_RESET) {
                HAL_GPIO_WritePin(EFUSE_GPIO_Port, EFUSE_Pin, GPIO_PIN_SET);
            }
        }
    }
}