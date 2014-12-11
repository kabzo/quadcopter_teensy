################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Calibration_MPU6050_Teensy.cpp 

LINK_OBJ += \
./Calibration_MPU6050_Teensy.cpp.o 

CPP_DEPS += \
./Calibration_MPU6050_Teensy.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
Calibration_MPU6050_Teensy.cpp.o: ../Calibration_MPU6050_Teensy.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Programs/Arduino-1.5.6r2/hardware/teensy/tools/windows/arm-none-eabi/bin/arm-none-eabi-g++" -c -g -Os -w -ffunction-sections -fdata-sections -nostdlib -fno-rtti -fno-exceptions -mcpu=cortex-m4 -DF_CPU=96000000 -DUSB_SERIAL -DLAYOUT_US_ENGLISH -MMD -DARDUINO=156-r2  -mthumb  -D__MK20DX256__  -felide-constructors -std=gnu++0x -DTEENSYDUINO=120   -I"C:\Programs\Arduino-1.5.6r2\hardware\teensy\all\cores\teensy3" -I"C:\Programming\Arduino\libraries\i2c_t3" -I"C:\Programming\Arduino\libraries\I2Cdev" -I"C:\Programming\Arduino\libraries\MPU6050" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


