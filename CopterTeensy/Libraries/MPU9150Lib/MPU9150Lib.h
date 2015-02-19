////////////////////////////////////////////////////////////////////////////
//
//  This file is part of MPU9150Lib
//
//  Copyright (c) 2013 Pansenti, LLC
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of 
//  this software and associated documentation files (the "Software"), to deal in 
//  the Software without restriction, including without limitation the rights to use, 
//  copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the 
//  Software, and to permit persons to whom the Software is furnished to do so, 
//  subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all 
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
//  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
//  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
//  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
//  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
//  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef _MPU9150LIB_H_
#define _MPU9150LIB_H_

#include <Arduino.h>
#include <HIL.hpp>
#include <MotionDriver_v5.1/dmpKey.h>
#include <MotionDriver_v5.1/dmpmap.h>
#include <MotionDriver_v5.1/inv_mpu.h>
#include <MotionDriver_v5.1/inv_mpu_dmp_motion_driver.h>
#include <I2Cdev.h>
#include <Math.hpp>

#define MPULIB_DEBUG

#define MAX_COMPASS_SAMPLE_RATE (100)

//  This symbol defines the scaled range for mag and accel values
#define SENSOR_RANGE   4096

typedef struct
{
	short valid;                        // should contain the valid pattern if a good config
	short magValid;                     // true if mag data valid
	short magMinX;                      // mag min x value
	short magMaxX;                      // mag max x value
	short magMinY;                      // mag min y value
	short magMaxY;                      // mag max y value
	short magMinZ;                      // mag min z value
	short magMaxZ;                      // mag max z value
	short accelValid;                   // true if accel data valid
	short accelMinX;                    // mag min x value
	short accelMaxX;                    // mag max x value
	short accelMinY;                    // mag min y value
	short accelMaxY;                    // mag max y value
	short accelMinZ;                    // mag min z value
	short accelMaxZ;                    // mag max z value
	short unused;                       // must be multiple of 32 bits for Due
} CALLIB_DATA;

#define M11 1.321
#define M12 0.023
#define M13 0.066

#define M21 0.002
#define M22 1.303
#define M23 -0.022

#define M31 0.031
#define M32 -0.002
#define M33 1.429

#define Bx 65.781
#define By -7.52
#define Bz -17.862

enum Ascale
{
		AFS_2G = 2,
		AFS_4G = 4,
		AFS_8G = 8,
		AFS_16G = 16
};

enum Gscale
{
		GFS_250DPS = 250,
		GFS_500DPS = 500,
		GFS_1000DPS = 1000,
		GFS_2000DPS = 2000
};



class MPU9150lib
{
public:

	// Constructor

	MPU9150lib();

	// init must be called to setup the MPU chip.
	// mpuRate is the update rate in Hz.
	// It returns false if something went wrong with the initialization.
	// magRate is the magnetometer update rate in Hz. magRate <= mpuRate.
	//   Also, magRate must be <= 100Hz.
	// lpf is the low pass filter setting - can be between 5Hz and 188Hz.
	//   0 means let the MotionDriver library decide.
	int init(	signed char orientation[9],
						int fifoRate,
						int mpuRate,
						int magRate = 10,
						int lpf = 0);

	//  read checks to see if there's been a new update.
	//  returns true if yes, false if not.
	int read();

	//  these variables are processed results
	Quaternion dmpQuaternion;
	Vector3Float dmpEuler;
	float heading;

	Vector3Int16 rawMag;
	Vector3Float calMag;

	Vector3Int16 rawGyro;
	Vector3Float calGyro;

	Vector3Int16 rawAccel;
	Vector3Float calAccel;

private:
	signed char gyro_orientation[9];


	static const Matrix3f orientation_mag_to_gyro;
	Matrix3f orientation_gyro_accel;


	CALLIB_DATA m_calData;                                    // calibration data

	byte m_device;                                            // IMU device index

	unsigned long m_magInterval;               // interval between mag reads in mS
	unsigned long m_lastMagSample;                       // last time mag was read
	Vector3Int16 m_magOffset; 	//  calibration data in processed form
	Vector3Float m_magScale;

	short m_accelXRange;										// range of accel X
	short m_accelYRange;										// range of accel Y
	short m_accelZRange;										// range of accel Z
//	long m_accelOffset[3];
	Vector3Int32 m_accelOffset;

	//  these variables are the values from the MPU
	long m_rawQuaternion[4];                 // the quaternion output from the DMP
	short m_rawAccel[3];                                      // raw accel data
	short m_rawMag[3];

	short m_rawGyro[3];                  // calibrated gyro output from the sensor
	Vector3Float gyroOffset;

	void getGres();
	void getAres();
	float aRes;
	float gRes;
	Gscale gScale = GFS_2000DPS;
	Ascale aScale = AFS_2G;

	int check_sacesfull(String str,
											int returnVal);

	//-----------------------------------------------------------------------------------------------------------------------//
	//-----------------------------------------------------------------------------------------------------------------------//
	//-----------------------------------------------------------------------------------------------------------------------//

	void mag_ypr_fusion();
	const float alphaYaw = 0.35;
	float yawFilteredOld;

	//-----------------------------------------------------------------------------------------------------------------------//
	//-----------------------------------------------------------------------------------------------------------------------//
	//-----------------------------------------------------------------------------------------------------------------------//
#define betaDef		0.1f		// 2 * proportional gain

	// Implementation of Sebastian Madgwick's "...efficient orientation filter for... inertial/magnetic sensor arrays"
	// (see http://www.x-io.co.uk/category/open-source/ for examples and more details)
	// which fuses acceleration, rotation rate, and magnetic moments to produce a quaternion-based estimate of absolute
	// device orientation -- which can be converted to yaw, pitch, and roll. Useful for stabilizing quadcopters, etc.
	// The performance of the orientation filter is at least as good as conventional Kalman-based filtering algorithms
	// but is much less computationally intensive---it can be performed on a 3.3 V Pro Mini operating at 8 MHz!
	void MadgwickAHRSupdateIMU(	float gx,
															float gy,
															float gz,
															float ax,
															float ay,
															float az);

	void MadgwickAHRSupdate(float gx,
													float gy,
													float gz,
													float ax,
													float ay,
													float az,
													float mx,
													float my,
													float mz);
	// global constants for 9 DoF fusion and AHRS (Attitude and Heading Reference System)
	float beta;   // compute beta

	//-----------------------------------------------------------------------------------------------------------------------//
	//-----------------------------------------------------------------------------------------------------------------------//
	//-----------------------------------------------------------------------------------------------------------------------//

	void AHRSupdate(float gx,
									float gy,
									float gz,
									float ax,
									float ay,
									float az,
									float mx,
									float my,
									float mz);
	// Set initial input parameters
#define Kp 2.0f			// proportional gain governs rate of convergence to accelerometer/magnetometer
#define Ki 0.005f		// integral gain governs rate of convergence of gyroscope biases
#define halfT 0.5f		// half the sample period

	// Variable definitions
	float q0, q1, q2, q3;	// quaternion elements representing the estimated orientation
	float exInt, eyInt, ezInt;	// scaled integral error

	//-----------------------------------------------------------------------------------------------------------------------//
	//-----------------------------------------------------------------------------------------------------------------------//
	//-----------------------------------------------------------------------------------------------------------------------//

	void transformation(float uncalibrated_values[3],
											float calibrated_values_raw[3]);
	void vector_length_stabilasation(float calibrated_values_raw[3]);
	//-----------------------------------------------------------------------------------------------------------------------//
	//-----------------------------------------------------------------------------------------------------------------------//
	//-----------------------------------------------------------------------------------------------------------------------//

#define sampleFreq	200.0f			// sample frequency in Hz
#define twoKpDef	(2.0f * 0.5f)	// 2 * proportional gain
#define twoKiDef	(2.0f * 0.0f)	// 2 * integral gain

	float twoKp;											// 2 * proportional gain (Kp)
	float twoKi;											// 2 * integral gain (Ki)
	float integralFBx, integralFBy, integralFBz;	// integral error terms scaled by Ki

	void MahonyAHRSupdate(float gx,
												float gy,
												float gz,
												float ax,
												float ay,
												float az,
												float mx,
												float my,
												float mz);
	void MahonyAHRSupdateIMU(	float gx,
														float gy,
														float gz,
														float ax,
														float ay,
														float az);
	float invSqrt(float x);

};

#endif // _MPU9150LIB_H_
