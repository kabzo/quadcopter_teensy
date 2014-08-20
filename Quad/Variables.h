/*
 * Variables.h
 *
 *  Created on: 28.6.2014
 *      Author: Duri
 */

#ifndef VARIABLES_H_
#define VARIABLES_H_

/////////////////////////FlightControll/////////////////////////
double setpointRoll = 0;
double setpointPitch = 0;
double setpointYaw = 0;
double throttle = THROTTLE_MIN;

double outputRoll;
double outputPitch;
double outputYaw;

double roll,pitch,yaw;
double motorFLpower,motorFRpower,motorBLpower,motorBRpower;

PID pidRoll(&roll, &outputRoll, &setpointRoll, 5, 0, 1, DIRECT);
PID pidPitch(&pitch, &outputPitch, &setpointPitch, 0, 0,0, REVERSE);
PID pidYaw(&yaw, &outputYaw, &setpointYaw, 5, 0, 1, DIRECT);

bool calibrateESC = false; //calibrate ESC
Servo motorBL,motorFL,motorBR,motorFR;
/////////////////////////FlightControll/////////////////////////




#endif /* VARIABLES_H_ */
