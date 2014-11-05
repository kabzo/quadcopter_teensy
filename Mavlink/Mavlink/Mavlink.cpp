// Do not remove the include below
#include "Mavlink.h"

GCS_Mavlink GCS;

void comm_receive() {
	mavlink_message_t msg;
	mavlink_status_t status;

	//receive data over serial
	if(Serial.available() > 0) {
		uint8_t c = Serial.read();

		//try to get a new message
		if(mavlink_parse_char(MAVLINK_COMM_0, c, &msg, &status)) {
			// Handle message
 			switch(msg.msgid) {
			        case MAVLINK_MSG_ID_SET_MODE: {
			        	// set mode
			        }
			        break;

				default:
					//Do nothing
				break;
			}
		}
		// And get the next one
	}
}


void setup() {

	Serial.begin(57600);

//	GCS.send_hearthbeat(MAV_STATE_STANDBY, MAV_MODE_MANUAL_DISARMED);
	pinMode(13, OUTPUT);
	digitalWrite(13, LOW);

//	delay(500);
}

unsigned int lastTime = 0;
bool on = false;

void loop() {
	digitalWrite(13, on);

	if ((millis() - lastTime) > 1000) {
	GCS.send_hearthbeat(MAV_STATE_ACTIVE, MAV_MODE_AUTO_ARMED);
	on = !on;

		lastTime = millis();
	}
//	comm_receive();

}
