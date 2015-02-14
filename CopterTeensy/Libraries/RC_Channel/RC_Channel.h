#ifndef RC_CHANNEL_H_
#define RC_CHANNEL_H_

#include <Mav_Param.hpp>

#define RC_CHANNEL_TYPE_ANGLE       0
#define RC_CHANNEL_TYPE_RANGE       1

class RC_Channel
{
public:
	RC_Channel(	uint8_t pinIn,
							bool invert = false) :
					pin(pinIn),
					pwm_in(0),
					_type(RC_CHANNEL_TYPE_ANGLE),
					_high(0),
					_low(1000),
					_high_out(0),
					_low_out(1000),
					invert(invert)
	{
		Mav_Param::setup_object_defaults(this, var_info);

	}
	RC_Channel(	uint8_t pinIn,
							float radioMin,
							float radioMax,
							bool invert = false) :
					pin(pinIn),
					pwm_in(0),
					_type(RC_CHANNEL_TYPE_ANGLE),
					_high(0),
					_low(1000),
					_high_out(0),
					_low_out(1000),
					invert(invert)
	{
		Mav_Param::setup_object_defaults(this, var_info);
		pinMode(pinIn, INPUT);
		radio_max = radioMax;
		radio_min = radioMin;
		radio_trim = (radioMax + radioMin) / 2;
	}

	int16_t range_to_pwm();
	int16_t pwm_to_range_dz();
	void set_range_out(	int16_t low,
											int16_t high);
	void set_range(	int16_t low,
									int16_t high);
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

	void localCopy()
	{
		_localPwm_in = pwm_in;
	}
	void set_servo_out(float val){
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
	bool invert;
};

volatile bool RC_Channel::newPwm = false;

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

//	if (r_in > radio_trim_low)
//		return (_low + ((long) (_high - _low) * (long) (r_in - radio_trim_low)) / (long) (radio_max - radio_trim_low));
//	else
//		return 1000;

	int16_t ret;
	if (r_in > radio_trim_low)
		ret = map(r_in, radio_trim_low, radio_max._value, _low, _high);
	else
		ret = _low;

	if (invert)
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
//		return ((long) _high * (long) (pwm_in - radio_trim_high)) / (long) (radio_max - radio_trim_high);
		ret = map(pwm_in, radio_trim_high, radio_max, 0, _high);
	} else if (pwm_in < radio_trim_low)
	{
//		return ((long) _high * (long) (pwm_in - radio_trim_low)) / (long) (radio_trim_low - radio_min);
		ret = map(pwm_in, radio_min, radio_trim_low, -_high, 0);

	} else
		ret = 0;

	if (invert)
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
