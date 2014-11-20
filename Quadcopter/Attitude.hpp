/*
 * Attitude.hpp
 *
 *  Created on: 10.11.2014
 *      Author: Juraj
 */

#ifndef ATTITUDE_HPP_
#define ATTITUDE_HPP_

void initializeImu(){

	GCS.setMavState(MAV_STATE_CALIBRATING);
	GCS.send_hearthbeat();

	if(!imu.setDMP()){

		GCS.setMavState(MAV_STATE_CRITICAL);
		GCS.setMavMode(MAV_MODE_PREFLIGHT);
		GCS.send_hearthbeat();

//		setMotorsSpeed(THROTTLE_MIN);

		while(true);
	}

	GCS.setMavState(MAV_STATE_ACTIVE);
	GCS.setMavMode(MAV_MODE_MANUAL_DISARMED);
	GCS.send_hearthbeat();



}



#endif /* ATTITUDE_HPP_ */
