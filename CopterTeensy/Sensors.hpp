/*
 * Sensors.hpp
 *
 *  Created on: 11.2.2015
 *      Author: Juraj
 */

#ifndef SENSORS_HPP_
#define SENSORS_HPP_

#define MPU_UPDATE_RATE  (100)
#define DMP_FIFO_UPDATE_RATE  (100)

//  MAG_UPDATE_RATE defines the rate (in Hz) at which the MPU updates the magnetometer data
//  MAG_UPDATE_RATE should be less than or equal to the MPU_UPDATE_RATE
#define MAG_UPDATE_RATE  (50)

//  MPU_LPF_RATE is the low pas filter rate and can be between 5 and 188Hz
#define MPU_LPF_RATE   98

// signed char gyro_orientation[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
signed char gyro_orientation[9] = { 0, 1, 0, -1, 0, 0, 0, 0, 1 };

Matrix3i orientation(0, 1, 0, -1, 0, 0, 0, 0, 1);

void interrupt_lpf(float val)
{
	imu.set_lpf(val);
}
void interrupt_mpu_rate(float val)
{
	imu.set_mpu_rate(val);
}

void init_imu()
{
	Wire.begin(I2C_MASTER, 0x68, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_800);
	delay(1000);

//	int status = imu.init_dmp(gyro_orientation,DMP_FIFO_UPDATE_RATE, MPU_UPDATE_RATE, MAG_UPDATE_RATE);
	int status = imu.init_raw(gyro_orientation, MPU_UPDATE_RATE, MAG_UPDATE_RATE, MPU_LPF_RATE);

	if (status != 1)
	{
		while (true)
		{
			GCS.send_hearthbeat(MAV_STATE_EMERGENCY, MAV_MODE_PREFLIGHT, MAV_MODE_FLAG_ENUM_END);
			delay(1000);
		}
	}

	imu._lpf.attache_interrupt(interrupt_lpf);
	imu._mpu_rate.attache_interrupt(interrupt_mpu_rate);

}

#endif /* SENSORS_HPP_ */
