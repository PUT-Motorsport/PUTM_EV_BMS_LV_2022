/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
void SystemClock_Config(void);
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
extern SPI_HandleTypeDef hspi1;
extern CAN_HandleTypeDef hcan1;
extern RTC_HandleTypeDef hrtc;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
