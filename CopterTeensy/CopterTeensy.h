#ifndef _CopterTeensy_H_
#define _CopterTeensy_H_

#define TEENSY

#include "Config.hpp"
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

#ifdef GCS_COM_USB
GCS_USB GCS(Serial);
#elif defined GCS_COM_BLUETOOTH
GCS_BLUETOOTH GCS(Serial1);
#else
#error "ERROR"
#endif

Parameters con;
IMU_MPU9150 imu;
MotorsQuadX motorsQuad(&con.rc1, &con.rc2, &con.rc3, &con.rc4);
AttitudeControl attitudeControl(imu, motorsQuad, &con.stab_pid, &con.rate_pid);

//LedPanel ledMiddle(LED3);
//LedPanel ledLeft(LED2);
//LedPanel ledRight(LED1);

LedPanel leds(LED1,LED2,LED3);

const Mav_Param::Info var_info[] =
{
	GSCALAR(throttle_min, "throttle_min", 1000),
	GSCALAR(throttle_max, "throttle_max", 1500),
	GGROUP(rc1, "RC1_", RC_Channel),
	GGROUP(rc2, "RC2_", RC_Channel),
	GGROUP(rc3, "RC3_", RC_Channel),
	GGROUP(rc4, "RC4_", RC_Channel),
	GGROUP(rate_pid.ROLL, "roll_rate_", PID),GGROUP(rate_pid.PITCH, "pitch_rate_", PID),GGROUP(rate_pid.YAW, "yaw_rate_", PID),
	GGROUP(stab_pid.ROLL, "roll_stab_", PID),GGROUP(stab_pid.PITCH, "pitch_stab_", PID),GGROUP(stab_pid.YAW, "yaw_stab_", PID),
	GOBJECT(attitudeControl, "ATC_",AttitudeControl),
	GOBJECT(imu, "IMU_",IMU_MPU9150),
	VAREND
};

#endif /* _CopterTeensy_H_ */
