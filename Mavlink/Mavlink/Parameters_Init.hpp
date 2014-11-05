/*
 * parameters.hpp
 *
 *  Created on: 1.11.2014
 *      Author: Juraj
 */

#ifndef PARAMETERS_INIT_HPP_
#define PARAMETERS_INIT_HPP_

#include "Mav_Param.hpp"

class parameters {
	public:

		parameters()
				: kProll(99), kIroll(0), kDroll(0),

				kPpitch(66), kIpitch(0), kDpitch(0) {
		}
		Mav_Float roll_angle;
		Mav_Float pitch_angle;
		Mav_Float yaw_angle;

		Mav_Float roll_rad;
		Mav_Float pitch_rad;
		Mav_Float yaw_rad;

		Mav_Int32 pidRollOutput;
		Mav_Int32 pidPitchOutput;
		Mav_Int32 pidYawOutput;

		Mav_Float kProll;
		Mav_Float kIroll;
		Mav_Float kDroll;

		Mav_Float kPpitch;
		Mav_Float kIpitch;
		Mav_Float kDpitch;

		Mav_Float kPyaw;
		Mav_Float kIyaw;
		Mav_Float kDyaw;

		enum {
			k_param_roll_angle = 0, k_param_pitch_angle, k_param_yaw_angle,

			k_param_roll_rad,
			k_param_pitch_rad, k_param_yaw_rad,

			k_param_pidRollOutput,
			k_param_pidPitchOutput, k_param_pidYawOutput,

			k_param_kProll,  k_param_kIroll, k_param_kDroll,

			k_param_kPpitch, k_param_kIpitch, k_param_kDpitch,

			k_param_kPyaw, k_param_kIyaw, k_param_kDyaw,
		};

};

static parameters param_container;

#define GSCALAR(v, name) { param_container.v.vtype, name, parameters::k_param_ ## v, &param_container.v }
#define PARAM_END       { PARAM_NONE, "", 0, NULL }

const Mav_Param::Info Mav_Param::_var_info[] = {
GSCALAR(roll_angle,"roll_angle"),
GSCALAR(pitch_angle,"pitch_angle"),
GSCALAR(yaw_angle,"yaw_angle"),

GSCALAR(roll_rad,"roll_rad"),
GSCALAR(pitch_rad,"pitch_rad"),
GSCALAR(yaw_rad,"yaw_rad"),

GSCALAR(pidRollOutput,"pidRollOutput"),
GSCALAR(pidPitchOutput,"pidPitchOutput"),
GSCALAR(pidYawOutput,"pidYawOutput"),

GSCALAR(kProll,"kProll"),
GSCALAR(kIroll,"kIroll"),
GSCALAR(kDroll,"kDroll"),

GSCALAR(kPpitch,"kPpitch"),
GSCALAR(kIpitch,"kIpitch"),
GSCALAR(kDpitch,"kDpitch"),

GSCALAR(kPyaw,"kPyaw"),
GSCALAR(kIyaw,"kIyaw"),
GSCALAR(kDyaw,"kDyaw"),

PARAM_END

};

uint8_t Mav_Param::_num_vars = 18;

#endif /* PARAMETERS_INIT_HPP_ */
