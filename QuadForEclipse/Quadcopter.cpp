#include "Quadcopter.h"

/******************************************
 ****************SETUP*********************
 ******************************************/

void setup() {
	Serial.begin(115200); /**start communication*/
	Serial.println("QUADCOPTER FIRMWARE");

	imu.setDMP(); /**Initialize DMP */

	Serial.println(F("Connect battery now you have 8 seconds"));

#if CALIBRATEESC != 0
	motorBL.setSwitch(CALIBRATEESC);
	motorBR.setSwitch(CALIBRATEESC);
	motorFR.setSwitch(CALIBRATEESC);
	motorFL.setSwitch(CALIBRATEESC);
#endif

	delay(8000);

	motorBR.initialize();
	motorBL.initialize();
	motorFR.initialize();
	motorFL.initialize();

#if CALIBRATEESC == 0
	if (CALIBRATEESC == 0) {
		Serial.println("Waiting 6 seconds for ESC");
		delay(6000);
		Serial.println("after");
	}
#endif

	/**set GUI parameteras*/
	Serial.println("Setting GUI:");
	arduinoCommunication.sendOverSerial();
	Serial.print("..");
	arduinoCommunication.setGuiValues();
	Serial.println(F("DONE!"));
	/**set GUI parameteras*/

	Serial.println(F("Start DMP"));
	imu.startDMP();

	Serial.println(F("START"));

}

/******************************************
 ****************LOOP**********************
 ******************************************/

void loop() {
	imu.getYPRdmp();

	rollControll.pid.Compute();
//	pitchControll.pid.Compute();
//	yawControll.pid.Compute();

	motorBL.setMotorSpeed(throttle + rollControll.output + pitchControll.output);
	motorBR.setMotorSpeed(throttle - rollControll.output + pitchControll.output);
	motorFL.setMotorSpeed(throttle + rollControll.output - pitchControll.output);
	motorFR.setMotorSpeed(throttle - rollControll.output - pitchControll.output);

	arduinoCommunication.sendOverSerial();
}

void serialEvent() {
	arduinoCommunication.serial_Communication_GUI_Csharp();
}
