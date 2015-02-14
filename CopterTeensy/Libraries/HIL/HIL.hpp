/*
 * HIL.hpp
 *
 *  Created on: 9.2.2015
 *      Author: Juraj
 */

#ifndef LIBRARIES_HIL_HIL_HPP_
#define LIBRARIES_HIL_HIL_HPP_

#include <Arduino.h>
/*  ESC / Servo signal generation done in hardware by FLEX timer, without ISR (yay!)

 We are using flex timer0 which supports 8 channels.

 Currently generating 400 Hz PWM signal that is fed into electronic speed controllers
 corresponding to each rotor.

 This code will probably be expanded to also generate servo signal for
 gimbal stabilization (hopefully in near future).

 Big thanks to kha from #aeroquad for helping me get this up and running.

 == PIN Configuration ==

 Channel - PIN name - Teensy 3.0 PIN numbering

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

void port_pcr(uint32_t pin, uint32_t val)
{
	switch (pin) {
		case PIN22:
			PORTC_PCR1 |= val;
			break;
		case PIN23:
			PORTC_PCR2 |= val;
			break;
		case PIN9:
			PORTC_PCR3 |= val;
			break;
		case PIN10:
			PORTC_PCR4 |= val;
			break;
		case PIN6:
			PORTD_PCR4 |= val;
			break;
		case PIN20:
			PORTD_PCR5 |= val;
			break;
		case PIN21:
			PORTD_PCR6 |= val;
			break;
		case PIN5:
			PORTD_PCR7 |= val;
			break;
	}
}

void setFTM0_CxV(enum PIN pin, float val)
{
	switch (pin) {
		case PIN22:
			FTM0_C0V = val;
			break;
		case PIN23:
			FTM0_C1V = val;
			break;
		case PIN9:
			FTM0_C2V = val;
			break;
		case PIN10:
			FTM0_C3V = val;
			break;
		case PIN6:
			FTM0_C4V = val;
			break;
		case PIN20:
			FTM0_C5V = val;
			break;
		case PIN21:
			FTM0_C6V = val;
			break;
		case PIN5:
			FTM0_C7V = val;
			break;
	}
}


#endif /* LIBRARIES_HIL_HIL_HPP_ */
