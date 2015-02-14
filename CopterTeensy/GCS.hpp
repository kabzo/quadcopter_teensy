#ifndef COPTERARDUINODUE_GCS_HPP_
#define COPTERARDUINODUE_GCS_HPP_

void sendToGCS_1HZ() // takes around 12 us
{
	if (!GCS.send_hearthbeat())
		ledLeft.changeState(Led::off);
	else
		ledLeft.changeState(Led::on);
}

void send_GCS_attitude()
{
	mavlink_attitude_t mav_attitude;
	mav_attitude.yaw = imu.dmpEuler.yaw;
	mav_attitude.pitch = imu.dmpEuler.pitch;
	mav_attitude.roll = imu.dmpEuler.roll;
	mav_attitude.pitchspeed = imu.calGyro.y;
	mav_attitude.rollspeed = imu.calGyro.x;
	mav_attitude.yawspeed = imu.calGyro.z;
	mav_attitude.time_boot_ms = millis();

	GCS.send_attitude(mav_attitude);
}
void send_GCS_attitude_scaled()
{
	mavlink_scaled_imu_t mav_scaled_imu;
	mav_scaled_imu.xacc = imu.calAccel.x;
	mav_scaled_imu.yacc = imu.calAccel.y;
	mav_scaled_imu.zacc = imu.calAccel.z;
	mav_scaled_imu.xgyro = imu.calGyro.x;
	mav_scaled_imu.ygyro = imu.calGyro.y;
	mav_scaled_imu.zgyro = imu.calGyro.z;
	mav_scaled_imu.xmag = imu.calMag.x;
	mav_scaled_imu.ymag = imu.calMag.y;
	mav_scaled_imu.zmag = imu.calMag.z;

	GCS.send_scaled_imu(mav_scaled_imu);
}

void sendToGCS_40HZ() //max 0.1ms
{
	if (!GCS.isGcsConnection())
		return;

	send_GCS_attitude();
//	send_GCS_attitude_scaled();

	send_GCS_radio_raw();
	send_GCS_radio_scaled();
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
				ledRight.changeState(Led::on);
				break;
			}
			case MAV_MODE_STABILIZE_DISARMED: {
				mav_state = MAV_STATE_STANDBY;
				mav_mode_flag &= ~MAV_MODE_FLAG_SAFETY_ARMED;
				mav_mode = (MAV_MODE) set_mode_t.base_mode;
				motorsQuad.setArmed(DISARM);
				ledRight.changeState(Led::off);

				break;
			}
			case MAV_MODE_MANUAL_DISARMED: {
				mav_state = MAV_STATE_STANDBY;
				mav_mode_flag &= ~MAV_MODE_FLAG_SAFETY_ARMED;
				mav_mode = (MAV_MODE) set_mode_t.base_mode;
				motorsQuad.setArmed(DISARM);
				ledRight.changeState(Led::off);
				break;
			}
			case MAV_MODE_MANUAL_ARMED: {
				mav_state = MAV_STATE_ACTIVE;
				mav_mode_flag |= MAV_MODE_FLAG_SAFETY_ARMED;
				mav_mode = (MAV_MODE) set_mode_t.base_mode;
				motorsQuad.setArmed(ARM);
				ledRight.changeState(Led::on);
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
