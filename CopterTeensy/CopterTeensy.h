#ifndef _CopterTeensy_H_
#define _CopterTeensy_H_

#define TEENSY


#include <Arduino.h>

#include <PID.hpp>
#include <MPU9150Lib.h>
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

MPU9150Lib imu;
MotorsQuad motorsQuad(&con.rc1,&con.rc2,&con.rc3,&con.rc4);
Mav_Param param_loader(var_info);
GCS_Mavlink GCS;

#endif /* _CopterTeensy_H_ */
