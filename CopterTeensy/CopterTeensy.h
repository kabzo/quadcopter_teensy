#ifndef _CopterTeensy_H_
#define _CopterTeensy_H_

#define TEENSY
#define DEBUG(X,Y) Serial.print(X); Serial.print(Y)
#define DEBUGLN(X,Y) Serial.print(X); Serial.println(Y)

#include <Arduino.h>

#include <PID.hpp>
#include <IMU.h>
#include <RC_Channel.h>
#include <Thread.h>
#include <MotorESC.h>
#include <GCS_Mavlink.hpp>

#include "Parameters_Init.hpp"

#ifdef __cplusplus
extern "C"
{
#endif
	void loop();
	void setup();
#ifdef __cplusplus
}  // extern "C"
#endif

IMU imu;
MotorsQuad motorsQuad;
Mav_Param param_loader(var_info);
GCS_Mavlink GCS;

#endif /* _CopterTeensy_H_ */
