################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include arduino/variant/subdir.mk
-include arduino/core/avr/subdir.mk
-include arduino/core/USB/subdir.mk
-include arduino/core/subdir.mk
-include Libraries/Wire/subdir.mk
-include Libraries/MPU6050/subdir.mk
-include Libraries/I2Cdev_Arduino/subdir.mk
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
C:/Programming/Workspace/Eclipse_C++_Arduino_v2.2/Calibration_MPU6050_DUE/Release/arduino.ar \

ELF += \
Calibration_MPU6050_DUE.elf \

EEP += \
Calibration_MPU6050_DUE.eep \

FLASH_IMAGE += \
Calibration_MPU6050_DUE.bin \


# All Target
all: Calibration_MPU6050_DUE

# Tool invocations
Calibration_MPU6050_DUE: $(FLASH_IMAGE)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"C:/Programs/Arduino-1.5.6r2/hardware/tools/gcc-arm-none-eabi-4.8.3-2014q1/bin/arm-none-eabi-size" -A "C:/Programming/Workspace/Eclipse_C++_Arduino_v2.2/Calibration_MPU6050_DUE/Release/Calibration_MPU6050_DUE.elf"
	@echo 'Finished building target: $@'
	@echo ' '

C:/Programming/Workspace/Eclipse_C++_Arduino_v2.2/Calibration_MPU6050_DUE/Release/arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"C:/Programs/Arduino-1.5.6r2/hardware/tools/gcc-arm-none-eabi-4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "C:/Programming/Workspace/Eclipse_C++_Arduino_v2.2/Calibration_MPU6050_DUE/Release/arduino.ar"   $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

Calibration_MPU6050_DUE.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"C:/Programs/Arduino-1.5.6r2/hardware/tools/gcc-arm-none-eabi-4.8.3-2014q1/bin/arm-none-eabi-gcc" -Os -Wl,--gc-sections -mcpu=cortex-m3 "-T/C:/Programs/Arduino-1.5.6r2/hardware/arduino/sam/variants/arduino_due_x/linker_scripts/gcc/flash.ld" "-Wl,-Map,C:/Programming/Workspace/Eclipse_C++_Arduino_v2.2/Calibration_MPU6050_DUE/Release/Calibration_MPU6050_DUE.map"  -o "C:/Programming/Workspace/Eclipse_C++_Arduino_v2.2/Calibration_MPU6050_DUE/Release/Calibration_MPU6050_DUE.elf" "-LC:/Programming/Workspace/Eclipse_C++_Arduino_v2.2/Calibration_MPU6050_DUE/Release" -mthumb -Wl,--cref -Wl,--check-sections -Wl,--gc-sections -Wl,--entry=Reset_Handler -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-section-align -Wl,--warn-unresolved-symbols -Wl,--start-group "C:/Programming/Workspace/Eclipse_C++_Arduino_v2.2/Calibration_MPU6050_DUE/Release/arduino/syscalls_sam3.c.o"   $(LINK_OBJ) $(AR)  "/C:/Programs/Arduino-1.5.6r2/hardware/arduino/sam/variants/arduino_due_x/libsam_sam3x8e_gcc_rel.a" "C:/Programming/Workspace/Eclipse_C++_Arduino_v2.2/Calibration_MPU6050_DUE/Release/arduino.ar" -Wl,--end-group -lm -gcc
	@echo 'Finished building: $@'
	@echo ' '

Calibration_MPU6050_DUE.eep: $(ELF)
	@echo 'Create eeprom image'
	${A.RECIPE.OBJCOPY.EEP.PATTERN}
	@echo 'Finished building: $@'
	@echo ' '

Calibration_MPU6050_DUE.bin: $(EEP)
	@echo 'Create Flash image (ihex format)'
	"C:/Programs/Arduino-1.5.6r2/hardware/tools/gcc-arm-none-eabi-4.8.3-2014q1/bin/arm-none-eabi-objcopy" -O binary  "C:/Programming/Workspace/Eclipse_C++_Arduino_v2.2/Calibration_MPU6050_DUE/Release/Calibration_MPU6050_DUE.elf" "C:/Programming/Workspace/Eclipse_C++_Arduino_v2.2/Calibration_MPU6050_DUE/Release/Calibration_MPU6050_DUE.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(C_DEPS)$(AR)$(EEP)$(FLASH_IMAGE)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(SIZEDUMMY)$(ELF)$(CPP_DEPS) Calibration_MPU6050_DUE
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
