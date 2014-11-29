/*
 * Attitude.hpp
 *
 *  Created on: 10.11.2014
 *      Author: Juraj
 */

#ifndef COPTERARDUINODUE_ATTITUDE_HPP_
#define COPTERARDUINODUE_ATTITUDE_HPP_

IMU imu(&param_container.attitude_t);

void initializeImu()
{

	GCS.send_hearthbeat(MAV_STATE_CALIBRATING,MAV_MODE_PREFLIGHT,MAV_MODE_FLAG_MANUAL_INPUT_ENABLED);

	if (!imu.setDMP()) {

		GCS.send_hearthbeat(MAV_STATE_CRITICAL,MAV_MODE_PREFLIGHT,MAV_MODE_FLAG_ENUM_END);
		setMotorsSpeed(THROTTLE_MIN);

		while (true)
			;
	}
	GCS.send_hearthbeat(MAV_STATE_ACTIVE,MAV_MODE_MANUAL_DISARMED,MAV_MODE_FLAG_MANUAL_INPUT_ENABLED);
}

#endif /* COPTERARDUINODUE_ATTITUDE_HPP_ */
