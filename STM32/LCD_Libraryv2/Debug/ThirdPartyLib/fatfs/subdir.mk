################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ThirdPartyLib/fatfs/diskio.c \
../ThirdPartyLib/fatfs/ff.c \
../ThirdPartyLib/fatfs/ff_ioctl_test.c \
../ThirdPartyLib/fatfs/syscall.c \
../ThirdPartyLib/fatfs/unicode.c 

OBJS += \
./ThirdPartyLib/fatfs/diskio.o \
./ThirdPartyLib/fatfs/ff.o \
./ThirdPartyLib/fatfs/ff_ioctl_test.o \
./ThirdPartyLib/fatfs/syscall.o \
./ThirdPartyLib/fatfs/unicode.o 

C_DEPS += \
./ThirdPartyLib/fatfs/diskio.d \
./ThirdPartyLib/fatfs/ff.d \
./ThirdPartyLib/fatfs/ff_ioctl_test.d \
./ThirdPartyLib/fatfs/syscall.d \
./ThirdPartyLib/fatfs/unicode.d 


# Each subdirectory must supply rules for building sources it contributes
ThirdPartyLib/fatfs/%.o: ../ThirdPartyLib/fatfs/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F746xx -I"C:/Users/eepc18adm/Desktop/ECE477-GarageMonitoringSystem/STM32/LCD_Libraryv2/Inc" -I"C:/Users/eepc18adm/Desktop/ECE477-GarageMonitoringSystem/STM32/LCD_Libraryv2/Drivers/STM32F7xx_HAL_Driver/Inc" -I"C:/Users/eepc18adm/Desktop/ECE477-GarageMonitoringSystem/STM32/LCD_Libraryv2/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"C:/Users/eepc18adm/Desktop/ECE477-GarageMonitoringSystem/STM32/LCD_Libraryv2/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"C:/Users/eepc18adm/Desktop/ECE477-GarageMonitoringSystem/STM32/LCD_Libraryv2/Drivers/CMSIS/Include" -I"C:/Users/eepc18adm/Desktop/ECE477-GarageMonitoringSystem/STM32/LCD_Libraryv2/FT_Esd_Framework" -I"C:/Users/eepc18adm/Desktop/ECE477-GarageMonitoringSystem/STM32/LCD_Libraryv2/FT_Esd_Widgets" -I"C:/Users/eepc18adm/Desktop/ECE477-GarageMonitoringSystem/STM32/LCD_Libraryv2/FT_Eve_Hal" -I"C:/Users/eepc18adm/Desktop/ECE477-GarageMonitoringSystem/STM32/LCD_Libraryv2/Timer"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


