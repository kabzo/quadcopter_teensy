/*
 * LedPanel.cpp
 *
 *  Created ON: 17.2.2015
 *      Author: Juraj
 */

#include <LedPanel.hpp>


	void LedPanel::actualize_leds(){
		for(int i = 0 ; i< led_number;i++){
			start_led((enum led)i);
		}
	}

void LedPanel::set_state(led led_id, ledState state)
{

	if (led_con[led_id]._state != state)
		{
		led_con[led_id]._state = state;
		led_con[led_id]._lastUpdate = 0;
			start_led(led_id);
		}
}

void LedPanel::negate_state(led led_id)
{
	if (led_con[led_id]._state == ON)
		led_con[led_id]._state = OFF;
	else
		led_con[led_id]._state = ON;

	start_led(led_id);

}

void LedPanel::set_blink(led led_id, blinkState state)
{
	led_con[led_id]._blinkState= state;
}

void LedPanel::start_led(led led_id)
{
	switch (led_con[led_id]._state) {
		case ON:
			set_led_on_off(led_id, (bool) ON);
			break;
		case BLINK:
			if (millis() - led_con[led_id]._lastUpdate > led_con[led_id]._blinkState)
			{
				if (led_con[led_id]._actualState)
					set_led_on_off(led_id, (bool) OFF);
				else
					set_led_on_off(led_id, (bool) ON);
				led_con[led_id]._lastUpdate = millis();
			}
			break;
		default:
			set_led_on_off(led_id, (bool) OFF);
			break;
	}
}

void LedPanel::set_led_on_off(led led_id, bool on_off)
{
	if (led_con[led_id]._actualState != on_off)
	{
		digitalWrite(led_con[led_id]._pin, on_off);
		led_con[led_id]._actualState = on_off;
	}
}

