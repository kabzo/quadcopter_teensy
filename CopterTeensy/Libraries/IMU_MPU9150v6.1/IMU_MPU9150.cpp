#include <IMU_MPU9150.h>
#include <Vector3.hpp>

const Mav_Param::GroupInfo IMU_MPU9150::var_info[]  = {
GROUPINFO("lpf", IMU_MPU9150, _lpf, 0),
GROUPINFO("rate", IMU_MPU9150, _mpu_rate, 100),
GROUPEND
};

const Matrix3f IMU_MPU9150::orientation_mag_to_gyro(0, 1, 0, 1, 0, 0, 0, 0, -1);

IMU_MPU9150::IMU_MPU9150() :
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
	Mav_Param::setup_object_defaults(this, var_info);

	aRes = getAres();
	gRes = getGres();

	//  Process calibration data for runtime
	m_calibrate_Data.magMax(189, 224, 167);
	m_calibrate_Data.magMin(-149, -113, -165);

	m_calibrate_Data.accelMax(17390, 16242, 17474);
	m_calibrate_Data.accelMin(-16084, -17172, -17132);

	m_gyroOffset(2.73,-4.97,-0.25);
}

void IMU_MPU9150::init_param()
{
	//-----------------------------------------------------------------------------------------------------------------------//
	//----------------------------------------MAG CALIBRATION----------------------------------------------------------------//
	//-----------------------------------------------------------------------------------------------------------------------//
	m_magOffset = (m_calibrate_Data.magMax + m_calibrate_Data.magMin) / 2;
	Vector3Float m_magRangeMax = m_calibrate_Data.magMax - m_magOffset;
	Vector3Float m_magRangeMin = m_calibrate_Data.magMin - m_magOffset;
	Vector3Float avgs = m_magRangeMax + (m_magRangeMin * -1);
	avgs *= 0.5;

	float avg_rad = avgs.average();

	m_magScale(avg_rad / avgs.x, avg_rad / avgs.y, avg_rad / avgs.z);

	m_magScale *= avg_rad;
	m_magScale /= avgs;

	//-----------------------------------------------------------------------------------------------------------------------//
	//----------------------------------------MAG CALIBRATION----------------------------------------------------------------//
	//-----------------------------------------------------------------------------------------------------------------------//

	//-----------------------------------------------------------------------------------------------------------------------//
	//----------------------------------------ACCEL CALIBRATION--------------------------------------------------------------//
	//-----------------------------------------------------------------------------------------------------------------------//
	m_accelOffset = (m_calibrate_Data.accelMax + m_calibrate_Data.accelMin) / 2;
	long accel_bias[3];
	m_accelOffset.get_array(accel_bias);
	mpu_set_accel_bias_6050_reg(accel_bias);
	//-----------------------------------------------------------------------------------------------------------------------//
	//----------------------------------------ACCEL CALIBRATION--------------------------------------------------------------//
	//-----------------------------------------------------------------------------------------------------------------------//

	//-----------------------------------------------------------------------------------------------------------------------//
	//----------------------------------------GYRO CALIBRATION--------------------------------------------------------------//
	//-----------------------------------------------------------------------------------------------------------------------//

	long gyro_bias[3];
	m_gyroOffset.get_array(gyro_bias);
	mpu_set_gyro_bias_reg(gyro_bias);
	//-----------------------------------------------------------------------------------------------------------------------//
	//----------------------------------------GYRO CALIBRATION--------------------------------------------------------------//
	//-----------------------------------------------------------------------------------------------------------------------//

	mpu_init_structures();

}

int IMU_MPU9150::init_dmp(signed char orientation[9],
													int fifoRate,
													int mpuRate,
													int magRate,
													int lpf)
{
	init_param();

	// Not using interrupts so set up this structure to keep the driver happy

	mpuRate = constrain(mpuRate, 1, 1000); //mpu betweeh 1-1000hz

	orientation_gyro_accel(orientation);

	magRate = constrain(magRate, 1, MAX_COMPASS_SAMPLE_RATE); // rate must be less than or equal to 100Hz
	m_magInterval = (unsigned long) (1000 / magRate);       // record mag interval
	m_lastMagSample = millis();

	struct int_param_s int_param;
	int_param.cb = NULL;
	int_param.pin = 0;
	int_param.lp_exit = 0;
	int_param.active_low = 1;

	if (check_sacesfull("mpu_init", mpu_init(&int_param)) != 0)
		return -1;

	if (check_sacesfull("mpu_set_sensors",
											mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL | INV_XYZ_COMPASS)) != 0)
		return -2;  // enable all of the sensors

	if (check_sacesfull("mpu_configure_fifo", mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL)) != 0)
		return -3;  	 // get accel and gyro data in the FIFO also

	if (check_sacesfull("mpu_set_sample_rate", mpu_set_sample_rate(mpuRate)) != 0)
		return -4;

	if (check_sacesfull("mpu_set_gyro_fsr", mpu_set_gyro_fsr(gScale)) != 0)
		return -5;

	if (check_sacesfull("mpu_set_accel_fsr", mpu_set_accel_fsr(aScale)) != 0)
		return -6;

	if (check_sacesfull("dmp_load_motion_driver_firmware", dmp_load_motion_driver_firmware()) != 0)
		return -7;

	if (check_sacesfull("dmp_set_orientation",
											dmp_set_orientation(inv_orientation_matrix_to_scalar(orientation))) != 0)
		return -8;   // set up the correct orientation

	if (check_sacesfull("dmp_enable_feature",
											dmp_enable_feature(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO)) != 0)
		return -9;

	if (check_sacesfull("dmp_set_fifo_rate", dmp_set_fifo_rate(fifoRate)) != 0)
		return -10;

	if (check_sacesfull("mpu_set_dmp_state", mpu_set_dmp_state(1)) != 0)
		return -11;

	if (check_sacesfull("mpu_set_compass_sample_rate", mpu_set_compass_sample_rate(magRate)) != 0)
		return -12;	 // set the compass update rate to match

	if (lpf != 0)
		if (check_sacesfull("mpu_set_lpf", mpu_set_lpf(lpf)) != 0)
			return -13;  // set the low pass filter

	return true;
}

int IMU_MPU9150::init_raw(signed char orientation[9], int mpuRate, int magRate, int lpf)
{
	init_param();
	orientation_gyro_accel(orientation);

	// Not using interrupts so set up this structure to keep the driver happy

	mpuRate = constrain(mpuRate, 1, 1000); //mpu betweeh 1-1000hz
	_lpf = mpuRate >> 1;
	_mpu_rate = mpuRate;

	magRate = constrain(magRate, 1, MAX_COMPASS_SAMPLE_RATE); // rate must be less than or equal to 100Hz
	m_magInterval = (unsigned long) (1000 / magRate);       // record mag interval
	m_lastMagSample = millis();

	struct int_param_s int_param;
	int_param.cb = NULL;
	int_param.pin = 0;
	int_param.lp_exit = 0;
	int_param.active_low = 1;

	if (check_sacesfull("mpu_init", mpu_init(&int_param)) != 0)
		return -1;

	if (check_sacesfull("mpu_set_sensors",
											mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL | INV_XYZ_COMPASS)) != 0)
		return -2;  // enable all of the sensors

	if (check_sacesfull("mpu_configure_fifo", mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL)) != 0)
		return -3;  	 // get accel and gyro data in the FIFO also

	if (check_sacesfull("mpu_set_sample_rate", mpu_set_sample_rate(mpuRate)) != 0)
		return -4;

	if (check_sacesfull("mpu_set_gyro_fsr", mpu_set_gyro_fsr(gScale)) != 0)
		return -5;

	if (check_sacesfull("mpu_set_accel_fsr", mpu_set_accel_fsr(aScale)) != 0)
		return -6;

	if (check_sacesfull("mpu_set_compass_sample_rate", mpu_set_compass_sample_rate(magRate)) != 0)
		return -12;	 // set the compass update rate to match

	if (lpf != 0)
	{
		_lpf= lpf;
		if (check_sacesfull("mpu_set_lpf", mpu_set_lpf(lpf)) != 0)
			return -13;  // set the low pass filter
	}
	return true;
}

int IMU_MPU9150::read_dmp()
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
//		GCS._serial.println("fifo owerflou");
		return -2;
	}
	if ((intStatus & (MPU_INT_STATUS_DMP | MPU_INT_STATUS_DMP_0)) != (MPU_INT_STATUS_DMP | MPU_INT_STATUS_DMP_0))
	{
		//GCS._serial.println(intStatus,BIN);
		return -3;
	}
	short m_rawMag[3];
	short m_rawAccel[3];                 // raw accel data
	short m_rawGyro[3];                  // gyro output from the sensor
	long m_rawQuaternion[4];             // the quaternion output from the DMP

	//get the data from the fifo, data are ready
	if ((dmp_read_fifo(m_rawGyro, m_rawAccel, m_rawQuaternion, &timestamp, &sensors, &more)) != 0)
	{
		return -4;
	}

	dmpQuaternion(m_rawQuaternion);   // get float version of quaternion
	dmpQuaternion.normalize();
	dmpEuler.quaternion_to_euler(dmpQuaternion);

	//  got the fifo data so now get the mag data if it's time
	if ((millis() - m_lastMagSample) >= m_magInterval)
	{
		if (check_sacesfull("mpu_get_compass_reg", mpu_get_compass_reg(m_rawMag, &timestamp)) != 0)
			return -5;
		m_lastMagSample = millis();

		//	*** Note mag axes are changed here to align with gyros: Y=X,X=Y,Z=-Z
		rawMag(m_rawMag);
		calMag = rawMag - m_magOffset;

		calMag *= m_magScale;

		calMag = orientation_mag_to_gyro * calMag;
		calMag = orientation_gyro_accel * calMag;

	}

	rawAccel(m_rawAccel);
	calAccel = rawAccel - m_accelOffset;
	calAccel *= aRes * G_TO_M_S;
	calAccel = orientation_gyro_accel * calAccel;

	// Scale gyro data
	rawGyro(m_rawGyro);
	calGyro = rawGyro - m_gyroOffset;
	calGyro *= gRes;

//	dmpEuler = dataFusion();

//	heading = compassHeadingTiltCompensatedRadians(dmpEuler.PITCH, dmpEuler.ROLL, calMag);
//	mag_ypr_fusion();
//	MahonyAHRSupdate(radians(calGyro.x), radians(calGyro.y), radians(calGyro.z), rawAccel.x, rawAccel.y, rawAccel.z, calMag.x, calMag.y, calMag.z);
//	MadgwickAHRSupdate(	calAccel.x,calAccel.y,calAccel.z,calGyro.x * PI / 180.0f,calGyro.y * PI / 180.0f,calGyro.z * PI / 180.0f,calMag.x,calMag.y,calMag.z);
//	heading = atan2(2.0f * (q2 * q0 - q1 * q3), 1 - 2 * q2 * q2 - 2 * q3 * q3);
	return 0;
}

int IMU_MPU9150::read_raw()
{
	short intStatus;
//	unsigned char sensors;
//	unsigned char more;
	unsigned long timestamp;

	if (mpu_get_int_status(&intStatus) != 0)
		return -1;   // get the current MPU state

	if (intStatus & MPU_INT_STATUS_FIFO_OVERFLOW)
	{
		mpu_reset_fifo();
		Serial.println("fifo owerflou");
		return -2;
	}
	if ((intStatus & (MPU_INT_STATUS_DATA_READY)) != (MPU_INT_STATUS_DATA_READY))
	{
		//GCS._serial.println(intStatus,BIN);
		return -3;
	}

	short m_rawMag[3];
	short m_rawAccel[3];                 // raw accel data
	short m_rawGyro[3];                  // gyro output from the sensor

	mpu_get_accel_reg(m_rawAccel, &timestamp);
	mpu_get_gyro_reg(m_rawGyro, &timestamp);

//	mpu_read_fifo(m_rawGyro,m_rawAccel,&timestamp,&sensors,&more);

	rawAccel(m_rawAccel);
	calAccel = rawAccel - m_accelOffset;
//	calAccel *= aRes * G_TO_M_S;
	calAccel *= aRes;
	calAccel = orientation_gyro_accel * calAccel;

	// Scale gyro data
	rawGyro(m_rawGyro);
	calGyro = rawGyro - m_gyroOffset;
	calGyro *= gRes;
	calGyro = orientation_gyro_accel * calGyro;

	MadgwickAHRSupdateIMU(radians(calGyro.x),
												radians(calGyro.y),
												radians(calGyro.z),
												calAccel.x,
												calAccel.y,
												calAccel.z);

	Quaternion quat(q0, q1, q2, q3);
	quat.normalize();
	dmpEuler.quaternion_to_euler(quat);
//	dmpEuler.YAW = atan2(2.0f * (q1 * q2 + q0 * q3),
//								q0 * q0 + q1 * q1 - q2 * q2 - q3 * q3);
//	dmpEuler.PITCH	 = -asin(2.0f * (q1 * q3 - q0 * q2));
//	dmpEuler.ROLL	 = atan2(	2.0f * (q0 * q1 + q2 * q3),
//									q0 * q0 - q1 * q1 - q2 * q2 + q3 * q3);
	return 0;

}

void IMU_MPU9150::set_lpf(float lpf){
	mpu_set_lpf((unsigned short) lpf);
}

void IMU_MPU9150::set_mpu_rate(float rate){
	unsigned short rate_uns = (unsigned short) rate;
	mpu_set_sample_rate(rate_uns);
	_lpf = rate_uns>>2;
}

Vector3Float IMU_MPU9150::dataFusion()
{
	Quaternion qMagnetometer;
	float qMag[4];
	float deltaDMPYaw, deltaMagYaw;
	float newMagYaw, newYaw;
	float temp1[4], unFused[4];
	float unFusedConjugate[4];
	Vector3Float fusedEuler(0, dmpEuler.PITCH, dmpEuler.ROLL);

	// *** NOTE *** pitch direction swapped here

//  m_fusedEulerPose[VEC3_X] = m_dmpEulerPose[VEC3_X];
//  m_fusedEulerPose[VEC3_Y] = -m_dmpEulerPose[VEC3_Y];
//  m_fusedEulerPose[VEC3_Z] = 0;
	Quaternion unFus = dmpQuaternion;
//  MPUQuaternionEulerToQuaternion(m_fusedEulerPose, unFused);    // create a new quaternion

	deltaDMPYaw = -dmpEuler.YAW + m_lastDMPYaw;         // calculate change in yaw from dmp
	m_lastDMPYaw = dmpEuler.YAW;                        // update that

//  qMag[QUAT_W] = 0;
//  qMag[QUAT_X] = m_calMag[VEC3_X];
//  qMag[QUAT_Y] = m_calMag[VEC3_Y];
//  qMag[QUAT_Z] = m_calMag[VEC3_Z];

	qMagnetometer(0.0f, calMag.x, calMag.y, calMag.z);

	// Tilt compensate mag with the unfused data (i.e. just roll and pitch with yaw 0)

	Quaternion conjugated = qMagnetometer.getConjugate();
	Quaternion temp1_multipl = qMagnetometer * conjugated;
	qMagnetometer = unFus * temp1_multipl;
//  MPUQuaternionConjugate(unFused, unFusedConjugate);
//  MPUQuaternionMultiply(qMag, unFusedConjugate, temp1);
//  MPUQuaternionMultiply(unFused, temp1, qMag);

	// Now fuse this with the dmp yaw gyro information

//  newMagYaw = -atan2(qMag[QUAT_Y], qMag[QUAT_X]);
	newMagYaw = -atan2(qMagnetometer.y, qMagnetometer.x);

	if (newMagYaw != newMagYaw)
	{                                 // check for nAn
#ifdef MPULIB_DEBUG
		Serial.println("***nAn\n");
#endif
		return fusedEuler;                                                   // just ignore in this case
	}
	if (newMagYaw < 0)
		newMagYaw = 2.0f * (float) M_PI + newMagYaw;                 // need 0 <= newMagYaw <= 2*PI

	newYaw = m_lastYaw + deltaDMPYaw;                             // compute new yaw from change

	if (newYaw > (2.0f * (float) M_PI))                            // need 0 <= newYaw <= 2*PI
		newYaw -= 2.0f * (float) M_PI;
	if (newYaw < 0)
		newYaw += 2.0f * (float) M_PI;

	deltaMagYaw = newMagYaw - newYaw;                             // compute difference

	if (deltaMagYaw >= (float) M_PI)
		deltaMagYaw = deltaMagYaw - 2.0f * (float) M_PI;
	if (deltaMagYaw <= -(float) M_PI)
		deltaMagYaw = (2.0f * (float) M_PI + deltaMagYaw);

	int m_magMix = 10;
	if (m_magMix > 0)
	{
		newYaw += deltaMagYaw / m_magMix;                             // apply some of the correction

		if (newYaw > (2.0f * (float) M_PI))				            // need 0 <= newYaw <= 2*PI
			newYaw -= 2.0f * (float) M_PI;
		if (newYaw < 0)
			newYaw += 2.0f * (float) M_PI;
	}

	m_lastYaw = newYaw;

	if (newYaw > (float) M_PI)
		newYaw -= 2.0f * (float) M_PI;

//  m_fusedEulerPose[VEC3_Z] = newYaw;                            // fill in output yaw value
	fusedEuler.YAW = newYaw;                            // fill in output yaw value

//  fusedEuler.euler_to_quaternion()
//  MPUQuaternionEulerToQuaternion(m_fusedEulerPose, m_fusedQuaternion);
}

void IMU_MPU9150::mag_ypr_fusion()
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

int IMU_MPU9150::check_sacesfull(String str, int returnVal)
{
	if (returnVal != 0)
	{
		DEBUGLN3(str, "FAILED", returnVal);
		return returnVal;
	}
	return 0;
}

float IMU_MPU9150::getGres()
{
	float gRes = 0;
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
	return gRes;
}

float IMU_MPU9150::getAres()
{
	float aRes = 0;
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
	return aRes;
}

void IMU_MPU9150::MadgwickAHRSupdate(	float gx,
																			float gy,
																			float gz,
																			float ax,
																			float ay,
																			float az,
																			float mx,
																			float my,
																			float mz)
{
	float recipNorm;
	float s0, s1, s2, s3;
	float qDot1, qDot2, qDot3, qDot4;
	float hx, hy;
	float _2q0mx, _2q0my, _2q0mz, _2q1mx, _2bx, _2bz, _4bx, _4bz, _2q0, _2q1, _2q2, _2q3, _2q0q2,
			_2q2q3, q0q0, q0q1, q0q2, q0q3, q1q1, q1q2, q1q3, q2q2, q2q3, q3q3;

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
		s0 = -_2q2 * (2.0f * q1q3 - _2q0q2 - ax) + _2q1 * (2.0f * q0q1 + _2q2q3 - ay) - _2bz * q2 * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx) + (-_2bx * q3 + _2bz * q1) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my) + _2bx * q2 * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
		s1 = _2q3 * (2.0f * q1q3 - _2q0q2 - ax) + _2q0 * (2.0f * q0q1 + _2q2q3 - ay) - 4.0f * q1 * (1 - 2.0f * q1q1 - 2.0f * q2q2 - az) + _2bz * q3 * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx) + (_2bx * q2 + _2bz * q0) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my) + (_2bx * q3 - _4bz * q1) * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
		s2 = -_2q0 * (2.0f * q1q3 - _2q0q2 - ax) + _2q3 * (2.0f * q0q1 + _2q2q3 - ay) - 4.0f * q2 * (1 - 2.0f * q1q1 - 2.0f * q2q2 - az) + (-_4bx * q2 - _2bz * q0) * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx) + (_2bx * q1 + _2bz * q3) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my) + (_2bx * q0 - _4bz * q2) * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
		s3 = _2q1 * (2.0f * q1q3 - _2q0q2 - ax) + _2q2 * (2.0f * q0q1 + _2q2q3 - ay) + (-_4bx * q3 + _2bz * q1) * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx) + (-_2bx * q0 + _2bz * q2) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my) + _2bx * q1 * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
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

void IMU_MPU9150::MadgwickAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az)
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

void IMU_MPU9150::MahonyAHRSupdate(	float gx,
																		float gy,
																		float gz,
																		float ax,
																		float ay,
																		float az,
																		float mx,
																		float my,
																		float mz)
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

void IMU_MPU9150::MahonyAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az)
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

float IMU_MPU9150::invSqrt(float x)
{
	float halfx = 0.5f * x;
	float y = x;
	long i = *(long*) &y;
	i = 0x5f3759df - (i >> 1);
	y = *(float*) &i;
	y = y * (1.5f - (halfx * y * y));
	return y;
}

void IMU_MPU9150::AHRSupdate(	float gx,
															float gy,
															float gz,
															float ax,
															float ay,
															float az,
															float mx,
															float my,
															float mz)
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

void IMU_MPU9150::transformation(float uncalibrated_values[3], float calibrated_values_raw[3])
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

void IMU_MPU9150::vector_length_stabilasation(float calibrated_values_raw[3])
{
	float scaler;

	float normal_vector_length = sqrt(calibrated_values_raw[0] * calibrated_values_raw[0] + calibrated_values_raw[1] * calibrated_values_raw[1] + calibrated_values_raw[2] * calibrated_values_raw[2]);

	//calculate the current scaler
	scaler = normal_vector_length / sqrt(calibrated_values_raw[0] * calibrated_values_raw[0] + calibrated_values_raw[1] * calibrated_values_raw[1] + calibrated_values_raw[2] * calibrated_values_raw[2]);
	//apply the current scaler to the calibrated coordinates (global array calibrated_values_raw)
	calibrated_values_raw[0] = calibrated_values_raw[0] * scaler;
	calibrated_values_raw[1] = calibrated_values_raw[1] * scaler;
	calibrated_values_raw[2] = calibrated_values_raw[2] * scaler;
}

bool IMU_MPU9150::check_max_min(CALIBRATE_MPU &calib, Vector3Int16 rawData, Sens sensor)
{
	bool changed = false;
	Vector3Int32 *calibrateMax;
	Vector3Int32 *calibrateMin;

	switch (sensor) {
		case ACCEL: {
			calibrateMax = &calib.accelMax;
			calibrateMin = &calib.accelMin;
			break;
		}
		case MAG: {
			calibrateMax = &calib.magMax;
			calibrateMin = &calib.magMin;
			break;
		}
		default: {
			return false;
			break;
		}
	}

	if (calibrateMax == 0 || calibrateMin == 0)
		return false;

	if (rawData.x < calibrateMin->x)
	{
		calibrateMin->x = rawData.x;
		changed = true;
	}
	if (rawData.x > calibrateMax->x)
	{
		calibrateMax->x = rawData.x;
		changed = true;
	}
	if (rawData.y < calibrateMin->y)
	{
		calibrateMin->y = rawData.y;
		changed = true;
	}
	if (rawData.y > calibrateMax->y)
	{
		calibrateMax->y = rawData.y;
		changed = true;
	}
	if (rawData.z < calibrateMin->z)
	{
		calibrateMin->z = rawData.z;
		changed = true;
	}
	if (rawData.z > calibrateMax->z)
	{
		calibrateMax->z = rawData.z;
		changed = true;
	}

	return changed;
}

float IMU_MPU9150::compassHeadingTiltCompensatedRadians(float pitch_radians,
																												float roll_radians,
																												Vector3Float xr)
{

	float tilt_compensated_heading;
	float MAG_X;
	float MAG_Y;
	float cos_roll;
	float sin_roll;
	float cos_pitch;
	float sin_pitch;

	cos_roll = cos(roll_radians);
	sin_roll = sin(roll_radians);
	cos_pitch = cos(pitch_radians);
	sin_pitch = sin(pitch_radians);

	/*
	 // Tilt compensated Magnetic field X:
	 MAG_X = xr*cos_pitch+yr*sin_roll*sin_pitch+zr*cos_roll*sin_pitch;
	 // Tilt compensated Magnetic field Y:
	 MAG_Y = yr*cos_roll-zr*sin_roll;
	 // Magnetic Heading
	 tilt_compensated_heading = atan2(MAG_Y,MAG_X);  // TODO:  Review - why negative Y?
	 */
	MAG_X = xr.x * cos_pitch + xr.z * sin_pitch;
	MAG_Y = xr.x * sin_roll * sin_pitch + xr.y * cos_roll - xr.z * sin_roll * cos_pitch;
	tilt_compensated_heading = atan2(MAG_Y, MAG_X);

	return tilt_compensated_heading;
}
