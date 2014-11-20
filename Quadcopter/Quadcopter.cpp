#include "Quadcopter.h"

#include "Motors.hpp"
#include "Attitude.hpp"
/******************************************
 ****************SETUP*********************
 ******************************************/

uint8_t ledPin = 13;

void setup() {
	Serial.begin(115200); /*start communication*/

	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin,LOW);

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
void loop() {

	imu.getYPRdmp();

	pitch_pid.Compute();

	GCS.send_hearthbeat_1HZ();
	GCS.send_attitude(param_container.attitude_t);


	setMotorsSpeed();

}

void serialEvent() {
	GCS.mavlink_receive();
}
