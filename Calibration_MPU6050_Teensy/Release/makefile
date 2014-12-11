################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include arduino/core/subdir.mk
-include Libraries/i2c_t3/subdir.mk
-include Libraries/MPU6050/subdir.mk
-include Libraries/I2Cdev/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
C:/Programming/Workspace/Eclipse_C++_Arduino_v2.2/Calibration_MPU6050_Teensy/Release/teensy.ar \

ELF += \
Calibration_MPU6050_Teensy.elf \

EEP += \
Calibration_MPU6050_Teensy.eep \

FLASH_IMAGE += \
Calibration_MPU6050_Teensy.hex \


# All Target
all: Calibration_MPU6050_Teensy

# Tool invocations
Calibration_MPU6050_Teensy: $(FLASH_IMAGE)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"C:/Programs/Arduino-1.5.6r2/hardware/teensy/tools/windows/arm-none-eabi/bin/arm-none-eabi-size" -A "C:/Programming/Workspace/Eclipse_C++_Arduino_v2.2/Calibration_MPU6050_Teensy/Release/Calibration_MPU6050_Teensy.elf"
	@echo 'Finished building target: $@'
	@echo ' '

C:/Programming/Workspace/Eclipse_C++_Arduino_v2.2/Calibration_MPU6050_Teensy/Release/teensy.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"C:/Programs/Arduino-1.5.6r2/hardware/teensy/tools/windows/arm-none-eabi/bin/arm-none-eabi-ar" -r "C:/Programming/Workspace/Eclipse_C++_Arduino_v2.2/Calibration_MPU6050_Teensy/Release/teensy.ar"   $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

Calibration_MPU6050_Teensy.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"C:/Programs/Arduino-1.5.6r2/hardware/teensy/tools/windows/arm-none-eabi/bin/arm-none-eabi-gcc"  -Os -Wl,--gc-sections -mcpu=cortex-m4 -mthumb "-TC:/Programs/Arduino-1.5.6r2/hardware/teensy/all/cores/teensy3/mk20dx256.ld" -o "C:/Programming/Workspace/Eclipse_C++_Arduino_v2.2/Calibration_MPU6050_Teensy/Release/Calibration_MPU6050_Teensy.elf"   $(LINK_OBJ) $(AR)  -L"C:/Programming/Workspace/Eclipse_C++_Arduino_v2.2/Calibration_MPU6050_Teensy/Release" -lm
	@echo 'Finished building: $@'
	@echo ' '

Calibration_MPU6050_Teensy.eep: $(ELF)
	@echo 'Create eeprom image'
	"C:/Programs/Arduino-1.5.6r2/hardware/teensy/tools/windows/arm-none-eabi/bin/arm-none-eabi-objcopy" -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 "C:/Programming/Workspace/Eclipse_C++_Arduino_v2.2/Calibration_MPU6050_Teensy/Release/Calibration_MPU6050_Teensy.elf" "C:/Programming/Workspace/Eclipse_C++_Arduino_v2.2/Calibration_MPU6050_Teensy/Release/Calibration_MPU6050_Teensy.eep"
	@echo 'Finished building: $@'
	@echo ' '

Calibration_MPU6050_Teensy.hex: $(EEP)
	@echo 'Create Flash image (ihex format)'
	"C:/Programs/Arduino-1.5.6r2/hardware/teensy/tools/windows/arm-none-eabi/bin/arm-none-eabi-objcopy" -O ihex -R .eeprom "C:/Programming/Workspace/Eclipse_C++_Arduino_v2.2/Calibration_MPU6050_Teensy/Release/Calibration_MPU6050_Teensy.elf" "C:/Programming/Workspace/Eclipse_C++_Arduino_v2.2/Calibration_MPU6050_Teensy/Release/Calibration_MPU6050_Teensy.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(C_DEPS)$(AR)$(EEP)$(FLASH_IMAGE)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(SIZEDUMMY)$(ELF)$(CPP_DEPS) Calibration_MPU6050_Teensy
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
