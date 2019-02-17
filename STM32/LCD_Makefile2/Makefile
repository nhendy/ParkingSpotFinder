######################################
# Makefile by CubeMX2Makefile.py
######################################

######################################
# target
######################################
TARGET = LCD_Makefile2

######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -O0

#######################################
# pathes
#######################################
# Build path
BUILD_DIR = build

######################################
# source
######################################
C_SOURCES = \
  ./syscalls.c \
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc.c \
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash.c \
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_gpio.c \
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2c.c \
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_spi.c \
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim.c \
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2c_ex.c \
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim_ex.c \
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash_ex.c \
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal.c \
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc_ex.c \
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma.c \
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cortex.c \
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma_ex.c \
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr_ex.c \
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr.c \
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart.c \
  Timer/App__Generated.c \
  Timer/MainPage__Generated.c \
  FT_Esd_Widgets/Ft_Esd_Theme.c \
  FT_Esd_Widgets/Ft_Esd_Label__Generated.c \
  FT_Esd_Widgets/Ft_Esd_Toggle__Generated.c \
  FT_Esd_Widgets/Ft_Esd_Rectangle__Generated.c \
  FT_Esd_Widgets/Ft_Esd_RadioButton.c \
  FT_Esd_Widgets/Ft_Esd_DemoPage__Generated.c \
  FT_Esd_Widgets/Ft_Esd_Theme_DarkOrange.c \
  FT_Esd_Widgets/Ft_Esd_CheckBox__Generated.c \
  FT_Esd_Widgets/Ft_Esd_NumericLabel__Generated.c \
  FT_Esd_Widgets/Ft_Esd_RadioGroup.c \
  FT_Esd_Widgets/Ft_Esd_IntCounter__Generated.c \
  FT_Esd_Widgets/Ft_Esd_PushButton__Generated.c \
  FT_Esd_Widgets/SwitchBool__Generated.c \
  FT_Esd_Widgets/Ft_Esd_ScrollPanel.c \
  FT_Esd_Widgets/Ft_Esd_Clock__Generated.c \
  FT_Esd_Widgets/Ft_Esd_SpinBox__Generated.c \
  FT_Esd_Widgets/Ft_Esd_PosSizeToRadius__Generated.c \
  FT_Esd_Widgets/Ft_Esd_Elements__h__Simulation.c \
  FT_Esd_Widgets/Ft_Esd_Theme_LightBlue.c \
  FT_Esd_Widgets/Ft_Esd_Slider__Generated.c \
  FT_Esd_Widgets/LayoutMargin__Generated.c \
  FT_Esd_Widgets/Ft_Esd_Theme__h__Simulation.c \
  FT_Esd_Widgets/SwitchPage.c \
  FT_Esd_Widgets/Ft_Esd_Elements.c \
  FT_Esd_Widgets/Ft_Esd_LabelButton__Generated.c \
  FT_Esd_Widgets/Ft_Esd_RadioButton__Generated.c \
  FT_Esd_Widgets/Ft_Esd_ProgressBar__Generated.c \
  FT_Esd_Widgets/Ft_Esd_Slider.c \
  FT_Esd_Widgets/Ft_Esd_ColorPicker.c \
  FT_Esd_Widgets/Ft_Esd_ImageButton__Generated.c \
  FT_Esd_Widgets/Ft_Esd_Gauge__Generated.c \
  FT_Esd_Widgets/Ft_Esd_ScrollPanel__Generated.c \
  FT_Esd_Widgets/Ft_Esd_RadioGroup__Generated.c \
  FT_Esd_Widgets/LayoutSplit__Generated.c \
  FT_Esd_Widgets/Ft_Esd_ColorPicker__Generated.c \
  FT_Eve_Hal/FT_CoPro_Cmds.c \
  FT_Eve_Hal/FT_Gpu_Hal.c \
  FT_Eve_Hal/FT_Emu_main.c \
  FT_Eve_Hal/FT_ILI9488.c \
  FT_Esd_Framework/Ft_Esd_TouchArea.c \
  FT_Esd_Framework/FT_Esd_CoPro_Cmds__h__Simulation.c \
  FT_Esd_Framework/FT_Esd_Dl.c \
  FT_Esd_Framework/Ft_Esd_TouchArea__Generated.c \
  FT_Esd_Framework/Ft_Esd_GpuAlloc.c \
  FT_Esd_Framework/Ft_Esd_BitmapInfo.c \
  FT_Esd_Framework/Ft_Esd_TouchTag.c \
  FT_Esd_Framework/Ft_Esd_Timer.c \
  FT_Esd_Framework/Ft_Esd.c \
  FT_Esd_Framework/FT_Esd_MainLoop.c \
  FT_Esd_Framework/FT_Esd_Primitives__h__Simulation.c \
  FT_Esd_Framework/Ft_Esd_Timer__Generated.c \
  FT_Esd_Framework/Ft_Esd_App.c \
  FT_Esd_Framework/FT_Esd_Primitives.c \
  Src/stm32f7xx_it.c \
  Src/main.c \
  Src/system_stm32f7xx.c \
  Src/stm32f7xx_hal_msp.c
ASM_SOURCES = \
  startup/startup_stm32f746xx.s

#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m7

# fpu
FPU = -mfpu=fpv5-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS =

# C defines
C_DEFS = -D__weak=__attribute__\(\(weak\)\) -D__packed=__attribute__\(\(__packed__\)\) -DUSE_HAL_DRIVER -DSTM32F746xx

# AS includes
AS_INCLUDES =

# C includes
C_INCLUDES = -IInc
C_INCLUDES += -IDrivers/STM32F7xx_HAL_Driver/Inc
C_INCLUDES += -IDrivers/STM32F7xx_HAL_Driver/Inc/Legacy
C_INCLUDES += -IDrivers/CMSIS/Include
C_INCLUDES += -IDrivers/CMSIS/Device/ST/STM32F7xx/Include
C_INCLUDES += -ITimer
C_INCLUDES += -IFT_Esd_Widgets
C_INCLUDES += -IFT_Eve_Hal
C_INCLUDES += -IFT_Esd_Framework


# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = STM32F746ZGTx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys
LIBDIR =
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@

$(BUILD_DIR):
	mkdir -p $@/.dep

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)

#######################################
# dependencies
#######################################
-include $(shell mkdir -p $(BUILD_DIR)/.dep 2>/dev/null) $(wildcard $(BUILD_DIR)/.dep/*)

.PHONY: clean all

# *** EOF ***
