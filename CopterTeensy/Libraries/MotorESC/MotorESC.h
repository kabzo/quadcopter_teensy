#ifndef MOTOR_HPP_
#define MOTOR_HPP_

#ifndef Arduino_h
#include "Arduino.h"
#endif

#include <HIL.hpp>
#include <RC_Channel.h>

#define MPINBL PIN23
#define MPINBR PIN22
#define MPINFR PIN21
#define MPINFL PIN20

#define THROTTLE_MIN 1000
#define MAX_SIGNAL 2000
#define MIN_SIGNAL 1000

#define STARTING_THROTTLE_FLY 1100

#define CALIBRATEESC 0 //0 = initialize, 1 = calibrate, 2 = reset

#define ARM true
#define DISARM false

#define ESC_400HZ

void update_motor(float val,
									enum PIN pin)
{
	setFTM0_CxV(pin, val * 3);
}

void init_motor(enum PIN pin)
{
	setFTM0_CxV(pin, 3000);
	port_pcr(pin, 0x400);
}

void init_pwm()
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

//class MotorESC
//{
//public:
//	MotorESC(	enum PIN pin,
//						String name) :
//					speed_(THROTTLE_MIN),
//
//					max_signal_(MAX_SIGNAL),
//					min_signal_(MIN_SIGNAL),
//					name_(name),
//					_switch(CALIBRATEESC),
//					pin_(pin)
//	{
//	}
//
//	MotorESC(uint32_t pin) :
//					speed_(THROTTLE_MIN),
//					max_signal_(MAX_SIGNAL),
//					min_signal_(MIN_SIGNAL),
//					name_(""),
//					_switch(CALIBRATEESC),
//					pin_((enum PIN) pin)
//
//	{
//	}
//
//	void resetESC();
//	void calibrate();
//	void init();
//	void setMotorSpeed(float speed);
//
//
//	void updateMotor(float val)
//	{
//		setFTM0_CxV(pin_, val * 3);
//	}
//
//	void setupMotor(enum PIN pin)
//	{
//		setFTM0_CxV(pin, 3000);
//		port_pcr(pin, 0x400);
//
//	}
//	static void setupPWM()
//	{
//		if (seted == false)
//		{
//			FTM0_SC = 0x0c;   // TOF=0 TOIE=0 CPWMS=0 CLKS=01 PS=100 (divide by 16)
//#ifdef ESC_400HZ
//			// 400Hz PWM signal
//			FTM0_MOD = 7500;
//#else
//			// 250Hz PWM signal
//			FTM0_MOD = 12000;
//#endif
//			FTM0_C0SC = 0x28;
//
//			seted = true;
//		}
//	}
//
//	double speed_;
//
//private:
//
//	int max_signal_;
//	int min_signal_;
//	String name_;
//	unsigned int _switch;
//	enum PIN pin_;
//	static bool seted;
//
//};
//
//bool MotorESC::seted = false;
//
//void MotorESC::resetESC()
//{
//	Serial.println(F("Reseting ESC"));
//	Serial.print(F("Sending:"));
//	Serial.println(max_signal_);
//	updateMotor(max_signal_);
//	delay(62500);
//	Serial.print(F("Sending:"));
//	Serial.println(min_signal_);
//	updateMotor(min_signal_);
//	Serial.println(F("Waiting for ESC 6 seconds"));
//	delay(6000);
//	Serial.println(F("DONE"));
//}
//
//void MotorESC::calibrate()
//{
//	Serial.print(F("Starting calibrate:"));
//	Serial.println(pin_);
//	Serial.print(F("Sending:"));
//	Serial.println(max_signal_);
//	updateMotor(max_signal_);
//	delay(7000);
//	Serial.print(F("Sending:"));
//	Serial.println(min_signal_);
//	updateMotor(min_signal_);
//	Serial.print(F("Waiting for ESC 6 seconds "));
//	delay(6000);
//	Serial.println(F("DONE"));
//}
//
//void MotorESC::init()
//{
//	setupMotor(pin_);
//}
//
//void MotorESC::setMotorSpeed(float speed)
//{
//	speed_ = constrain(round(speed), min_signal_, max_signal_);
//	updateMotor(speed);
//}
#define NUMBER_OF_MOTORS 4

enum motorNum
{
		FL = 0,
		FR,
		BL,
		BR
};

enum rc
{
		rcRoll,
		rcPitch,
		rcThrottle,
		rcYaw
};

class MotorsQuad
{
public:

	MotorsQuad(	RC_Channel *rc1 = 0,
							RC_Channel *rc2 = 0,
							RC_Channel *rc3 = 0,
							RC_Channel *rc4 = 0) :

					_armed(false)
	{
		_rc[rcRoll] = rc1;
		_rc[rcPitch] = rc2;
		_rc[rcThrottle] = rc3;
		_rc[rcYaw] = rc4;

		_motors_pins[FL] = MPINFL;
		_motors_pins[FR] = MPINFR;
		_motors_pins[BL] = MPINBL;
		_motors_pins[BR] = MPINBR;

	}

	void init();

	bool isArmed() const;
	void setArmed(bool armed);

	bool isReadyToFly();
	bool check_radio_arm_pos();

	void set_speed_motor(	motorNum num,
												float speed);
	void set_speet_motors(float speed);
	void set_motor_roll(float val)
	{
		_rc[rcRoll]->set_servo_out(val);
	}
	void set_motor_pitch(float val)
	{
		_rc[rcPitch]->set_servo_out(val);
	}
	void set_motor_yaw(float val)
	{
		_rc[rcYaw]->set_servo_out(val);
	}
	void stop_motors();

	void write_motors_out(int32_t* motors_output);
	void mix_motors_out();

private:
//	static MotorESC _motors[];
	RC_Channel *_rc[4];
	enum PIN _motors_pins[4];
	bool _armed;

	static uint32_t armRequestTime;
	static bool armRequest;
};

uint32_t MotorsQuad::armRequestTime = 0;
bool MotorsQuad::armRequest = false;

//MotorESC MotorsQuad::_motors[] = { MotorESC(MPINFL), MotorESC(MPINFR), MotorESC(MPINBL), MotorESC(MPINBR) };
void MotorsQuad::stop_motors()
{
	set_speet_motors(MIN_SIGNAL);
}
void MotorsQuad::mix_motors_out()
{
	int32_t motors_output[4];

	motors_output[FL] = _rc[rcThrottle]->getScaled() + _rc[rcPitch]->get_pwm_out() - _rc[rcRoll]->get_pwm_out() + _rc[rcYaw]->get_pwm_out();
	motors_output[FR] = _rc[rcThrottle]->getScaled() + _rc[rcPitch]->get_pwm_out() + _rc[rcRoll]->get_pwm_out() - _rc[rcYaw]->get_pwm_out();
	motors_output[BL] = _rc[rcThrottle]->getScaled() - _rc[rcPitch]->get_pwm_out() - _rc[rcRoll]->get_pwm_out() - _rc[rcYaw]->get_pwm_out();
	motors_output[BR] = _rc[rcThrottle]->getScaled() - _rc[rcPitch]->get_pwm_out() + _rc[rcRoll]->get_pwm_out() + _rc[rcYaw]->get_pwm_out();

	for (int i = 0; i < NUMBER_OF_MOTORS; i++)
	{
		motors_output[i] = round(motors_output[i]);
	}

	write_motors_out(motors_output);
}

void MotorsQuad::write_motors_out(int32_t* motors_output)
{
	if (isArmed())
	{
		for (int8_t i = 0; i < NUMBER_OF_MOTORS; i++)
		{
			update_motor(motors_output[i], _motors_pins[i]);
		}
//		_motors[FL].setMotorSpeed(motors_output[FL]);
//		_motors[FR].setMotorSpeed(motors_output[FR]);
//		_motors[BL].setMotorSpeed(motors_output[BL]);
//		_motors[BR].setMotorSpeed(motors_output[BR]);
	}
}

bool MotorsQuad::check_radio_arm_pos()
{
	bool armPositionRc3 = _rc[rcThrottle]->getPwmIn() < (_rc[rcThrottle]->getRadioMin() + _rc[rcThrottle]->getDeadZone()) ? true : false;
	bool armPositionRc4 = _rc[rcYaw]->getPwmIn() < (_rc[rcYaw]->getRadioMin() + _rc[rcYaw]->getDeadZone()) ? true : false;

	if (armPositionRc3 && armPositionRc4 && _rc[rcThrottle]->getPwmIn() > 100 && _rc[rcYaw]->getPwmIn() > 100)
	{
		if (!MotorsQuad::armRequest)
		{
			MotorsQuad::armRequest = true;
			MotorsQuad::armRequestTime = millis();
		}

	} else
		MotorsQuad::armRequest = false;

	if (millis() - MotorsQuad::armRequestTime > 1000 && MotorsQuad::armRequest)
	{
		bool armed = isArmed();
		setArmed(!armed);
		DEBUG2("armed?:", isArmed());

		MotorsQuad::armRequest = false;
		return true;
	}
	return false;
}

void MotorsQuad::set_speed_motor(	motorNum num,
																	float speed)
{
	update_motor(speed, _motors_pins[num]);
//	_motors[num].setMotorSpeed(speed);
}

void MotorsQuad::set_speet_motors(float speed)
{
	for (uint8_t i = 0; i < NUMBER_OF_MOTORS; i++)
	{
//		_motors[i].setMotorSpeed(speed);
		update_motor(speed, _motors_pins[i]);
	}
}

void MotorsQuad::init()
{
//	MotorESC::setupPWM();
	init_pwm();

	for (int i = 0; i < NUMBER_OF_MOTORS; i++)
	{
//			_motors[i].init();
		init_motor(_motors_pins[i]);
	}

}

bool MotorsQuad::isReadyToFly()
{
	if (isArmed() && _rc[rcThrottle]->getScaled() > STARTING_THROTTLE_FLY)
		return true;
	return false;
}

inline bool MotorsQuad::isArmed() const
{
	return _armed;
}

inline void MotorsQuad::setArmed(bool armed)
{
	_armed = armed;
}

#endif /* MOTOR_HPP_ */
