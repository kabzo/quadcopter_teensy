/*
 * Attitude.hpp
 *
 *  Created on: 10.11.2014
 *      Author: Juraj
 */

#ifndef COPTERARDUINODUE_ATTITUDE_HPP_
#define COPTERARDUINODUE_ATTITUDE_HPP_

void resetPid()
{
//	con.stab_pid_pitch.reset_I();
//	con.stab_pid_roll.reset_I();
//	con.stab_pid_yaw.reset_I();
//
//	con.rate_pid_pitch.reset_I();
//	con.rate_pid_roll.reset_I();
//	con.rate_pid_yaw.reset_I();

//	con.targetHeading = radToCentiDeg(imu.dmpEuler.YAW);

//	con.roll_pidOutput = 0;
//	con.pitch_pidOutput = 0;
//	con.yaw_pidOutput = 0;
}

uint32_t lastT = 0;

void stabilize()
{
//		uint32_t noww = micros();
//		float diff = (noww - lastT) / 1000;
//		if(diff)
//		Serial.println(diff);
//		lastT = noww;

	if (!attitudeControl.is_ready())
		return;

	uint32_t now = micros();
	uint32_t dt = now - attitudeControl.get_last_update_pid();

	attitudeControl.stab_roll_pitch_yaw(dt);
	attitudeControl.rate_roll_pitch_yaw(dt);

	motorsQuad.set_motor_angles(attitudeControl.get_rate_output());
	motorsQuad.mix_motors_out();

	attitudeControl.set_last_update_pid(now);
}

#endif /* COPTERARDUINODUE_ATTITUDE_HPP_ */
