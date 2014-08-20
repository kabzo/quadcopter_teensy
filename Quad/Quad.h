// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _Quad_H_
#define _Quad_H_

#include "Include.h"

#ifdef __cplusplus
extern "C" {
#endif
	void loop();
	void setup();
#ifdef __cplusplus
} // extern "C"
#endif

/////////////////////////MPU6050/////////////////////////

MPU6050 mpu;

volatile bool mpuInterrupt = false; // indicates whether MPU interrupt pin has gone high
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO

uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
Quaternion q;           // [w, x, y, z]         quaternion container
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3]; // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
uint8_t fifoBuffer[64]; // FIFO storage buffer
/////////////////////////MPU6050/////////////////////////

#endif /* _Quad_H_ */
