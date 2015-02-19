#ifndef _CopterTeensy_H_
#define _CopterTeensy_H_

#define TEENSY


#include <HIL.hpp>
#include <LedPanel.hpp>

#include <AttitudeControl.hpp>

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


MPU9150lib imu;
MotorsQuadX motorsQuad(&con.rc1,&con.rc2,&con.rc3,&con.rc4);

//AttitudeControl attitudeControl(imu,motorsQuad,
//																&con.rate_pid_yaw,&con.rate_pid_pitch,&con.rate_pid_roll,
//																&con.stab_pid_yaw,&con.stab_pid_pitch,&con.stab_pid_roll);

AttitudeControl attitudeControl(imu,motorsQuad,
																&con.stab_pid,&con.rate_pid);

LedPanel ledMiddle(LED3);
LedPanel ledLeft(LED2);
LedPanel ledRight(LED1);



#endif /* _CopterTeensy_H_ */
