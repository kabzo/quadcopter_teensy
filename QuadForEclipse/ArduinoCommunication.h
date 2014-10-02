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

#define TIMETOSEND 20

class ArduinoCommunication {
	public:
		ArduinoCommunication(controlAngle * rollControll, controlAngle * pitchControll, controlAngle * yawControll,
				IMU * imu, double * throttle, double * motorBRspeed, double * motorBLspeed, double * motorFRspeed,
				double * motorFLspeed) :
				throttle_(throttle), lastTime_(0), timeSendData_(TIMETOSEND), rollControll_(rollControll),
						pitchControll_(pitchControll), yawControll_(yawControll), imu_(imu) {

			for (int i = 0; i < 10; i++) {
				sendOverSerialArray[i] = 0;
				sendoverSerialName[i] = "";
			}
			sendOverSerialArray[0] = motorBRspeed;
			sendoverSerialName[0] = "br";
			sendOverSerialArray[1] = motorBLspeed;
			sendoverSerialName[1] = "bl";
			sendOverSerialArray[2] = motorFRspeed;
			sendoverSerialName[2] = "fr";
			sendOverSerialArray[3] = motorFLspeed;
			sendoverSerialName[3] = "fl";
			sendOverSerialArray[4] = throttle;
			sendoverSerialName[4] = "e";
			sendOverSerialArray[5] = &(rollControll->angle);
			sendoverSerialName[5] = "roll";
			sendOverSerialArray[6] = &(pitchControll->angle);
			sendoverSerialName[6] = "pitch";
			sendOverSerialArray[7] = &(yawControll->angle);
			sendoverSerialName[7] = "yaw";

		}
		void serial_Communication_GUI_Csharp();

//		template<class VALUE>
//		void addVariableToSend(double *, String);

		void sendOverSerial();
		void sendSerialVal(String str, double val);
		void setGuiValues();

		unsigned int getLastTime() const;
		void setLastTime(unsigned int lastTime);
		unsigned int getTimeSendData() const;
		void setTimeSendData(unsigned int timeSendData);

	private:
		double * throttle_;

		unsigned int lastTime_;
		unsigned int timeSendData_;

		double * sendOverSerialArray[10];	//max 10 ariables can this class be checking
		String sendoverSerialName[10];

		controlAngle * rollControll_;
		controlAngle * pitchControll_;
		controlAngle * yawControll_;

		IMU * imu_;
};

#endif /* ARDUINOCOMMUNICATION_H_ */
