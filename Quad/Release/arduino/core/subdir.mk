################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/CDC.cpp \
C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/HID.cpp \
C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/HardwareSerial.cpp \
C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/HardwareSerial0.cpp \
C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/HardwareSerial1.cpp \
C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/HardwareSerial2.cpp \
C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/HardwareSerial3.cpp \
C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/IPAddress.cpp \
C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/Print.cpp \
C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/Stream.cpp \
C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/Tone.cpp \
C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/USBCore.cpp \
C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/WMath.cpp \
C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/WString.cpp \
C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/main.cpp \
C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/new.cpp 

C_SRCS += \
C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/WInterrupts.c \
C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/hooks.c \
C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/wiring.c \
C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/wiring_analog.c \
C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/wiring_digital.c \
C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/wiring_pulse.c \
C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/wiring_shift.c 

C_DEPS += \
./arduino/WInterrupts.c.d \
./arduino/hooks.c.d \
./arduino/wiring.c.d \
./arduino/wiring_analog.c.d \
./arduino/wiring_digital.c.d \
./arduino/wiring_pulse.c.d \
./arduino/wiring_shift.c.d 

AR_OBJ += \
./arduino/CDC.cpp.o \
./arduino/HID.cpp.o \
./arduino/HardwareSerial.cpp.o \
./arduino/HardwareSerial0.cpp.o \
./arduino/HardwareSerial1.cpp.o \
./arduino/HardwareSerial2.cpp.o \
./arduino/HardwareSerial3.cpp.o \
./arduino/IPAddress.cpp.o \
./arduino/Print.cpp.o \
./arduino/Stream.cpp.o \
./arduino/Tone.cpp.o \
./arduino/USBCore.cpp.o \
./arduino/WInterrupts.c.o \
./arduino/WMath.cpp.o \
./arduino/WString.cpp.o \
./arduino/hooks.c.o \
./arduino/main.cpp.o \
./arduino/new.cpp.o \
./arduino/wiring.c.o \
./arduino/wiring_analog.c.o \
./arduino/wiring_digital.c.o \
./arduino/wiring_pulse.c.o \
./arduino/wiring_shift.c.o 

CPP_DEPS += \
./arduino/CDC.cpp.d \
./arduino/HID.cpp.d \
./arduino/HardwareSerial.cpp.d \
./arduino/HardwareSerial0.cpp.d \
./arduino/HardwareSerial1.cpp.d \
./arduino/HardwareSerial2.cpp.d \
./arduino/HardwareSerial3.cpp.d \
./arduino/IPAddress.cpp.d \
./arduino/Print.cpp.d \
./arduino/Stream.cpp.d \
./arduino/Tone.cpp.d \
./arduino/USBCore.cpp.d \
./arduino/WMath.cpp.d \
./arduino/WString.cpp.d \
./arduino/main.cpp.d \
./arduino/new.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
arduino/CDC.cpp.o: C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/CDC.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Programs/Arduino/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=157 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"C:\Programs\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Programs\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -I"C:\Programs\Arduino\libraries\I2Cdev" -I"C:\Programs\Arduino\libraries\MPU6050" -I"C:\Programs\Arduino\libraries\Servo" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire\utility" -I"C:\Programs\Arduino\libraries\PID_v1" -I"C:\Programs\Arduino\libraries\ArduinoCommunication" -I"C:\Programs\Arduino\libraries\Servo\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -w
	@echo 'Finished building: $<'
	@echo ' '

arduino/HID.cpp.o: C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/HID.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Programs/Arduino/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=157 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"C:\Programs\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Programs\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -I"C:\Programs\Arduino\libraries\I2Cdev" -I"C:\Programs\Arduino\libraries\MPU6050" -I"C:\Programs\Arduino\libraries\Servo" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire\utility" -I"C:\Programs\Arduino\libraries\PID_v1" -I"C:\Programs\Arduino\libraries\ArduinoCommunication" -I"C:\Programs\Arduino\libraries\Servo\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -w
	@echo 'Finished building: $<'
	@echo ' '

arduino/HardwareSerial.cpp.o: C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/HardwareSerial.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Programs/Arduino/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=157 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"C:\Programs\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Programs\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -I"C:\Programs\Arduino\libraries\I2Cdev" -I"C:\Programs\Arduino\libraries\MPU6050" -I"C:\Programs\Arduino\libraries\Servo" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire\utility" -I"C:\Programs\Arduino\libraries\PID_v1" -I"C:\Programs\Arduino\libraries\ArduinoCommunication" -I"C:\Programs\Arduino\libraries\Servo\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -w
	@echo 'Finished building: $<'
	@echo ' '

arduino/HardwareSerial0.cpp.o: C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/HardwareSerial0.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Programs/Arduino/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=157 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"C:\Programs\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Programs\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -I"C:\Programs\Arduino\libraries\I2Cdev" -I"C:\Programs\Arduino\libraries\MPU6050" -I"C:\Programs\Arduino\libraries\Servo" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire\utility" -I"C:\Programs\Arduino\libraries\PID_v1" -I"C:\Programs\Arduino\libraries\ArduinoCommunication" -I"C:\Programs\Arduino\libraries\Servo\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -w
	@echo 'Finished building: $<'
	@echo ' '

arduino/HardwareSerial1.cpp.o: C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/HardwareSerial1.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Programs/Arduino/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=157 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"C:\Programs\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Programs\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -I"C:\Programs\Arduino\libraries\I2Cdev" -I"C:\Programs\Arduino\libraries\MPU6050" -I"C:\Programs\Arduino\libraries\Servo" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire\utility" -I"C:\Programs\Arduino\libraries\PID_v1" -I"C:\Programs\Arduino\libraries\ArduinoCommunication" -I"C:\Programs\Arduino\libraries\Servo\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -w
	@echo 'Finished building: $<'
	@echo ' '

arduino/HardwareSerial2.cpp.o: C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/HardwareSerial2.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Programs/Arduino/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=157 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"C:\Programs\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Programs\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -I"C:\Programs\Arduino\libraries\I2Cdev" -I"C:\Programs\Arduino\libraries\MPU6050" -I"C:\Programs\Arduino\libraries\Servo" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire\utility" -I"C:\Programs\Arduino\libraries\PID_v1" -I"C:\Programs\Arduino\libraries\ArduinoCommunication" -I"C:\Programs\Arduino\libraries\Servo\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -w
	@echo 'Finished building: $<'
	@echo ' '

arduino/HardwareSerial3.cpp.o: C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/HardwareSerial3.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Programs/Arduino/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=157 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"C:\Programs\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Programs\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -I"C:\Programs\Arduino\libraries\I2Cdev" -I"C:\Programs\Arduino\libraries\MPU6050" -I"C:\Programs\Arduino\libraries\Servo" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire\utility" -I"C:\Programs\Arduino\libraries\PID_v1" -I"C:\Programs\Arduino\libraries\ArduinoCommunication" -I"C:\Programs\Arduino\libraries\Servo\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -w
	@echo 'Finished building: $<'
	@echo ' '

arduino/IPAddress.cpp.o: C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/IPAddress.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Programs/Arduino/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=157 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"C:\Programs\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Programs\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -I"C:\Programs\Arduino\libraries\I2Cdev" -I"C:\Programs\Arduino\libraries\MPU6050" -I"C:\Programs\Arduino\libraries\Servo" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire\utility" -I"C:\Programs\Arduino\libraries\PID_v1" -I"C:\Programs\Arduino\libraries\ArduinoCommunication" -I"C:\Programs\Arduino\libraries\Servo\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -w
	@echo 'Finished building: $<'
	@echo ' '

arduino/Print.cpp.o: C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/Print.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Programs/Arduino/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=157 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"C:\Programs\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Programs\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -I"C:\Programs\Arduino\libraries\I2Cdev" -I"C:\Programs\Arduino\libraries\MPU6050" -I"C:\Programs\Arduino\libraries\Servo" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire\utility" -I"C:\Programs\Arduino\libraries\PID_v1" -I"C:\Programs\Arduino\libraries\ArduinoCommunication" -I"C:\Programs\Arduino\libraries\Servo\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -w
	@echo 'Finished building: $<'
	@echo ' '

arduino/Stream.cpp.o: C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/Stream.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Programs/Arduino/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=157 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"C:\Programs\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Programs\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -I"C:\Programs\Arduino\libraries\I2Cdev" -I"C:\Programs\Arduino\libraries\MPU6050" -I"C:\Programs\Arduino\libraries\Servo" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire\utility" -I"C:\Programs\Arduino\libraries\PID_v1" -I"C:\Programs\Arduino\libraries\ArduinoCommunication" -I"C:\Programs\Arduino\libraries\Servo\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -w
	@echo 'Finished building: $<'
	@echo ' '

arduino/Tone.cpp.o: C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/Tone.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Programs/Arduino/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=157 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"C:\Programs\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Programs\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -I"C:\Programs\Arduino\libraries\I2Cdev" -I"C:\Programs\Arduino\libraries\MPU6050" -I"C:\Programs\Arduino\libraries\Servo" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire\utility" -I"C:\Programs\Arduino\libraries\PID_v1" -I"C:\Programs\Arduino\libraries\ArduinoCommunication" -I"C:\Programs\Arduino\libraries\Servo\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -w
	@echo 'Finished building: $<'
	@echo ' '

arduino/USBCore.cpp.o: C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/USBCore.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Programs/Arduino/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=157 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"C:\Programs\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Programs\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -I"C:\Programs\Arduino\libraries\I2Cdev" -I"C:\Programs\Arduino\libraries\MPU6050" -I"C:\Programs\Arduino\libraries\Servo" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire\utility" -I"C:\Programs\Arduino\libraries\PID_v1" -I"C:\Programs\Arduino\libraries\ArduinoCommunication" -I"C:\Programs\Arduino\libraries\Servo\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -w
	@echo 'Finished building: $<'
	@echo ' '

arduino/WInterrupts.c.o: C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/WInterrupts.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"C:/Programs/Arduino/hardware/tools/avr/bin/avr-gcc" -c -g -Os -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=157 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"C:\Programs\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Programs\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -I"C:\Programs\Arduino\libraries\I2Cdev" -I"C:\Programs\Arduino\libraries\MPU6050" -I"C:\Programs\Arduino\libraries\Servo" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire\utility" -I"C:\Programs\Arduino\libraries\PID_v1" -I"C:\Programs\Arduino\libraries\ArduinoCommunication" -I"C:\Programs\Arduino\libraries\Servo\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"   -w
	@echo 'Finished building: $<'
	@echo ' '

arduino/WMath.cpp.o: C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/WMath.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Programs/Arduino/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=157 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"C:\Programs\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Programs\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -I"C:\Programs\Arduino\libraries\I2Cdev" -I"C:\Programs\Arduino\libraries\MPU6050" -I"C:\Programs\Arduino\libraries\Servo" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire\utility" -I"C:\Programs\Arduino\libraries\PID_v1" -I"C:\Programs\Arduino\libraries\ArduinoCommunication" -I"C:\Programs\Arduino\libraries\Servo\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -w
	@echo 'Finished building: $<'
	@echo ' '

arduino/WString.cpp.o: C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/WString.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Programs/Arduino/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=157 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"C:\Programs\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Programs\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -I"C:\Programs\Arduino\libraries\I2Cdev" -I"C:\Programs\Arduino\libraries\MPU6050" -I"C:\Programs\Arduino\libraries\Servo" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire\utility" -I"C:\Programs\Arduino\libraries\PID_v1" -I"C:\Programs\Arduino\libraries\ArduinoCommunication" -I"C:\Programs\Arduino\libraries\Servo\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -w
	@echo 'Finished building: $<'
	@echo ' '

arduino/hooks.c.o: C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/hooks.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"C:/Programs/Arduino/hardware/tools/avr/bin/avr-gcc" -c -g -Os -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=157 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"C:\Programs\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Programs\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -I"C:\Programs\Arduino\libraries\I2Cdev" -I"C:\Programs\Arduino\libraries\MPU6050" -I"C:\Programs\Arduino\libraries\Servo" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire\utility" -I"C:\Programs\Arduino\libraries\PID_v1" -I"C:\Programs\Arduino\libraries\ArduinoCommunication" -I"C:\Programs\Arduino\libraries\Servo\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"   -w
	@echo 'Finished building: $<'
	@echo ' '

arduino/main.cpp.o: C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/main.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Programs/Arduino/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=157 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"C:\Programs\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Programs\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -I"C:\Programs\Arduino\libraries\I2Cdev" -I"C:\Programs\Arduino\libraries\MPU6050" -I"C:\Programs\Arduino\libraries\Servo" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire\utility" -I"C:\Programs\Arduino\libraries\PID_v1" -I"C:\Programs\Arduino\libraries\ArduinoCommunication" -I"C:\Programs\Arduino\libraries\Servo\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -w
	@echo 'Finished building: $<'
	@echo ' '

arduino/new.cpp.o: C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/new.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Programs/Arduino/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=157 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"C:\Programs\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Programs\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -I"C:\Programs\Arduino\libraries\I2Cdev" -I"C:\Programs\Arduino\libraries\MPU6050" -I"C:\Programs\Arduino\libraries\Servo" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire\utility" -I"C:\Programs\Arduino\libraries\PID_v1" -I"C:\Programs\Arduino\libraries\ArduinoCommunication" -I"C:\Programs\Arduino\libraries\Servo\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -w
	@echo 'Finished building: $<'
	@echo ' '

arduino/wiring.c.o: C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/wiring.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"C:/Programs/Arduino/hardware/tools/avr/bin/avr-gcc" -c -g -Os -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=157 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"C:\Programs\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Programs\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -I"C:\Programs\Arduino\libraries\I2Cdev" -I"C:\Programs\Arduino\libraries\MPU6050" -I"C:\Programs\Arduino\libraries\Servo" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire\utility" -I"C:\Programs\Arduino\libraries\PID_v1" -I"C:\Programs\Arduino\libraries\ArduinoCommunication" -I"C:\Programs\Arduino\libraries\Servo\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"   -w
	@echo 'Finished building: $<'
	@echo ' '

arduino/wiring_analog.c.o: C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/wiring_analog.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"C:/Programs/Arduino/hardware/tools/avr/bin/avr-gcc" -c -g -Os -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=157 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"C:\Programs\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Programs\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -I"C:\Programs\Arduino\libraries\I2Cdev" -I"C:\Programs\Arduino\libraries\MPU6050" -I"C:\Programs\Arduino\libraries\Servo" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire\utility" -I"C:\Programs\Arduino\libraries\PID_v1" -I"C:\Programs\Arduino\libraries\ArduinoCommunication" -I"C:\Programs\Arduino\libraries\Servo\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"   -w
	@echo 'Finished building: $<'
	@echo ' '

arduino/wiring_digital.c.o: C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/wiring_digital.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"C:/Programs/Arduino/hardware/tools/avr/bin/avr-gcc" -c -g -Os -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=157 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"C:\Programs\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Programs\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -I"C:\Programs\Arduino\libraries\I2Cdev" -I"C:\Programs\Arduino\libraries\MPU6050" -I"C:\Programs\Arduino\libraries\Servo" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire\utility" -I"C:\Programs\Arduino\libraries\PID_v1" -I"C:\Programs\Arduino\libraries\ArduinoCommunication" -I"C:\Programs\Arduino\libraries\Servo\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"   -w
	@echo 'Finished building: $<'
	@echo ' '

arduino/wiring_pulse.c.o: C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/wiring_pulse.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"C:/Programs/Arduino/hardware/tools/avr/bin/avr-gcc" -c -g -Os -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=157 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"C:\Programs\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Programs\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -I"C:\Programs\Arduino\libraries\I2Cdev" -I"C:\Programs\Arduino\libraries\MPU6050" -I"C:\Programs\Arduino\libraries\Servo" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire\utility" -I"C:\Programs\Arduino\libraries\PID_v1" -I"C:\Programs\Arduino\libraries\ArduinoCommunication" -I"C:\Programs\Arduino\libraries\Servo\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"   -w
	@echo 'Finished building: $<'
	@echo ' '

arduino/wiring_shift.c.o: C:/Programs/Arduino/hardware/arduino/avr/cores/arduino/wiring_shift.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"C:/Programs/Arduino/hardware/tools/avr/bin/avr-gcc" -c -g -Os -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=157 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"C:\Programs\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Programs\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -I"C:\Programs\Arduino\libraries\I2Cdev" -I"C:\Programs\Arduino\libraries\MPU6050" -I"C:\Programs\Arduino\libraries\Servo" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire" -I"C:\Programs\Arduino\hardware\arduino\avr\libraries\Wire\utility" -I"C:\Programs\Arduino\libraries\PID_v1" -I"C:\Programs\Arduino\libraries\ArduinoCommunication" -I"C:\Programs\Arduino\libraries\Servo\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"   -w
	@echo 'Finished building: $<'
	@echo ' '


