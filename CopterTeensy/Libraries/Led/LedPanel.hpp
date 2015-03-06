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

enum led
{
		R = 0, //right
		G,		//left
		B 		//middle
};

enum ledState
{
		OFF,
		ON,
		BLINK,
};

class LedPanel
{
public:
	enum blinkState
	{
			fast = 250,
			middle = 500,
			slow = 1000,
	};



	struct led_control
	{
		uint8_t _pin;
		ledState _state;
		blinkState _blinkState;
		bool _actualState;
		uint32_t _lastUpdate;
	};

	LedPanel(uint8_t pin1, uint8_t pin2, uint8_t pin3, ledState state = OFF, blinkState blink = slow)

	{
		led_con[0]._pin = pin1;
		led_con[1]._pin = pin2;
		led_con[2]._pin = pin3;

		for (int i = 0; i < led_number; i++)
		{
			pinMode(led_con[i]._pin, OUTPUT);
			led_con[i]._actualState = false;
			led_con[i]._blinkState = slow;
			led_con[i]._state = OFF;
		}
	}

	void set_state(led led_id, ledState state);
	void negate_state(led led_id);
	void set_blink(led led_id, blinkState state);
	void start_led(led led_id);

	void actualize_leds();

private:

	led_control led_con[3];
	void set_led_on_off(led led_id, bool on_off);

	const uint8_t led_number = 3;
};

#endif /* LEDPANEL_HPP_ */
