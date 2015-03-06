################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/Programming/Arduino/libraries/Led/LedPanel.cpp 

LINK_OBJ += \
./Libraries/Led/LedPanel.cpp.o 

CPP_DEPS += \
./Libraries/Led/LedPanel.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/Led/LedPanel.cpp.o: C:/Programming/Arduino/libraries/Led/LedPanel.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Programs/Arduino-1.5.6r2/hardware/teensy/tools/windows/arm-none-eabi/bin/arm-none-eabi-g++" -c -g -Os -ffunction-sections -fdata-sections -nostdlib -fno-rtti -fno-exceptions -mcpu=cortex-m4 -DF_CPU=96000000 -DUSB_SERIAL -DLAYOUT_US_ENGLISH -MMD -DARDUINO=156-r2  -mthumb  -D__MK20DX256__  -felide-constructors -std=gnu++0x -DTEENSYDUINO=120   -I"C:\Programs\Arduino-1.5.6r2\hardware\teensy\all\cores\teensy3" -I"C:\Programming\Arduino\libraries\IMU_MPU9150v6.1" -I"C:\Programming\Arduino\libraries\Math" -I"C:\Programming\Arduino\libraries\Led" -I"C:\Programming\Arduino\libraries\Mavlink" -I"C:\Programming\Arduino\libraries\MotorsQuadX" -I"C:\Programming\Arduino\libraries\Thread" -I"C:\Programming\Arduino\libraries\I2Cdev_Teensy" -I"C:\Programming\Arduino\libraries\PID_v2" -I"C:\Programming\Arduino\libraries\RC_Channel" -I"C:\Programming\Arduino\libraries\HIL" -I"C:\Programming\Arduino\libraries\AttitudeControl" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '


