/*
 * Include.h
 *
 *  Created on: 28.6.2014
 *      Author: Duri
 */

#ifndef INCLUDE_H_
#define INCLUDE_H_

#include "Arduino.h"

//MPU6050
#include "MPU6050_6Axis_MotionApps20.h"


//MotorControl
#include "Servo.h"
#include "PID_v1.h"

//I2C communication
#include "I2Cdev.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
	#include "Wire.h"
#endif
//GUI communication
#include "ArduinoCommunication.h"
//#include "SoftwareSerial.h"
#include "Config.h"

#endif /* INCLUDE_H_ */
