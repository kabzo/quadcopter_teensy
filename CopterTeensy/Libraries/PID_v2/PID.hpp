#ifndef PID_h
#define PID_h

#include <Mav_Param.hpp>

#define PID_D_TERM_FILTER 0.556864f    // Default 100Hz Filter Rate with 20Hz Cutoff Frequency
//Constants used in some of the functions below
#define AUTOMATIC	1
#define MANUAL	0
#define DIRECT  0
#define REVERSE  1

class PID
{
public:
	PID() :

					_outLimit(0),
					_controllerDirection(false),
					_integrator(0),
					_last_input(0),
					_error(0),
					_dInput(0),
					_last_derivative(0),
					_d_lpf_alpha(PID_D_TERM_FILTER),
					_inAuto(MANUAL),
					lastUpdate(0)
	{
	}

	PID(float kp,
			float ki,
			float kd,
			float imax,
			int controllerDirection) :
					_controllerDirection(controllerDirection),
					_integrator(0),
					_last_input(0),
					_error(0),
					_dInput(0),
					_last_derivative(0),
					_d_lpf_alpha(PID_D_TERM_FILTER),
					_inAuto(AUTOMATIC),
					lastUpdate(0)
	{
		Mav_Param::setup_object_defaults(this, var_info);
		_kP = kp;
		_kI = ki;
		_kD = kd;
		_imax = imax;
	}

	void setControllerDirection(int controllerDirection);
	float get_pid(float targetInput,
								float actualInput,
								float dt);
	float get_pi(float error);

	float get_p(float error);
	float get_i(float error,
							float dt);
	float get_d(float error,
							float dt);
	void reset_I();
	float get_integrator()
	{
		return _integrator;
	}

	int getMode();
	int getDirection();

	float getKp();
	float getKi();
	float getKd();

	static const struct Mav_Param::GroupInfo var_info[];
	static Mav_Float _deltaTime;
	static uint32_t _lastRunned;

private:
	void Initialize();

	Mav_Float _kP;
	Mav_Float _kI;
	Mav_Float _kD;
	Mav_Float p, i, d;

	Mav_Float _imax;

	int _controllerDirection;

	float _integrator;
	float _last_input;
	float _error;
	float _dInput;
	float _last_derivative;
	float _d_lpf_alpha;

	bool _inAuto;
	uint32_t lastUpdate;

};
uint32_t PID::_lastRunned = 0;
Mav_Float PID::_deltaTime = 8;

float PID::getKp()
{
	return _kP._value;
}
float PID::getKi()
{
	return _kI._value;
}
float PID::getKd()
{
	return _kD._value;
}

void PID::setControllerDirection(int controllerDirection)
{
	if (_inAuto && controllerDirection != controllerDirection)
	{
		_kP = (0 - _kP);
		_kI = (0 - _kI);
		_kD = (0 - _kD);
	}
	_controllerDirection = controllerDirection;
}

float PID::get_p(float error)
{
	return (float) error * _kP;
}

float PID::get_i(	float error,
									float dt)
{
	if (_kI != 0)
	{
		float _deltaTimeSec = dt / 1000000;
		_integrator += ((float) error * _kI) * _deltaTimeSec;
		_integrator = constrain(_integrator, -_imax._value, _imax._value);
		return _integrator;
	}
	return 0;
}

float PID::get_d(	float input,
									float dt)
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
		derivative = _last_derivative + _d_lpf_alpha * (derivative - _last_derivative);
		_last_derivative = derivative;
		_last_input = input;
		return -_kD * derivative;
	}

//		float derivative;
//		double _deltaTimeSec = dt / 1000;
//		derivative = (input - _last_input) / _deltaTimeSec;
//		_last_input = input;
//
//		// add in derivative component
//		return -_kD * derivative;

	return 0;
}

float PID::get_pi(float error)
{
	return get_p(error) + get_i(error, 0);
}

float PID::get_pid(	float targetInput,
										float actualInput,
										float dt)
{
	if (!_inAuto)
		return 0;

	float error = targetInput - actualInput;
	p = get_p(error);
	i = get_i(error, dt);
	d = get_d(actualInput, dt);

	return p + i + d;			//, -_outLimit._value, _outLimit._value);
}

void PID::reset_I()
{
	_integrator = 0;
// mark derivative as invalid
	_last_derivative = NAN;
}

int PID::getMode()
{
	return _inAuto ? AUTOMATIC : MANUAL;
}
int PID::getDirection()
{
	return _controllerDirection;
}

const Mav_Param::GroupInfo PID::var_info[]  = {

GROUPINFO("kP", PID, _kP, 0)
,
GROUPINFO("kI", PID, _kI, 0)
,
GROUPINFO("kD", PID, _kD, 0)

,
GROUPINFO("iMax", PID, _imax, 0)
,
GROUPINFO("pT", PID, p, 0)
,
GROUPINFO("iT", PID, i, 0)
,
GROUPINFO("dT", PID, d, 0)
,
GROUPINFO("dTim", PID, _deltaTime, 8)
,

GROUPEND

};

#endif

