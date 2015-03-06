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

					rc1(3, 	1068, 	1924), 	//roll
					rc2(4, 	1143, 	1841, 	true),	//pitch
					rc3(5, 	1073, 	1938), //throttle
					rc4(6, 	1086, 	1951,true),	//yaw

							//		YAW		 (P			, I			,D  		,iMax),		PITCH    (P			, I			,D  		,iMax),		ROLL    (P			, I			,D  		,iMax),
					rate_pid(	YAW_PID(0.0650f, 0.02f, 0.000f, 500), 	PITCH_PID(0.065f, 0.025f, 0.0014f, 500), 		ROLL_PID(0.065f, 0.025f, 0.0014f, 500)),

					stab_pid(	YAW_PID(4.000f, 0.000f, 0.000f, 1500),	PITCH_PID(3.00f, 0.000f, 0.0000f, 1500),	ROLL_PID(3.00f, 0.000f, 0.0000f, 1500))
	{

	}

	Mav_Float throttle_min;
	Mav_Float throttle_max;

	RC_Channel rc1;
	RC_Channel rc2;
	RC_Channel rc3;
	RC_Channel rc4;

	Vector3<PID> rate_pid;
	Vector3<PID> stab_pid;
};




#endif /* COPTERTEENSY_PARAMETERS_INIT_HPP_ */
