/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 512 * 4
};
/* Definitions for ltc_task */
osThreadId_t ltc_taskHandle;
uint32_t ltc_taskBuffer[ 512 ];
osStaticThreadDef_t ltc_taskControlBlock;
const osThreadAttr_t ltc_task_attributes = {
  .name = "ltc_task",
  .stack_mem = &ltc_taskBuffer[0],
  .stack_size = sizeof(ltc_taskBuffer),
  .cb_mem = &ltc_taskControlBlock,
  .cb_size = sizeof(ltc_taskControlBlock),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for soc_update_task */
osThreadId_t soc_update_taskHandle;
uint32_t soc_update_taskBuffer[ 512 ];
osStaticThreadDef_t soc_update_taskControlBlock;
const osThreadAttr_t soc_update_task_attributes = {
  .name = "soc_update_task",
  .stack_mem = &soc_update_taskBuffer[0],
  .stack_size = sizeof(soc_update_taskBuffer),
  .cb_mem = &soc_update_taskControlBlock,
  .cb_size = sizeof(soc_update_taskControlBlock),
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for balance_task */
osThreadId_t balance_taskHandle;
uint32_t balance_taskBuffer[ 512 ];
osStaticThreadDef_t balance_taskControlBlock;
const osThreadAttr_t balance_task_attributes = {
  .name = "balance_task",
  .stack_mem = &balance_taskBuffer[0],
  .stack_size = sizeof(balance_taskBuffer),
  .cb_mem = &balance_taskControlBlock,
  .cb_size = sizeof(balance_taskControlBlock),
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for comm_err_task */
osThreadId_t comm_err_taskHandle;
uint32_t comm_err_taskBuffer[ 512 ];
osStaticThreadDef_t comm_err_taskControlBlock;
const osThreadAttr_t comm_err_task_attributes = {
  .name = "comm_err_task",
  .stack_mem = &comm_err_taskBuffer[0],
  .stack_size = sizeof(comm_err_taskBuffer),
  .cb_mem = &comm_err_taskControlBlock,
  .cb_size = sizeof(comm_err_taskControlBlock),
  .priority = (osPriority_t) osPriorityHigh,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
extern void start_ltc_function(void *argument);
extern void start_soc_function(void *argument);
extern void start_balance_function(void *argument);
extern void start_comm_err_function(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of ltc_task */
  ltc_taskHandle = osThreadNew(start_ltc_function, NULL, &ltc_task_attributes);

  /* creation of soc_update_task */
  soc_update_taskHandle = osThreadNew(start_soc_function, NULL, &soc_update_task_attributes);

  /* creation of balance_task */
  balance_taskHandle = osThreadNew(start_balance_function, NULL, &balance_task_attributes);

  /* creation of comm_err_task */
  comm_err_taskHandle = osThreadNew(start_comm_err_function, NULL, &comm_err_task_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* init code for USB_Device */
  MX_USB_Device_Init();
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

