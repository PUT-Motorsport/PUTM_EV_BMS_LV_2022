/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "stm32g4xx_hal.h"

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

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define THERM_4_Pin GPIO_PIN_0
#define THERM_4_GPIO_Port GPIOC
#define THERM_5_Pin GPIO_PIN_1
#define THERM_5_GPIO_Port GPIOC
#define THERM_6_Pin GPIO_PIN_2
#define THERM_6_GPIO_Port GPIOC
#define THERM_1_Pin GPIO_PIN_0
#define THERM_1_GPIO_Port GPIOA
#define THERM_2_Pin GPIO_PIN_1
#define THERM_2_GPIO_Port GPIOA
#define THERM_3_Pin GPIO_PIN_2
#define THERM_3_GPIO_Port GPIOA
#define THERM_7_Pin GPIO_PIN_3
#define THERM_7_GPIO_Port GPIOA
#define Standby_Pin GPIO_PIN_0
#define Standby_GPIO_Port GPIOB
#define EFUSE_Pin GPIO_PIN_11
#define EFUSE_GPIO_Port GPIOB
#define THERM_8_Pin GPIO_PIN_14
#define THERM_8_GPIO_Port GPIOB
#define FUSE_VOLTAGE_Pin GPIO_PIN_15
#define FUSE_VOLTAGE_GPIO_Port GPIOB
#define INTERLOCK_Pin GPIO_PIN_6
#define INTERLOCK_GPIO_Port GPIOC
#define SPI1_CS_Pin GPIO_PIN_8
#define SPI1_CS_GPIO_Port GPIOA
#define UART_TX_Pin GPIO_PIN_10
#define UART_TX_GPIO_Port GPIOC
#define RED_Pin GPIO_PIN_4
#define RED_GPIO_Port GPIOB
#define GREEN_Pin GPIO_PIN_5
#define GREEN_GPIO_Port GPIOB
#define YELLOW_Pin GPIO_PIN_6
#define YELLOW_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
