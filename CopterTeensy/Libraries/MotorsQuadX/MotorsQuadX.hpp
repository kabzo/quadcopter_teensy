#ifndef MOTOR_HPP_
#define MOTOR_HPP_

#ifndef Arduino_h
#include <Arduino.h>
#endif

#include <HIL.hpp>
#include <RC_Channel.hpp>
#include <Vector3.hpp>

#define MPINBL PIN23
#define MPINBR PIN22
#define MPINFR PIN21
#define MPINFL PIN20

#define NUMBER_OF_MOTORS 4

#define MAX_SIGNAL 2000
#define MIN_SIGNAL 1000

#define STARTING_THROTTLE_FLY 1100

#define CALIBRATEESC 0 //0 = initialize, 1 = calibrate, 2 = reset

#define ARM true
#define DISARM false

#define ESC_400HZ

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

class MotorsQuadX
{
public:

	MotorsQuadX(RC_Channel *rc1 = 0, RC_Channel *rc2 = 0, RC_Channel *rc3 = 0, RC_Channel *rc4 = 0) :

			_armed(false), _min_signal(MIN_SIGNAL), _max_signal(MAX_SIGNAL)
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

	bool is_armed() const;
	void set_armed(bool armed);

	bool is_ready_fly();
	bool check_radio_arm_pos();

	void set_speed_motor(motorNum num, float speed);
	void set_speet_motors(float speed);
	void set_motor_roll(float val);
	void set_motor_pitch(float val);
	void set_motor_yaw(float val);
	void set_motor_angles(Vector3Float& angles);
	void stop_motors();
	void motor_bounds();

	void write_motors_out(int32_t* motors_output);
	void mix_motors_out();

	void get_target_rc_roll_pitch(Vector3Float& v);

private:

	RC_Channel *_rc[4];
	enum PIN _motors_pins[4];
	bool _armed;
	int32_t motors_output[4];

	static uint32_t armRequestTime;
	static bool armRequest;
	uint16_t _min_signal;
	uint16_t _max_signal;

	void update_motor(float val, enum PIN pin);
	void init_motor(enum PIN pin);
	void init_pwm();
};

#endif /* MOTOR_HPP_ */
