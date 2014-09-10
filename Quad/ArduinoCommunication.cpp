#include "ArduinoCommunication.h"

void ArduinoCommunication::sendSerialVal(String str, double val) {
	String send = "";
	send += ",";
	send += str;
	send += "/";
	send += String(val);
	send += ",";
	Serial.println(send);
}

void ArduinoCommunication::serial_Communication_GUI_Csharp() {
	if ((millis() - lastTime_) >= timeSendData_) {
		String inputString = "";         // a string to hold incoming data
		Serial.flush();
		char controlChar = '0';
		while (Serial.available()) {
			// get the new byte:
			char inChar = (char) Serial.read();
			if (controlChar == '0')
				controlChar = inChar;
			else
				inputString += inChar;
		}
		if (inputString != "" && controlChar != '0') {
			float val = inputString.toFloat() / 100;
			switch (controlChar) {
				/********************************PID ROLL********************************/
				case 'P': {		//konstant PID roll P
					this->rollControll_->pid.SetTunings(val, this->rollControll_->pid.GetKi(), this->rollControll_->pid.GetKd());
					sendSerialVal("pR", this->rollControll_->pid.GetKp());
					break;
				}
				case 'I': {		//konstant PID roll I
					this->rollControll_->pid.SetTunings(this->rollControll_->pid.GetKp(), val, this->rollControll_->pid.GetKd());
					sendSerialVal("iR", this->rollControll_->pid.GetKi());
					break;
				}
				case 'D': {		//konstant PID roll D
					this->rollControll_->pid.SetTunings(this->rollControll_->pid.GetKp(), this->rollControll_->pid.GetKi(), val);
					sendSerialVal("dR", this->rollControll_->pid.GetKd());
					break;
				}
				case 'X': {		//output limits PID roll
					this->rollControll_->pid.SetOutputLimits(-val, val);
					sendSerialVal("limR", this->rollControll_->pid.getOutMax());
					break;
				}
				case 'Y': {	//set sample time of PID roll
					this->rollControll_->pid.SetSampleTime(val);
					sendSerialVal("timeR", this->rollControll_->pid.getSampleTime());
					break;
				}
					/********************************PID ROLL********************************/

					/********************************PID PITCH********************************/
				case 'Q': {		//konstant PID pitch P
					this->pitchControll_->pid.SetTunings(val, this->pitchControll_->pid.GetKi(),
							this->pitchControll_->pid.GetKd());
					sendSerialVal("pP", this->pitchControll_->pid.GetKp());
					break;
				}
				case 'R': {		//konstant PID pitch I
					this->pitchControll_->pid.SetTunings(this->pitchControll_->pid.GetKp(), val,
							this->pitchControll_->pid.GetKd());
					sendSerialVal("iP", this->pitchControll_->pid.GetKi());
					break;
				}
				case 'W': {		//konstant PID pitch D
					this->pitchControll_->pid.SetTunings(this->pitchControll_->pid.GetKp(), this->pitchControll_->pid.GetKi(),
							val);
					sendSerialVal("dP", this->pitchControll_->pid.GetKd());
					break;
				}
				case 'B': {		//output limits PID roll
					this->pitchControll_->pid.SetOutputLimits(-val, val);
					sendSerialVal("limP", this->pitchControll_->pid.getOutMax());
					break;
				}
				case 'N': {	//set sample time of PID roll
					this->pitchControll_->pid.SetSampleTime(val);
					sendSerialVal("timeP", this->pitchControll_->pid.getSampleTime());
					break;
				}
					/********************************PID PITCH********************************/

					/********************************FLIGHT CONTROLL********************************/

				case 'E': {		//throttle power
					*throttle_ = val;
					sendSerialVal("e", *throttle_);
					break;
				}
				case 'U': {		//angle roll
					rollControll_->setpoint = val;
					sendSerialVal("setR", this->rollControll_->setpoint);

					break;
				}
				case 'L': {		//angle pitch
					pitchControll_->setpoint = val;
					sendSerialVal("setP", pitchControll_->setpoint);
					break;
				}
					/********************************FLIGHT CONTROLL********************************/

			}
			controlChar = '0';
			inputString = "";
		}

		sendOverSerial();
		lastTime_ = millis();
	}

}

void ArduinoCommunication::setGuiValues() {
	sendSerialVal("pR", this->rollControll_->pid.GetKp());
	sendSerialVal("iR", this->rollControll_->pid.GetKi());
	sendSerialVal("dR", this->rollControll_->pid.GetKd());
	sendSerialVal("limR", this->rollControll_->pid.getOutMax());
	sendSerialVal("timeR", this->rollControll_->pid.getSampleTime());

	sendSerialVal("pP", this->pitchControll_->pid.GetKp());
	sendSerialVal("iP", this->pitchControll_->pid.GetKi());
	sendSerialVal("dP", this->pitchControll_->pid.GetKd());
	sendSerialVal("limP", this->pitchControll_->pid.getOutMax());
	sendSerialVal("timeP", this->pitchControll_->pid.getSampleTime());
}

////template<typename VALUE>
//void ArduinoCommunication::addVariableToSend(double * value, String s) {
//	for (int i = 0; i < 10; i++) {
//		if (sendOverSerialArray[i] == 0) {
//			sendOverSerialArray[i] = value;
//			sendoverSerialName[i] = s;
//			break;
//		}
//	}
//}

void ArduinoCommunication::sendOverSerial() {
	String send = "";
	send += ",";
	for (int i = 0; i < 10; i++) {
		if (sendOverSerialArray[i] == 0) {
			break;
		}
		send += sendoverSerialName[i];
		send += "/";
		send += String(*sendOverSerialArray[i]);
		send += ",";
	}

#ifdef DEBUG
	send += "pTr/";
	send += this->rollControll_->pid.GetPterm();
	send += ",";
	send += "iTr/";
	send += this->rollControll_->pid.GetIterm();
	send += ",";
	send += "dTr/";
	send += this->rollControll_->pid.GetDterm();
	send += ",";
	send += "pTp/";
	send += this->pitchControll_->pid.GetPterm();
	send += ",";
	send += "iTp/";
	send += this->pitchControll_->pid.GetIterm();
	send += ",";
	send += "dTp/";
	send += this->pitchControll_->pid.GetDterm();
	send += ",";
#endif

	Serial.println(send);
}

unsigned int ArduinoCommunication::getLastTime() const {
	return lastTime_;
}

void ArduinoCommunication::setLastTime(unsigned int lastTime) {
	lastTime_ = lastTime;
}

unsigned int ArduinoCommunication::getTimeSendData() const {
	return timeSendData_;
}

void ArduinoCommunication::setTimeSendData(unsigned int timeSendData) {
	timeSendData_ = timeSendData;
}

