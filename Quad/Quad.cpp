#include "Quad.h"
#include "Variables.h"
#include "serialCommunication.h"
#include "IMU.h"
#include "ESC.h"

//SoftwareSerial bluetooth(10, 11);

//**Maximal 2100 ninimal 1050 ESC signal write microseconds
void setup() {
	//bluetooth.begin(115200);
	boolean devStatus = IMU::setDMP(); 	//Initialize DMP if succed return true

	pidRoll.SetSampleTime(PIDTIME);
	pidRoll.SetMode(AUTOMATIC);
	pidRoll.SetOutputLimits(MIN_PID, MAX_PID);

	pidPitch.SetSampleTime(PIDTIME);
	pidPitch.SetMode(AUTOMATIC);
	pidPitch.SetOutputLimits(MIN_PID, MAX_PID);

	pidYaw.SetSampleTime(PIDTIME);
	pidYaw.SetMode(AUTOMATIC);
	pidYaw.SetOutputLimits(MIN_PID, MAX_PID);

	SerialCommunicaion::setGuiForFirstTime();

	Servo s[4];
	s[0] = motorBL;
	s[1] = motorFL;
	s[2] = motorBR;
	s[3] = motorFR;

	Serial.println(F("Connect battery now you have 8 seconds"));
	delay(8000);
	ESC::initializeESC();

	if (calibrateESC) {
		Serial.println(F("Calibrating ESCs"));
		ESC::calibrateThrottleESC(s, 4);
	} else {
		Serial.println(F("Initialazing ESCs with MIN_SIGNAL"));
		ESC::setESCsignallAll(s, MIN_SIGNAL);
	}

	Serial.println(F("Start DMP"));
	IMU::startDMP(devStatus);

	Serial.println(F("START"));
}

void loop() {
	IMU::getYPRdmp();
	//pidRoll.Compute();
	pidPitch.Compute();
	//pidYaw.Compute();
	motorBLpower = throttle + outputRoll + outputPitch;
	motorBRpower = throttle - outputRoll + outputPitch;
	motorFLpower = throttle + outputRoll - outputPitch;
	motorFRpower = throttle - outputRoll - outputPitch;

	ESC::setMotorSpeed(motorBR,constrain(motorBRpower, 1000, 1500));
	ESC::setMotorSpeed(motorBL,constrain(motorBLpower, 1000, 1500));
	ESC::setMotorSpeed(motorFR,constrain(motorFRpower, 1000, 1500));
	ESC::setMotorSpeed(motorFL,constrain(motorFLpower, 1000, 1500));

	SerialCommunicaion::setParametersGUI();
}

