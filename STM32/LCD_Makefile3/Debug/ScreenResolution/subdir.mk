################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ScreenResolution/AppScreen__Generated.c \
../ScreenResolution/App__Generated.c \
../ScreenResolution/MainPage__Generated.c 

OBJS += \
./ScreenResolution/AppScreen__Generated.o \
./ScreenResolution/App__Generated.o \
./ScreenResolution/MainPage__Generated.o 

C_DEPS += \
./ScreenResolution/AppScreen__Generated.d \
./ScreenResolution/App__Generated.d \
./ScreenResolution/MainPage__Generated.d 


# Each subdirectory must supply rules for building sources it contributes
ScreenResolution/%.o: ../ScreenResolution/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F746xx -I"C:/Users/eepc18adm/Desktop/ECE477-GarageMonitoringSystem/STM32/LCD_Makefile3/Inc" -I"C:/Users/eepc18adm/Desktop/ECE477-GarageMonitoringSystem/STM32/LCD_Makefile3/Drivers/STM32F7xx_HAL_Driver/Inc" -I"C:/Users/eepc18adm/Desktop/ECE477-GarageMonitoringSystem/STM32/LCD_Makefile3/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"C:/Users/eepc18adm/Desktop/ECE477-GarageMonitoringSystem/STM32/LCD_Makefile3/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"C:/Users/eepc18adm/Desktop/ECE477-GarageMonitoringSystem/STM32/LCD_Makefile3/Drivers/CMSIS/Include" -I"C:/Users/eepc18adm/Desktop/ECE477-GarageMonitoringSystem/STM32/LCD_Makefile3/FT_Esd_Framework" -I"C:/Users/eepc18adm/Desktop/ECE477-GarageMonitoringSystem/STM32/LCD_Makefile3/FT_Esd_Widgets" -I"C:/Users/eepc18adm/Desktop/ECE477-GarageMonitoringSystem/STM32/LCD_Makefile3/FT_Eve_Hal" -I"C:/Users/eepc18adm/Desktop/ECE477-GarageMonitoringSystem/STM32/LCD_Makefile3/PanL_BSP" -I"C:/Users/eepc18adm/Desktop/ECE477-GarageMonitoringSystem/STM32/LCD_Makefile3/ScreenResolution" -I"C:/Users/eepc18adm/Desktop/ECE477-GarageMonitoringSystem/STM32/LCD_Makefile3/ThirdPartyLib" -I../FT_Eve_Hal/Lib -I../FT_Eve_Hal/FT900  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


