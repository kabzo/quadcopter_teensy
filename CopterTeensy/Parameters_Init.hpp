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

class Parameters {
public:

	Parameters() :

					rc1(3,1110,1977), //roll
					rc2(4,1156,1859),	//pith
					rc3(5,1099,1952), //throttle
					rc4(6,1087,1953),	//yaw
					pid_roll(0, 0, 0, 50, DIRECT),
					pid_pitch(0, 0, 0, 50, DIRECT),
					pid_yaw(0, 0, 0, 50, DIRECT) {

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

	PID pid_roll;
	PID pid_pitch;
	PID pid_yaw;

	VectorFloat vectorYpr;
	VectorInt16 vectorGyro;
	VectorInt16 vectorAcc;
	VectorInt16 vectorMag;

	float heading;


};

static Parameters param_container;


const Mav_Param::Info var_info[] = {

GSCALAR(roll_pidOutput, 	"roll_pidOutput", 	0),
GSCALAR(pitch_pidOutput,	"pitch_pidOutput", 	0),
GSCALAR(yaw_pidOutput,		"yaw_pidOutput",		0),

GSCALAR(throttle_min,			"throttle_min", 		1070),
GSCALAR(throttle_max,			"throttle_max", 		2000),

GGROUP(	rc1, 							"RC1_", 			RC_Channel),
GGROUP(	rc2, 							"RC2_", 			RC_Channel),
GGROUP(	rc3, 							"RC3_", 			RC_Channel),
GGROUP(	rc4, 							"RC4_", 			RC_Channel),

GGROUP(	pid_roll, 				"pid_roll_",	PID),
GGROUP(	pid_pitch,				"pid_pitch_", PID),
GGROUP(	pid_yaw, 					"pid_yaw_", 	PID),

VAREND
};

#endif /* COPTERTEENSY_PARAMETERS_INIT_HPP_ */
