/*
 * LedPanel.cpp
 *
 *  Created on: 17.2.2015
 *      Author: Juraj
 */

#include <LedPanel.hpp>

void LedPanel::setLedHigh()
{
	if (_actualState != HIGH)
	{
		digitalWrite(_pin, HIGH);
		_actualState = HIGH;
	}
}

void LedPanel::changeBlink(blinkState state)
{
	_blinkState = state;
}

void LedPanel::changeState(ledState state)
{
	if (_state != state)
	{
		_state = state;
		_lastUpdate = 0;
		startLed();
	}
}

void LedPanel::startLed()
{
	switch (_state) {
		case on:
			setLedHigh();
			break;
		case blink:
			if (millis() - _lastUpdate > _blinkState)
			{
				if (_actualState)
					setLedLow();
				else
					setLedHigh();
				_lastUpdate = millis();
			}
			break;
		default:
			setLedLow();
			break;
	}
}

void LedPanel::setLedLow()
{
	if (_actualState != LOW)
	{
		digitalWrite(_pin, LOW);
		_actualState = LOW;
	}
}

void LedPanel::negateState()
{
	if (_state == LedPanel::on)
		_state = LedPanel::off;
	else
		_state = LedPanel::on;

	startLed();
}
