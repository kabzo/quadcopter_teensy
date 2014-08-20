/*
 * Config.h
 *
 *  Created on: 28.6.2014
 *      Author: Duri
 */

#ifndef CONFIG_H_
#define CONFIG_H_

//***********************ESC***********************//
#define MAX_SIGNAL 2000
#define MIN_SIGNAL 1000
#define MPINBL 5
#define MPINBR 4
#define MPINFR 6
#define MPINFL 7
//***********************ESC***********************//

//***********************PID***********************//
#define MAX_PID 50
#define MIN_PID -MAX_PID
#define PIDTIME 20
//***********************PID***********************//

//***********************MPU6050***********************//
#define MPUINTERRUPT 2
//***********************MPU6050***********************//

//***********************FLIGHT CONTROL***********************//
#define THROTTLE_MIN 1000
//***********************FLIGHT CONTROL***********************//

#endif /* CONFIG_H_ */
