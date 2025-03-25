################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/balance_task.cpp \
../Core/Src/comm_err_task.cpp \
../Core/Src/global_variables.cpp \
../Core/Src/ltc_library.cpp \
../Core/Src/ltc_task.cpp \
../Core/Src/main.cpp \
../Core/Src/parser.cpp \
../Core/Src/soc_ekf.cpp \
../Core/Src/soc_update_task.cpp 

C_SRCS += \
../Core/Src/freertos.c \
../Core/Src/ring_buffer.c \
../Core/Src/stm32l4xx_hal_msp.c \
../Core/Src/stm32l4xx_hal_timebase_tim.c \
../Core/Src/stm32l4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l4xx.c 

C_DEPS += \
./Core/Src/freertos.d \
./Core/Src/ring_buffer.d \
./Core/Src/stm32l4xx_hal_msp.d \
./Core/Src/stm32l4xx_hal_timebase_tim.d \
./Core/Src/stm32l4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32l4xx.d 

OBJS += \
./Core/Src/balance_task.o \
./Core/Src/comm_err_task.o \
./Core/Src/freertos.o \
./Core/Src/global_variables.o \
./Core/Src/ltc_library.o \
./Core/Src/ltc_task.o \
./Core/Src/main.o \
./Core/Src/parser.o \
./Core/Src/ring_buffer.o \
./Core/Src/soc_ekf.o \
./Core/Src/soc_update_task.o \
./Core/Src/stm32l4xx_hal_msp.o \
./Core/Src/stm32l4xx_hal_timebase_tim.o \
./Core/Src/stm32l4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32l4xx.o 

CPP_DEPS += \
./Core/Src/balance_task.d \
./Core/Src/comm_err_task.d \
./Core/Src/global_variables.d \
./Core/Src/ltc_library.d \
./Core/Src/ltc_task.d \
./Core/Src/main.d \
./Core/Src/parser.d \
./Core/Src/soc_ekf.d \
./Core/Src/soc_update_task.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.cpp Core/Src/subdir.mk
	arm-none-eabi-g++ -fsingle-precision-constant "$<" -mcpu=cortex-m4 -std=c++20 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L4P5xx -c -I../Core/Inc -I"/home/michal/Desktop/PUTMotorsport/BMS_LV/PUTM_EV_BMS_LV_2022/FIRMWARE/Drivers/ETL/include" -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -Wextra -pedantic -Wswitch-default -Wswitch-enum -Wconversion -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=c18 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L4P5xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/balance_task.cyclo ./Core/Src/balance_task.d ./Core/Src/balance_task.o ./Core/Src/balance_task.su ./Core/Src/comm_err_task.cyclo ./Core/Src/comm_err_task.d ./Core/Src/comm_err_task.o ./Core/Src/comm_err_task.su ./Core/Src/freertos.cyclo ./Core/Src/freertos.d ./Core/Src/freertos.o ./Core/Src/freertos.su ./Core/Src/global_variables.cyclo ./Core/Src/global_variables.d ./Core/Src/global_variables.o ./Core/Src/global_variables.su ./Core/Src/ltc_library.cyclo ./Core/Src/ltc_library.d ./Core/Src/ltc_library.o ./Core/Src/ltc_library.su ./Core/Src/ltc_task.cyclo ./Core/Src/ltc_task.d ./Core/Src/ltc_task.o ./Core/Src/ltc_task.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/parser.cyclo ./Core/Src/parser.d ./Core/Src/parser.o ./Core/Src/parser.su ./Core/Src/ring_buffer.cyclo ./Core/Src/ring_buffer.d ./Core/Src/ring_buffer.o ./Core/Src/ring_buffer.su ./Core/Src/soc_ekf.cyclo ./Core/Src/soc_ekf.d ./Core/Src/soc_ekf.o ./Core/Src/soc_ekf.su ./Core/Src/soc_update_task.cyclo ./Core/Src/soc_update_task.d ./Core/Src/soc_update_task.o ./Core/Src/soc_update_task.su ./Core/Src/stm32l4xx_hal_msp.cyclo ./Core/Src/stm32l4xx_hal_msp.d ./Core/Src/stm32l4xx_hal_msp.o ./Core/Src/stm32l4xx_hal_msp.su ./Core/Src/stm32l4xx_hal_timebase_tim.cyclo ./Core/Src/stm32l4xx_hal_timebase_tim.d ./Core/Src/stm32l4xx_hal_timebase_tim.o ./Core/Src/stm32l4xx_hal_timebase_tim.su ./Core/Src/stm32l4xx_it.cyclo ./Core/Src/stm32l4xx_it.d ./Core/Src/stm32l4xx_it.o ./Core/Src/stm32l4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32l4xx.cyclo ./Core/Src/system_stm32l4xx.d ./Core/Src/system_stm32l4xx.o ./Core/Src/system_stm32l4xx.su

.PHONY: clean-Core-2f-Src

