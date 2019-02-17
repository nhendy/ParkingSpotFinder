################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FT_Esd_Framework/FT_Esd_CoPro_Cmds__h__Simulation.c \
../FT_Esd_Framework/FT_Esd_Dl.c \
../FT_Esd_Framework/FT_Esd_MainLoop.c \
../FT_Esd_Framework/FT_Esd_Primitives.c \
../FT_Esd_Framework/FT_Esd_Primitives__h__Simulation.c \
../FT_Esd_Framework/Ft_Esd.c \
../FT_Esd_Framework/Ft_Esd_App.c \
../FT_Esd_Framework/Ft_Esd_BitmapInfo.c \
../FT_Esd_Framework/Ft_Esd_GpuAlloc.c \
../FT_Esd_Framework/Ft_Esd_Timer.c \
../FT_Esd_Framework/Ft_Esd_Timer__Generated.c \
../FT_Esd_Framework/Ft_Esd_TouchArea.c \
../FT_Esd_Framework/Ft_Esd_TouchArea__Generated.c \
../FT_Esd_Framework/Ft_Esd_TouchTag.c 

OBJS += \
./FT_Esd_Framework/FT_Esd_CoPro_Cmds__h__Simulation.o \
./FT_Esd_Framework/FT_Esd_Dl.o \
./FT_Esd_Framework/FT_Esd_MainLoop.o \
./FT_Esd_Framework/FT_Esd_Primitives.o \
./FT_Esd_Framework/FT_Esd_Primitives__h__Simulation.o \
./FT_Esd_Framework/Ft_Esd.o \
./FT_Esd_Framework/Ft_Esd_App.o \
./FT_Esd_Framework/Ft_Esd_BitmapInfo.o \
./FT_Esd_Framework/Ft_Esd_GpuAlloc.o \
./FT_Esd_Framework/Ft_Esd_Timer.o \
./FT_Esd_Framework/Ft_Esd_Timer__Generated.o \
./FT_Esd_Framework/Ft_Esd_TouchArea.o \
./FT_Esd_Framework/Ft_Esd_TouchArea__Generated.o \
./FT_Esd_Framework/Ft_Esd_TouchTag.o 

C_DEPS += \
./FT_Esd_Framework/FT_Esd_CoPro_Cmds__h__Simulation.d \
./FT_Esd_Framework/FT_Esd_Dl.d \
./FT_Esd_Framework/FT_Esd_MainLoop.d \
./FT_Esd_Framework/FT_Esd_Primitives.d \
./FT_Esd_Framework/FT_Esd_Primitives__h__Simulation.d \
./FT_Esd_Framework/Ft_Esd.d \
./FT_Esd_Framework/Ft_Esd_App.d \
./FT_Esd_Framework/Ft_Esd_BitmapInfo.d \
./FT_Esd_Framework/Ft_Esd_GpuAlloc.d \
./FT_Esd_Framework/Ft_Esd_Timer.d \
./FT_Esd_Framework/Ft_Esd_Timer__Generated.d \
./FT_Esd_Framework/Ft_Esd_TouchArea.d \
./FT_Esd_Framework/Ft_Esd_TouchArea__Generated.d \
./FT_Esd_Framework/Ft_Esd_TouchTag.d 


# Each subdirectory must supply rules for building sources it contributes
FT_Esd_Framework/%.o: ../FT_Esd_Framework/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F746xx -I"/Users/noureldinhendy/Developmentspace/ECE477-GarageMonitoringSystem/STM32/LCD_Makefile/Inc" -I"/Users/noureldinhendy/Developmentspace/ECE477-GarageMonitoringSystem/STM32/LCD_Makefile/Drivers/STM32F7xx_HAL_Driver/Inc" -I"/Users/noureldinhendy/Developmentspace/ECE477-GarageMonitoringSystem/STM32/LCD_Makefile/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"/Users/noureldinhendy/Developmentspace/ECE477-GarageMonitoringSystem/STM32/LCD_Makefile/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/Users/noureldinhendy/Developmentspace/ECE477-GarageMonitoringSystem/STM32/LCD_Makefile/Drivers/CMSIS/Include" -I"/Users/noureldinhendy/Developmentspace/ECE477-GarageMonitoringSystem/STM32/LCD_Makefile/FT_Esd_Framework" -I"/Users/noureldinhendy/Developmentspace/ECE477-GarageMonitoringSystem/STM32/LCD_Makefile/FT_Esd_Widgets" -I"/Users/noureldinhendy/Developmentspace/ECE477-GarageMonitoringSystem/STM32/LCD_Makefile/FT_Eve_Hal" -I"/Users/noureldinhendy/Developmentspace/ECE477-GarageMonitoringSystem/STM32/LCD_Makefile/Timer"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


