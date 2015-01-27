#ifndef RADIO_HPP_
#define RADIO_HPP_

#define ROLL_PITCH_INPUT_MAX 45

void initRadio()
{
	param_container.rc1.set_angle(ROLL_PITCH_INPUT_MAX);
	param_container.rc2.set_angle(ROLL_PITCH_INPUT_MAX);
	param_container.rc3.set_range(param_container.throttle_min,
																param_container.throttle_max);
	param_container.rc4.set_angle(180);
}

void updateRadio()
{
	param_container.rc1.read_pwm();
	param_container.rc2.read_pwm();
	param_container.rc3.read_pwm();
	param_container.rc4.read_pwm();

	bool armPositionRc3 =
			param_container.rc3.getPwmIn()
					< (param_container.rc3.getRadioMin()
							+ param_container.rc3.getDeadZone()) ? true : false;

	bool armPositionRc4 =
			param_container.rc4.getPwmIn()
					< (param_container.rc4.getRadioMin()
							+ param_container.rc4.getDeadZone()) ? true : false;

//	DEBUG("armrc3:", armPositionRc3);
//	DEBUGLN("armrc4:", armPositionRc4);

	if (armPositionRc3 && armPositionRc4)
	{
		if (!RC_Channel::armRequest)
		{
			RC_Channel::armRequest = true;
			RC_Channel::armRequestTime = millis();
		}

	} else
		RC_Channel::armRequest = false;

	if (millis() - RC_Channel::armRequestTime > 3000 && RC_Channel::armRequest)
	{
		bool armed = motorsQuad.isArmed();
		motorsQuad.setArmed(!armed);
		DEBUG("armed?:", motorsQuad.isArmed());

		if (motorsQuad.isArmed())
		{
			GCS.setMavModeFlag((uint8_t) MAV_MODE_FLAG_SAFETY_ARMED);
			GCS.setMavMode(MAV_MODE_STABILIZE_ARMED);
			GCS.setMavState(MAV_STATE_ACTIVE);
		} else
		{
			GCS.deleteMavModeFlag((uint8_t) MAV_MODE_FLAG_SAFETY_ARMED);
			GCS.setMavMode(MAV_MODE_STABILIZE_DISARMED);
			GCS.setMavState(MAV_STATE_STANDBY);
		}

		RC_Channel::armRequest = false;
	}

}

void send_GCS_radio_raw()
{
	mavlink_rc_channels_raw_t rc_channels_raw_t;

	rc_channels_raw_t.time_boot_ms = millis();
	rc_channels_raw_t.port = 1;
	rc_channels_raw_t.rssi = 255;

	rc_channels_raw_t.chan1_raw = param_container.rc1.getPwmIn();
	rc_channels_raw_t.chan2_raw = param_container.rc2.getPwmIn();
	rc_channels_raw_t.chan3_raw = param_container.rc3.getPwmIn();
	rc_channels_raw_t.chan4_raw = param_container.rc4.getPwmIn();
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
	rc_channels_scaled.chan1_scaled = param_container.rc1.getScaled();
	rc_channels_scaled.chan2_scaled = param_container.rc2.getScaled();
	rc_channels_scaled.chan3_scaled = param_container.rc3.getScaled();
	rc_channels_scaled.chan4_scaled = param_container.rc4.getScaled();
	rc_channels_scaled.chan5_scaled = 0;
	rc_channels_scaled.chan6_scaled = 0;
	rc_channels_scaled.chan7_scaled = 0;
	rc_channels_scaled.chan8_scaled = 0;

	GCS.send_rc_channels_scaled(rc_channels_scaled);

}

#endif /* RADIO_HPP_ */
