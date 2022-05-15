/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "soc_ekf.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define EFUSE_Pin GPIO_PIN_2
#define EFUSE_GPIO_Port GPIOA
#define THERM_1_Pin GPIO_PIN_3
#define THERM_1_GPIO_Port GPIOA
#define THERM_2_Pin GPIO_PIN_4
#define THERM_2_GPIO_Port GPIOA
#define THERM_3_Pin GPIO_PIN_5
#define THERM_3_GPIO_Port GPIOA
#define THERM_4_Pin GPIO_PIN_6
#define THERM_4_GPIO_Port GPIOA
#define THERM_5_Pin GPIO_PIN_7
#define THERM_5_GPIO_Port GPIOA
#define THERM_6_Pin GPIO_PIN_4
#define THERM_6_GPIO_Port GPIOC
#define THERM_7_Pin GPIO_PIN_5
#define THERM_7_GPIO_Port GPIOC
#define THERM_8_Pin GPIO_PIN_0
#define THERM_8_GPIO_Port GPIOB
#define CURRENT_SENSOR_Pin GPIO_PIN_1
#define CURRENT_SENSOR_GPIO_Port GPIOB
#define INTERLOCK_Pin GPIO_PIN_2
#define INTERLOCK_GPIO_Port GPIOB
#define FUSE_VOLTAGE_Pin GPIO_PIN_11
#define FUSE_VOLTAGE_GPIO_Port GPIOB
#define LED_1_Pin GPIO_PIN_6
#define LED_1_GPIO_Port GPIOC
#define LED_2_Pin GPIO_PIN_7
#define LED_2_GPIO_Port GPIOC
#define LED_3_Pin GPIO_PIN_8
#define LED_3_GPIO_Port GPIOC
#define LED_4_Pin GPIO_PIN_9
#define LED_4_GPIO_Port GPIOC
#define SW_DIO_Pin GPIO_PIN_13
#define SW_DIO_GPIO_Port GPIOA
#define SW_CLK_Pin GPIO_PIN_14
#define SW_CLK_GPIO_Port GPIOA
#define SPI1_CS_Pin GPIO_PIN_15
#define SPI1_CS_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */
#define NUMBER_OF_CELLS 			6
#define NUMBER_OF_TEMPERATURES		5
#define NUMBER_OF_CS_SAMPLES		300
#define NEUTRAL_CURRENT_SENSOR		2160 	//TO CHECK

#define VOL_DOWN_LIMIT				30000 	//3.0V
#define VOL_DOWN_OK					36000 	//3.6V

#define VOL_UP_LIMIT				42200 	//4.22V
#define VOL_UP_OVERCHARGE			42100
#define VOL_UP_OK					42010 	//4.201V
#define VOL_UP_NEARLY_OK			41950	//4.195V

#define BALANCE_VALUE				50 		//0.005V
#define BALANCE_TIME				10000   //10s
#define UNBALANCE_LIMIT				2000 	// 0.2V
#define MAX_CELLS_DISCHARGE_AT_ONCE	3
#define CHARGING_CUTOFF_CURRENT		0.3f

#define NEUTRAL_CURRENT_CAR 		0.3 	//to check

#define TIME_TO_SLEEP				1200000 //20 min = 20*60*1000 ms
#define ERROR_TIME					500   	//500ms
#define ERROR_TIME_TEMPERATURES		1000  	//1000ms


#define TOO_HIGH_CURRENT			20 		//27A
#define TEMPERATURE_WARNING	50.0f
#define TEMPERATURE_LIMIT			55.0f

struct Voltages{
	uint16_t cells[NUMBER_OF_CELLS];
	uint8_t cells_can[NUMBER_OF_CELLS];
	uint32_t total;
	uint16_t lowest_cell_voltage;
	uint16_t highest_cell_voltage;
	uint16_t highest_cell_voltage_index;
};

struct Temperatures{
	uint16_t values[NUMBER_OF_TEMPERATURES];
	uint8_t values_can[NUMBER_OF_TEMPERATURES];
	uint16_t average;
	volatile uint16_t adc[NUMBER_OF_TEMPERATURES];
};

struct Current_Sensor{
	uint32_t adc[NUMBER_OF_CS_SAMPLES] = {0};
	float value;
	float value_max;
	float value_min;

};

struct SoC{
	float value;
	uint8_t value_can;
};

struct Charging{
	bool cell_discharge[NUMBER_OF_CELLS];
	bool charger_plugged;
	bool charging_state;
	bool discharge_activation;
	static uint32_t discharge_tick_end;
};

struct Data{
	Voltages voltages;
	Temperatures temperatures;
	Current_Sensor current;
	SoC soc;
	Charging charging;
} data;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
