################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/avr-libc/malloc.c \
C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/avr-libc/realloc.c 

C_DEPS += \
./arduino/malloc.c.d \
./arduino/realloc.c.d 

AR_OBJ += \
./arduino/malloc.c.o \
./arduino/realloc.c.o 


# Each subdirectory must supply rules for building sources it contributes
arduino/malloc.c.o: C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/avr-libc/malloc.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"C:/Programs/Arduino/hardware/tools/avr/bin/avr-gcc" -c -g -Os -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=157 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"C:\Programs\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Programs\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -I"C:\Programs\Arduino\libraries\I2Cdev" -I"C:\Programs\Arduino\libraries\MPU6050" -I"C:\Programs\Arduino\libraries\Servo" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire\utility" -I"C:\Programs\Arduino\libraries\PID_v1" -I"C:\Programs\Arduino\libraries\ArduinoCommunication" -I"C:\Programs\Arduino\libraries\Servo\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"   -w
	@echo 'Finished building: $<'
	@echo ' '

arduino/realloc.c.o: C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/avr-libc/realloc.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"C:/Programs/Arduino/hardware/tools/avr/bin/avr-gcc" -c -g -Os -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=157 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"C:\Programs\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Programs\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -I"C:\Programs\Arduino\libraries\I2Cdev" -I"C:\Programs\Arduino\libraries\MPU6050" -I"C:\Programs\Arduino\libraries\Servo" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire\utility" -I"C:\Programs\Arduino\libraries\PID_v1" -I"C:\Programs\Arduino\libraries\ArduinoCommunication" -I"C:\Programs\Arduino\libraries\Servo\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"   -w
	@echo 'Finished building: $<'
	@echo ' '


