/*
 * ESC.h
 *
 *  Created on: 18.7.2014
 *      Author: Juraj
 */

#ifndef ESC_H_
#define ESC_H_

namespace ESC {

	void calibrateThrottleESC(Servo s[], int length) {
		Serial.println(F("Starting calibrate"));
		Serial.print(F("Sending:"));
		Serial.println(MAX_SIGNAL);
		for (int i = 0; i < length; i++)
			s[i].writeMicroseconds(MAX_SIGNAL);

		delay(5000);

		Serial.print(F("Sending:"));
		Serial.println(MIN_SIGNAL);

		for (int i = 0; i < length; i++)
			s[i].writeMicroseconds(MIN_SIGNAL);
		Serial.println(F("Waiting for ESC 6 seconds"));
		delay(6000);
		Serial.println(F("DONE"));
	}

	void initializeESC() {
		motorFL.attach(MPINFL);
		motorFR.attach(MPINFR);
		motorBR.attach(MPINBR);
		motorBL.attach(MPINBL);
	}

	template<class VALUE>
	void setESCsignal(Servo s, VALUE val) {
		s.writeMicroseconds(val);
	}

	template<class VALUE>
	void setESCsignallAll(Servo s[], VALUE val[]) {
		for (int i = 0; i < 4; i++) {
			s[i].writeMicroseconds(val[i]);
		}
	}

	template<class VALUE>
	void setESCsignallAll(Servo s[], VALUE val) {
		for (int i = 0; i < 4; i++) {
			s[i].writeMicroseconds(val);
		}
		Serial.println(F("Waiting for ESC 6 seconds"));
		delay(6000);
	}

	void setMotorSpeed(Servo motor, long val){
		motor.writeMicroseconds(constrain(val,MIN_SIGNAL,MAX_SIGNAL));
	}
}

#endif /* ESC_H_ */
