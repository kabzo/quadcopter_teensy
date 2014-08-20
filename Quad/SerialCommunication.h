/*
 * SerialCommunicationFunctions.h
 *
 *  Created on: 28.6.2014
 *      Author: Duri
 */

#ifndef SERIALCOMMUNICATIONFUNCTIONS_H_
#define SERIALCOMMUNICATIONFUNCTIONS_H_

/////////////////////////GUI Communication/////////////////////////
unsigned long timeToSendSerial = 40;
unsigned long lastTime = 0;
ArduinoCommunication arduinoCommunication;
/////////////////////////GUI Communication/////////////////////////

namespace SerialCommunicaion {

void setParametersGUI();
void setGuiForFirstTime();
void serialOutGUI();

void setParametersGUI() {

	if ((millis() - lastTime) >= timeToSendSerial) {
		SerialCommunicaion::serialOutGUI();

		arduinoCommunication.serialIn_GUI_Csharp();
		if (arduinoCommunication.getKp() != pidRoll.GetKp()
				|| arduinoCommunication.getKi() != pidRoll.GetKi()
				|| arduinoCommunication.getKd() != pidRoll.GetKd()) {
			pidRoll.SetTunings(arduinoCommunication.getKp(),
					arduinoCommunication.getKi(), arduinoCommunication.getKd());

			String stra[3];
			stra[0] = "pR/" + String(pidRoll.GetKp());
			stra[1] = "iR/" + String(pidRoll.GetKi());
			stra[2] = "dR/" + String(pidRoll.GetKd());
			arduinoCommunication.sendSerialArray(stra, 3);
		}

		if (arduinoCommunication.getKpPitch() != pidPitch.GetKp()
				|| arduinoCommunication.getKiPitch() != pidPitch.GetKi()
				|| arduinoCommunication.getKdPitch() != pidPitch.GetKd()) {
			pidPitch.SetTunings(arduinoCommunication.getKpPitch(),
					arduinoCommunication.getKiPitch(),
					arduinoCommunication.getKdPitch());

			String stra[3];
			stra[0] = "pP/" + String(pidPitch.GetKp());
			stra[1] = "iP/" + String(pidPitch.GetKi());
			stra[2] = "dP/" + String(pidPitch.GetKd());
			arduinoCommunication.sendSerialArray(stra, 3);
		}

		if (arduinoCommunication.getThrottle() != throttle) {
			throttle = arduinoCommunication.getThrottle();
		}

		lastTime = millis();

	}
}

void serialOutGUI() {
	arduinoCommunication.sendOverSerial();
	String str[3];
	str[0] = "pTp/" + String(pidPitch.GetPterm());
	str[1] = "iTp/" + String(pidPitch.GetIterm());
	str[2] = "dTp/" + String(pidPitch.GetDterm());
	arduinoCommunication.sendSerialArray(str, 3);

}

void setGuiForFirstTime() {
	arduinoCommunication.addVariableToSend(&roll, "roll");
	arduinoCommunication.addVariableToSend(&pitch, "pitch");
	arduinoCommunication.addVariableToSend(&yaw, "yaw");

	arduinoCommunication.addVariableToSend(&motorFLpower, "fl");
	arduinoCommunication.addVariableToSend(&motorFRpower, "fr");
	arduinoCommunication.addVariableToSend(&motorBLpower, "bl");
	arduinoCommunication.addVariableToSend(&motorBRpower, "br");

	arduinoCommunication.addVariableToSend(&throttle, "e");

	arduinoCommunication.setKd(pidRoll.GetKd());
	arduinoCommunication.setKi(pidRoll.GetKi());
	arduinoCommunication.setKp(pidRoll.GetKp());

	arduinoCommunication.setKdPitch(pidPitch.GetKd());
	arduinoCommunication.setKiPitch(pidPitch.GetKi());
	arduinoCommunication.setKpPitch(pidPitch.GetKp());

	arduinoCommunication.setThrottle(THROTTLE_MIN);

	String str[3];
	str[0] = "pR/" + String(pidRoll.GetKp());
	str[1] = "iR/" + String(pidRoll.GetKi());
	str[2] = "dR/" + String(pidRoll.GetKd());
	arduinoCommunication.sendSerialArray(str, 3);

	String stra[3];
	stra[0] = "pP/" + String(pidPitch.GetKp());
	stra[1] = "iP/" + String(pidPitch.GetKi());
	stra[2] = "dP/" + String(pidPitch.GetKd());
	arduinoCommunication.sendSerialArray(stra, 3);

}
}
#endif /* SERIALCOMMUNICATIONFUNCTIONS_H_ */
