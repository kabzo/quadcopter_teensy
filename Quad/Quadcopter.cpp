#include "Quadcopter.h"

controlAngle rollControll = { 0, 0, 0, PID(&(rollControll.angle), &(rollControll.setpoint), &(rollControll.output), 1,
		1, 1, DIRECT) };
controlAngle pitchControll = { 0, 0, 0, PID(&(rollControll.angle), &(rollControll.setpoint), &(rollControll.output), 1,
		1, 1, DIRECT) };
controlAngle yawControll = { 0, 0, 0, PID(&(rollControll.angle), &(rollControll.setpoint), &(rollControll.output), 1, 1,
		1, DIRECT) };

/////////////////////////FlightControll/////////////////////////
double throttle = THROTTLE_MIN;

MotorESC motorBL(MPINBL);
MotorESC motorFL(MPINFL);
MotorESC motorFR(MPINFR);
MotorESC motorBR(MPINBR);

IMU imu(&(yawControll.angle), &(pitchControll.angle), &(rollControll.angle));
/////////////////////////FlightControll/////////////////////////

/////////////////////////GUI Communication/////////////////////////
ArduinoCommunication arduinoCommunication(&(rollControll), &(pitchControll), &(yawControll), &imu, &throttle,
		&(motorBR.speed_), &(motorBL.speed_), &(motorFR.speed_), &(motorFL.speed_));
/////////////////////////GUI Communication/////////////////////////



//SoftwareSerial bluetooth(10, 11);

/**Maximal 2100 ninimal 1050 ESC signal write microseconds*/
void setup() {

	//bluetooth.begin(115200);
	imu.setDMP(); /**Initialize DMP if succed return true*/

	/**set GUI parameteras*/
	arduinoCommunication.sendOverSerial();
	/**set GUI parameteras*/

	Serial.println(F("Connect battery now you have 8 seconds"));
//	delay(8000);

	motorBR.initialize();
	motorBL.initialize();
	motorFR.initialize();
	motorFL.initialize();

	Serial.println(F("Start DMP"));
	imu.startDMP();

	Serial.println(F("START"));
	arduinoCommunication.setGuiValues();

}

void loop() {
	imu.getYPRdmp();

	rollControll.pid.Compute();
	pitchControll.pid.Compute();
	yawControll.pid.Compute();

//	motorBLpower = throttle + rollControll.output + pitchControll.output;
//	motorBRpower = throttle - rollControll.output + pitchControll.output;
//	motorFLpower = throttle + rollControll.output - pitchControll.output;
//	motorFRpower = throttle - rollControll.output - pitchControll.output;

//	motorBL.setMotorSpeed(throttle + rollControll.output + pitchControll.output);
//	motorBR.setMotorSpeed(throttle - rollControll.output + pitchControll.output);
//	motorFL.setMotorSpeed(throttle + rollControll.output - pitchControll.output);
//	motorFR.setMotorSpeed(throttle - rollControll.output - pitchControll.output);
//
	arduinoCommunication.serial_Communication_GUI_Csharp();

}
