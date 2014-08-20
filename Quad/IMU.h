/*
 * ImuFunctions.h
 *
 *  Created on: 28.6.2014
 *      Author: Duri
 */
/////////////////////////Initialize DMP/////////////////////////
#ifndef IMUFUNCTIONS_H_
#define IMUFUNCTIONS_H_
namespace IMU {
/////////////////////////Initialize DMP/////////////////////////
	boolean setDMP();
	void getYPRdmp();
/////////////////////////Initialize DMP//////////////////////////

	void dmpDataReady() {
		mpuInterrupt = true;
	}
	void getYPRdmp() {
		// if programming failed, don't try to do anything
//	if (!dmpReady)
//		return;
		// wait for MPU interrupt or extra packet(s) available
		while (!mpuInterrupt && fifoCount < packetSize) {
			if(mpuInterrupt)break;
		}
		// reset interrupt flag and get INT_STATUS byte
		mpuInterrupt = false;
		mpuIntStatus = mpu.getIntStatus();

		// get current FIFO count
		fifoCount = mpu.getFIFOCount();

		// check for overflow (this should never happen unless our code is too inefficient)
		if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
			// reset so we can continue cleanly
			mpu.resetFIFO();
			Serial.println(F("FIFO overflow!"));

			// otherwise, check for DMP data ready interrupt (this should happen frequently)
		} else if (mpuIntStatus & 0x02) {
			// wait for correct available data length, should be a VERY short wait
			while (fifoCount < packetSize)
				fifoCount = mpu.getFIFOCount();

			// read a packet from FIFO
			mpu.getFIFOBytes(fifoBuffer, packetSize);

			// track FIFO count here in case there is > 1 packet available
			// (this lets us immediately read more without waiting for an interrupt)
			fifoCount -= packetSize;

			// display Euler angles in degrees
			mpu.dmpGetQuaternion(&q, fifoBuffer);
			mpu.dmpGetGravity(&gravity, &q);
			mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
			roll = -ypr[1] * 180 / M_PI;
			pitch = ypr[2] * 180 / M_PI;
			yaw = ypr[0] * 180 / M_PI;

		}

	}
	boolean setDMP() {
		Serial.begin(115200);
		Wire.begin();
		boolean error = true;
		while (error) {
			Wire.beginTransmission(104);
			error = Wire.endTransmission(); // if error = 0, we are properly connected
			if (error) { // if we aren't properly connected, try connecting again and loop
				Serial.println("  ");
				Serial.println("Not properly connected to I2C, trying again");
				Serial.println(" ");
				Wire.begin();

			}
		}
		Serial.println("Properly connected to I2C");
		TWBR = 24; // 400kHz I2C clock
		// initialize device
		Serial.println(F("Initializing I2C devices..."));
		mpu.initialize();
		Serial.println(F("Testing device connections...")); // verify connection
		Serial.println(
				mpu.testConnection() ?
						F("MPU6050 connection successful") :
						F("MPU6050 connection failed"));
		// wait for ready
		while (Serial.available() && Serial.read())
			; // empty buffer

		// load and configure the DMP
		Serial.println(F("Initializing DMP..."));
		boolean devStatus = mpu.dmpInitialize();
		mpu.setXGyroOffset(49);
		mpu.setYGyroOffset(24);
		mpu.setZGyroOffset(-24);

		mpu.setXAccelOffset(-4057);
		mpu.setYAccelOffset(-325);
		mpu.setZAccelOffset(1635);
		return devStatus;

	}
	boolean startDMP(boolean devStatus) {

		// make sure it worked (returns 0 if so)
		if (devStatus == 0) {
			// turn on the DMP, now that it's ready
			Serial.println(F("Enabling DMP..."));
			mpu.setDMPEnabled(true);
			// enable Arduino interrupt detection
			Serial.println(
					F(
							"Enabling interrupt detection (Arduino external interrupt 0)..."));
			//PCintPort::attachInterrupt(MPUINTERRUPT, &dmpDataReady, RISING);
			attachInterrupt(0, dmpDataReady, RISING);
			uint8_t mpuIntStatus = mpu.getIntStatus(); // holds actual interrupt status byte from MPU

			// set our DMP Ready flag so the main loop() function knows it's okay to use it
			Serial.println(F("DMP ready! Waiting for first interrupt..."));
			boolean dmpReady = true;

			// get expected DMP packet size for later comparison
			packetSize = mpu.dmpGetFIFOPacketSize();
			while (dmpReady != true)
				;
			return dmpReady;

		} else {
			// ERROR!
			// 1 = initial memory load failed
			// 2 = DMP configuration updates failed
			// (if it's going to break, usually the code will be 1)
			Serial.print(F("DMP Initialization failed (code "));
			Serial.print(devStatus);
			Serial.println(F(")"));
			while (true)
				;
		}
		return 0;
	}

}
/////////////////////////Initialize DMP//////////////////////////
#endif /* IMUFUNCTIONS_H_ */
