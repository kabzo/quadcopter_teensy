#ifndef PID_h
#define PID_h

#include <HIL.hpp>

#define PID_D_TERM_FILTER 0.556864f    // Default 100Hz Filter Rate with 20Hz Cutoff Frequency
//Constants used in some of the functions below
#define P_MAX 4500

#define ENABLED	true
#define DISABLED	false

class PID
{
public:
	PID() :
					_p(0),
					_i(0),
					_d(0),
					_integrator(0),
					_last_input(0),
					_error(0),
					_dInput(0),
					_last_derivative(0),
					_d_lpf_alpha(PID_D_TERM_FILTER),
					_active(DISABLED),
					lastUpdate(0)
	{
	}

	PID(float kp, float ki, float kd, float imax) :
					_p(0),
					_i(0),
					_d(0),
					_integrator(0),
					_last_input(0),
					_error(0),
					_dInput(0),
					_last_derivative(0),
					_d_lpf_alpha(PID_D_TERM_FILTER),
					_active(ENABLED),
					lastUpdate(0)
	{
		Mav_Param::setup_object_defaults(this, var_info);
		_kP = kp;
		_kI = ki;
		_kD = kd;
		_iMax = imax;
	}

	float get_pid(float targetInput, float actualInput, float dt);
	float get_pi(float error);
	float get_p(float error);
	float get_i(float error, float dt);
	float get_d(float error, float dt);
	float get_error();
	float get_p_error_lim(float targetInput, float actualInput);

	void reset_I();
	float get_integrator();

	int get_mode();
	void set_active(bool activate);
	bool get_active();

	float get_pMax();
	bool is_k_zero();
	float get_kp();
	float get_ki();
	float get_kd();
	Mav_Float get_mav_kp();
	Mav_Float get_mav_ki();
	Mav_Float get_mav_kd();
	bool is_k_changed();
	void set_k_pid(PID* pid);
	void set_d_lpf_alpha(int16_t cutoff_frequency, float time_step);

	float get_p_term();
	float get_i_term();
	float get_d_term();

	static const struct Mav_Param::GroupInfo var_info[];
private:
	void Initialize();

	Mav_Float _kP;
	Mav_Float _kI;
	Mav_Float _kD;
	Mav_Float _iMax;
	Mav_Float _pMax;

	float _p, _i, _d;

	float _integrator;
	float _last_input;
	float _error;
	float _dInput;
	float _last_derivative;
	float _d_lpf_alpha;

	bool _active;
	uint32_t lastUpdate;

};

#endif

