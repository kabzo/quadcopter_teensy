#ifndef RADIO_HPP_
#define RADIO_HPP_

#define ROLL_PITCH_OUTPUT_MAX 4500
#define YAW_OUTPUT_MAX 18000


void handleInterrupt(RC_Channel *rc)
{
	// if the pin is high, its a rising edge of the signal pulse, so lets record its value
	if (digitalRead(rc->pin) == HIGH)
	{
		rc->pwmStart = micros();
	} else
	{
		// else it must be a falling edge, so lets get the time and subtract the time of the rising edge
		// this gives use the time between the rising and falling edges i.e. the pulse duration.
		rc->pwm_in = (uint16_t) (micros() - rc->pwmStart);
		// use set the flag to indicate that a signal has been received
		RC_Channel::newPwm = true;
	}
}

// simple interrupt service routine
void PWM_ISR_1(){	handleInterrupt(&con.rc1);}
void PWM_ISR_2(){	handleInterrupt(&con.rc2);}		// simple interrupt service routine
void PWM_ISR_3(){	handleInterrupt(&con.rc3);}		// simple interrupt service routine
void PWM_ISR_4(){	handleInterrupt(&con.rc4);}

void init_radio()
{
	attachInterrupt(con.rc1.pin, PWM_ISR_1, CHANGE);
	attachInterrupt(con.rc2.pin, PWM_ISR_2, CHANGE);
	attachInterrupt(con.rc3.pin, PWM_ISR_3, CHANGE);
	attachInterrupt(con.rc4.pin, PWM_ISR_4, CHANGE);

	con.rc1.set_angle(ROLL_PITCH_OUTPUT_MAX);
	con.rc2.set_angle(ROLL_PITCH_OUTPUT_MAX);
	con.rc3.set_range(con.throttle_min, con.throttle_max);
	con.rc4.set_angle(YAW_OUTPUT_MAX);
}

void update_radio() //max 22ms
{
	if (!RC_Channel::newPwm)
		return;

	noInterrupts()
	; // turn interrupts off quickly while we take local copies of the shared variables

	con.rc1.localCopy();
	con.rc2.localCopy();
	con.rc3.localCopy();
	con.rc4.localCopy();

	interrupts()
	; // we have local copies of the inputs, so now we can turn interrupts back on
	// as soon as interrupts are back on, we can no longer use the shared copies, the interrupt
	// service routines own these and could update them at any time. During the update, the
	// shared copies may contain junk. Luckily we have our local copies to work with :-)
	RC_Channel::newPwm = false;

	if (motorsQuad.is_ready_fly())
	{
//		con.targetHeading += con.rc4.getScaled() / 100;
		attitudeControl.get_target_angles().YAW += con.rc4.getScaled() / 100;
	}

	if (motorsQuad.check_radio_arm_pos())
	{
		ledRight.negateState();
		GCS.change_arm_GCS(motorsQuad.is_armed());
	}
}

void send_GCS_radio_raw()
{
	mavlink_rc_channels_raw_t rc_channels_raw_t;

	rc_channels_raw_t.time_boot_ms = millis();
	rc_channels_raw_t.port = 1;
	rc_channels_raw_t.rssi = 255;

	rc_channels_raw_t.chan1_raw = con.rc1.getPwmIn();
	rc_channels_raw_t.chan2_raw = con.rc2.getPwmIn();
	rc_channels_raw_t.chan3_raw = con.rc3.getPwmIn();
	rc_channels_raw_t.chan4_raw = con.rc4.getPwmIn();
	rc_channels_raw_t.chan5_raw = 0;
	rc_channels_raw_t.chan6_raw = 0;
	rc_channels_raw_t.chan7_raw = 0;
	rc_channels_raw_t.chan8_raw = 0;

	GCS.send_rc_channels_raw(rc_channels_raw_t);

}

void send_GCS_radio_scaled()
{

	mavlink_rc_channels_scaled_t rc_channels_scaled;

	rc_channels_scaled.time_boot_ms = millis();
	rc_channels_scaled.chan1_scaled = con.rc1.getScaled();
	rc_channels_scaled.chan2_scaled = con.rc2.getScaled();
	rc_channels_scaled.chan3_scaled = con.rc3.getScaled();
	rc_channels_scaled.chan4_scaled = con.rc4.getScaled();
	rc_channels_scaled.chan5_scaled = 0;
	rc_channels_scaled.chan6_scaled = 0;
	rc_channels_scaled.chan7_scaled = 0;
	rc_channels_scaled.chan8_scaled = 0;

	GCS.send_rc_channels_scaled(rc_channels_scaled);

}

template<class T>
void GCS_Mavlink<T>::handle_manual_control(mavlink_message_t *msg)
{
		mavlink_manual_control_t manual_control_t;
		mavlink_msg_manual_control_decode(msg, &manual_control_t);
		if (manual_control_t.target == _systemId)
		{
			con.rc1.overwritePwm(manual_control_t.x);
			con.rc2.overwritePwm(manual_control_t.y);
			con.rc3.overwritePwm(manual_control_t.z);
			con.rc4.overwritePwm(manual_control_t.r);
		}

}

template void GCS_Mavlink<HardwareSerial>::handle_manual_control(mavlink_message_t *msg);
template void GCS_Mavlink<usb_serial_class>::handle_manual_control(mavlink_message_t *msg);

#endif /* RADIO_HPP_ */
