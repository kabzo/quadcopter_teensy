#ifndef COPTERARDUINODUE_GCS_HPP_
#define COPTERARDUINODUE_GCS_HPP_

void sendToGCS_1HZ() // takes around 12 us
{
	if (!GCS.send_hearthbeat())
		ledLeft.changeState(LedPanel::off);
	else
		ledLeft.changeState(LedPanel::on);
}

void send_GCS_attitude()
{
	mavlink_attitude_t mav_attitude;
	mav_attitude.yaw = imu.dmpEuler.YAW;
	mav_attitude.pitch = imu.dmpEuler.PITCH;
	mav_attitude.roll = imu.dmpEuler.ROLL;
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
	if (!GCS.is_gcs_connected())
		return;

	send_GCS_attitude();
//	send_GCS_attitude_scaled();

	send_GCS_radio_raw();
	send_GCS_radio_scaled();
}

template<class T>
void GCS_Mavlink<T>::handle_set_mode(mavlink_message_t *msg)
{
	mavlink_set_mode_t set_mode_t;
	mavlink_msg_set_mode_decode(msg, &set_mode_t);
	if (set_mode_t.target_system == _systemId)
	{
		switch (set_mode_t.base_mode) {
			case MAV_MODE_STABILIZE_ARMED: {
				_mav_state = MAV_STATE_ACTIVE;
				_mav_mode_flag |= MAV_MODE_FLAG_SAFETY_ARMED;
				_mav_mode = (MAV_MODE) set_mode_t.base_mode;
				motorsQuad.set_armed(ARM);
				ledRight.changeState(LedPanel::on);
				break;
			}
			case MAV_MODE_STABILIZE_DISARMED: {
				_mav_state = MAV_STATE_STANDBY;
				_mav_mode_flag &= ~MAV_MODE_FLAG_SAFETY_ARMED;
				_mav_mode = (MAV_MODE) set_mode_t.base_mode;
				motorsQuad.set_armed(DISARM);
				ledRight.changeState(LedPanel::off);

				break;
			}
			case MAV_MODE_MANUAL_DISARMED: {
				_mav_state = MAV_STATE_STANDBY;
				_mav_mode_flag &= ~MAV_MODE_FLAG_SAFETY_ARMED;
				_mav_mode = (MAV_MODE) set_mode_t.base_mode;
				motorsQuad.set_armed(DISARM);
				ledRight.changeState(LedPanel::off);
				break;
			}
			case MAV_MODE_MANUAL_ARMED: {
				_mav_state = MAV_STATE_ACTIVE;
				_mav_mode_flag |= MAV_MODE_FLAG_SAFETY_ARMED;
				_mav_mode = (MAV_MODE) set_mode_t.base_mode;
				motorsQuad.set_armed(ARM);
				ledRight.changeState(LedPanel::on);
				break;
			}
			default: {
				_mav_mode = (MAV_MODE) set_mode_t.base_mode;
				break;
			}
		}

//		Serial.println(mav_mode);
		send_hearthbeat();
	}
}

template void GCS_Mavlink<HardwareSerial>::handle_set_mode(mavlink_message_t *msg);
template void GCS_Mavlink<usb_serial_class>::handle_set_mode(mavlink_message_t *msg);

#endif /* COPTERARDUINODUE_GCS_HPP_ */
