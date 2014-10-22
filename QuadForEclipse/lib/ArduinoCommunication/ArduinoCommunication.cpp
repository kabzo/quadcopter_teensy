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

	if (receivedControll) {
		receivedControll = false;
		char conChar = inputString[0];
		inputString = inputString.substring(1);
		switch (conChar) {
			/********************************PID ROLL********************************/
			case 'P': {		//konstant PID roll P
				float val = inputString.toFloat() / 100;
				this->rollControll_->pid.SetTunings(val, this->rollControll_->pid.GetKi(), this->rollControll_->pid.GetKd());
#if defined(DEBUG_SERIAL)
				sendSerialVal("pR", this->rollControll_->pid.GetKp());
#endif
				break;
			}
			case 'I': {		//konstant PID roll I
				float val = inputString.toFloat() / 100;
				this->rollControll_->pid.SetTunings(this->rollControll_->pid.GetKp(), val, this->rollControll_->pid.GetKd());
#if defined(DEBUG_SERIAL)
				sendSerialVal("iR", this->rollControll_->pid.GetKi());
#endif
				break;
			}
			case 'D': {		//konstant PID roll
				float val = inputString.toFloat() / 100;
				this->rollControll_->pid.SetTunings(this->rollControll_->pid.GetKp(), this->rollControll_->pid.GetKi(), val);
#if defined(DEBUG_SERIAL)
				sendSerialVal("dR", this->rollControll_->pid.GetKd());
#endif
				break;
			}
			case 'X': {		//output limits PID roll
				float val = inputString.toFloat() / 100;
				this->rollControll_->pid.SetOutputLimits(-val, val);
#if defined(DEBUG_SERIAL)
				sendSerialVal("limR", this->rollControll_->pid.getOutMax());
#endif
				break;
			}
			case 'Y': {	//set sample time of PID roll
				float val = inputString.toFloat() / 100;
				this->rollControll_->pid.SetSampleTime(val);
#if defined(DEBUG_SERIAL)

				sendSerialVal("timeR", this->rollControll_->pid.getSampleTime());
#endif
				break;
			}
				/********************************PID ROLL********************************/
				/********************************PID PITCH********************************/
			case 'Q': {		//konstant PID pitch P
				float val = inputString.toFloat() / 100;
				this->pitchControll_->pid.SetTunings(val, this->pitchControll_->pid.GetKi(), this->pitchControll_->pid.GetKd());
#if defined(DEBUG_SERIAL)
				sendSerialVal("pP", this->pitchControll_->pid.GetKp());
#endif
				break;
			}
			case 'R': {		//konstant PID pitch I
				float val = inputString.toFloat() / 100;
				this->pitchControll_->pid.SetTunings(this->pitchControll_->pid.GetKp(), val, this->pitchControll_->pid.GetKd());
#if defined(DEBUG_SERIAL)
				sendSerialVal("iP", this->pitchControll_->pid.GetKi());
#endif
				break;
			}
			case 'W': {		//konstant PID pitch D
				float val = inputString.toFloat() / 100;
				this->pitchControll_->pid.SetTunings(this->pitchControll_->pid.GetKp(), this->pitchControll_->pid.GetKi(), val);
#if defined(DEBUG_SERIAL)
				sendSerialVal("dP", this->pitchControll_->pid.GetKd());
#endif

				break;
			}
			case 'B': {		//output limits PID roll
				float val = inputString.toFloat() / 100;
				this->pitchControll_->pid.SetOutputLimits(-val, val);
#if defined(DEBUG_SERIAL)
				sendSerialVal("limP", this->pitchControll_->pid.getOutMax());
#endif
				break;
			}
			case 'N': {	//set sample time of PID roll
				float val = inputString.toFloat() / 100;
				this->pitchControll_->pid.SetSampleTime(val);
#if defined(DEBUG_SERIAL)

				sendSerialVal("timeP", this->pitchControll_->pid.getSampleTime());
#endif
				break;
			}
				/********************************PID PITCH********************************/
				/********************************FLIGHT CONTROLL********************************/
				//String : K/throttle/roll/pitch/yaw/|
			case 'K': {		//throttle power
				int trpy[4];
				for (int i = 0; i < 4; i++) {
					String str;
					str = inputString.substring(0, inputString.indexOf('/'));
					trpy[i] = str.toInt();
					inputString = inputString.substring(inputString.indexOf('/') + 1);
				}
				this->rollControll_->setpoint = trpy[1];
				this->pitchControll_->setpoint = trpy[2];
				*throttle_ = (float) trpy[0];
#if defined(DEBUG_SERIAL)
				sendSerialVal("setR", this->rollControll_->setpoint);
				sendSerialVal("setP", this->pitchControll_->setpoint);
				sendSerialVal("e", *throttle_);
#endif
				break;
			}
				/********************************FLIGHT CONTROLL********************************/
		}
		inputString = "";
	}

}

void ArduinoCommunication::setGuiValues() {
	Serial.println("Setting GUI values for the first time...");
	Serial.println("-");
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
	Serial.println("-");

}

void ArduinoCommunication::sendOverSerial() {
	if ((millis() - lastTimeSlow_) >= timeSendDataSlow_) {
		String send = "";
		send += ",";
		for (int i = 0; i < 10; i++) {
			if (sendOverSerialArraySlow[i] == 0) {
				break;
			}
			send += sendoverSerialNameSlow[i];
			send += "/";
			send += String(*sendOverSerialArraySlow[i]);
			send += ",";
		}

#if defined(DEBUG_ALL)
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
		lastTimeSlow_ = millis();
	}

	if ((millis() - lastTimeFast_) >= timeSendDataFast_) {
		String send = "";
		send += ",";
		for (int i = 0; i < 10; i++) {
			if (sendOverSerialArrayFast[i] == 0) {
				break;
			}
			send += sendoverSerialNameFast[i];
			send += "/";
			send += String(*sendOverSerialArrayFast[i]);
			send += ",";
		}
		Serial.println(send);
		lastTimeFast_ = millis();
	}
}

