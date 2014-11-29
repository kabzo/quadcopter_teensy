#include "CopterArduinoDUE.h"
#include "ControllMotors.hpp"
#include "Attitude.hpp"
#include "GCS.hpp"

Thread::Task Thread::_tasks[] = {
		THREADTASK(sendToGCS_1HZ,1000,true),
		THREADTASK(sendToGCS_40HZ,100,true),
		THREADEND
	};

uint8_t Thread::_num_tasks = Thread::countTasks();

/******************************************
 ****************SETUP*********************
 ******************************************/

uint8_t ledPin = 13;

void setup()
{
	Serial.begin(115200); /*start communication*/

	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, LOW);

	GCS.waitGCSconnect();

	digitalWrite(ledPin, HIGH);

	initializeImu();

	motorsInit();

	imu.startDMP();

	Serial.println(F("START"));
}

/******************************************
 ****************LOOP**********************
 ******************************************/
void loop()
{

	imu.getYPRdmp();

	pitch_pid.Compute();

//	setMotorsSpeed();

	Thread::run(millis());

}

void serialEvent()
{
	GCS.mavlink_receive();
}
