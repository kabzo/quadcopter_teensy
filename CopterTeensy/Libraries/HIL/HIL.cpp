/*
 * HIL.cpp
 *
 *  Created on: 17.2.2015
 *      Author: Juraj
 */
#include <HIL.hpp>


#ifdef USB
GCS_USB GCS(Serial);
#elif defined BLUETOOTH
GCS_BLUETOOTH GCS(Serial1);
#endif


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
