/*
 * parameters.hpp
 *
 *  Created on: 1.11.2014
 *      Author: Juraj
 */

#ifndef COPTERTEENSY_PARAMETERS_INIT_HPP_
#define COPTERTEENSY_PARAMETERS_INIT_HPP_

#include <Mav_Param.hpp>
#include <mavlinkCommon/common/mavlink.h>

class Parameters
{
public:

	Parameters() :

					rc1(3, 1052, 1910), //roll
					rc2(4, 1173, 1867, true),	//pitch
					rc3(5, 1068, 1936), //throttle
					rc4(6, 1073, 1936),	//yaw
					stab_pid_roll(3.8, 0, 0,4500, 1500, DIRECT),
					stab_pid_pitch(3.8, 0, 0, 4500, 1500, DIRECT),
					stab_pid_yaw(3.8, 0, 0, 18000, 1500, DIRECT),

					rate_pid_pitch(0.15, 0.1, 0.004, 4500, 5, DIRECT),
					rate_pid_roll(0.15, 0.1, 0.004,4500, 5, DIRECT),
					rate_pid_yaw(0.2, 0.02, 0.0, 10000, 8, DIRECT)

	{

	}

	Mav_Float roll_pidOutput;
	Mav_Float pitch_pidOutput;
	Mav_Float yaw_pidOutput;

	Mav_Float throttle_min;
	Mav_Float throttle_max;

	RC_Channel rc1;
	RC_Channel rc2;
	RC_Channel rc3;
	RC_Channel rc4;

	PID stab_pid_roll;
	PID stab_pid_pitch;
	PID stab_pid_yaw;

	PID rate_pid_pitch;
	PID rate_pid_roll;
	PID rate_pid_yaw;

	Mav_Float targetHeading;

};

static Parameters con;

const Mav_Param::Info var_info[] = {

GSCALAR(roll_pidOutput, "roll_pidOutput", 0)
,
GSCALAR(pitch_pidOutput, "pitch_pidOutput", 0)
,
GSCALAR(yaw_pidOutput, "yaw_pidOutput", 0)
,

GSCALAR(throttle_min, "throttle_min", 1000)
,
GSCALAR(throttle_max, "throttle_max", 2000)
,

GGROUP(rc1, "RC1_", RC_Channel)
,
GGROUP(rc2, "RC2_", RC_Channel)
,
GGROUP(rc3, "RC3_", RC_Channel)
,
GGROUP(rc4, "RC4_", RC_Channel)
,

GGROUP(stab_pid_roll, "roll_stab_", PID)
,
GGROUP(stab_pid_pitch, "pitch_stab_", PID)
,
GGROUP(stab_pid_yaw, "yaw_stab_", PID)
,

GGROUP(rate_pid_pitch, "pitch_rate_", PID)
,
GGROUP(rate_pid_roll, "roll_rate_", PID)
,
GGROUP(rate_pid_yaw, "yaw_rate_", PID)
,

VAREND
};

#endif /* COPTERTEENSY_PARAMETERS_INIT_HPP_ */
