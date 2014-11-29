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

#include <GCS_Mavlink.hpp>
#include "Parameters_Init.hpp"

//Motors controll class
#include <MotorESC.h>

//Configuration file and typedefinitions file
#include "Config.h"
#include <Typedef.hpp>

#include <Thread.h>

#ifdef __cplusplus
extern "C"
{
#endif
	void loop();
	void setup();
#ifdef __cplusplus
}  // extern "C"
#endif

////////////////////////////////////////////////////FlightControll//////////////////////////////////////////////////
//
PID roll_pid(	&param_container.attitude_t.roll,
							&param_container.roll_pidOutput._value,
							&param_container.manual_rcY._value,
							&param_container.roll_kP._value,
							&param_container.roll_kI._value,
							&param_container.roll_kD._value,
							DIRECT);
PID pitch_pid(&param_container.attitude_t.pitch,
							&param_container.pitch_pidOutput._value,
							&param_container.manual_rcX._value,
							&param_container.pitch_kP._value,
							&param_container.pitch_kI._value,
							&param_container.pitch_kD._value,
							DIRECT);
//PID yaw_pid(&param_container.attitude_t.yaw, &param_container.yaw_pidOutput._value, &param_container.manual_rcR._value, &param_container.yaw_kP._value, &param_container.yaw_kI._value, &param_container.yaw_kD._value,
//DIRECT);
//
//

////////////////////////////////////////////////////FlightControll//////////////////////////////////////////////////

GCS_Mavlink GCS;

#endif /* _Quadcopter_H_ */
