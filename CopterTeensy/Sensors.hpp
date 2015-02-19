/*
 * Sensors.hpp
 *
 *  Created on: 11.2.2015
 *      Author: Juraj
 */

#ifndef SENSORS_HPP_
#define SENSORS_HPP_

#define MPU_UPDATE_RATE  (400)
#define FIFO_UPDATE_RATE  (100)

//  MAG_UPDATE_RATE defines the rate (in Hz) at which the MPU updates the magnetometer data
//  MAG_UPDATE_RATE should be less than or equal to the MPU_UPDATE_RATE
#define MAG_UPDATE_RATE  (50)

//  MPU_LPF_RATE is the low pas filter rate and can be between 5 and 188Hz
#define MPU_LPF_RATE   98

// signed char gyro_orientation[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
 signed char gyro_orientation[9] = { 0, 1, 0,
		 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 -1, 0, 0,
																		 0, 0, 1 };


void init_imu()
{
	GCS.send_hearthbeat(MAV_STATE_CALIBRATING, MAV_MODE_PREFLIGHT, 0);

	Wire.begin(I2C_MASTER, 0x68, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_800);

	delay(1000);

	int status = imu.init(gyro_orientation,FIFO_UPDATE_RATE, MPU_UPDATE_RATE, MAG_UPDATE_RATE, MPU_LPF_RATE);
	if (status != 1)
	{
		while (true)
		{
			GCS.send_hearthbeat(MAV_STATE_EMERGENCY, MAV_MODE_PREFLIGHT, MAV_MODE_FLAG_ENUM_END);
			delay(1000);
		}
	}

	GCS.send_hearthbeat(MAV_STATE_CALIBRATING, MAV_MODE_STABILIZE_DISARMED, 0);
}



#endif /* SENSORS_HPP_ */
