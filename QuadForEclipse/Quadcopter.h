#ifndef _Quadcopter_H_
#define _Quadcopter_H_

#include <Arduino.h>

//MPU6050
#ifndef IMU_H_
#include <IMU.h>
#endif
//#include <IMU.h>
#ifndef PID_h
#include <PID.h>
#endif

//GUI communication
#include <ArduinoCommunication.h>

//Motors controll class
#include <MotorESC.h>

//Configuration file and typedefinitions file
#include <Config.h>
#include <Typedef.h>

#ifdef __cplusplus
extern "C" {
#endif
	void loop();
	void setup();
#ifdef __cplusplus
} // extern "C"
#endif

//////////////////////////////////////////////////FlightControll//////////////////////////////////////////////////
controlAngle rollControll = { 0, 0, 0, PID(&(rollControll.angle), &(rollControll.output), &(rollControll.setpoint), 1,
		0, 0, DIRECT) };
controlAngle pitchControll = { 0, 0, 0, PID(&(pitchControll.angle), &(pitchControll.output), &(pitchControll.setpoint),
		0, 0, 0, DIRECT) };
controlAngle yawControll = { 0, 0, 0, PID(&(yawControll.angle), &(yawControll.output), &(yawControll.setpoint), 0, 0, 0,
DIRECT) };
double throttle = THROTTLE_MIN;

MotorESC motorBL(MPINBL, "motorBL");
MotorESC motorFL(MPINFL, "motorFL");
MotorESC motorFR(MPINFR, "motorFR");
MotorESC motorBR(MPINBR, "motorBR");
//////////////////////////////////////////////////FlightControll//////////////////////////////////////////////////

IMU imu(&(yawControll.angle), &(pitchControll.angle), &(rollControll.angle));

/////////////////////////GUI Communication/////////////////////////
ArduinoCommunication arduinoCommunication(&(rollControll), &(pitchControll), &(yawControll), &imu, &throttle,
		&(motorBR.speed_), &(motorBL.speed_), &(motorFR.speed_), &(motorFL.speed_));
/////////////////////////GUI Communication/////////////////////////
#endif /* _Quadcopter_H_ */
