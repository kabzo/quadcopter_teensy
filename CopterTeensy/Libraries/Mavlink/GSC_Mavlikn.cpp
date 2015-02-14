#include <GCS_Mavlink.hpp>

void GCS_Mavlink::changeArmGCS(bool arm)
{
	if (arm)
	{
		setMavModeFlag((uint8_t) MAV_MODE_FLAG_SAFETY_ARMED);
		setMavState(MAV_STATE_ACTIVE);
		armMavMode();
	} else
	{
		deleteMavModeFlag((uint8_t) MAV_MODE_FLAG_SAFETY_ARMED);
		setMavState(MAV_STATE_STANDBY);
		disarmMavMode();
	}
	send_hearthbeat();
}

void GCS_Mavlink::armMavMode()
{
	switch (mav_mode) {
		case MAV_MODE_MANUAL_DISARMED:
			mav_mode = MAV_MODE_MANUAL_ARMED;
			break;
		case MAV_MODE_TEST_DISARMED:
			mav_mode = MAV_MODE_TEST_ARMED;
			break;
		case MAV_MODE_STABILIZE_DISARMED:
			mav_mode = MAV_MODE_STABILIZE_ARMED;
			break;
		case MAV_MODE_GUIDED_DISARMED:
			mav_mode = MAV_MODE_GUIDED_ARMED;
			break;
		case MAV_MODE_AUTO_DISARMED:
			mav_mode = MAV_MODE_AUTO_ARMED;
			break;
		default:
			mav_mode = MAV_MODE_STABILIZE_ARMED;
			break;
	}
	send_hearthbeat();
}

void GCS_Mavlink::disarmMavMode()
{
	switch (mav_mode) {
		case MAV_MODE_MANUAL_ARMED:
			mav_mode = MAV_MODE_MANUAL_DISARMED;
			break;
		case MAV_MODE_TEST_ARMED:
			mav_mode = MAV_MODE_TEST_DISARMED;
			break;
		case MAV_MODE_STABILIZE_ARMED:
			mav_mode = MAV_MODE_STABILIZE_DISARMED;
			break;
		case MAV_MODE_GUIDED_ARMED:
			mav_mode = MAV_MODE_GUIDED_DISARMED;
			break;
		case MAV_MODE_AUTO_ARMED:
			mav_mode = MAV_MODE_AUTO_DISARMED;
			break;
		default:
			mav_mode = MAV_MODE_STABILIZE_DISARMED;
			break;
	}
	send_hearthbeat();
}

void GCS_Mavlink::debugParameter(const char* str)
{
	mavlink_debug_t debug;
	debug.time_boot_ms = millis();
	var_type type;
	debug.value = Mav_Param::get_param_value_id_name(debug.ind, type, str);
	mavlink_message_t msg;
	mavlink_msg_debug_encode(systemId, MAV_COMP_ID_ALL, &msg, &debug);
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];
	uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
	Serial.write(buf, len);
}

void GCS_Mavlink::debugParameter(float val ,uint8_t id)
{
	mavlink_debug_t debug;
	debug.time_boot_ms = millis();
	debug.value = val;
	debug.value = id;

	mavlink_message_t msg;
	mavlink_msg_debug_encode(systemId, MAV_COMP_ID_ALL, &msg, &debug);
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];
	uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
	Serial.write(buf, len);
}

void GCS_Mavlink::mavlink_receive()
{
	mavlink_message_t msg;
	mavlink_status_t status;
	if (Serial.available())
	{
		char c = (char) Serial.read();
		if (mavlink_parse_char(MAVLINK_COMM_0, c, &msg, &status))
		{
			switch (msg.msgid) {
				case MAVLINK_MSG_ID_HEARTBEAT: {
					GCS_connection = true;
					lastReceivedHearthbeat = millis();
					break;
				}
				case MAVLINK_MSG_ID_PARAM_REQUEST_LIST: {
					handle_request_param_list();
					break;
				}
				case MAVLINK_MSG_ID_PARAM_SET: {
					handle_param_set(&msg);
					break;
				}
				case MAVLINK_MSG_ID_SET_MODE: {
					handle_set_mode(&msg);
					break;
				}
				case MAVLINK_MSG_ID_PARAM_REQUEST_READ: {
					handle_param_request_read(&msg);
					break;
				}
				case MAVLINK_MSG_ID_MANUAL_CONTROL: {
					handle_manual_control(&msg);
					break;
				}
				default:
					Serial.println(msg.msgid);
					break;
			}
		}
	}

}

void GCS_Mavlink::waitGCSconnect()
{
#ifdef TEENSY
	ledLeft.changeState(Led::off);
#endif
	do
	{
		mavlink_receive();
	} while (!GCS_connection);
#ifdef TEENSY
	ledLeft.changeState(Led::on);
#endif

}

void GCS_Mavlink::send_rc_channels_raw(mavlink_rc_channels_raw_t &rc_channels_raw)
{

	mavlink_message_t msg;
	mavlink_msg_rc_channels_raw_encode(systemId, MAV_COMP_ID_ALL, &msg, &rc_channels_raw);
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];
	uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
	Serial.write(buf, len);

}

void GCS_Mavlink::send_rc_channels_scaled(mavlink_rc_channels_scaled_t &rc_channels_scaled)
{
	mavlink_message_t msg;
	mavlink_msg_rc_channels_scaled_encode(systemId, MAV_COMP_ID_ALL, &msg, &rc_channels_scaled);
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];
	uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
	Serial.write(buf, len);
}

void GCS_Mavlink::send_param_list_next()
{
	if (next_id <= param_count)
	{
		var_type vtype;
		char name[MAVLINK_MSG_PARAM_SET_FIELD_PARAM_ID_LEN + 1];
		float value = Mav_Param::get_param_value_name_id(vtype, name, next_id);
		mavlink_message_t msg;
		uint8_t buf[MAVLINK_MAX_PACKET_LEN];
		next_id++;

//		Serial.print(name);
//		Serial.print(",");
//		Serial.print(value);
//		Serial.print(",");
//		Serial.print(vtype);
//		Serial.print(",");
//		Serial.print(param_count);
//		Serial.print(",");
//		Serial.println(next_id);

		mavlink_msg_param_value_pack(systemId, MAV_COMP_ID_ALL, &msg, name, value, vtype, param_count, next_id);
		uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
		Serial.write(buf, len);
	}
}

void GCS_Mavlink::handle_request_param_list()
{
	next_id = 0;
//	uint32_t time = micros();
	for (uint8_t i = 0; i < param_count; i++)
	{
		send_param_list_next();
	}
//	Serial.println(micros()-time);
}

void GCS_Mavlink::handle_param_request_read(mavlink_message_t *msg)
{
	mavlink_param_request_read_t packet;
	mavlink_msg_param_request_read_decode(msg, &packet);
	enum var_type vtype;
	uint8_t id;
	float value = Mav_Param::get_param_value_id_name(id, vtype, packet.param_id);
	mavlink_msg_param_value_pack(systemId, MAV_COMP_ID_ALL, msg, packet.param_id, value, vtype, param_count, id);
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];
	uint16_t len = mavlink_msg_to_send_buffer(buf, msg);
	Serial.write(buf, len);

}

void GCS_Mavlink::handle_param_set(mavlink_message_t *msg)
{
	Mav_Param *param;
	enum var_type vtype;
	mavlink_param_set_t packet;
	mavlink_msg_param_set_decode(msg, &packet);

//	Serial.println("Received");
//	Serial.print(packet.param_id);
//	Serial.print(",");
//	Serial.print(packet.param_type);
//	Serial.print(",");
//	Serial.print(packet.param_value);
//	Serial.print(",");
//	Serial.println(packet.target_system);

	param = Mav_Param::find_by_name(packet.param_id, vtype);
	if (param != NULL)
	{
		param->set_value(packet.param_value, vtype);

//		Serial.println("sending bacl");
//		Serial.print(packet.param_id);
//		Serial.print(",");
//		Serial.print(param->cast_to_float_mav(vtype));
//		Serial.print(",");
//		Serial.print(vtype);
//		Serial.print(",");
//		Serial.print(param_count);
//		Serial.print(",");
//		Serial.println(next_id);

		mavlink_msg_param_value_pack(	systemId,
																	MAV_COMP_ID_ALL,
																	msg,
																	packet.param_id,
																	param->cast_to_float_mav(vtype),
																	vtype,
																	param_count,
																	Mav_Param::get_param_id_name(packet.param_id));
		uint8_t buf[MAVLINK_MAX_PACKET_LEN];
		uint16_t len = mavlink_msg_to_send_buffer(buf, msg);
		Serial.write(buf, len);
	}
}

void GCS_Mavlink::send_hearthbeat(MAV_STATE mav_state_define, MAV_MODE mav_mode_define, uint8_t mav_mode_flag_define)
{

	mav_state = mav_state_define;
	mav_mode = mav_mode_define;
	mav_mode_flag |= mav_mode_flag_define;

	mavlink_message_t msg;
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];			// Pack the message
	mavlink_msg_heartbeat_pack(systemId, 0, &msg, MAV_TYPE_QUADROTOR, MAV_AUTOPILOT_PX4, mav_mode, mav_mode_flag, mav_state);

	uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
	Serial.write(buf, len);
}

bool GCS_Mavlink::send_hearthbeat()
{
	if ((millis() - lastReceivedHearthbeat) > 3000)
		GCS_connection = false;
	else
		GCS_connection = true;

	mavlink_message_t msg;
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];			// Pack the message
	mavlink_msg_heartbeat_pack(systemId, 0, &msg, MAV_TYPE_QUADROTOR, MAV_AUTOPILOT_PX4, mav_mode, mav_mode_flag, mav_state);

	// Copy the message to the send buffer
	uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
	Serial.write(buf, len);
	return GCS_connection;
}

void GCS_Mavlink::send_attitude(mavlink_attitude_t &attitude)
{
	mavlink_message_t msg;
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];

	mavlink_msg_attitude_encode(systemId, MAV_COMP_ID_ALL, &msg, &attitude);
	uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
	Serial.write(buf, len);
}

void GCS_Mavlink::send_scaled_imu(mavlink_scaled_imu_t &scaled_imu)
{
	mavlink_message_t msg;
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];

	mavlink_msg_scaled_imu_encode(systemId, MAV_COMP_ID_ALL, &msg, &scaled_imu);
	uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
	Serial.write(buf, len);
}

void GCS_Mavlink::setMavMode(enum MAV_MODE mavMode)
{
	mav_mode = mavMode;
}

void GCS_Mavlink::setMavModeFlag(uint8_t mavModeFlag)
{
	mav_mode_flag |= mavModeFlag;
}

void GCS_Mavlink::deleteMavModeFlag(uint8_t mavModeFlag)
{
	mav_mode_flag &= ~mavModeFlag;
}

inline enum MAV_STATE GCS_Mavlink::getMavState() const
{
	return mav_state;
}

void GCS_Mavlink::setMavState(enum MAV_STATE mavState)
{
	mav_state = mavState;
}

inline void GCS_Mavlink::setGcsConnection(bool gcsConnection)
{
	GCS_connection = gcsConnection;
}

inline uint8_t GCS_Mavlink::getSystemId() const
{
	return systemId;
}

inline void GCS_Mavlink::setSystemId(uint8_t systemId)
{
	this->systemId = systemId;
}

