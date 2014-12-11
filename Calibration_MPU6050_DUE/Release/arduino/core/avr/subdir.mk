################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Programs/Arduino-1.5.6r2/hardware/arduino/sam/cores/arduino/avr/dtostrf.c 

C_DEPS += \
./arduino/dtostrf.c.d 

AR_OBJ += \
./arduino/dtostrf.c.o 


# Each subdirectory must supply rules for building sources it contributes
arduino/dtostrf.c.o: C:/Programs/Arduino-1.5.6r2/hardware/arduino/sam/cores/arduino/avr/dtostrf.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"C:/Programs/Arduino-1.5.6r2/hardware/tools/gcc-arm-none-eabi-4.8.3-2014q1/bin/arm-none-eabi-gcc" -c -g -Os -w -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -Dprintf=iprintf -mcpu=cortex-m3 -DF_CPU=84000000L -DARDUINO=156-r2 -DARDUINO_SAM_DUE -DARDUINO_ARCH_SAM  -D__SAM3X8E__ -mthumb -DUSB_VID=0x2341 -DUSB_PID=0x003e -DUSBCON '-DUSB_MANUFACTURER="Unknown"' '-DUSB_PRODUCT="Arduino Due"' "-IC:/Programs/Arduino-1.5.6r2/hardware/arduino/sam/system/libsam" "-IC:/Programs/Arduino-1.5.6r2/hardware/arduino/sam/system/CMSIS/CMSIS/Include/" "-IC:/Programs/Arduino-1.5.6r2/hardware/arduino/sam/system/CMSIS/Device/ATMEL/"   -I"C:\Programs\Arduino-1.5.6r2\hardware\arduino\sam\cores\arduino" -I"C:\Programs\Arduino-1.5.6r2\hardware\arduino\sam\variants\arduino_due_x" -I"C:\Programming\Arduino\libraries\MPU6050" -I"C:\Programs\Arduino-1.5.6r2\hardware\arduino\sam\libraries\Wire" -I"C:\Programming\Arduino\libraries\I2Cdev_Arduino" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


