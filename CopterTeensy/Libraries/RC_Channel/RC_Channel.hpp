#ifndef RC_CHANNEL_H_
#define RC_CHANNEL_H_

#include <Mav_Param.hpp>

#define RC_CHANNEL_TYPE_ANGLE       0
#define RC_CHANNEL_TYPE_RANGE       1

class RC_Channel
{
public:

	RC_Channel(uint8_t pinIn, float radioMin, float radioMax, bool invert = false) :
					pin(pinIn),
					pwm_in(radioMin),
					_servo_out(0),
					_type(RC_CHANNEL_TYPE_ANGLE),
					_high(radioMax),
					_low(radioMin),
					_high_out(radioMax),
					_low_out(radioMin),
					_localPwm_in(radioMin),
					_invert(invert)
	{
		Mav_Param::setup_object_defaults(this, var_info);
		pinMode(pinIn, INPUT);
		radio_max = radioMax;
		radio_min = radioMin;
		radio_trim = (radioMax + radioMin) / 2;
	}

	int16_t range_to_pwm();
	int16_t pwm_to_range_dz();
	void set_range_out(int16_t low, int16_t high);
	void set_range(int16_t low, int16_t high);
	void set_angle(int16_t angle);
	int16_t get_pwm_to_angle();
	int16_t angle_to_pwm();

	void overwritePwm(int32_t val);
	int32_t getPwmIn();
	int16_t getScaled();
	float get_pwm_out();
	Mav_Float getDeadZone() const;
	Mav_Float getRadioMax() const;
	Mav_Float getRadioMin() const;
	int16_t get_low();

	void localCopy()
	{
		_localPwm_in = pwm_in;
	}
	void set_servo_out(float val)
	{
		_servo_out = val;
	}

	static const struct Mav_Param::GroupInfo var_info[];

	volatile uint8_t pin;
	volatile uint32_t pwmStart;
	volatile static bool newPwm;
	volatile int32_t pwm_in;

private:
	Mav_Float radio_min;
	Mav_Float radio_trim;
	Mav_Float radio_max;
	Mav_Float control_out;
	Mav_Float dead_zone;

	float _servo_out;
	uint8_t _type;
	int16_t _high;
	int16_t _low;
	int16_t _high_out;
	int16_t _low_out;
	int32_t _localPwm_in;
	bool _invert;
};

inline Mav_Float RC_Channel::getDeadZone() const
{
	return dead_zone;
}

inline Mav_Float RC_Channel::getRadioMax() const
{
	return radio_max;
}

inline Mav_Float RC_Channel::getRadioMin() const
{
	return radio_min;
}

#endif /* RC_CHANNEL_H_ */
