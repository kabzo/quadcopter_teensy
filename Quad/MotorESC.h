#ifndef MOTOR_HPP_
#define MOTOR_HPP_

#ifndef Arduino_h
#include "Arduino.h"
#endif

#include "Servo.h"
#include "Config.h"

class MotorESC {
	public:
		MotorESC(int pin, String name) :
				speed_(THROTTLE_MIN), max_signal_(MAX_SIGNAL), min_signal_(MIN_SIGNAL), name_(name) {
			pin_ = pin;
			motor_.attach(pin);
		}

		void resetESC() {
			Serial.println(F("Reseting ESC"));
			Serial.print(F("Sending:"));
			Serial.println(max_signal_);
			motor_.writeMicroseconds(2100);
			delay(62500);
			Serial.print(F("Sending:"));
			Serial.println(min_signal_);
			motor_.writeMicroseconds(MIN_SIGNAL);
			Serial.println(F("Waiting for ESC 6 seconds"));
			delay(6000);
			Serial.println(F("DONE"));
		}

		void calibrate() {
			Serial.println(F("Starting calibrate"));
			Serial.print(F("Sending:"));
			Serial.println(max_signal_);
			motor_.writeMicroseconds(max_signal_);
			delay(5000);
			Serial.print(F("Sending:"));
			Serial.println(min_signal_);
			motor_.writeMicroseconds(MIN_SIGNAL);
			Serial.println(F("Waiting for ESC 6 seconds"));
			delay(6000);
			Serial.println(F("DONE"));
		}

		void initializeMinSignal() {
			Serial.println(F("Initialazing ESCs with MIN_SIGNAL"));
			motor_.writeMicroseconds(min_signal_);
		}

		void initialize() {
			motor_.attach(pin_);
			if (CALIBRATEESC == 1) {
				Serial.println(F("Calibrating ESCs"));
				calibrate();
			} else if (CALIBRATEESC == 0) {
				initializeMinSignal();
			} else if (CALIBRATEESC == 2) {
				resetESC();
			}
		}

		void setMotorSpeed(double speed) {
			speed_ = constrain(speed, min_signal_, max_signal_);
			motor_.writeMicroseconds(constrain(speed_, min_signal_, max_signal_));
		}

		double speed_;
	private:
		Servo motor_;
		unsigned int max_signal_;
		unsigned int min_signal_;
		unsigned int pin_;
		String name_;

};

#endif /* MOTOR_HPP_ */
