/*
 * RC_Channel.cpp
 *
 *  Created on: 17.2.2015
 *      Author: Juraj
 */
#include <RC_Channel.hpp>

const Mav_Param::GroupInfo RC_Channel::var_info[]  = {

GROUPINFO("MIN", RC_Channel, radio_min, 2300)
,
GROUPINFO("TRIM", RC_Channel, radio_trim, 2645)
,
GROUPINFO("MAX", RC_Channel, radio_max, 3740)
,
GROUPINFO("control_out", RC_Channel, control_out, 0)
,
GROUPINFO("dead_zone", RC_Channel, dead_zone, 30)
,

GROUPEND

};

volatile bool RC_Channel::newPwm = false;

int16_t RC_Channel::get_low(){
	return _low;
}

int16_t RC_Channel::angle_to_pwm()
{
	return  _servo_out*0.1f;

}

float RC_Channel::get_pwm_out(){
	if (_type == RC_CHANNEL_TYPE_ANGLE)
	{
		return angle_to_pwm();
	}
	return (float) radio_min._value;
}

void RC_Channel::set_angle(int16_t angle)
{
	_type = RC_CHANNEL_TYPE_ANGLE;
	_high = angle;
}

void RC_Channel::overwritePwm(int32_t val)
{
	_localPwm_in = val;

}

void RC_Channel::set_range(	int16_t low,
														int16_t high)
{
	_type = RC_CHANNEL_TYPE_RANGE;
	_high = high;
	_low = low;
	_high_out = high;
	_low_out = low;
}

void RC_Channel::set_range_out(	int16_t low,
																int16_t high)
{
	_high_out = high;
	_low_out = low;
}

int16_t RC_Channel::pwm_to_range_dz()
{
	int16_t r_in = pwm_in;
	int16_t radio_trim_low = radio_min + dead_zone;
	int16_t ret;

	if (r_in > radio_trim_low)
		ret = map(r_in, radio_trim_low, radio_max._value, _low, _high);
	else
		ret = _low;

	if (_invert)
		return -ret;
	else
		return ret;

}

int16_t RC_Channel::get_pwm_to_angle()
{
	int16_t radio_trim_high = radio_trim + dead_zone;
	int16_t radio_trim_low = radio_trim - dead_zone;

	// prevent div by 0
	if ((radio_trim_low - radio_min) == 0 || (radio_max - radio_trim_high) == 0)
		return 0;

	int16_t ret;

	if (pwm_in > radio_trim_high)
	{
		ret = map(pwm_in, radio_trim_high, radio_max, 0, _high);
	} else if (pwm_in < radio_trim_low)
	{
		ret = map(pwm_in, radio_min, radio_trim_low, -_high, 0);
	} else
		ret = 0;

	if (_invert)
		return -ret;
	else
		return ret;
}

int16_t RC_Channel::getScaled()
{
	if (_type == RC_CHANNEL_TYPE_ANGLE)
	{
		return get_pwm_to_angle();
	} else
	{
		return pwm_to_range_dz();
	}
}

int32_t RC_Channel::getPwmIn()
{
	return _localPwm_in;
}

