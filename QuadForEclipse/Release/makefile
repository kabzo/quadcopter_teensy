################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include lib/PID/subdir.mk
-include lib/MotorESC/subdir.mk
-include lib/IMU/subdir.mk
-include lib/I2C/subdir.mk
-include lib/ArduinoCommunication/subdir.mk
-include arduino/variant/subdir.mk
-include arduino/core/avr/subdir.mk
-include arduino/core/USB/subdir.mk
-include arduino/core/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
C:/Users/Juraj/Workspace/Eclipse_C++_Arduino/Quadcopter/Release/arduino.ar \

ELF += \
Quadcopter.elf \

EEP += \
Quadcopter.eep \

FLASH_IMAGE += \
Quadcopter.bin \


# All Target
all: Quadcopter

# Tool invocations
Quadcopter: $(FLASH_IMAGE)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"C:/Programs/Arduino/hardware/tools/g++_arm_none_eabi/bin/arm-none-eabi-size" -A "C:/Users/Juraj/Workspace/Eclipse_C++_Arduino/Quadcopter/Release/Quadcopter.elf"
	@echo 'Finished building target: $@'
	@echo ' '

C:/Users/Juraj/Workspace/Eclipse_C++_Arduino/Quadcopter/Release/arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"C:/Programs/Arduino/hardware/tools/g++_arm_none_eabi/bin/arm-none-eabi-ar" rcs "C:/Users/Juraj/Workspace/Eclipse_C++_Arduino/Quadcopter/Release/arduino.ar"   $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

Quadcopter.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"C:/Programs/Arduino/hardware/tools/g++_arm_none_eabi/bin/arm-none-eabi-g++" -Os -Wl,--gc-sections -mcpu=cortex-m3 "-T/C:/Programs/Arduino/hardware/arduino/sam/variants/arduino_due_x/linker_scripts/gcc/flash.ld" "-Wl,-Map,C:/Users/Juraj/Workspace/Eclipse_C++_Arduino/Quadcopter/Release/Quadcopter.map" -o "C:/Users/Juraj/Workspace/Eclipse_C++_Arduino/Quadcopter/Release/Quadcopter.elf" "-LC:/Users/Juraj/Workspace/Eclipse_C++_Arduino/Quadcopter/Release" -lm -lgcc -mthumb -Wl,--cref -Wl,--check-sections -Wl,--gc-sections -Wl,--entry=Reset_Handler -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-section-align -Wl,--warn-unresolved-symbols -Wl,--start-group "C:/Users/Juraj/Workspace/Eclipse_C++_Arduino/Quadcopter/Release/arduino/syscalls_sam3.c.o"   $(LINK_OBJ) $(AR)  "/C:/Programs/Arduino/hardware/arduino/sam/variants/arduino_due_x/libsam_sam3x8e_gcc_rel.a" "C:/Users/Juraj/Workspace/Eclipse_C++_Arduino/Quadcopter/Release/arduino.ar" -Wl,--end-group
	@echo 'Finished building: $@'
	@echo ' '

Quadcopter.eep: $(ELF)
	@echo 'Create eeprom image'
	${A.RECIPE.OBJCOPY.EEP.PATTERN}
	@echo 'Finished building: $@'
	@echo ' '

Quadcopter.bin: $(EEP)
	@echo 'Create Flash image (ihex format)'
	"C:/Programs/Arduino/hardware/tools/g++_arm_none_eabi/bin/arm-none-eabi-objcopy" -O binary "C:/Users/Juraj/Workspace/Eclipse_C++_Arduino/Quadcopter/Release/Quadcopter.elf" "C:/Users/Juraj/Workspace/Eclipse_C++_Arduino/Quadcopter/Release/Quadcopter.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_DEPS)$(AR)$(FLASH_IMAGE)$(EEP)$(CXX_DEPS)$(S_UPPER_DEPS)$(ELF)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(INO_DEPS)$(AR_OBJ)$(CPP_DEPS)$(PDE_DEPS)$(LINK_OBJ)$(C_UPPER_DEPS)$(SIZEDUMMY) Quadcopter
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
