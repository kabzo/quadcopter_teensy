#ifndef IMU_H_
#define IMU_H_

#ifndef Arduino_h
#include "Arduino.h"
#endif

//MPU6050
#include "MPU6050_6Axis_MotionApps20.h"

#define OFFSETACCX -1974
#define OFFSETACCY -1625
#define OFFSETACCZ 1285

#define OFFSETGYROX 25
#define OFFSETGYROY -32
#define OFFSETGYROZ -7

struct Attitude_t
{
		float roll;  ///< Roll angle (rad, -pi..+pi)
		float pitch;  ///< Pitch angle (rad, -pi..+pi)
		float yaw;  ///< Yaw angle (rad, -pi..+pi)

		float rollspeed;  ///< Roll angular speed (rad/s)
		float pitchspeed;  ///< Pitch angular speed (rad/s)
		float yawspeed;  ///< Yaw angular speed (rad/s)
};

/////////////////////////Initialize DMP/////////////////////////
class IMU
{
	public:
		IMU(Attitude_t *attitude)
				: status_(true),
					initialized_(false),
					packetSize_(0),
					fifoCount_(0),
					attitude_t(attitude)
		{
		}

		bool setDMP();
		void getYPRdmp();
		void startDMP();

	private:
		/////////////////////////MPU6050/////////////////////////
		MPU6050 mpu_;
		bool status_;
		bool initialized_;
		uint16_t packetSize_;    // expected DMP packet size (default is 42 bytes)

		uint16_t fifoCount_;     // count of all bytes currently in FIFO
		Quaternion q_;           // [w, x, y, z]         quaternion container
		VectorFloat gravity_;    // [x, y, z]            gravity vector

		uint8_t fifoBuffer_[128];

		float ypr_[3];  // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
		int32_t accelxyz_[3];
		Attitude_t *attitude_t;

		/////////////////////////MPU6050/////////////////////////
};

bool IMU::setDMP()
{
	Wire.begin();
	while (!Serial)
		;

	mpu_.initialize();
	initialized_ = mpu_.testConnection();
	Serial.println(
			initialized_ ?
					F("MPU6050 connection successful") : F("mpu_6050 connection failed"));

	if (!initialized_) {
		return initialized_;
	}

	Serial.println(F("Initializing DMP..."));
	status_ = mpu_.dmpInitialize();

	mpu_.setXGyroOffset(OFFSETGYROX);
	mpu_.setYGyroOffset(OFFSETGYROY);
	mpu_.setZGyroOffset(OFFSETGYROZ);

	mpu_.setXAccelOffset(OFFSETACCX);
	mpu_.setYAccelOffset(OFFSETACCY);
	mpu_.setZAccelOffset(OFFSETACCZ);

	return initialized_;

}

void IMU::startDMP()
{
	if (status_ == 0) { 					// make sure it worked (returns 0 if so)
		mpu_.setDMPEnabled(true); 	// turn on the DMP, now that it's ready
		status_ = true;  				// get expected DMP packet size for later comparison
		packetSize_ = mpu_.dmpGetFIFOPacketSize();
	} else {
		// ERROR!
		// 1 = initial memory load failed
		// 2 = DMP configuration updates failed
		// (if it's going to break, usually the code will be 1)
		Serial.print(F("DMP Initialization failed (code "));
		Serial.print(status_);
		Serial.println(F(")"));
		while (true)
			;
	}
}
void IMU::getYPRdmp()
{
	uint8_t mpuIntStatus = mpu_.getIntStatus();  // holds actual interrupt status byte from mpu_
	fifoCount_ = mpu_.getFIFOCount();						// get current FIFO count

	if ((mpuIntStatus & 0x10) || fifoCount_ == 1024) {  // check for overflow (this should never happen unless our code is too inefficient)
		mpu_.resetFIFO();												// reset so we can continue cleanly
	} else if (mpuIntStatus & 0x02) {	// otherwise, check for DMP data ready interrupt (this should happen frequently)
		while (fifoCount_ < packetSize_) {	// wait for correct available data length, should be a VERY short wait
			fifoCount_ = mpu_.getFIFOCount();
		}
		mpu_.getFIFOBytes(fifoBuffer_, packetSize_);			// read a packet from FIFO
		// track FIFO count here in case there is > 1 packet available
		// (this lets us immediately read more without waiting for an interrupt)
		fifoCount_ -= packetSize_;

		mpu_.dmpGetQuaternion(&q_, fifoBuffer_);	// display Euler angles in degrees
		mpu_.dmpGetGravity(&gravity_, &q_);
		mpu_.dmpGetYawPitchRoll(ypr_, &q_, &gravity_);
//		mpu_.dmpGetAccel(accelxyz_);

		attitude_t->yaw = ypr_[0];
		attitude_t->pitch = ypr_[2];
		attitude_t->roll = ypr_[1];

//		attitude_t->pitchspeed = accelxyz_[0];
//		attitude_t->rollspeed = accelxyz_[1];
//		attitude_t->yawspeed = accelxyz_[2];

	}

}

/////////////////////////Initialize DMP//////////////////////////
#endif /* IMUFUNCTIONS_H_ */
