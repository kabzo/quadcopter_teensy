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

#define OFFSETACCX -1928
#define OFFSETACCY -1625
#define OFFSETACCZ 1254

#define OFFSETGYROX 35
#define OFFSETGYROY -28
#define OFFSETGYROZ -7

#endif

#define RESETPIN 42

/////////////////////////Initialize DMP/////////////////////////
class IMU {
	public:
		IMU(double * yaw, double * pitch, double * roll) :
				status_(true), packetSize_(0), fifoCount_(0), yaw_(yaw), pitch_(pitch), roll_(roll) {
		}

		void setDMP();
		void getYPRdmp();
		void startDMP();

//		static volatile bool mpuInterrupt;  // indicates whether MPU interrupt pin has gone high

	private:
		/////////////////////////MPU6050/////////////////////////
		MPU6050 mpu_;
		bool status_;
		uint16_t packetSize_;    // expected DMP packet size (default is 42 bytes)

		uint16_t fifoCount_;     // count of all bytes currently in FIFO
		Quaternion q_;           // [w, x, y, z]         quaternion container
		VectorFloat gravity_;    // [x, y, z]            gravity vector

		uint8_t fifoBuffer_[128];

		float ypr_[3]; // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
		double * yaw_;
		double * pitch_;
		double * roll_;
		/////////////////////////MPU6050/////////////////////////
};

//void dmpDataReady();

/////////////////////////Initialize DMP//////////////////////////
#endif /* IMUFUNCTIONS_H_ */
