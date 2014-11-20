#ifndef IMU_H_
#define IMU_H_

#ifndef Arduino_h
#include "Arduino.h"
#endif

//MPU6050
#include "MPU6050_6Axis_MotionApps20.h"

//#define OLDMPU6050

#ifdef OLDMPU6050

#define OFFSETACCX -3983
#define OFFSETACCY -403
#define OFFSETACCZ 1625

#define OFFSETGYROX 56
#define OFFSETGYROY 10
#define OFFSETGYROZ -19

#else

#define OFFSETACCX -1974
#define OFFSETACCY -1625
#define OFFSETACCZ 1285

#define OFFSETGYROX 25
#define OFFSETGYROY -32
#define OFFSETGYROZ -7

#endif

#define RESETPIN 42

#include"mavlinkCommon/common/mavlink.h"

struct Attitude_t{
		float pitch;
		float roll;
		float yaw;
};

/////////////////////////Initialize DMP/////////////////////////
class IMU {
	public:
		IMU(Attitude_t *attitude)
				:
						status_(true),
						initialized_(false),
						packetSize_(0),
						fifoCount_(0),
						attitude_t(attitude) {
		}

		bool setDMP();
		void getYPRdmp();
		void startDMP();

//		static volatile bool mpuInterrupt;  // indicates whether MPU interrupt pin has gone high

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

		float ypr_[3]; // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
		Attitude_t *attitude_t;

		/////////////////////////MPU6050/////////////////////////
};

bool IMU::setDMP() {
	Wire.begin();
	while (!Serial)
		;

	// initialize device
//	Serial.println(F("Initializing I2C devices..."));
	mpu_.initialize();
//	Serial.print(F("Testing device connections: ")); // verify connection
	initialized_ = mpu_.testConnection();
	Serial.println(initialized_ ? F("MPU6050 connection successful") : F("mpu_6050 connection failed"));

	if (!initialized_) {
		return initialized_;
	}

	// wait for ready
	while (Serial.available() && Serial.read())
		;

	// load and configure the DMP
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

void IMU::startDMP() {
	// make sure it worked (returns 0 if so)
	if (status_ == 0) {
		// turn on the DMP, now that it's ready
//		Serial.println(F("Enabling DMP..."));
		mpu_.setDMPEnabled(true);

		// get expected DMP packet size for later comparison
		status_ = true;
		packetSize_ = mpu_.dmpGetFIFOPacketSize();
//		Serial.print("PacketSize:");
//		Serial.println(packetSize_);
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
void IMU::getYPRdmp() {

	uint8_t mpuIntStatus = mpu_.getIntStatus(); // holds actual interrupt status byte from mpu_

	// get current FIFO count
	fifoCount_ = mpu_.getFIFOCount();

	// check for overflow (this should never happen unless our code is too inefficient)
	if ((mpuIntStatus & 0x10) || fifoCount_ == 1024) {
		// reset so we can continue cleanly
		mpu_.resetFIFO();
//		Serial.println(F("FIFO overflow!"));

		// otherwise, check for DMP data ready interrupt (this should happen frequently)
	} else if (mpuIntStatus & 0x02) {

		// wait for correct available data length, should be a VERY short wait
		while (fifoCount_ < packetSize_) {
			Serial.println("wait");
			fifoCount_ = mpu_.getFIFOCount();
		}

		// read a packet from FIFO
		mpu_.getFIFOBytes(fifoBuffer_, packetSize_);

		// track FIFO count here in case there is > 1 packet available
		// (this lets us immediately read more without waiting for an interrupt)
		fifoCount_ -= packetSize_;

		// display Euler angles in degrees
		mpu_.dmpGetQuaternion(&q_, fifoBuffer_);
		mpu_.dmpGetGravity(&gravity_, &q_);
		mpu_.dmpGetYawPitchRoll(ypr_, &q_, &gravity_);

		attitude_t->yaw = ypr_[0]* 180/M_PI;
		attitude_t->pitch = ypr_[2]* 180/M_PI;
		attitude_t->roll = ypr_[1]* 180/M_PI;

	}

}

/////////////////////////Initialize DMP//////////////////////////
#endif /* IMUFUNCTIONS_H_ */
