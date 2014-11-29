/*
 * GCS.hpp
 *
 *  Created on: 22.11.2014
 *      Author: Juraj
 */

#ifndef COPTERARDUINODUE_GCS_HPP_
#define COPTERARDUINODUE_GCS_HPP_

void sendToGCS_1HZ()
{
	GCS.send_hearthbeat();
}

void sendToGCS_40HZ()
{
	mavlink_attitude_t mav_attitude;

	mav_attitude.pitch = param_container.attitude_t.pitch;
	mav_attitude.roll = param_container.attitude_t.roll;
	mav_attitude.yaw = param_container.attitude_t.yaw;

//	mav_attitude.pitchspeed = param_container.attitude_t.pitchspeed;
//	mav_attitude.rollspeed = param_container.attitude_t.rollspeed;
//	mav_attitude.yawspeed = param_container.attitude_t.yawspeed;

	mav_attitude.time_boot_ms = millis();

	GCS.send_attitude(mav_attitude);

}

#endif /* COPTERARDUINODUE_GCS_HPP_ */
