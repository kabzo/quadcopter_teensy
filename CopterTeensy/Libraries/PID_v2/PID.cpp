/*
 * PID.cpp
 *
 *  Created on: 17.2.2015
 *      Author: Juraj
 */
#include <PID.hpp>

const Mav_Param::GroupInfo PID::var_info[]  = {

GROUPINFO("kP", PID, _kP, 0)
,
GROUPINFO("kI", PID, _kI, 0)
,
GROUPINFO("kD", PID, _kD, 0)
,
GROUPINFO("iMax", PID, _iMax, 0)
,
GROUPINFO("pMax", PID, _pMax, P_MAX)
,
GROUPEND

};

float	PID::get_pMax(){
	return _pMax._value;
}

bool PID::is_k_changed()
{
if (_kP.is_changed() || _kD.is_changed() || _kI.is_changed())
	return true;
return false;
}

void PID::set_k_pid(PID* pid)
{
_kP._value = pid->get_kp();
_kI._value = pid->get_ki();
_kD._value = pid->get_kd();
}

Mav_Float PID::get_mav_kp()
{
return _kP;
}

Mav_Float PID::get_mav_ki()
{
return _kI;
}

Mav_Float PID::get_mav_kd()
{
return _kD;
}

bool PID::is_k_zero()
{
if (_kP._value == 0 && _kI._value == 0 && _kD._value == 0)
	return true;
else
	return false;
}

float PID::get_p(float error)
{
return (float) error * _kP;
}

float PID::get_i(float error, float dt)
{
if (_kI != 0)
{
	float _deltaTimeSec = dt / 1000000;
	_integrator += ((float) error * _kI) * _deltaTimeSec;
	_integrator = constrain(_integrator, -_iMax._value, _iMax._value);
	return _integrator;
}
return 0;
}

float PID::get_d(float input, float dt)
{
if ((_kD != 0))
{
	float derivative;
	if (isnan(_last_derivative))
	{
		// we've just done a reset, suppress the first derivative
		// term as we don't want a sudden change in input to cause
		// a large D output change
		derivative = 0;
		_last_derivative = 0;
	} else
	{
		double _deltaTimeSec = dt / 1000000;
		derivative = (input - _last_input) / _deltaTimeSec;
		//calculate instantaneous derivative
	}

	//	discrete low pass filter, cuts out the
	//	high frequency noise that can drive the controller crazy
	// see wikipedia low pass filter
//	Serial.println(_d_lpf_alpha);
	derivative = _last_derivative + _d_lpf_alpha * (derivative - _last_derivative);
	_last_derivative = derivative;
	_last_input = input;
	return -_kD * derivative;
}

return 0;
}

float PID::get_pi(float error)
{
return get_p(error) + get_i(error, 0);
}

float PID::get_pid(float targetInput, float actualInput, float dt)
{
if (_active == DISABLED)
	return 0;

_error = targetInput - actualInput;
_p = get_p(_error);
_i = get_i(_error, dt);
_d = get_d(actualInput, dt);

return _p + _i + _d;			//, -_outLimit._value, _outLimit._value);
}

float PID::get_error(){
	return _error;
}

float PID::get_p_error_lim(float targetInput, float actualInput){
	_error = targetInput - actualInput;
	_error = constrain(_error,-_pMax._value,_pMax._value);
	return _error;
}

void PID::set_d_lpf_alpha(int16_t cutoff_frequency, float time_step)
{
    // calculate alpha
    float rc = 1/(2*PI*cutoff_frequency);
    _d_lpf_alpha = time_step / (time_step + rc);

#ifdef DEBUG_ALL
    Serial.print("_d_lpf_alpha:");Serial.print(_d_lpf_alpha,5);
    Serial.print("cutoff_frequency:");Serial.print((long)cutoff_frequency);
    Serial.print("time_step:");Serial.println(time_step,5);
#endif
}

void PID::reset_I()
{
_integrator = 0;
// mark derivative as invalid
_last_derivative = NAN;
}

int PID::get_mode()
{
return _active ? ENABLED : DISABLED;
}

float PID::get_kp()
{
return _kP._value;
}

float PID::get_ki()
{
return _kI._value;
}

float PID::get_kd()
{
return _kD._value;
}

float PID::get_integrator()
{
return _integrator;
}

void PID::set_active(bool activate)
{
_active = activate;
}

bool PID::get_active()
{
return _active;
}

float PID::get_p_term(){
	return _p;
}

float PID::get_i_term(){
	return _i;
}

float PID::get_d_term(){
	return _d;
}


