/*
 * parameters.hpp
 *
 *  Created on: 1.11.2014
 *      Author: Juraj
 */

#ifndef COPTERTEENSY_PARAMETERS_INIT_HPP_
#define COPTERTEENSY_PARAMETERS_INIT_HPP_

#define YAW_PID PID
#define PITCH_PID PID
#define ROLL_PID PID



class Parameters
{
public:

	Parameters() :

					rc1(3, 	1068, 	1924), //roll
					rc2(4, 	1143, 	1841, 	true),	//pitch
					rc3(5, 	1073, 	1938), //throttle
					rc4(6, 	1086, 	1951),	//yaw
											//		 P,	I,	D,	IMAX
					stab_pid_roll(	0, 0, 	0, 	1500),
					stab_pid_pitch(	0, 0, 	0,  1500),
					stab_pid_yaw(		0, 0, 	0,  1500),

											//		P,	I,	D,	IMAX
					rate_pid_pitch(	0.165, 0.6, 	0.0045,  5),
					rate_pid_roll(	0.0, 0.0, 	0.0045,  5),
					rate_pid_yaw(		0.0, 	0.0, 0.0,  	8),

							//		YAW		 (P			, I			,D  		,iMax),		PITCH    (P			, I			,D  		,iMax),		ROLL    (P			, I			,D  		,iMax),
					rate_pid(	YAW_PID(0.000f, 0.000f, 0.000f, 8), 		PITCH_PID(0.165f, 0.600f, 0.0045f, 5), 		ROLL_PID(0.165f, 0.600f, 0.0045f, 5)),

					stab_pid(	YAW_PID(0.000f, 0.000f, 0.000f, 1500),	PITCH_PID(0.000f, 0.000f, 0.0000f, 1500),	ROLL_PID(0.000f, 0.000f, 0.0000f, 1500))


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

	Vector3<PID> rate_pid;
	Vector3<PID> stab_pid;

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

//GGROUP(stab_pid_roll, "roll_stab_", PID)
//,
//GGROUP(stab_pid_pitch, "pitch_stab_", PID)
//,
//GGROUP(stab_pid_yaw, "yaw_stab_", PID)
//,
//
//GGROUP(rate_pid_pitch, "pitch_rate_", PID)
//,
//GGROUP(rate_pid_roll, "roll_rate_", PID)
//,
//GGROUP(rate_pid_yaw, "yaw_rate_", PID)
//,
GGROUP(rate_pid.ROLL, "roll_rate_", PID),GGROUP(rate_pid.PITCH, "pitch_rate_", PID),GGROUP(rate_pid.YAW, "yaw_rate_", PID),
GGROUP(stab_pid.ROLL, "roll_stab_", PID),GGROUP(stab_pid.PITCH, "pitch_stab_", PID),GGROUP(stab_pid.YAW, "yaw_stab_", PID),




VAREND
};

#endif /* COPTERTEENSY_PARAMETERS_INIT_HPP_ */
