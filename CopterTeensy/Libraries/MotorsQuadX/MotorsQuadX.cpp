/*
 * MotorsQuadX.cpp
 *
 *  Created on: 17.2.2015
 *      Author: Juraj
 */
#include <MotorsQuadX.hpp>

uint32_t MotorsQuadX::armRequestTime = 0;

bool MotorsQuadX::armRequest = false;

void MotorsQuadX::get_target_rc_roll_pitch(Vector3Float& v)
{
	v.PITCH = _rc[rcPitch]->getScaled();
	v.ROLL = _rc[rcRoll]->getScaled();
}

void MotorsQuadX::motor_bounds()
{
	// Fix motor mix range
	int16_t motorFix = 0;
	uint16_t motorMin = motors_output[FL], motorMax = motors_output[FL];
	for (int i = 1; i < 4; i++)
	{
		if (motors_output[i] < motorMin)
			motorMin = motors_output[i];
		if (motors_output[i] > motorMax)
			motorMax = motors_output[i];
	}
	if (motorMin < _min_signal)
		motorFix = _min_signal - motorMin;
	else if (motorMax > _max_signal)
		motorFix = _max_signal - motorMax;

	// Refresh motors
	DEBUGLN1(motorFix);
	for (int i = 0; i < 4; i++)
		motors_output[i] = motors_output[i] + motorFix;
}

void MotorsQuadX::stop_motors()
{
	set_speet_motors(MIN_SIGNAL);
}

void MotorsQuadX::mix_motors_out()
{
	float output[4];
	output[FL] = _rc[rcThrottle]->getScaled() + _rc[rcPitch]->get_pwm_out() - _rc[rcRoll]->get_pwm_out() + _rc[rcYaw]->get_pwm_out();
	output[FR] = _rc[rcThrottle]->getScaled() + _rc[rcPitch]->get_pwm_out() + _rc[rcRoll]->get_pwm_out() - _rc[rcYaw]->get_pwm_out();
	output[BL] = _rc[rcThrottle]->getScaled() - _rc[rcPitch]->get_pwm_out() - _rc[rcRoll]->get_pwm_out() - _rc[rcYaw]->get_pwm_out();
	output[BR] = _rc[rcThrottle]->getScaled() - _rc[rcPitch]->get_pwm_out() + _rc[rcRoll]->get_pwm_out() + _rc[rcYaw]->get_pwm_out();

	for (int i = 0; i < NUMBER_OF_MOTORS; i++)
		motors_output[i] = round(output[i]);

//	motor_bounds();
	write_motors_out(motors_output);
}

void MotorsQuadX::write_motors_out(int32_t* motors_output_us)
{
	if (is_armed())
	{
		for (int8_t i = 0; i < NUMBER_OF_MOTORS; i++)
		{
			update_motor(motors_output_us[i], _motors_pins[i]);
		}
	}
}

bool MotorsQuadX::check_radio_arm_pos()
{
	bool armPositionRc3 =
			_rc[rcThrottle]->getPwmIn() < (_rc[rcThrottle]->getRadioMin() + _rc[rcThrottle]->getDeadZone()) ? true : false;
	bool armPositionRc4 =
			_rc[rcYaw]->getPwmIn() < (_rc[rcYaw]->getRadioMin() + _rc[rcYaw]->getDeadZone()) ? true : false;

	if (armPositionRc3 && armPositionRc4 && _rc[rcThrottle]->getPwmIn() > 100 && _rc[rcYaw]->getPwmIn() > 100)
	{
		if (!MotorsQuadX::armRequest)
		{
			MotorsQuadX::armRequest = true;
			MotorsQuadX::armRequestTime = millis();
		}
	} else
		MotorsQuadX::armRequest = false;

	if (millis() - MotorsQuadX::armRequestTime > 1000 && MotorsQuadX::armRequest)
	{
		bool armed = is_armed();
		set_armed(!armed);
		MotorsQuadX::armRequest = false;
		return true;
	}
	return false;
}

void MotorsQuadX::set_speed_motor(motorNum num, float speed)
{
	update_motor(speed, _motors_pins[num]);
}

void MotorsQuadX::set_speet_motors(float speed)
{
	for (uint8_t i = 0; i < NUMBER_OF_MOTORS; i++)
		update_motor(speed, _motors_pins[i]);

}

void MotorsQuadX::init()
{
	init_pwm();
	for (int i = 0; i < NUMBER_OF_MOTORS; i++)
	{
		init_motor(_motors_pins[i]);
	}

}

bool MotorsQuadX::is_ready_fly()
{
	if (is_armed() && _rc[rcThrottle]->getScaled() > STARTING_THROTTLE_FLY)
		return true;
	return false;
}

bool MotorsQuadX::is_armed() const
{
	return _armed;
}

void MotorsQuadX::set_armed(bool armed)
{
	_armed = armed;
}

void MotorsQuadX::update_motor(float val, enum PIN pin)
{
	setFTM0_CxV(pin, val * 3);
}

void MotorsQuadX::init_motor(enum PIN pin)
{
	setFTM0_CxV(pin, 3000);
	port_pcr(pin, 0x400);
}

void MotorsQuadX::init_pwm()
{
	FTM0_SC = 0x0c;   // TOF=0 TOIE=0 CPWMS=0 CLKS=01 PS=100 (divide by 16)
#ifdef ESC_400HZ
// 400Hz PWM signal
	FTM0_MOD = 7500;
#else
// 250Hz PWM signal
	FTM0_MOD = 12000;
#endif
	FTM0_C0SC = 0x28;
}

void MotorsQuadX::set_motor_angles(Vector3Float& angles){
	_rc[rcRoll]->set_servo_out(angles.ROLL);
	_rc[rcPitch]->set_servo_out(angles.PITCH);
	_rc[rcYaw]->set_servo_out(angles.YAW);

}

void MotorsQuadX::set_motor_roll(float val)
{
	_rc[rcRoll]->set_servo_out(val);
}

void MotorsQuadX::set_motor_pitch(float val)
{
	_rc[rcPitch]->set_servo_out(val);
}

void MotorsQuadX::set_motor_yaw(float val)
{
	_rc[rcYaw]->set_servo_out(val);
}


