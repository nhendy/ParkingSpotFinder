################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL_Driver/Src/Legacy/stm32f7xx_hal_can.c 

OBJS += \
./HAL_Driver/Src/Legacy/stm32f7xx_hal_can.o 

C_DEPS += \
./HAL_Driver/Src/Legacy/stm32f7xx_hal_can.d 


# Each subdirectory must supply rules for building sources it contributes
HAL_Driver/Src/Legacy/%.o: ../HAL_Driver/Src/Legacy/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -DSTM32 -DSTM32F7 -DSTM32F746ZGTx -DNUCLEO_F746ZG -DDEBUG -DSTM32F746xx -DUSE_HAL_DRIVER -I"C:/Users/eepc18adm/workspace/TESTING/HAL_Driver/Inc/Legacy" -I"C:/Users/eepc18adm/workspace/TESTING/Utilities/STM32F7xx_Nucleo_144" -I"C:/Users/eepc18adm/workspace/TESTING/inc" -I"C:/Users/eepc18adm/workspace/TESTING/CMSIS/device" -I"C:/Users/eepc18adm/workspace/TESTING/CMSIS/core" -I"C:/Users/eepc18adm/workspace/TESTING/HAL_Driver/Inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


