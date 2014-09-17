#include "Quadcopter.h"

/////////////////////////FlightControll/////////////////////////

controlAngle rollControll = { 0, 0, 0, PID(&(rollControll.angle), &(rollControll.output), &(rollControll.setpoint), 1,
		0, 0, DIRECT) };
controlAngle pitchControll = { 0, 0, 0, PID(&(pitchControll.angle), &(pitchControll.output), &(pitchControll.setpoint),
		1, 0, 1, DIRECT) };
controlAngle yawControll = { 0, 0, 0, PID(&(yawControll.angle), &(yawControll.output), &(yawControll.setpoint), 1, 0, 1,
DIRECT) };

double throttle = THROTTLE_MIN;

MotorESC motorBL(MPINBL, "motorBL");
MotorESC motorFL(MPINFL, "motorFL");
MotorESC motorFR(MPINFR, "motorFR");
MotorESC motorBR(MPINBR, "motorBR");

IMU imu(&(yawControll.angle), &(pitchControll.angle), &(rollControll.angle));
/////////////////////////FlightControll/////////////////////////

/////////////////////////GUI Communication/////////////////////////
ArduinoCommunication arduinoCommunication(&(rollControll), &(pitchControll), &(yawControll), &imu, &throttle,
		&(motorBR.speed_), &(motorBL.speed_), &(motorFR.speed_), &(motorFL.speed_));
/////////////////////////GUI Communication/////////////////////////

/******************************************
 ****************SETUP*********************
 ******************************************/

void setup() {
	Serial.begin(115200); /**start communication*/
	Serial.println("QUADCOPTER FIRMWARE");

	imu.setDMP(); /**Initialize DMP if succed return true*/

	Serial.println(F("Connect battery now you have 8 seconds"));
	delay(8000);

	motorBR.initialize();
	motorBL.initialize();
	motorFR.initialize();
	motorFL.initialize();
	if (CALIBRATEESC == 0)
		delay(6000);

	/**set GUI parameteras*/
	arduinoCommunication.sendOverSerial();
	arduinoCommunication.setGuiValues();
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
//
//	Serial.println(rollControll.output);
	arduinoCommunication.sendOverSerial();
}

void serialEvent() {
	arduinoCommunication.serial_Communication_GUI_Csharp();
}
