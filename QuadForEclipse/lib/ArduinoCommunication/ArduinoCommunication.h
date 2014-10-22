#ifndef ARDUINOCOMMUNICATION_H_
#define ARDUINOCOMMUNICATION_H_

#ifndef Arduino_h
#include "Arduino.h"
#endif

#ifndef PID_h
#include "PID.h"
#endif

#ifndef IMU_H_
#include "IMU.h"
#endif

#include "Typedef.h"
#include "MotorESC.h"

#define TIMESENDFAST 20
#define TIMESENDSLOW 100

#define DEBUG_SERIAL
class ArduinoCommunication {
	public:
		ArduinoCommunication(
				controlAngle * rollControll, controlAngle * pitchControll, controlAngle * yawControll,
				IMU * imu,
				double * throttle,
				double * motorBRspeed, double * motorBLspeed, double * motorFRspeed, double * motorFLspeed):
				receivedControll(false), inputString(""),throttle_(throttle), lastTimeFast_(0),
				lastTimeSlow_(0), timeSendDataFast_(TIMESENDFAST), timeSendDataSlow_(TIMESENDSLOW),
				rollControll_(rollControll), pitchControll_(pitchControll), yawControll_(yawControll), imu_(imu) {
			*throttle_ = THROTTLE_MIN;
			for (int i = 0; i < 10; i++) {
				sendOverSerialArrayFast[i] = 0;
				sendoverSerialNameFast[i] = "";
				sendOverSerialArraySlow[i] = 0;
				sendoverSerialNameSlow[i] = "";
			}
			sendOverSerialArraySlow[0] = motorBRspeed;
			sendoverSerialNameSlow[0] = "br";
			sendOverSerialArraySlow[1] = motorBLspeed;
			sendoverSerialNameSlow[1] = "bl";
			sendOverSerialArraySlow[2] = motorFRspeed;
			sendoverSerialNameSlow[2] = "fr";
			sendOverSerialArraySlow[3] = motorFLspeed;
			sendoverSerialNameSlow[3] = "fl";

			sendOverSerialArrayFast[0] = &(rollControll->angle);
			sendoverSerialNameFast[0] = "roll";
			sendOverSerialArrayFast[1] = &(pitchControll->angle);
			sendoverSerialNameFast[1] = "pitch";
			sendOverSerialArrayFast[2] = &(yawControll->angle);
			sendoverSerialNameFast[2] = "yaw";
		}

		void serial_Communication_GUI_Csharp();

		void sendOverSerial();
		void sendSerialVal(String str, double val);
		void setGuiValues();

		void receiveStringSerial(){
			inputString = Serial.readStringUntil('|');
			receivedControll = true;
		}

		void setTimeSendData(unsigned int timeSendData);
		void setControlChar(const char& controlChar);

	private:
		bool receivedControll;
		String inputString;
		double * throttle_;

		unsigned int lastTimeFast_;
		unsigned int lastTimeSlow_;
		unsigned int timeSendDataFast_;
		unsigned int timeSendDataSlow_;

		double * sendOverSerialArrayFast[10];	//max 10 ariables can this class be checking
		String sendoverSerialNameFast[10];
		double * sendOverSerialArraySlow[10];	//max 10 ariables can this class be checking
		String sendoverSerialNameSlow[10];

		controlAngle * rollControll_;
		controlAngle * pitchControll_;
		controlAngle * yawControll_;

		IMU * imu_;
};

#endif /* ARDUINOCOMMUNICATION_H_ */
