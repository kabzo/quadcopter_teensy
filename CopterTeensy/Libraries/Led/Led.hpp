/*
 * Led.hpp
 *
 *  Created on: 30.11.2014
 *      Author: Juraj
 */

#ifndef LED_HPP_
#define LED_HPP_

#define LED1  12      // pin on teensy imu board
#define LED2  11
#define LED3  2

class Led
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

	Led(uint8_t pin, ledState state = off, blinkState blink = slow) :
					_pin(pin),
					_state(state),
					_value(0),
					_lastUpdate(0),
					_blinkState(blink),
//					_statePower(false),
					_actualState(LOW)
	{
		pinMode(pin, OUTPUT);
	}

	void changeState(ledState state)
	{

		if (_state != state)
		{
			_value = 0;
//			_statePower = false;
			_state = state;
			_lastUpdate = 0;
			startLed();
		}

	}

	void negateState()
	{
		if (_state == Led::on)
			_state = Led::off;
		else
			_state = Led::on;
	}

	void changeBlink(blinkState state)
	{
		_blinkState = state;
	}

	void startLed()
	{
		switch (_state) {
			case on: {
				setLedHigh();
				break;
			}
			case blink: {
				if (millis() - _lastUpdate > _blinkState)
				{
//					if (_statePower)
//					{
						setLedHigh();
//					} else
//					{
						setLedLow();
//					}
//					_statePower = !_statePower;
					_lastUpdate = millis();
				}
				break;
			}
			default: {
				setLedLow();
				break;
			}
		}

	}

private:
	uint8_t _pin;
	ledState _state;
	uint16_t _value;
	uint32_t _lastUpdate;
	blinkState _blinkState;
//	bool _statePower;
	bool _actualState;

	void setLedHigh()
	{
		if (_actualState != HIGH)
		{
			digitalWrite(_pin, HIGH);
			_actualState = HIGH;
		}
	}
	void setLedLow()
	{
		if (_actualState != LOW)
		{
			digitalWrite(_pin, LOW);
			_actualState = LOW;
		}
	}
}
;

Led ledMiddle(LED3, Led::off);
Led ledLeft(LED2, Led::off);
Led ledRight(LED1, Led::off);

void ledStart()
{
	ledMiddle.startLed();
	ledLeft.startLed();
	ledRight.startLed();
}

#endif /* LED_HPP_ */
