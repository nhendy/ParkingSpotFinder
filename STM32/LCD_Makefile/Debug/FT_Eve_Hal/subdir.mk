################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FT_Eve_Hal/FT_CoPro_Cmds.c \
../FT_Eve_Hal/FT_Emu_main.c \
../FT_Eve_Hal/FT_Gpu_Hal.c \
../FT_Eve_Hal/FT_ILI9488.c 

OBJS += \
./FT_Eve_Hal/FT_CoPro_Cmds.o \
./FT_Eve_Hal/FT_Emu_main.o \
./FT_Eve_Hal/FT_Gpu_Hal.o \
./FT_Eve_Hal/FT_ILI9488.o 

C_DEPS += \
./FT_Eve_Hal/FT_CoPro_Cmds.d \
./FT_Eve_Hal/FT_Emu_main.d \
./FT_Eve_Hal/FT_Gpu_Hal.d \
./FT_Eve_Hal/FT_ILI9488.d 


# Each subdirectory must supply rules for building sources it contributes
FT_Eve_Hal/%.o: ../FT_Eve_Hal/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F746xx -I"/Users/noureldinhendy/Developmentspace/ECE477-GarageMonitoringSystem/STM32/LCD_Makefile/Inc" -I"/Users/noureldinhendy/Developmentspace/ECE477-GarageMonitoringSystem/STM32/LCD_Makefile/Drivers/STM32F7xx_HAL_Driver/Inc" -I"/Users/noureldinhendy/Developmentspace/ECE477-GarageMonitoringSystem/STM32/LCD_Makefile/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"/Users/noureldinhendy/Developmentspace/ECE477-GarageMonitoringSystem/STM32/LCD_Makefile/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/Users/noureldinhendy/Developmentspace/ECE477-GarageMonitoringSystem/STM32/LCD_Makefile/Drivers/CMSIS/Include" -I"/Users/noureldinhendy/Developmentspace/ECE477-GarageMonitoringSystem/STM32/LCD_Makefile/FT_Esd_Framework" -I"/Users/noureldinhendy/Developmentspace/ECE477-GarageMonitoringSystem/STM32/LCD_Makefile/FT_Esd_Widgets" -I"/Users/noureldinhendy/Developmentspace/ECE477-GarageMonitoringSystem/STM32/LCD_Makefile/FT_Eve_Hal" -I"/Users/noureldinhendy/Developmentspace/ECE477-GarageMonitoringSystem/STM32/LCD_Makefile/Timer"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


