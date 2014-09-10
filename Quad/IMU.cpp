#include "IMU.h"

//volatile bool IMU::mpuInterrupt = false;
//
//void dmpDataReady() {
//	IMU::mpuInterrupt = true;
//}

void IMU::setDMP() {
//	while (status_) {
//		Wire.beginTransmission(104);
//		status_ = Wire.endTransmission(); // if error = 0, we are properly connected
//		if (status_) { // if we aren't properly connected, try connecting again and loop
//			Serial.println("  ");
//			Serial.println("Not properly connected to I2C, trying again");
//			Serial.println(" ");
//			Wire.begin();
//		}
//	}

#if defined(ARDUINO_ARCH_AVR)
	TWBR = 24; // 400kHz I2C clock
#endif

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
	Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
	Fastwire::setup(400, true);
#endif

	Serial.begin(115200); /**start communication*/

	while (!Serial)
		;
	// initialize device
	Serial.println(F("Initializing I2C devices..."));
	mpu_.initialize();
	Serial.println(F("Testing device connections...")); // verify connection
	bool mpuConnection = mpu_.testConnection();
	Serial.println(mpuConnection ? F("mpu_6050 connection successful") : F("mpu_6050 connection failed"));
	if (!mpuConnection)
		while (true)
			;
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
		// enable Arduino interrupt detection
		Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
		//PCintPort::attachInterrupt(mpu_INTERRUPT, &dmpDataReady, RISING);
//		attachInterrupt(MPUINTERRUPTPIN, dmpDataReady, RISING);
		uint8_t mpu_IntStatus = mpu_.getIntStatus(); // holds actual interrupt status byte from mpu_

		// set our DMP Ready flag so the main loop() function knows it's okay to use it
		Serial.println(F("DMP ready! Waiting for first interrupt..."));
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

	// if programming failed, don't try to do anything
	//	if (!dmpReady)
	//		return;
	// wait for mpu_ interrupt or extra packet(s) available

//	while (!IMU::mpuInterrupt && fifoCount_ < packetSize_) {
//		if (IMU::mpuInterrupt)
//			break;
//	}

//
//	// reset interrupt flag and get INT_STATUS byte

//	IMU::mpuInterrupt = false;

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
		while (fifoCount_ < packetSize_){
			Serial.println("wait");
			fifoCount_ = mpu_.getFIFOCount();
		}
//		Serial.println(fifoCount_);
		// read a packet from FIFO
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
		*pitch_ = ypr_[1] * 180 / M_PI;
		*roll_ = ypr_[2] * 180 / M_PI;

	}

}

