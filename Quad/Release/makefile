################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include arduino/core/avr-libc/subdir.mk
-include arduino/core/subdir.mk
-include Libraries/Wire/utility/subdir.mk
-include Libraries/Wire/subdir.mk
-include Libraries/SoftwareSerial/subdir.mk
-include Libraries/Servo/src/sam/subdir.mk
-include Libraries/Servo/src/avr/subdir.mk
-include Libraries/PID_v1/subdir.mk
-include Libraries/MPU6050/subdir.mk
-include Libraries/I2Cdev/subdir.mk
-include Libraries/ArduinoCommunication/subdir.mk
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
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
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
C:/Users/Juraj/Documents/Workspace/Eclipse_C++_Arduino/Quad/Release/arduino.ar \

ELF += \
Quad.elf \

EEP += \
Quad.eep \

FLASH_IMAGE += \
Quad.hex \


# All Target
all: Quad

# Tool invocations
Quad: $(FLASH_IMAGE)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"C:/Programs/Arduino/hardware/tools/avr/bin/avr-size" -A "C:/Users/Juraj/Documents/Workspace/Eclipse_C++_Arduino/Quad/Release/Quad.elf"
	@echo 'Finished building target: $@'
	@echo ' '

C:/Users/Juraj/Documents/Workspace/Eclipse_C++_Arduino/Quad/Release/arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"C:/Programs/Arduino/hardware/tools/avr/bin/avr-ar" rcs  "C:/Users/Juraj/Documents/Workspace/Eclipse_C++_Arduino/Quad/Release/arduino.ar"   $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

Quad.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"C:/Programs/Arduino/hardware/tools/avr/bin/avr-gcc" -Os -Wl,--gc-sections -mmcu=atmega328p  -o "C:/Users/Juraj/Documents/Workspace/Eclipse_C++_Arduino/Quad/Release/Quad.elf"   $(LINK_OBJ) $(AR)  "C:/Users/Juraj/Documents/Workspace/Eclipse_C++_Arduino/Quad/Release/arduino.ar" "-LC:/Users/Juraj/Documents/Workspace/Eclipse_C++_Arduino/Quad/Release" -lm
	@echo 'Finished building: $@'
	@echo ' '

Quad.eep: $(ELF)
	@echo 'Create eeprom image'
	"C:/Programs/Arduino/hardware/tools/avr/bin/avr-objcopy" -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0  "C:/Users/Juraj/Documents/Workspace/Eclipse_C++_Arduino/Quad/Release/Quad.elf" "C:/Users/Juraj/Documents/Workspace/Eclipse_C++_Arduino/Quad/Release/Quad.eep"
	@echo 'Finished building: $@'
	@echo ' '

Quad.hex: $(EEP)
	@echo 'Create Flash image (ihex format)'
	"C:/Programs/Arduino/hardware/tools/avr/bin/avr-objcopy" -O ihex -R .eeprom  "C:/Users/Juraj/Documents/Workspace/Eclipse_C++_Arduino/Quad/Release/Quad.elf" "C:/Users/Juraj/Documents/Workspace/Eclipse_C++_Arduino/Quad/Release/Quad.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(C_DEPS)$(AR)$(EEP)$(FLASH_IMAGE)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(ASM_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(ELF)$(CPP_DEPS) Quad
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
