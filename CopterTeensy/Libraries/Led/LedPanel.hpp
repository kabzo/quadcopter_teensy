/*
 * Led.hpp
 *
 *  Created on: 30.11.2014
 *      Author: Juraj
 */

#ifndef LEDPANEL_HPP_
#define LEDPANEL_HPP_

#include <Arduino.h>

#define LED1  12      // pin on teensy imu board
#define LED2  11
#define LED3  2

class LedPanel
{
public:
	enum blinkState
	{
			slow = 1000,
			middle = 500,
			fast = 250,
	};

	enum ledState
	{
			on,
			blink,
			off,
	};

	LedPanel(uint8_t pin, ledState state = off, blinkState blink = slow) :
			_pin(pin), _state(state), _blinkState(blink), _lastUpdate(0), _actualState(LOW)
	{
		pinMode(pin, OUTPUT);
	}

	void changeState(ledState state);
	void negateState();
	void changeBlink(blinkState state);
	void startLed();

private:
	void setLedHigh();
	void setLedLow();

	uint8_t _pin;
	ledState _state;
	blinkState _blinkState;
	uint32_t _lastUpdate;
	bool _actualState;
};

#endif /* LEDPANEL_HPP_ */
