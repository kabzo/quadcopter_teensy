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

//  MPU_MAG_MIX defines the influence that the magnetometer has on the yaw output.
//  The magnetometer itself is quite noisy so some mixing with the gyro yaw can help
//  significantly. Some example values are defined below:
#define  MPU_MAG_MIX_GYRO_ONLY          0                   // just use gyro yaw
#define  MPU_MAG_MIX_MAG_ONLY           1                   // just use magnetometer and no gyro yaw
#define  MPU_MAG_MIX_GYRO_AND_MAG       10                  // a good mix value
#define  MPU_MAG_MIX_GYRO_AND_SOME_MAG  50                  // mainly gyros with a bit of mag correction

//  MPU_LPF_RATE is the low pas filter rate and can be between 5 and 188Hz
#define MPU_LPF_RATE   98

void initializeImu()
{
	GCS.send_hearthbeat(MAV_STATE_CALIBRATING, MAV_MODE_PREFLIGHT, 0);

	Wire.begin(I2C_MASTER, 0x68, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_800);

	delay(1000);

	int status = imu.init(FIFO_UPDATE_RATE, MPU_UPDATE_RATE, MPU_MAG_MIX_GYRO_AND_MAG, MAG_UPDATE_RATE, MPU_LPF_RATE);
	if (status != 1)
	{
		while (true)
		{
			GCS.send_hearthbeat(MAV_STATE_EMERGENCY, MAV_MODE_PREFLIGHT, MAV_MODE_FLAG_ENUM_END);
			motorsQuad.set_speet_motors(THROTTLE_MIN);
			delay(1000);
		}
	}

	GCS.send_hearthbeat(MAV_STATE_CALIBRATING, MAV_MODE_STABILIZE_DISARMED, 0);
}



#endif /* SENSORS_HPP_ */
