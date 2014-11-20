/*
 * Motors.hpp
 *
 *  Created on: 10.11.2014
 *      Author: Juraj
 */

#ifndef MOTORS_HPP_
#define MOTORS_HPP_

void motorsInit() {

//	Serial.println(F("STARTING ESC INITIALAZING"));

#if CALIBRATEESC != 0
	motorBL.setSwitch(CALIBRATEESC);
	motorBR.setSwitch(CALIBRATEESC);
	motorFR.setSwitch(CALIBRATEESC);
	motorFL.setSwitch(CALIBRATEESC);
#endif

	motorBR.initialize();
	motorBL.initialize();
	motorFR.initialize();
	motorFL.initialize();

#if CALIBRATEESC == 0
	if (CALIBRATEESC == 0) {
//		Serial.println("Waiting 6 seconds for ESC");
//		delay(6000);
	}
#endif
}

void setMotorsSpeed() {

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

void setMotorsSpeed(float speed) {
	motorBL.setMotorSpeed(speed);
	motorBR.setMotorSpeed(speed);
	motorFL.setMotorSpeed(speed);
	motorFR.setMotorSpeed(speed);
}

#endif /* MOTORS_HPP_ */
