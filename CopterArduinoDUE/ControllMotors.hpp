/*
 * Motors.hpp
 *
 *  Created on: 10.11.2014
 *      Author: Juraj
 */

#ifndef COPTERARDUINODUE_CONTROLLMOTORS_HPP_
#define COPTERARDUINODUE_CONTROLLMOTORS_HPP_

MotorESC motorBL(MPINBL);
MotorESC motorFL(MPINFL);
MotorESC motorFR(MPINFR);
MotorESC motorBR(MPINBR);

void motorsInit()
{
	motorBR.initialize(CALIBRATEESC);
	motorBL.initialize(CALIBRATEESC);
	motorFR.initialize(CALIBRATEESC);
	motorFL.initialize(CALIBRATEESC);
}

void setMotorsSpeed()
{

	if (GCS.getMavMode() == MAV_MODE_MANUAL_ARMED && GCS.isGcsConnection()) {
		motorBL.setMotorSpeed(param_container.manual_rcZ._value
				+ param_container.roll_pidOutput._value
				+ param_container.pitch_pidOutput._value);
		motorBR.setMotorSpeed(param_container.manual_rcZ._value
				- param_container.roll_pidOutput._value
				+ param_container.pitch_pidOutput._value);
		motorFL.setMotorSpeed(param_container.manual_rcZ._value
				+ param_container.roll_pidOutput._value
				- param_container.pitch_pidOutput._value);
		motorFR.setMotorSpeed(param_container.manual_rcZ._value
				- param_container.roll_pidOutput._value
				- param_container.pitch_pidOutput._value);
	} else {
		motorBL.setMotorSpeed(THROTTLE_MIN);
		motorBR.setMotorSpeed(THROTTLE_MIN);
		motorFL.setMotorSpeed(THROTTLE_MIN);
		motorFR.setMotorSpeed(THROTTLE_MIN);

	}
}

void setMotorsSpeed(float speed)
{
	motorBL.setMotorSpeed(speed);
	motorBR.setMotorSpeed(speed);
	motorFL.setMotorSpeed(speed);
	motorFR.setMotorSpeed(speed);
}

#endif /* COPTERARDUINODUE_CONTROLLMOTORS_HPP_ */
