/*
 * HIL.hpp
 *
 *  Created on: 9.2.2015
 *      Author: Juraj
 */

#ifndef LIBRARIES_HIL_HIL_HPP_
#define LIBRARIES_HIL_HIL_HPP_

#include <Arduino.h>
#include <GCS_Mavlink.hpp>
#include <Thread.hpp>

//#define DEBUG_ALL

//  Define this symbol to get debug messages

#ifdef DEBUG_ALL

#define DEBUG2(X,Y) Serial.print(X);Serial.print(":"); Serial.print(Y);Serial.print(",")
#define DEBUGLN2(X,Y) Serial.print(X);Serial.print(":"); Serial.println(Y)
#define DEBUGLN3(X,Y,Z) Serial.print(X);Serial.print(","); Serial.print(Y);Serial.print(",");Serial.println(Z)
#define DEBUGLN1(X) Serial.println(X)
#define DEBUG1(X) Serial.print(X);Serial.print(",")

#else

#define DEBUG2(X,Y)
#define DEBUGLN2(X,Y)
#define DEBUGLN3(X,Y,Z)
#define DEBUGLN1(X)
#define DEBUG1(X)

#endif


#define SUCCESFULL 0


#define HZ_200_MS	5
#define HZ_100_MS	10
#define HZ_50_MS	20

#define HZ_20 20
#define HZ_40 40




/*  ESC / Servo signal generation done in hardware by FLEX timer, without ISR (yay!)

 We are using flex timer0 which supports 8 channels.

 Currently generating 400 Hz PWM signal that is fed into electronic speed controllers
 corresponding to each rotor.

 This code will probably be expanded to also generate servo signal for
 gimbal stabilization (hopefully in near future).

 Big thanks to kha from #aeroquad for helping me get this up and running.

 == PIN Configuration ==

 Channel - PIN name - Teensy 3.1 PIN numbering

 FTM0_CH0 - PTC1 - 22:1
 FTM0_CH1 - PTC2 - 23:2
 FTM0_CH2 - PTC3 - 9 :3
 FTM0_CH3 - PTC4 - 10:4
 FTM0_CH4 - PTD4 - 6 :5
 FTM0_CH5 - PTD5 - 20:6
 FTM0_CH6 - PTD6 - 21:7
 FTM0_CH7 - PTD7 - 5 :8
 */
enum PIN
{
		PIN22,
		PIN23,
		PIN9,
		PIN10,
		PIN6,
		PIN20,
		PIN21,
		PIN5
};

void port_pcr(uint32_t pin, uint32_t val);

void setFTM0_CxV(enum PIN pin, float val);


#endif /* LIBRARIES_HIL_HIL_HPP_ */
