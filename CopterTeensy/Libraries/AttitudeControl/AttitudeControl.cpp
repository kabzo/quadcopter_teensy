/*
 * AttitudeControl.cpp
 *
 *  Created on: 17.2.2015
 *      Author: Juraj
 */
#include <AttitudeControl.hpp>

uint8_t AttitudeControl::_sampleTime = 8;

float AttitudeControl::pid_stab(PID* pid, float target, float input, uint32_t dt)
{
	if (!pid->is_k_zero() && pid->get_active())
	{
		float output = pid->get_pid(target, input, dt);
		output -= pid->get_integrator();
		return output;
	} else
		return target;
}

void AttitudeControl::rate_roll_pitch_yaw(uint32_t dt)
{

	_actual_rates = _imu.calGyro.to_centi_deg();

	_rate_output.ROLL = _rate_pid.ROLL->get_pid(_stab_output.ROLL, _actual_rates.x, dt);
	_rate_output.PITCH = _rate_pid.PITCH->get_pid(_stab_output.PITCH, _actual_rates.y, dt);
	_rate_output.YAW = _rate_pid.YAW->get_pid(_stab_output.YAW, _actual_rates.z, dt);
}

void AttitudeControl::stab_roll_pitch_yaw(uint32_t dt)
{

	_actual_angles = _imu.dmpEuler.rad_to_centi_deg();

	_motors.get_target_rc_roll_pitch(_target_angles);

	_stab_output.ROLL = pid_stab(_stab_pid.ROLL, _target_angles.ROLL, _actual_angles.ROLL, dt);
	_stab_output.PITCH = pid_stab(_stab_pid.PITCH, _target_angles.PITCH, _actual_angles.PITCH, dt);
	_stab_output.YAW = pid_stab(_stab_pid.YAW, _target_angles.YAW, _actual_angles.YAW, dt);
}

void AttitudeControl::reset_pid()
{
	_rate_pid.ROLL->reset_I();
	_rate_pid.PITCH->reset_I();
	_rate_pid.YAW->reset_I();

	_stab_pid.ROLL->reset_I();
	_stab_pid.PITCH->reset_I();
	_stab_pid.YAW->reset_I();

	_target_angles.YAW = _actual_angles.YAW;

	_rate_output.reset();
	_stab_output.reset();
}

bool AttitudeControl::is_ready()
{
	handle_stab_pid_k_change();
	handle_rate_pid_k_change();

	if (!_motors.is_ready_fly())
	{
		reset_pid();
		_motors.stop_motors();
		return false;
	}
	return true;
}

void AttitudeControl::set_last_update_pid(uint32_t time)
{
	_lastUpdatePid = time;
}

uint32_t AttitudeControl::get_last_update_pid()
{
	return _lastUpdatePid;
}

Vector3Float& AttitudeControl::get_rate_output()
{
	return _rate_output;
}

Vector3Float&  AttitudeControl::get_stab_output(){
	return _stab_output;
}

Vector3Float& AttitudeControl::get_target_angles()
{
	return _target_angles;
}

Vector3Float& AttitudeControl::get_actual_angles()
{
	return _actual_angles;
}

Vector3Float& AttitudeControl::get_actual_rates()
{
	return _actual_rates;
}

void AttitudeControl::handle_stab_pid_k_change()
{

	if (_stab_pid.ROLL->is_k_changed())
	{
		_stab_pid.PITCH->set_k_pid(_stab_pid.ROLL);
//		_stab_pid.ROLL->erase_k_change();
//		Serial.println("_stab_pid.ROLL->is_k_changed()");
	}
	if (_stab_pid.PITCH->is_k_changed())
	{
		_stab_pid.ROLL->set_k_pid(_stab_pid.PITCH);
//		_stab_pid.PITCH->erase_k_change();
//		Serial.println("_stab_pid.PITCH->is_k_changed()");
	}
}

void AttitudeControl::handle_rate_pid_k_change()
{
	if (_rate_pid.ROLL->is_k_changed())
	{
		_rate_pid.PITCH->set_k_pid(_rate_pid.ROLL);
//		_rate_pid.ROLL->erase_k_change();
//		Serial.println("_rate_pid.ROLL->is_k_changed()");
	}

	if (_rate_pid.PITCH->is_k_changed())
	{
		_rate_pid.ROLL->set_k_pid(_rate_pid.PITCH);
//		_rate_pid.PITCH->erase_k_change();
//		Serial.println("_rate_pid.PITCH->is_k_changed()");
	}
}
