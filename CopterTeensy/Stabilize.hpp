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
	con.stab_pid_pitch.reset_I();
	con.stab_pid_roll.reset_I();
	con.stab_pid_yaw.reset_I();

	con.rate_pid_pitch.reset_I();
	con.rate_pid_roll.reset_I();
	con.rate_pid_yaw.reset_I();

	con.targetHeading = radToCentiDeg(imu.dmpEuler.YAW);

	con.roll_pidOutput = 0;
	con.pitch_pidOutput = 0;
	con.yaw_pidOutput = 0;
}


void stabilize()
{

	if (!attitudeControl.is_ready())
		return;

	uint32_t now = micros();
	uint32_t dt = now - attitudeControl.get_last_update_pid();

	attitudeControl.stab_roll_pitch_yaw(dt);
	attitudeControl.rate_roll_pitch_yaw(dt);

	motorsQuad.set_motor_angles(attitudeControl.get_rate_output());
	motorsQuad.mix_motors_out();

	attitudeControl.set_last_update_pid(now);

//	long rcPitch = con.rc2.getScaled();
//	float pitch = radToCentiDeg(imu.dmpEuler.PITCH);
//	float gyroPitch = toCentiDeg(imu.calGyro.y);
//
//	long rcRoll = con.rc1.getScaled();
//	float roll = radToCentiDeg(imu.dmpEuler.ROLL);
//	float gyroRoll = toCentiDeg(imu.calGyro.x);
//
//	long rcYaw = con.targetHeading;
//	float yaw = radToCentiDeg(imu.dmpEuler.YAW);
//	float gyroYaw = toCentiDeg(imu.calGyro.x);
//
//	if (con.stab_pid_pitch.get_kp() != 0 || con.stab_pid_pitch.get_ki() != 0 || con.stab_pid_pitch.get_kd() != 0)
//	{
//		con.pitch_pidOutput = con.stab_pid_pitch.get_pid(rcPitch, pitch, dt);
//		con.pitch_pidOutput -= con.stab_pid_pitch.get_integrator();
//
//		con.roll_pidOutput = con.stab_pid_roll.get_pid(rcRoll, roll, dt);
//		con.roll_pidOutput -= con.stab_pid_roll.get_integrator();
//
//		con.yaw_pidOutput = con.stab_pid_yaw.get_pid(rcYaw, yaw, dt);
//		con.yaw_pidOutput -= con.stab_pid_yaw.get_integrator();
//	} else
//	{
//		con.pitch_pidOutput = rcPitch;
//		con.roll_pidOutput = rcRoll;
//		con.yaw_pidOutput = rcYaw;
//	}
//
//	if (con.rate_pid_pitch.get_kp() != 0 || con.rate_pid_pitch.get_ki() != 0 || con.rate_pid_pitch.get_kd() != 0)
//	{
//		con.pitch_pidOutput = con.rate_pid_pitch.get_pid(con.pitch_pidOutput._value, gyroPitch, dt);
//		con.pitch_pidOutput += con.stab_pid_pitch.get_integrator();
//
//		con.roll_pidOutput = con.rate_pid_roll.get_pid(con.roll_pidOutput._value, gyroRoll, dt);
//		con.roll_pidOutput += con.stab_pid_roll.get_integrator();
//
//		con.yaw_pidOutput = con.rate_pid_yaw.get_pid(con.yaw_pidOutput._value, gyroYaw, dt);
//		con.yaw_pidOutput += con.stab_pid_yaw.get_integrator();
//	}
//
//	PID::_lastRunned = now;
//
//	motorsQuad.set_motor_pitch(con.pitch_pidOutput);
//	motorsQuad.set_motor_roll(con.roll_pidOutput);
//	motorsQuad.set_motor_yaw(con.yaw_pidOutput);

//	Serial.println(con.pitch_pidOutput);

//	motorsQuad.mix_motors_out();

//	setMotorsSpeed();

}

#endif /* COPTERARDUINODUE_ATTITUDE_HPP_ */
