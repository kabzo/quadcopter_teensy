/*
 * parameters.hpp
 *
 *  Created on: 1.11.2014
 *      Author: Juraj
 */

#ifndef COPTERARDUINODUE_PARAMETERS_INIT_HPP_
#define COPTERARDUINODUE_PARAMETERS_INIT_HPP_

#include "Mav_Param.hpp"
#include <mavlinkCommon/common/mavlink.h>

class Parameters {
	public:

		Parameters()
				:
						roll_kP(5),
						roll_kI(0.0),
						roll_kD(0.0),

						pitch_kP(0.0),
						pitch_kI(0.0),
						pitch_kD(0.0),

						yaw_kP(0.4634),
						yaw_kI(0.3543),
						yaw_kD(1.234) {
		}

		Mav_Float roll_pidOutput;
		Mav_Float pitch_pidOutput;
		Mav_Float yaw_pidOutput;

		Mav_Float roll_kP;
		Mav_Float roll_kI;
		Mav_Float roll_kD;

		Mav_Float pitch_kP;
		Mav_Float pitch_kI;
		Mav_Float pitch_kD;

		Mav_Float yaw_kP;
		Mav_Float yaw_kI;
		Mav_Float yaw_kD;

		Mav_Float manual_rcX; //roll
		Mav_Float manual_rcY; //pitch
		Mav_Float manual_rcZ; //throttle
		Mav_Float manual_rcR; //yaw

		Attitude_t attitude_t;

		enum {
			k_param_roll_pidOutput = 0,
			k_param_pitch_pidOutput,
			k_param_yaw_pidOutput,

			k_param_roll_kP,
			k_param_roll_kI,
			k_param_roll_kD,

			k_param_pitch_kP,
			k_param_pitch_kI,
			k_param_pitch_kD,

			k_param_yaw_kP,
			k_param_yaw_kI,
			k_param_yaw_kD,

			k_param_manual_rcX,
			k_param_manual_rcY,
			k_param_manual_rcZ,
			k_param_manual_rcR
		};

};

static Parameters param_container;

#define GSCALAR(v, name) { param_container.v.vtype, name, Parameters::k_param_ ## v, &param_container.v }
#define PARAM_END       { PARAM_NONE, "", 0, NULL }

const Mav_Param::Info Mav_Param::_var_info[] = {

GSCALAR(roll_pidOutput,"roll_pidOutput"),
GSCALAR(pitch_pidOutput,"pitch_pidOutput"),
GSCALAR(yaw_pidOutput,"yaw_pidOutput"),

GSCALAR(roll_kP,"roll_kP"),
GSCALAR(roll_kI,"roll_kI"),
GSCALAR(roll_kD,"roll_kD"),

GSCALAR(pitch_kP,"pitch_kP"),
GSCALAR(pitch_kI,"pitch_kI"),
GSCALAR(pitch_kD,"pitch_kD"),

GSCALAR(yaw_kP,"yaw_kP"),
GSCALAR(yaw_kI,"yaw_kI"),
GSCALAR(yaw_kD,"yaw_kD"),

GSCALAR(manual_rcX,"manual_rcX"),
GSCALAR(manual_rcY,"manual_rcY"),
GSCALAR(manual_rcZ,"manual_rcZ"),
GSCALAR(manual_rcR,"manual_rcR"),

PARAM_END

};

uint8_t Mav_Param::_num_vars = Mav_Param::cout_vars();

#endif /* COPTERARDUINODUE_PARAMETERS_INIT_HPP_ */
