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
#include <MotionDriver_v6.1/dmpKey.h>
#include <MotionDriver_v6.1/dmpmap.h>
#include <MotionDriver_v6.1/inv_mpu.h>
#include <MotionDriver_v6.1/inv_mpu_dmp_motion_driver.h>
#include <I2Cdev.h>
#include <Math.hpp>

#define MPULIB_DEBUG
#define MAX_COMPASS_SAMPLE_RATE 100

typedef struct
{
		Vector3Int32 magMin;
		Vector3Int32 magMax;

		Vector3Int32 accelMax;
		Vector3Int32 accelMin;
} CALIBRATE_MPU;

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

#define G_TO_M_S 9.81
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
enum Sens
{
		GYRO,
		ACCEL,
		MAG
};


class IMU_MPU9150
{
	public:

		IMU_MPU9150();

		// init must be called to setup the MPU chip.
		// mpuRate is the update rate in Hz.
		// It returns false if something went wrong with the initialization.
		// magRate is the magnetometer update rate in Hz. magRate <= mpuRate.
		//   Also, magRate must be <= 100Hz.
		// lpf is the low pass filter setting - can be between 5Hz and 188Hz.
		int init_dmp(	signed char orientation[9],
									int fifoRate,
									int mpuRate,
									int magRate = 10,
									int lpf = 0);
		int init_raw(signed char orientation[9], int mpuRate, int magRate = 10, int lpf = 0);
		void init_param();

		//  read checks to see if there's been a new update.
		int read_dmp();
		int read_raw();

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

		/*
		 * Sensor init
		 */
		Mav_Float _lpf;
		Mav_Float _mpu_rate;
		/*
		 * Sensor init
		 */

		void set_lpf(float lpf);
		void set_mpu_rate(float rate);

		static bool check_max_min(CALIBRATE_MPU &calib, Vector3Int16 rawData, Sens sensor);
		static const struct Mav_Param::GroupInfo var_info[];
	private:
		/*
		 * Calibration Data
		 */
		CALIBRATE_MPU m_calibrate_Data;

		/*
		 * Orientation Matrix
		 */
		static const Matrix3f orientation_mag_to_gyro;
		Matrix3f orientation_gyro_accel;

		unsigned long m_magInterval;               // interval between mag reads in mS
		unsigned long m_lastMagSample;                       // last time mag was read
		Vector3Float m_magScale;

		Vector3Int32 m_accelOffset;
		Vector3Float m_magOffset; 	//  calibration data in processed form

		Vector3Float m_gyroOffset;

		float getGres();
		float getAres();
		float aRes;
		float gRes;
		Gscale gScale = GFS_2000DPS;
		Ascale aScale = AFS_2G;

		int check_sacesfull(String str, int returnVal);

		float compassHeadingTiltCompensatedRadians(	float pitch_radians,
																								float roll_radians,
																								Vector3Float xr);

		float m_lastDMPYaw;
		float m_lastYaw;
		Vector3Float dataFusion();
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
		void MadgwickAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az);

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

		void transformation(float uncalibrated_values[3], float calibrated_values_raw[3]);
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
		void MahonyAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az);
		float invSqrt(float x);

};

#endif // _MPU9150LIB_H_
