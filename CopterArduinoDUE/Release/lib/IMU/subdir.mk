################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lib/IMU/MPU6050.cpp \
../lib/IMU/MPU6050_6Axis_MotionApps20.cpp 

LINK_OBJ += \
./lib/IMU/MPU6050.cpp.o \
./lib/IMU/MPU6050_6Axis_MotionApps20.cpp.o 

CPP_DEPS += \
./lib/IMU/MPU6050.cpp.d \
./lib/IMU/MPU6050_6Axis_MotionApps20.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
lib/IMU/MPU6050.cpp.o: ../lib/IMU/MPU6050.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Programs/Arduino-1.5.6r2/hardware/tools/g++_arm_none_eabi/bin/arm-none-eabi-g++" -c -g -Os -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -Dprintf=iprintf -mcpu=cortex-m3 -DF_CPU=84000000L -DARDUINO=156-r2 -DARDUINO_SAM_DUE -DARDUINO_ARCH_SAM -D__SAM3X8E__ -mthumb -DUSB_VID=0x2341 -DUSB_PID=0x003e -DUSBCON '-DUSB_MANUFACTURER="Unknown"' '-DUSB_PRODUCT="Arduino Due"' "-IC:/Programs/Arduino-1.5.6r2/hardware/arduino/sam/system/libsam" "-IC:/Programs/Arduino-1.5.6r2/hardware/arduino/sam/system/CMSIS/CMSIS/Include/" "-IC:/Programs/Arduino-1.5.6r2/hardware/arduino/sam/system/CMSIS/Device/ATMEL/"   -I"C:\Programs\Arduino-1.5.6r2\hardware\arduino\sam\cores\arduino" -I"C:\Users\Juraj\Workspace\Programming\Eclipse_C++_Arduino\CopterArduinoDUE\lib\Config" -I"C:\Users\Juraj\Workspace\Programming\Eclipse_C++_Arduino\CopterArduinoDUE\lib\I2C" -I"C:\Users\Juraj\Workspace\Programming\Eclipse_C++_Arduino\CopterArduinoDUE\lib\IMU" -I"C:\Users\Juraj\Workspace\Programming\Eclipse_C++_Arduino\CopterArduinoDUE\lib\Mavlink" -I"C:\Users\Juraj\Workspace\Programming\Eclipse_C++_Arduino\CopterArduinoDUE\lib\MotorESC" -I"C:\Users\Juraj\Workspace\Programming\Eclipse_C++_Arduino\CopterArduinoDUE\lib\PID" -I"C:\Users\Juraj\Workspace\Programming\Eclipse_C++_Arduino\CopterArduinoDUE\lib\Thread" -I"C:\Programs\Arduino-1.5.6r2\hardware\arduino\sam\variants\arduino_due_x" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

lib/IMU/MPU6050_6Axis_MotionApps20.cpp.o: ../lib/IMU/MPU6050_6Axis_MotionApps20.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Programs/Arduino-1.5.6r2/hardware/tools/g++_arm_none_eabi/bin/arm-none-eabi-g++" -c -g -Os -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -Dprintf=iprintf -mcpu=cortex-m3 -DF_CPU=84000000L -DARDUINO=156-r2 -DARDUINO_SAM_DUE -DARDUINO_ARCH_SAM -D__SAM3X8E__ -mthumb -DUSB_VID=0x2341 -DUSB_PID=0x003e -DUSBCON '-DUSB_MANUFACTURER="Unknown"' '-DUSB_PRODUCT="Arduino Due"' "-IC:/Programs/Arduino-1.5.6r2/hardware/arduino/sam/system/libsam" "-IC:/Programs/Arduino-1.5.6r2/hardware/arduino/sam/system/CMSIS/CMSIS/Include/" "-IC:/Programs/Arduino-1.5.6r2/hardware/arduino/sam/system/CMSIS/Device/ATMEL/"   -I"C:\Programs\Arduino-1.5.6r2\hardware\arduino\sam\cores\arduino" -I"C:\Users\Juraj\Workspace\Programming\Eclipse_C++_Arduino\CopterArduinoDUE\lib\Config" -I"C:\Users\Juraj\Workspace\Programming\Eclipse_C++_Arduino\CopterArduinoDUE\lib\I2C" -I"C:\Users\Juraj\Workspace\Programming\Eclipse_C++_Arduino\CopterArduinoDUE\lib\IMU" -I"C:\Users\Juraj\Workspace\Programming\Eclipse_C++_Arduino\CopterArduinoDUE\lib\Mavlink" -I"C:\Users\Juraj\Workspace\Programming\Eclipse_C++_Arduino\CopterArduinoDUE\lib\MotorESC" -I"C:\Users\Juraj\Workspace\Programming\Eclipse_C++_Arduino\CopterArduinoDUE\lib\PID" -I"C:\Users\Juraj\Workspace\Programming\Eclipse_C++_Arduino\CopterArduinoDUE\lib\Thread" -I"C:\Programs\Arduino-1.5.6r2\hardware\arduino\sam\variants\arduino_due_x" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '


