#ifndef COPTERARDUINODUE_GCS_HPP_
#define COPTERARDUINODUE_GCS_HPP_

void sendToGCS_1HZ()
{
	if (!GCS.send_hearthbeat())
		ledLeft.changeState(Led::off);
	else
		ledLeft.changeState(Led::on);

}

void send_GCS_attitude()
{
	mavlink_attitude_t mav_attitude;
	mav_attitude.yaw = param_container.vectorYpr.x;
	mav_attitude.pitch = param_container.vectorYpr.y;
	mav_attitude.roll = param_container.vectorYpr.z;
	mav_attitude.pitchspeed = param_container.vectorGyro.y;
	mav_attitude.rollspeed = param_container.vectorGyro.x;
	mav_attitude.yawspeed = param_container.vectorGyro.z;
	mav_attitude.time_boot_ms = millis();

	GCS.send_attitude(mav_attitude);
}
void send_GCS_attitude_scaled()
{
	mavlink_scaled_imu_t mav_scaled_imu;
	mav_scaled_imu.xacc = param_container.vectorAcc.x;
	mav_scaled_imu.yacc = param_container.vectorAcc.y;
	mav_scaled_imu.zacc = param_container.vectorAcc.z;
	mav_scaled_imu.xgyro = param_container.vectorGyro.x;
	mav_scaled_imu.ygyro = param_container.vectorGyro.y;
	mav_scaled_imu.zgyro = param_container.vectorGyro.z;
	mav_scaled_imu.xmag = param_container.vectorMag.x;
	mav_scaled_imu.ymag = param_container.vectorMag.y;
	mav_scaled_imu.zmag = param_container.vectorMag.z;

	GCS.send_scaled_imu(mav_scaled_imu);
}

void sendToGCS_40HZ()
{
	send_GCS_attitude();
	send_GCS_attitude_scaled();

	send_GCS_radio_raw();
	send_GCS_radio_scaled();

//	Serial.print(param_container.rc1.getPwmIn());Serial.print(",");
//	Serial.print(param_container.rc2.getPwmIn());Serial.print(",");
//	Serial.print(param_container.rc3.getPwmIn());Serial.print(",");
//	Serial.println(param_container.rc4.getPwmIn());
}

void GCS_Mavlink::handle_set_mode(mavlink_message_t *msg)
{
	mavlink_set_mode_t set_mode_t;
	mavlink_msg_set_mode_decode(msg, &set_mode_t);
	if (set_mode_t.target_system == systemId)
	{
		switch (set_mode_t.base_mode) {
			case MAV_MODE_STABILIZE_ARMED: {
				mav_state = MAV_STATE_ACTIVE;
				mav_mode_flag |= MAV_MODE_FLAG_SAFETY_ARMED;
				mav_mode = (MAV_MODE) set_mode_t.base_mode;
				motorsQuad.setArmed(ARM);
				break;
			}
			case MAV_MODE_STABILIZE_DISARMED: {
				mav_state = MAV_STATE_STANDBY;
				mav_mode_flag &= ~MAV_MODE_FLAG_SAFETY_ARMED;
				mav_mode = (MAV_MODE) set_mode_t.base_mode;
				motorsQuad.setArmed(DISARM);
				break;
			}
			case MAV_MODE_MANUAL_DISARMED: {
				mav_state = MAV_STATE_STANDBY;
				mav_mode_flag &= ~MAV_MODE_FLAG_SAFETY_ARMED;
				mav_mode = (MAV_MODE) set_mode_t.base_mode;
				motorsQuad.setArmed(DISARM);
				break;
			}
			case MAV_MODE_MANUAL_ARMED: {
				mav_state = MAV_STATE_ACTIVE;
				mav_mode_flag |= MAV_MODE_FLAG_SAFETY_ARMED;
				mav_mode = (MAV_MODE) set_mode_t.base_mode;
				motorsQuad.setArmed(ARM);
				break;
			}
			default: {
				mav_mode = (MAV_MODE) set_mode_t.base_mode;
				break;
			}
		}

//		Serial.println(mav_mode);
		send_hearthbeat();
	}
}

#endif /* COPTERARDUINODUE_GCS_HPP_ */
