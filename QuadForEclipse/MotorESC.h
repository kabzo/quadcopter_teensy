#ifndef MOTOR_HPP_
#define MOTOR_HPP_

#ifndef Arduino_h
#include "Arduino.h"
#endif

#include "Servo.h"

#define THROTTLE_MIN 1000
#define MAX_SIGNAL 2000
#define MIN_SIGNAL 1000

#define CALIBRATE 0

class MotorESC {
	public:
		MotorESC(int pin, String name) :
				speed_(THROTTLE_MIN), max_signal_(MAX_SIGNAL), min_signal_(MIN_SIGNAL), name_(name), _switch(CALIBRATE){
			pin_ = pin;
			motor_.attach(pin);
		}

		void resetESC() {
			Serial.println(F("Reseting ESC"));
			Serial.print(F("Sending:"));
			Serial.println(max_signal_);
			motor_.writeMicroseconds(max_signal_);
			delay(62500);
			Serial.print(F("Sending:"));
			Serial.println(min_signal_);
			motor_.writeMicroseconds(min_signal_);
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
			motor_.writeMicroseconds(min_signal_);
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
			if (_switch == 1) {
				Serial.println(F("Calibrating ESCs"));
				calibrate();
			} else if (_switch == 0) {
				initializeMinSignal();
			} else if (_switch == 2) {
				resetESC();
			}
		}

		void setMotorSpeed(double speed) {
			speed_ = constrain(speed, min_signal_, max_signal_);
			motor_.writeMicroseconds(constrain(speed_, min_signal_, max_signal_));
		}

		void setSwitch(unsigned int switch_){
			_switch = switch_;
		}

		double speed_;
	private:
		Servo motor_;
		unsigned int max_signal_;
		unsigned int min_signal_;
		unsigned int pin_;
		String name_;
		unsigned int _switch;

};

#endif /* MOTOR_HPP_ */
