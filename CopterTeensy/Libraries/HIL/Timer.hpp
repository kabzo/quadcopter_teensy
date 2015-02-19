/*
 * Timer.hpp
 *
 *  Created on: 16.2.2015
 *      Author: Juraj
 */

#ifndef LIBRARIES_HIL_TIMER_HPP_
#define LIBRARIES_HIL_TIMER_HPP_

#include <HIL.hpp>


class Timer
{
public:
	Timer() :
					actualTime(0),
					stopTime(0),
					differenz(0)
	{
	}

	void start()
	{
		actualTime = micros();
	}

	float stopDiff()
	{
		stopTime = micros();
		differenz = stopTime - actualTime;
		return differenz / 1000;
	}

	float diff()
	{
		uint32_t now = micros();
		differenz = now - actualTime;
		return differenz / 1000;
	}

	void printDiff()
	{
		GCS._serial.println(diff());
	}

private:
	uint32_t actualTime;
	uint32_t stopTime;
	float differenz;
};


#endif /* LIBRARIES_HIL_TIMER_HPP_ */
