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

#include <MPU9150Lib.h>
#include <Vector3.hpp>

const Matrix3f MPU9150lib::orientation_mag_to_gyro(0,1,0,
																									 	1,0,0,
																										0,0,-1);

MPU9150lib::MPU9150lib() :
				yawFilteredOld(0),
				beta(betaDef),
				q0(1),
				q1(0),
				q2(0),
				q3(0),
				exInt(0),
				eyInt(0),
				ezInt(0),
				twoKp(twoKpDef),
				twoKi(twoKiDef),
				integralFBx(0),
				integralFBy(0),
				integralFBz(0)
{
	m_device = 0;
	mpu_select_device(m_device);
	dmp_select_device(m_device);

	getAres();
	getGres();

	//  Process calibration data for runtime
	m_calData.magMinX = -214;
	m_calData.magMaxX = 192;
	m_calData.magMinY = -150;
	m_calData.magMaxY = 284;
	m_calData.magMinZ = -203;
	m_calData.magMaxZ = 227;

	//Accelerometer
	m_calData.accelMinX = -32768;
	m_calData.accelMaxX = 32767;
	m_calData.accelMinY = -12578;
	m_calData.accelMaxY = 23440;
	m_calData.accelMinZ = -32768;
	m_calData.accelMaxZ = 32767;

	gyroOffset = Vector3Float(1.83, -5.08, -3.23);
}

int MPU9150lib::init(signed char orientation[9],int fifoRate, int mpuRate, int magRate, int lpf)
{

	//-----------------------------------------------------------------------------------------------------------------------//
	//----------------------------------------MAG CALIBRATION----------------------------------------------------------------//
	//-----------------------------------------------------------------------------------------------------------------------//

	m_magOffset(m_calData.magMaxX + m_calData.magMinX, m_calData.magMaxY + m_calData.magMinY, m_calData.magMaxZ + m_calData.magMinZ);
	m_magOffset*=0.5;

	Vector3Int16 m_magRangeMax(m_calData.magMaxX - m_magOffset.x, m_calData.magMaxY - m_magOffset.y, m_calData.magMaxZ - m_magOffset.z);
	Vector3Int16 m_magRangeMin(m_calData.magMinX - m_magOffset.x, m_calData.magMinY - m_magOffset.y, m_calData.magMinZ - m_magOffset.z);

	Vector3Float avgs(m_magRangeMax.x + m_magRangeMin.x * -1, m_magRangeMax.y + m_magRangeMin.y * -1, m_magRangeMax.z + m_magRangeMin.z * -1);
	avgs*=0.5;
	float avg_rad = avgs.average();
	m_magScale(avg_rad / avgs.x, avg_rad / avgs.y, avg_rad / avgs.z);

	//-----------------------------------------------------------------------------------------------------------------------//
	//----------------------------------------MAG CALIBRATION----------------------------------------------------------------//
	//-----------------------------------------------------------------------------------------------------------------------//

	//-----------------------------------------------------------------------------------------------------------------------//
	//----------------------------------------ACCEL CALIBRATION--------------------------------------------------------------//
	//-----------------------------------------------------------------------------------------------------------------------//

	m_accelOffset.x = ((long) m_calData.accelMaxX + (long) m_calData.accelMinX) / 2;
	m_accelOffset.y = ((long) m_calData.accelMaxY + (long) m_calData.accelMinY) / 2;
	m_accelOffset.z = ((long) m_calData.accelMaxZ + (long) m_calData.accelMinZ) / 2;
	long accel_bias[3];
	m_accelOffset.get_array(accel_bias);
	mpu_set_accel_bias(accel_bias);

	m_accelXRange = m_calData.accelMaxX - (short) m_accelOffset.x;
	m_accelYRange = m_calData.accelMaxY - (short) m_accelOffset.y;
	m_accelZRange = m_calData.accelMaxZ - (short) m_accelOffset.z;

	//-----------------------------------------------------------------------------------------------------------------------//
	//----------------------------------------ACCEL CALIBRATION--------------------------------------------------------------//
	//-----------------------------------------------------------------------------------------------------------------------//

	mpu_init_structures();
	// Not using interrupts so set up this structure to keep the driver happy
	struct int_param_s int_param;

	int_param.cb = NULL;
	int_param.pin = 0;
	int_param.lp_exit = 0;
	int_param.active_low = 1;

	if (check_sacesfull("mpu_init", mpu_init(&int_param)) != 0)
		return -1;

	if (check_sacesfull("mpu_set_sensors", mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL | INV_XYZ_COMPASS)) != 0)
		return -2;  // enable all of the sensors

	if (check_sacesfull("mpu_configure_fifo", mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL)) != 0)
		return -3;  	 // get accel and gyro data in the FIFO also

	mpuRate = constrain(mpuRate, 1, 1000); //mpu betweeh 1-1000hz
	if (check_sacesfull("mpu_set_sample_rate", mpu_set_sample_rate(mpuRate)) != 0)
		return -4;

	if (check_sacesfull("mpu_set_gyro_fsr", mpu_set_gyro_fsr(gScale)) != 0)
		return -5;

	if (check_sacesfull("mpu_set_accel_fsr", mpu_set_accel_fsr(aScale)) != 0)
		return -6;

	if (check_sacesfull("dmp_load_motion_driver_firmware", dmp_load_motion_driver_firmware()) != 0)
		return -7;

	if (check_sacesfull("dmp_enable_6x_lp_quat", dmp_enable_6x_lp_quat(true)) != 0)
		return -7;

	memcpy(gyro_orientation,orientation,sizeof(signed char)*9);
	orientation_gyro_accel(orientation);
	if (check_sacesfull("dmp_set_orientation", dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation))) != 0)
		return -8;   // set up the correct orientation

	if (check_sacesfull("dmp_enable_feature", dmp_enable_feature(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO |
	DMP_FEATURE_GYRO_CAL)) != 0)
		return -9;

	if (check_sacesfull("dmp_enable_gyro_cal", dmp_enable_gyro_cal(true)) != 0)
		return -8;

	if (check_sacesfull("dmp_set_fifo_rate", dmp_set_fifo_rate(fifoRate)) != 0)
		return -10;

	if (check_sacesfull("mpu_set_dmp_state", mpu_set_dmp_state(1)) != 0)
		return -11;

	magRate = constrain(magRate, 1, MAX_COMPASS_SAMPLE_RATE); // rate must be less than or equal to 100Hz
	m_magInterval = (unsigned long) (1000 / magRate);       // record mag interval
	m_lastMagSample = millis();
	if (check_sacesfull("mpu_set_compass_sample_rate", mpu_set_compass_sample_rate(magRate)) != 0)
		return -12;	 // set the compass update rate to match

	if (check_sacesfull("mpu_set_lpf", mpu_set_lpf(lpf)) != 0)
		return -13;  // set the low pass filter

	return true;
}

int MPU9150lib::read()
{
	short intStatus;
	short sensors;
	unsigned char more;
	unsigned long timestamp;

	if (mpu_get_int_status(&intStatus) != 0)
		return -1;   // get the current MPU state

	if (intStatus & MPU_INT_STATUS_FIFO_OVERFLOW)
	{
		mpu_reset_fifo();
		GCS._serial.println("fifp owerflou");
		return -2;
	}
	if ((intStatus & (MPU_INT_STATUS_DMP | MPU_INT_STATUS_DMP_0)) != (MPU_INT_STATUS_DMP | MPU_INT_STATUS_DMP_0))
	{
		//Serial.println(intStatus,BIN);
		return -3;
	}

		//get the data from the fifo
	if ((dmp_read_fifo(m_rawGyro, m_rawAccel, m_rawQuaternion, &timestamp, &sensors, &more)) != 0)
	{
		return -4;
	}

	dmpQuaternion.setQuaternion(m_rawQuaternion);   // get float version of quaternion
	dmpQuaternion.normalize();
	dmpEuler.quaternion_to_ypr(dmpQuaternion);

	//  got the fifo data so now get the mag data if it's time
	if ((millis() - m_lastMagSample) >= m_magInterval)
	{
		if (check_sacesfull("mpu_get_compass_reg", mpu_get_compass_reg(m_rawMag, &timestamp)) != 0)
			return -5;
		m_lastMagSample = millis();
		//	*** Note mag axes are changed here to align with gyros: Y=X,X=Y,Z=-Z

		short mx = m_rawMag[VEC3_X];
		short my = m_rawMag[VEC3_Y];
		short mz = m_rawMag[VEC3_Z];
		rawMag(mx, my, mz);

		calMag(mx-m_magOffset.x,my-m_magOffset.y,mz-m_magOffset.z);
		calMag*=m_magScale;

		calMag = orientation_mag_to_gyro*calMag;
		calMag = orientation_gyro_accel*calMag;
	}

	short ax = m_rawAccel[VEC3_X];
	short ay = m_rawAccel[VEC3_Y];
	short az = m_rawAccel[VEC3_Z];
	rawAccel(ax, ay, az);
	calAccel.x = ax - m_accelOffset.x;
	calAccel.y = ay - m_accelOffset.y;
	calAccel.z = az - m_accelOffset.z;
	calAccel*=(aRes);

	// Scale gyro data
	rawGyro.setVector(m_rawGyro);
	calGyro.setVector(m_rawGyro);
	calGyro = Vector3Float(m_rawGyro[0] - gyroOffset.x, m_rawGyro[1] - gyroOffset.y, m_rawGyro[2] - gyroOffset.z);
	calGyro*=(gRes);

	mag_ypr_fusion();

//	dataFusion();

//	MahonyAHRSupdate(radians(calGyro.x), radians(calGyro.y), radians(calGyro.z), rawAccel.x, rawAccel.y, rawAccel.z, calMag.x, calMag.y, calMag.z);
//	heading = atan2(2.0f * (q2 * q0 - q1 * q3), 1 - 2 * q2 * q2 - 2 * q3 * q3);
	return 1;
}

void MPU9150lib::mag_ypr_fusion()
{
	float xMagnetMap = calMag.x;
	float yMagnetMap = calMag.y;
	float zMagnetMap = calMag.z;

	float norm = sqrt(sq(xMagnetMap) + sq(yMagnetMap) + sq(zMagnetMap));
	xMagnetMap /= norm;
	yMagnetMap /= norm;
	zMagnetMap /= norm;

	float Pitch = dmpEuler.PITCH;
	float Roll = dmpEuler.ROLL;
	//compare "Applications of Magnetic Sensors for Low Cost Compass Systems" by Michael J. Caruso
	//for the compensated Yaw equations...
	//http://www.ssec.honeywell.com/magnetic/datasheets/lowcost.pdf
	float yawRaw = atan2(	(-yMagnetMap * cos(Roll) + zMagnetMap * sin(Roll)),
												(xMagnetMap * cos(Pitch) + yMagnetMap * sin(Pitch) * sin(Roll) + zMagnetMap * sin(Pitch) * cos(Roll)));

	//apply Low Pass to Yaw
	//Digital Low Pass - compare: (for accelerometer)
	//http://en.wikipedia.org/wiki/Low-pass_filter
	heading = yawFilteredOld + alphaYaw * (yawRaw - yawFilteredOld);
	yawFilteredOld = heading;
}

int MPU9150lib::check_sacesfull(String str, int returnVal)
{
	if (returnVal != 0)
	{
		DEBUGLN3(str, "FAILED", returnVal);
		return returnVal;
	}
	return 0;
}

void MPU9150lib::getGres()
{
	switch (gScale) {
		// Possible gyro scales (and their register bit settings) are:
		// 250 DPS (00), 500 DPS (01), 1000 DPS (10), and 2000 DPS  (11).
		// Here's a bit of an algorith to calculate DPS/(ADC tick) based on that 2-bit value:
		case GFS_250DPS:
			gRes = 250.0 / 32768.0;
			break;
		case GFS_500DPS:
			gRes = 500.0 / 32768.0;
			break;
		case GFS_1000DPS:
			gRes = 1000.0 / 32768.0;
			break;
		case GFS_2000DPS:
			gRes = 2000.0 / 32768.0;
			break;
	}
}

void MPU9150lib::getAres()
{
	switch (aScale) {
		// Possible accelerometer scales (and their register bit settings) are:
		// 2 Gs (00), 4 Gs (01), 8 Gs (10), and 16 Gs  (11).
		// Here's a bit of an algorith to calculate DPS/(ADC tick) based on that 2-bit value:
		case AFS_2G:
			aRes = 2.0 / 32768.0;
			break;
		case AFS_4G:
			aRes = 4.0 / 32768.0;
			break;
		case AFS_8G:
			aRes = 8.0 / 32768.0;
			break;
		case AFS_16G:
			aRes = 16.0 / 32768.0;
			break;
	}
}

void MPU9150lib::MadgwickAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz)
{
	float recipNorm;
	float s0, s1, s2, s3;
	float qDot1, qDot2, qDot3, qDot4;
	float hx, hy;
	float _2q0mx, _2q0my, _2q0mz, _2q1mx, _2bx, _2bz, _4bx, _4bz, _2q0, _2q1, _2q2, _2q3, _2q0q2, _2q2q3, q0q0, q0q1, q0q2, q0q3, q1q1, q1q2, q1q3,
			q2q2, q2q3, q3q3;

	// Use IMU algorithm if magnetometer measurement invalid (avoids NaN in magnetometer normalisation)
	if ((mx == 0.0f) && (my == 0.0f) && (mz == 0.0f))
	{
		MadgwickAHRSupdateIMU(gx, gy, gz, ax, ay, az);
		return;
	}

	// Rate of change of quaternion from gyroscope
	qDot1 = 0.5f * (-q1 * gx - q2 * gy - q3 * gz);
	qDot2 = 0.5f * (q0 * gx + q2 * gz - q3 * gy);
	qDot3 = 0.5f * (q0 * gy - q1 * gz + q3 * gx);
	qDot4 = 0.5f * (q0 * gz + q1 * gy - q2 * gx);

	// Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
	if (!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f)))
	{

		// Normalise accelerometer measurement
		recipNorm = invSqrt(ax * ax + ay * ay + az * az);
		ax *= recipNorm;
		ay *= recipNorm;
		az *= recipNorm;

		// Normalise magnetometer measurement
		recipNorm = invSqrt(mx * mx + my * my + mz * mz);
		mx *= recipNorm;
		my *= recipNorm;
		mz *= recipNorm;

		// Auxiliary variables to avoid repeated arithmetic
		_2q0mx = 2.0f * q0 * mx;
		_2q0my = 2.0f * q0 * my;
		_2q0mz = 2.0f * q0 * mz;
		_2q1mx = 2.0f * q1 * mx;
		_2q0 = 2.0f * q0;
		_2q1 = 2.0f * q1;
		_2q2 = 2.0f * q2;
		_2q3 = 2.0f * q3;
		_2q0q2 = 2.0f * q0 * q2;
		_2q2q3 = 2.0f * q2 * q3;
		q0q0 = q0 * q0;
		q0q1 = q0 * q1;
		q0q2 = q0 * q2;
		q0q3 = q0 * q3;
		q1q1 = q1 * q1;
		q1q2 = q1 * q2;
		q1q3 = q1 * q3;
		q2q2 = q2 * q2;
		q2q3 = q2 * q3;
		q3q3 = q3 * q3;

		// Reference direction of Earth's magnetic field
		hx = mx * q0q0 - _2q0my * q3 + _2q0mz * q2 + mx * q1q1 + _2q1 * my * q2 + _2q1 * mz * q3 - mx * q2q2 - mx * q3q3;
		hy = _2q0mx * q3 + my * q0q0 - _2q0mz * q1 + _2q1mx * q2 - my * q1q1 + my * q2q2 + _2q2 * mz * q3 - my * q3q3;
		_2bx = sqrt(hx * hx + hy * hy);
		_2bz = -_2q0mx * q2 + _2q0my * q1 + mz * q0q0 + _2q1mx * q3 - mz * q1q1 + _2q2 * my * q3 - mz * q2q2 + mz * q3q3;
		_4bx = 2.0f * _2bx;
		_4bz = 2.0f * _2bz;

		// Gradient decent algorithm corrective step
		s0 = -_2q2 * (2.0f * q1q3 - _2q0q2 - ax) + _2q1 * (2.0f * q0q1 + _2q2q3 - ay)
				- _2bz * q2 * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx)
				+ (-_2bx * q3 + _2bz * q1) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my)
				+ _2bx * q2 * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
		s1 = _2q3 * (2.0f * q1q3 - _2q0q2 - ax) + _2q0 * (2.0f * q0q1 + _2q2q3 - ay) - 4.0f * q1 * (1 - 2.0f * q1q1 - 2.0f * q2q2 - az)
				+ _2bz * q3 * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx)
				+ (_2bx * q2 + _2bz * q0) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my)
				+ (_2bx * q3 - _4bz * q1) * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
		s2 = -_2q0 * (2.0f * q1q3 - _2q0q2 - ax) + _2q3 * (2.0f * q0q1 + _2q2q3 - ay) - 4.0f * q2 * (1 - 2.0f * q1q1 - 2.0f * q2q2 - az)
				+ (-_4bx * q2 - _2bz * q0) * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx)
				+ (_2bx * q1 + _2bz * q3) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my)
				+ (_2bx * q0 - _4bz * q2) * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
		s3 = _2q1 * (2.0f * q1q3 - _2q0q2 - ax) + _2q2 * (2.0f * q0q1 + _2q2q3 - ay)
				+ (-_4bx * q3 + _2bz * q1) * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx)
				+ (-_2bx * q0 + _2bz * q2) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my)
				+ _2bx * q1 * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
		recipNorm = invSqrt(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3); // normalise step magnitude
		s0 *= recipNorm;
		s1 *= recipNorm;
		s2 *= recipNorm;
		s3 *= recipNorm;

		// Apply feedback step
		qDot1 -= beta * s0;
		qDot2 -= beta * s1;
		qDot3 -= beta * s2;
		qDot4 -= beta * s3;
	}

	// Integrate rate of change of quaternion to yield quaternion
	q0 += qDot1 * (1.0f / sampleFreq);
	q1 += qDot2 * (1.0f / sampleFreq);
	q2 += qDot3 * (1.0f / sampleFreq);
	q3 += qDot4 * (1.0f / sampleFreq);

	// Normalise quaternion
	recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
	q0 *= recipNorm;
	q1 *= recipNorm;
	q2 *= recipNorm;
	q3 *= recipNorm;
}

void MPU9150lib::MadgwickAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az)
{
	float recipNorm;
	float s0, s1, s2, s3;
	float qDot1, qDot2, qDot3, qDot4;
	float _2q0, _2q1, _2q2, _2q3, _4q0, _4q1, _4q2, _8q1, _8q2, q0q0, q1q1, q2q2, q3q3;

	// Rate of change of quaternion from gyroscope
	qDot1 = 0.5f * (-q1 * gx - q2 * gy - q3 * gz);
	qDot2 = 0.5f * (q0 * gx + q2 * gz - q3 * gy);
	qDot3 = 0.5f * (q0 * gy - q1 * gz + q3 * gx);
	qDot4 = 0.5f * (q0 * gz + q1 * gy - q2 * gx);

	// Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
	if (!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f)))
	{

		// Normalise accelerometer measurement
		recipNorm = invSqrt(ax * ax + ay * ay + az * az);
		ax *= recipNorm;
		ay *= recipNorm;
		az *= recipNorm;

		// Auxiliary variables to avoid repeated arithmetic
		_2q0 = 2.0f * q0;
		_2q1 = 2.0f * q1;
		_2q2 = 2.0f * q2;
		_2q3 = 2.0f * q3;
		_4q0 = 4.0f * q0;
		_4q1 = 4.0f * q1;
		_4q2 = 4.0f * q2;
		_8q1 = 8.0f * q1;
		_8q2 = 8.0f * q2;
		q0q0 = q0 * q0;
		q1q1 = q1 * q1;
		q2q2 = q2 * q2;
		q3q3 = q3 * q3;

		// Gradient decent algorithm corrective step
		s0 = _4q0 * q2q2 + _2q2 * ax + _4q0 * q1q1 - _2q1 * ay;
		s1 = _4q1 * q3q3 - _2q3 * ax + 4.0f * q0q0 * q1 - _2q0 * ay - _4q1 + _8q1 * q1q1 + _8q1 * q2q2 + _4q1 * az;
		s2 = 4.0f * q0q0 * q2 + _2q0 * ax + _4q2 * q3q3 - _2q3 * ay - _4q2 + _8q2 * q1q1 + _8q2 * q2q2 + _4q2 * az;
		s3 = 4.0f * q1q1 * q3 - _2q1 * ax + 4.0f * q2q2 * q3 - _2q2 * ay;
		recipNorm = invSqrt(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3); // normalise step magnitude
		s0 *= recipNorm;
		s1 *= recipNorm;
		s2 *= recipNorm;
		s3 *= recipNorm;

		// Apply feedback step
		qDot1 -= beta * s0;
		qDot2 -= beta * s1;
		qDot3 -= beta * s2;
		qDot4 -= beta * s3;
	}

	// Integrate rate of change of quaternion to yield quaternion
	q0 += qDot1 * (1.0f / sampleFreq);
	q1 += qDot2 * (1.0f / sampleFreq);
	q2 += qDot3 * (1.0f / sampleFreq);
	q3 += qDot4 * (1.0f / sampleFreq);

	// Normalise quaternion
	recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
	q0 *= recipNorm;
	q1 *= recipNorm;
	q2 *= recipNorm;
	q3 *= recipNorm;
}

void MPU9150lib::MahonyAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz)
{
	float recipNorm;
	float q0q0, q0q1, q0q2, q0q3, q1q1, q1q2, q1q3, q2q2, q2q3, q3q3;
	float hx, hy, bx, bz;
	float halfvx, halfvy, halfvz, halfwx, halfwy, halfwz;
	float halfex, halfey, halfez;
	float qa, qb, qc;

	// Use IMU algorithm if magnetometer measurement invalid (avoids NaN in magnetometer normalisation)
	if ((mx == 0.0f) && (my == 0.0f) && (mz == 0.0f))
	{
		MahonyAHRSupdateIMU(gx, gy, gz, ax, ay, az);
		return;
	}

	// Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
	if (!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f)))
	{

		// Normalise accelerometer measurement
		recipNorm = invSqrt(ax * ax + ay * ay + az * az);
		ax *= recipNorm;
		ay *= recipNorm;
		az *= recipNorm;

		// Normalise magnetometer measurement
		recipNorm = invSqrt(mx * mx + my * my + mz * mz);
		mx *= recipNorm;
		my *= recipNorm;
		mz *= recipNorm;

		// Auxiliary variables to avoid repeated arithmetic
		q0q0 = q0 * q0;
		q0q1 = q0 * q1;
		q0q2 = q0 * q2;
		q0q3 = q0 * q3;
		q1q1 = q1 * q1;
		q1q2 = q1 * q2;
		q1q3 = q1 * q3;
		q2q2 = q2 * q2;
		q2q3 = q2 * q3;
		q3q3 = q3 * q3;

		// Reference direction of Earth's magnetic field
		hx = 2.0f * (mx * (0.5f - q2q2 - q3q3) + my * (q1q2 - q0q3) + mz * (q1q3 + q0q2));
		hy = 2.0f * (mx * (q1q2 + q0q3) + my * (0.5f - q1q1 - q3q3) + mz * (q2q3 - q0q1));
		bx = sqrt(hx * hx + hy * hy);
		bz = 2.0f * (mx * (q1q3 - q0q2) + my * (q2q3 + q0q1) + mz * (0.5f - q1q1 - q2q2));

		// Estimated direction of gravity and magnetic field
		halfvx = q1q3 - q0q2;
		halfvy = q0q1 + q2q3;
		halfvz = q0q0 - 0.5f + q3q3;
		halfwx = bx * (0.5f - q2q2 - q3q3) + bz * (q1q3 - q0q2);
		halfwy = bx * (q1q2 - q0q3) + bz * (q0q1 + q2q3);
		halfwz = bx * (q0q2 + q1q3) + bz * (0.5f - q1q1 - q2q2);

		// Error is sum of cross product between estimated direction and measured direction of field vectors
		halfex = (ay * halfvz - az * halfvy) + (my * halfwz - mz * halfwy);
		halfey = (az * halfvx - ax * halfvz) + (mz * halfwx - mx * halfwz);
		halfez = (ax * halfvy - ay * halfvx) + (mx * halfwy - my * halfwx);

		// Compute and apply integral feedback if enabled
		if (twoKi > 0.0f)
		{
			integralFBx += twoKi * halfex * (1.0f / sampleFreq);	// integral error scaled by Ki
			integralFBy += twoKi * halfey * (1.0f / sampleFreq);
			integralFBz += twoKi * halfez * (1.0f / sampleFreq);
			gx += integralFBx;	// apply integral feedback
			gy += integralFBy;
			gz += integralFBz;
		} else
		{
			integralFBx = 0.0f;	// prevent integral windup
			integralFBy = 0.0f;
			integralFBz = 0.0f;
		}

		// Apply proportional feedback
		gx += twoKp * halfex;
		gy += twoKp * halfey;
		gz += twoKp * halfez;
	}

	// Integrate rate of change of quaternion
	gx *= (0.5f * (1.0f / sampleFreq));		// pre-multiply common factors
	gy *= (0.5f * (1.0f / sampleFreq));
	gz *= (0.5f * (1.0f / sampleFreq));
	qa = q0;
	qb = q1;
	qc = q2;
	q0 += (-qb * gx - qc * gy - q3 * gz);
	q1 += (qa * gx + qc * gz - q3 * gy);
	q2 += (qa * gy - qb * gz + q3 * gx);
	q3 += (qa * gz + qb * gy - qc * gx);

	// Normalise quaternion
	recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
	q0 *= recipNorm;
	q1 *= recipNorm;
	q2 *= recipNorm;
	q3 *= recipNorm;
}

void MPU9150lib::MahonyAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az)
{
	float recipNorm;
	float halfvx, halfvy, halfvz;
	float halfex, halfey, halfez;
	float qa, qb, qc;

	// Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
	if (!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f)))
	{

		// Normalise accelerometer measurement
		recipNorm = invSqrt(ax * ax + ay * ay + az * az);
		ax *= recipNorm;
		ay *= recipNorm;
		az *= recipNorm;

		// Estimated direction of gravity and vector perpendicular to magnetic flux
		halfvx = q1 * q3 - q0 * q2;
		halfvy = q0 * q1 + q2 * q3;
		halfvz = q0 * q0 - 0.5f + q3 * q3;

		// Error is sum of cross product between estimated and measured direction of gravity
		halfex = (ay * halfvz - az * halfvy);
		halfey = (az * halfvx - ax * halfvz);
		halfez = (ax * halfvy - ay * halfvx);

		// Compute and apply integral feedback if enabled
		if (twoKi > 0.0f)
		{
			integralFBx += twoKi * halfex * (1.0f / sampleFreq);	// integral error scaled by Ki
			integralFBy += twoKi * halfey * (1.0f / sampleFreq);
			integralFBz += twoKi * halfez * (1.0f / sampleFreq);
			gx += integralFBx;	// apply integral feedback
			gy += integralFBy;
			gz += integralFBz;
		} else
		{
			integralFBx = 0.0f;	// prevent integral windup
			integralFBy = 0.0f;
			integralFBz = 0.0f;
		}

		// Apply proportional feedback
		gx += twoKp * halfex;
		gy += twoKp * halfey;
		gz += twoKp * halfez;
	}

	// Integrate rate of change of quaternion
	gx *= (0.5f * (1.0f / sampleFreq));		// pre-multiply common factors
	gy *= (0.5f * (1.0f / sampleFreq));
	gz *= (0.5f * (1.0f / sampleFreq));
	qa = q0;
	qb = q1;
	qc = q2;
	q0 += (-qb * gx - qc * gy - q3 * gz);
	q1 += (qa * gx + qc * gz - q3 * gy);
	q2 += (qa * gy - qb * gz + q3 * gx);
	q3 += (qa * gz + qb * gy - qc * gx);

	// Normalise quaternion
	recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
	q0 *= recipNorm;
	q1 *= recipNorm;
	q2 *= recipNorm;
	q3 *= recipNorm;

}

float MPU9150lib::invSqrt(float x)
{
	float halfx = 0.5f * x;
	float y = x;
	long i = *(long*) &y;
	i = 0x5f3759df - (i >> 1);
	y = *(float*) &i;
	y = y * (1.5f - (halfx * y * y));
	return y;
}

void MPU9150lib::AHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz)
{
	float norm;
	float hx, hy, hz, bx, bz;
	float vx, vy, vz, wx, wy, wz;
	float ex, ey, ez;

	// auxiliary variables to reduce number of repeated operations
	float q0q0 = q0 * q0;
	float q0q1 = q0 * q1;
	float q0q2 = q0 * q2;
	float q0q3 = q0 * q3;
	float q1q1 = q1 * q1;
	float q1q2 = q1 * q2;
	float q1q3 = q1 * q3;
	float q2q2 = q2 * q2;
	float q2q3 = q2 * q3;
	float q3q3 = q3 * q3;

	// normalise the measurements
	norm = sqrt(ax * ax + ay * ay + az * az);
	ax = ax / norm;
	ay = ay / norm;
	az = az / norm;
	norm = sqrt(mx * mx + my * my + mz * mz);
	mx = mx / norm;
	my = my / norm;
	mz = mz / norm;

	// compute reference direction of flux
	hx = 2 * mx * (0.5 - q2q2 - q3q3) + 2 * my * (q1q2 - q0q3) + 2 * mz * (q1q3 + q0q2);
	hy = 2 * mx * (q1q2 + q0q3) + 2 * my * (0.5 - q1q1 - q3q3) + 2 * mz * (q2q3 - q0q1);
	hz = 2 * mx * (q1q3 - q0q2) + 2 * my * (q2q3 + q0q1) + 2 * mz * (0.5 - q1q1 - q2q2);
	bx = sqrt((hx * hx) + (hy * hy));
	bz = hz;

	// estimated direction of gravity and flux (v and w)
	vx = 2 * (q1q3 - q0q2);
	vy = 2 * (q0q1 + q2q3);
	vz = q0q0 - q1q1 - q2q2 + q3q3;
	wx = 2 * bx * (0.5 - q2q2 - q3q3) + 2 * bz * (q1q3 - q0q2);
	wy = 2 * bx * (q1q2 - q0q3) + 2 * bz * (q0q1 + q2q3);
	wz = 2 * bx * (q0q2 + q1q3) + 2 * bz * (0.5 - q1q1 - q2q2);

	// error is sum of cross product between reference direction of fields and direction measured by sensors
	ex = (ay * vz - az * vy) + (my * wz - mz * wy);
	ey = (az * vx - ax * vz) + (mz * wx - mx * wz);
	ez = (ax * vy - ay * vx) + (mx * wy - my * wx);

	// integral error scaled integral gain
	exInt = exInt + ex * Ki;
	eyInt = eyInt + ey * Ki;
	ezInt = ezInt + ez * Ki;

	// adjusted gyroscope measurements
	gx = gx + Kp * ex + exInt;
	gy = gy + Kp * ey + eyInt;
	gz = gz + Kp * ez + ezInt;

	// integrate quaternion rate and normalise
	q0 = q0 + (-q1 * gx - q2 * gy - q3 * gz) * halfT;
	q1 = q1 + (q0 * gx + q2 * gz - q3 * gy) * halfT;
	q2 = q2 + (q0 * gy - q1 * gz + q3 * gx) * halfT;
	q3 = q3 + (q0 * gz + q1 * gy - q2 * gx) * halfT;

	// normalise quaternion
	norm = sqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
	q0 = q0 / norm;
	q1 = q1 / norm;
	q2 = q2 / norm;
	q3 = q3 / norm;

	heading = atan2(2.0f * (q1 * q2 + q0 * q3), q0 * q0 + q1 * q1 - q2 * q2 - q3 * q3);
}

void MPU9150lib::transformation(float uncalibrated_values[3], float calibrated_values_raw[3])
{
	//calibration_matrix[3][3] is the transformation matrix
	//replace M11, M12,..,M33 with your transformation matrix data
	double calibration_matrix[3][3] = { { M11, M12, M13 }, { M21, M22, M23 }, { M31, M32, M33 } };
	//bias[3] is the bias
	//replace Bx, By, Bz with your bias data
	double bias[3] = { Bx, By, Bz };
	//calculation
	for (int i = 0; i < 3; ++i)
		uncalibrated_values[i] = uncalibrated_values[i] - bias[i];
	float result[3] = { 0, 0, 0 };
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			result[i] += calibration_matrix[i][j] * uncalibrated_values[j];
	for (int i = 0; i < 3; ++i)
		calibrated_values_raw[i] = result[i];
}

void MPU9150lib::vector_length_stabilasation(float calibrated_values_raw[3])
{
	float scaler;

	float normal_vector_length = sqrt(calibrated_values_raw[0] * calibrated_values_raw[0] + calibrated_values_raw[1] * calibrated_values_raw[1]
			+ calibrated_values_raw[2] * calibrated_values_raw[2]);

	//calculate the current scaler
	scaler = normal_vector_length
			/ sqrt(calibrated_values_raw[0] * calibrated_values_raw[0] + calibrated_values_raw[1] * calibrated_values_raw[1]
					+ calibrated_values_raw[2] * calibrated_values_raw[2]);
	//apply the current scaler to the calibrated coordinates (global array calibrated_values_raw)
	calibrated_values_raw[0] = calibrated_values_raw[0] * scaler;
	calibrated_values_raw[1] = calibrated_values_raw[1] * scaler;
	calibrated_values_raw[2] = calibrated_values_raw[2] * scaler;
}
