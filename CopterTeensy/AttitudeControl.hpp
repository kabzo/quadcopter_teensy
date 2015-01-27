/*
 * Attitude.hpp
 *
 *  Created on: 10.11.2014
 *      Author: Juraj
 */

#ifndef COPTERARDUINODUE_ATTITUDE_HPP_
#define COPTERARDUINODUE_ATTITUDE_HPP_

//////////////////////////////////////////////////////FlightControll//////////////////////////////////////////////////
//PID roll_pid(	&param_container.attitude_t.roll,
//							&param_container.roll_pidOutput._value,
//							(float*) &param_container.manual_rcY._value,
//							&param_container.roll_kP._value,
//							&param_container.roll_kI._value,
//							&param_container.roll_kD._value,
//							DIRECT);
//PID pitch_pid(&param_container.attitude_t.pitch,
//							&param_container.pitch_pidOutput._value,
//							(float*) &param_container.manual_rcX._value,
//							&param_container.pitch_kP._value,
//							&param_container.pitch_kI._value,
//							&param_container.pitch_kD._value,
//							DIRECT);
//PID yaw_pid(&param_container.attitude_t.yaw,
//						&param_container.yaw_pidOutput._value,
//						(float*) &param_container.manual_rcR._value,
//						&param_container.yaw_kP._value,
//						&param_container.yaw_kI._value,
//						&param_container.yaw_kD._value,
//						DIRECT);
//////////////////////////////////////////////////////FlightControll//////////////////////////////////////////////////

void motorsInit()
{
	motorsQuad.init();

	GCS.send_hearthbeat(MAV_STATE_STANDBY, MAV_MODE_STABILIZE_DISARMED, 0);
}

void setMotorsSpeed(float speed)
{
	motorsQuad.setSpeedMotors(speed);
}

void setMotorsSpeed()
{

	if (motorsQuad.isArmed() && GCS.isGcsConnection())
	{
		motorsQuad.setSpeedMotor(MotorsQuad::BL, param_container.rc3.getScaled()
		//+ param_container.roll_pidOutput._value
																	+ param_container.pitch_pidOutput._value);
		motorsQuad.setSpeedMotor(MotorsQuad::BR,param_container.rc3.getScaled()
		//	- param_container.roll_pidOutput._value
																	+ param_container.pitch_pidOutput._value);
		motorsQuad.setSpeedMotor(MotorsQuad::FL, param_container.rc3.getScaled()
		//		+ param_container.roll_pidOutput._value
																	- param_container.pitch_pidOutput._value);
		motorsQuad.setSpeedMotor(MotorsQuad::FR, param_container.rc3.getScaled()
		//		- param_container.roll_pidOutput._value
																	- param_container.pitch_pidOutput._value);

	} else
		setMotorsSpeed (THROTTLE_MIN);
}

void initializeImu()
{
	GCS.send_hearthbeat(MAV_STATE_CALIBRATING, MAV_MODE_PREFLIGHT, 0);
	if (!imu.setDMP())
	{
		while (true)
		{
			GCS.send_hearthbeat(MAV_STATE_EMERGENCY,
													MAV_MODE_PREFLIGHT,
													MAV_MODE_FLAG_ENUM_END);
			setMotorsSpeed (THROTTLE_MIN);
			delay(1000);
		}
	}
	GCS.send_hearthbeat(MAV_STATE_CALIBRATING, MAV_MODE_STABILIZE_DISARMED, 0);
}

void getHeading()
{
	param_container.heading = atan2((double) param_container.vectorMag.y,
																	(double) param_container.vectorMag.x) * 180.0
			/ 3.14159265 + 180;
	while (param_container.heading < 0)
		param_container.heading += 360;
	while (param_container.heading > 360)
		param_container.heading -= 360;
}

uint32_t lastTime = 0;

void pidCompute()
{
	uint32_t actualTime = millis();

	param_container.roll_pidOutput =
			param_container.pid_roll.computeDirect(	param_container.vectorYpr.z,
																							param_container.rc1.getScaled(),
																							actualTime-PID::lastUpdate);

	param_container.pitch_pidOutput =
			param_container.pid_pitch.computeDirect(param_container.vectorYpr.y,
																							param_container.rc2.getScaled(),
																							actualTime-PID::lastUpdate);

	param_container.yaw_pidOutput =
			param_container.pid_pitch.computeDirect(param_container.vectorYpr.x,
																							param_container.rc4.getScaled(),
																							actualTime-PID::lastUpdate);
	PID::lastUpdate = millis();

//	Serial.println(param_container.roll_pidOutput._value);
//	uint32_t now = millis();
//	uint32_t dt = now - lastTime;
//	lastTime = millis();
//	if(dt>Thread::getPeriodThread(pidCompute)){
//		Serial.print("PID:");Serial.print(millis());Serial.print(",");
//		Serial.println(dt);
//	}

}

#endif /* COPTERARDUINODUE_ATTITUDE_HPP_ */
