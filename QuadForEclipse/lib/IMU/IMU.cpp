#include "IMU.h"

void IMU::setDMP() {
	Wire.begin();
	while (!Serial)
		;

	// initialize device
	Serial.println(F("Initializing I2C devices..."));
	mpu_.initialize();
	Serial.print(F("Testing device connections: ")); // verify connection
	bool connection = mpu_.testConnection();
	Serial.println(connection ? F("MPU6050 connection successful") : F("mpu_6050 connection failed"));

	if (!connection) {
		digitalWrite(RESETPIN, LOW);
		while (true)
			;
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

}

void IMU::startDMP() {
	// make sure it worked (returns 0 if so)
	if (status_ == 0) {
		// turn on the DMP, now that it's ready
		Serial.println(F("Enabling DMP..."));
		mpu_.setDMPEnabled(true);

		// get expected DMP packet size for later comparison
		status_ = true;
		packetSize_ = mpu_.dmpGetFIFOPacketSize();
		Serial.print("PacketSize:");
		Serial.println(packetSize_);
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
		Serial.println(F("FIFO overflow!"));

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
		*yaw_ = ypr_[0] * 180 / M_PI;
		*pitch_ = ypr_[2] * 180 / M_PI;
		*roll_ = -ypr_[1] * 180 / M_PI;

	}

}

