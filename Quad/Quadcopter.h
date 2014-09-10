// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _Quadcopter_H_
#define _Quadcopter_H_

#include "Arduino.h"

//MPU6050
#ifndef IMU_H_
#include "IMU.h"
#endif

#ifndef PID_h
#include "PID.h"
#endif

//GUI communication
#include "ArduinoCommunication.h"

//Motors controll class
#include "MotorESC.h"

//Configuration file and typedefinitions file
#include "Config.h"
#include "Typedef.h"

#ifdef __cplusplus
extern "C" {
#endif
	void loop();
	void setup();
#ifdef __cplusplus
} // extern "C"
#endif

extern controlAngle rollControll;
extern controlAngle pitchControll;
extern controlAngle yawControll;

/////////////////////////FlightControll/////////////////////////
extern double throttle;

extern MotorESC motorBL;
extern MotorESC motorFL;
extern MotorESC motorFR;
extern MotorESC motorBR;

extern IMU imu;
/////////////////////////FlightControll/////////////////////////

/////////////////////////GUI Communication/////////////////////////
extern ArduinoCommunication arduinoCommunication;
/////////////////////////GUI Communication/////////////////////////
#endif /* _Quadcopter_H_ */
