#include <GCS_Mavlink.hpp>

//template <class T>
//T& GCS_Mavlink<T>::_serial = Serial;
// template usb_serial_class& GCS_Mavlink<usb_serial_class>::_serial = Serial;
// template HardwareSerial& GCS_Mavlink<HardwareSerial>::_serial = Serial1;

//template<class T>
//T& GCS_Mavlink<T>::_serial = Serial;

//template<>
//usb_serial_class& GCS_Mavlink<usb_serial_class>::_serial = Serial;
//
//template<>
//HardwareSerial& GCS_Mavlink<HardwareSerial>::_serial = Serial1;


template<class T>
void GCS_Mavlink<T>::init(const Mav_Param::Info *info)
{
	Mav_Param param_loader(info);
	_param_count = Mav_Param::_num_vars_all;
	_serial.begin(115200);
}

template<class T>
void GCS_Mavlink<T>::change_arm_GCS(bool arm)
{
	if (arm)
	{
		set_mav_mode_flag((uint8_t) MAV_MODE_FLAG_SAFETY_ARMED);
		set_mav_state(MAV_STATE_ACTIVE);
		arm_mav_mode();
	} else
	{
		delete_mav_mode_flag((uint8_t) MAV_MODE_FLAG_SAFETY_ARMED);
		set_mav_state(MAV_STATE_STANDBY);
		disarm_mav_mode();
	}
	send_hearthbeat();
}

template<class T>
void GCS_Mavlink<T>::arm_mav_mode()
{
	switch (_mav_mode) {
		case MAV_MODE_MANUAL_DISARMED:
			_mav_mode = MAV_MODE_MANUAL_ARMED;
			break;
		case MAV_MODE_TEST_DISARMED:
			_mav_mode = MAV_MODE_TEST_ARMED;
			break;
		case MAV_MODE_STABILIZE_DISARMED:
			_mav_mode = MAV_MODE_STABILIZE_ARMED;
			break;
		case MAV_MODE_GUIDED_DISARMED:
			_mav_mode = MAV_MODE_GUIDED_ARMED;
			break;
		case MAV_MODE_AUTO_DISARMED:
			_mav_mode = MAV_MODE_AUTO_ARMED;
			break;
		default:
			_mav_mode = MAV_MODE_STABILIZE_ARMED;
			break;
	}
	send_hearthbeat();
}

template<class T>
void GCS_Mavlink<T>::disarm_mav_mode()
{
	switch (_mav_mode) {
		case MAV_MODE_MANUAL_ARMED:
			_mav_mode = MAV_MODE_MANUAL_DISARMED;
			break;
		case MAV_MODE_TEST_ARMED:
			_mav_mode = MAV_MODE_TEST_DISARMED;
			break;
		case MAV_MODE_STABILIZE_ARMED:
			_mav_mode = MAV_MODE_STABILIZE_DISARMED;
			break;
		case MAV_MODE_GUIDED_ARMED:
			_mav_mode = MAV_MODE_GUIDED_DISARMED;
			break;
		case MAV_MODE_AUTO_ARMED:
			_mav_mode = MAV_MODE_AUTO_DISARMED;
			break;
		default:
			_mav_mode = MAV_MODE_STABILIZE_DISARMED;
			break;
	}

	send_hearthbeat();
}

template<class T>
void GCS_Mavlink<T>::debug_parameter(const char* str)
{
	mavlink_debug_t debug;
	debug.time_boot_ms = millis();
	var_type type;
	debug.value = Mav_Param::get_value_id_by_name(debug.ind, type, str);
	_serial.print(debug.value);
	_serial.print(",");
	_serial.println(debug.ind);
	mavlink_message_t msg;
	mavlink_msg_debug_encode(_systemId, MAV_COMP_ID_ALL, &msg, &debug);
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];
	uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
	_serial.write(buf, len);
}

template<class T>
void GCS_Mavlink<T>::debug_parameter(float val, uint8_t& id)
{
	mavlink_debug_t debug;
	debug.time_boot_ms = millis();
	debug.value = (float) val;
	debug.ind = id;
	id++;

	mavlink_message_t msg;
	mavlink_msg_debug_encode(_systemId, MAV_COMP_ID_ALL, &msg, &debug);
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];
	uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
	_serial.write(buf, len);
}

template<class T>
void GCS_Mavlink<T>::mavlink_receive()
{
	mavlink_message_t msg;
	mavlink_status_t status;
	if (_serial.available())
	{
		char c = (char) _serial.read();
		if (mavlink_parse_char(MAVLINK_COMM_0, c, &msg, &status))
		{
			switch (msg.msgid) {
				case MAVLINK_MSG_ID_HEARTBEAT: {
					_GCS_connection = true;
					_lastReceivedHearthbeat = millis();
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
					_serial.print("msgid:");
					_serial.println((uint8_t) msg.msgid);
					break;
			}
		}
	}
	if (_GCS_connection)
		send_param_list_next();
}

template<class T>
void GCS_Mavlink<T>::wait_gcs_connect()
{
	do
	{
		mavlink_receive();
	} while (!_GCS_connection);
//	ledLeft.changeState(Led::on);

}

template<class T>
void GCS_Mavlink<T>::send_rc_channels_raw(mavlink_rc_channels_raw_t &rc_channels_raw)
{

	mavlink_message_t msg;
	mavlink_msg_rc_channels_raw_encode(_systemId, MAV_COMP_ID_ALL, &msg, &rc_channels_raw);
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];
	uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
	_serial.write(buf, len);

}

template<class T>
void GCS_Mavlink<T>::send_rc_channels_scaled(mavlink_rc_channels_scaled_t &rc_channels_scaled)
{
	mavlink_message_t msg;
	mavlink_msg_rc_channels_scaled_encode(_systemId, MAV_COMP_ID_ALL, &msg, &rc_channels_scaled);
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];
	uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
	_serial.write(buf, len);
}

template<class T>
void GCS_Mavlink<T>::send_param_list_next()
{
	if (_next_id <= _param_count)
	{
		var_type vtype;
		char name[MAVLINK_MSG_PARAM_SET_FIELD_PARAM_ID_LEN + 1];
		float value = Mav_Param::get_value_name_by_id(vtype, name, _next_id);
		mavlink_message_t msg;
		uint8_t buf[MAVLINK_MAX_PACKET_LEN];
		_next_id++;

//		serial.print(name);
//		serial.print(",");
//		serial.print(value);
//		serial.print(",");
//		serial.print(vtype);
//		serial.print(",");
//		serial.print(param_count);
//		serial.print(",");
//		serial.println(next_id);

		mavlink_msg_param_value_pack(	_systemId,
																	MAV_COMP_ID_ALL,
																	&msg,
																	name,
																	value,
																	vtype,
																	_param_count,
																	_next_id);
		uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
		_serial.write(buf, len);
	}
}

template<class T>
void GCS_Mavlink<T>::handle_request_param_list()
{
	_next_id = 0;
}

template<class T>
void GCS_Mavlink<T>::handle_param_request_read(mavlink_message_t *msg)
{
	mavlink_param_request_read_t packet;
	mavlink_msg_param_request_read_decode(msg, &packet);
	enum var_type vtype;

	_serial.print("handle_param_request_read:");
	_serial.println(packet.param_index);

	float value = Mav_Param::get_value_name_by_id(vtype, packet.param_id, packet.param_index);
	mavlink_msg_param_value_pack(	_systemId,
																MAV_COMP_ID_ALL,
																msg,
																packet.param_id,
																value,
																vtype,
																_param_count,
																packet.param_index);
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];
	uint16_t len = mavlink_msg_to_send_buffer(buf, msg);
	_serial.write(buf, len);

}

template<class T>
void GCS_Mavlink<T>::handle_param_set(mavlink_message_t *msg)
{
	Mav_Param *param;
	enum var_type vtype;
	mavlink_param_set_t packet;
	mavlink_msg_param_set_decode(msg, &packet);
	param = Mav_Param::get_param_by_name(packet.param_id, vtype);
	if (param != NULL)
	{
		param->set_value(packet.param_value, vtype);

		mavlink_msg_param_value_pack(	_systemId,
																	MAV_COMP_ID_ALL,
																	msg,
																	packet.param_id,
																	param->cast_to_float_mav(vtype),
																	vtype,
																	_param_count,
																	Mav_Param::get_id_by_name(packet.param_id));
		uint8_t buf[MAVLINK_MAX_PACKET_LEN];
		uint16_t len = mavlink_msg_to_send_buffer(buf, msg);
		_serial.write(buf, len);
	}
}

template<class T>
bool GCS_Mavlink<T>::send_hearthbeat()
{
	if ((millis() - _lastReceivedHearthbeat) > 3000)
		_GCS_connection = false;
	else
		_GCS_connection = true;

	mavlink_message_t msg;
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];			// Pack the message
	mavlink_msg_heartbeat_pack(	_systemId,
															0,
															&msg,
															MAV_TYPE_QUADROTOR,
															MAV_AUTOPILOT_PX4,
															_mav_mode,
															_mav_mode_flag,
															_mav_state);

	// Copy the message to the send buffer
	uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
	_serial.write(buf, len);
	return _GCS_connection;
}

template<class T>
void GCS_Mavlink<T>::send_hearthbeat(	MAV_STATE mav_state_define,
																			MAV_MODE mav_mode_define,
																			uint8_t mav_mode_flag_define)
{

	_mav_state = mav_state_define;
	_mav_mode = mav_mode_define;
	_mav_mode_flag |= mav_mode_flag_define;

	mavlink_message_t msg;
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];			// Pack the message
	mavlink_msg_heartbeat_pack(	_systemId,
															0,
															&msg,
															MAV_TYPE_QUADROTOR,
															MAV_AUTOPILOT_PX4,
															_mav_mode,
															_mav_mode_flag,
															_mav_state);

	uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
	_serial.write(buf, len);
}

template<class T>
void GCS_Mavlink<T>::send_attitude(mavlink_attitude_t &attitude)
{
	mavlink_message_t msg;
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];

	mavlink_msg_attitude_encode(_systemId, MAV_COMP_ID_ALL, &msg, &attitude);
	uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
	_serial.write(buf, len);
}

template<class T>
void GCS_Mavlink<T>::send_scaled_imu(mavlink_scaled_imu_t &scaled_imu)
{
	mavlink_message_t msg;
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];

	mavlink_msg_scaled_imu_encode(_systemId, MAV_COMP_ID_ALL, &msg, &scaled_imu);
	uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
	_serial.write(buf, len);
}

template<class T>
void GCS_Mavlink<T>::set_mav_mode(enum MAV_MODE mavMode)
{
	_mav_mode = mavMode;
}

template<class T>
void GCS_Mavlink<T>::set_mav_mode_flag(uint8_t mavModeFlag)
{
	_mav_mode_flag |= mavModeFlag;
}

template<class T>
void GCS_Mavlink<T>::delete_mav_mode_flag(uint8_t mavModeFlag)
{
	_mav_mode_flag &= ~mavModeFlag;
}

template<class T>
MAV_STATE GCS_Mavlink<T>::get_mav_state()
{
	return _mav_state;
}

template<class T>
void GCS_Mavlink<T>::set_mav_state(enum MAV_STATE mavState)
{
	_mav_state = mavState;
}

template<class T>
void GCS_Mavlink<T>::set_gcs_connection(bool gcsConnection)
{
	_GCS_connection = gcsConnection;
}

template<class T>
uint8_t GCS_Mavlink<T>::get_system_id()
{
	return _systemId;
}

template<class T>
bool GCS_Mavlink<T>::is_gcs_connected()
{
	return _GCS_connection;
}

template<class T>
MAV_MODE GCS_Mavlink<T>::get_mav_mode()
{
	return _mav_mode;
}

template<class T>
void GCS_Mavlink<T>::set_system_id(uint8_t systemId)
{
	this->_systemId = systemId;
}

template void GCS_Mavlink<HardwareSerial>::init(const Mav_Param::Info *info);
template void GCS_Mavlink<HardwareSerial>::handle_request_param_list();
template void GCS_Mavlink<HardwareSerial>::handle_param_request_read(mavlink_message_t *msg);
template void GCS_Mavlink<HardwareSerial>::handle_param_set(mavlink_message_t *msg);
template void GCS_Mavlink<HardwareSerial>::send_param_list_next();
template void GCS_Mavlink<HardwareSerial>::send_hearthbeat(	MAV_STATE mav_state_define,
																														MAV_MODE mav_mode_define,
																														uint8_t mav_mode_flag_define);
template bool GCS_Mavlink<HardwareSerial>::send_hearthbeat();
template void GCS_Mavlink<HardwareSerial>::send_attitude(mavlink_attitude_t &attitude);
template void GCS_Mavlink<HardwareSerial>::send_scaled_imu(mavlink_scaled_imu_t &scaled_imu);
template void GCS_Mavlink<HardwareSerial>::send_rc_channels_raw(mavlink_rc_channels_raw_t &rc_channels_raw);
template void GCS_Mavlink<HardwareSerial>::send_rc_channels_scaled(mavlink_rc_channels_scaled_t &rc_channels_scaled);
template void GCS_Mavlink<HardwareSerial>::mavlink_receive();
template void GCS_Mavlink<HardwareSerial>::wait_gcs_connect();
template void GCS_Mavlink<HardwareSerial>::set_mav_mode(enum MAV_MODE mavMode);
template void GCS_Mavlink<HardwareSerial>::set_mav_mode_flag(uint8_t mavModeFlag);
template void GCS_Mavlink<HardwareSerial>::delete_mav_mode_flag(uint8_t mavModeFlag);
template void GCS_Mavlink<HardwareSerial>::disarm_mav_mode();
template void GCS_Mavlink<HardwareSerial>::arm_mav_mode();
template void GCS_Mavlink<HardwareSerial>::change_arm_GCS(bool arm);
template void GCS_Mavlink<HardwareSerial>::debug_parameter(const char* str);
template void GCS_Mavlink<HardwareSerial>::debug_parameter(float val, uint8_t& id);
template MAV_STATE GCS_Mavlink<HardwareSerial>::get_mav_state();
template MAV_MODE GCS_Mavlink<HardwareSerial>::get_mav_mode();
template void GCS_Mavlink<HardwareSerial>::set_mav_state(enum MAV_STATE mavState);
template bool GCS_Mavlink<HardwareSerial>::is_gcs_connected();
template void GCS_Mavlink<HardwareSerial>::set_gcs_connection(bool gcsConnection);
template uint8_t GCS_Mavlink<HardwareSerial>::get_system_id();
template void GCS_Mavlink<HardwareSerial>::set_system_id(uint8_t systemId);

template void GCS_Mavlink<usb_serial_class>::init(const Mav_Param::Info *info);
template void GCS_Mavlink<usb_serial_class>::handle_request_param_list();
template void GCS_Mavlink<usb_serial_class>::handle_param_request_read(mavlink_message_t *msg);
template void GCS_Mavlink<usb_serial_class>::handle_param_set(mavlink_message_t *msg);
template void GCS_Mavlink<usb_serial_class>::send_param_list_next();
template void GCS_Mavlink<usb_serial_class>::send_hearthbeat(	MAV_STATE mav_state_define,
																															MAV_MODE mav_mode_define,
																															uint8_t mav_mode_flag_define);
template bool GCS_Mavlink<usb_serial_class>::send_hearthbeat();
template void GCS_Mavlink<usb_serial_class>::send_attitude(mavlink_attitude_t &attitude);
template void GCS_Mavlink<usb_serial_class>::send_scaled_imu(mavlink_scaled_imu_t &scaled_imu);
template void GCS_Mavlink<usb_serial_class>::send_rc_channels_raw(mavlink_rc_channels_raw_t &rc_channels_raw);
template void GCS_Mavlink<usb_serial_class>::send_rc_channels_scaled(mavlink_rc_channels_scaled_t &rc_channels_scaled);
template void GCS_Mavlink<usb_serial_class>::mavlink_receive();
template void GCS_Mavlink<usb_serial_class>::wait_gcs_connect();
template void GCS_Mavlink<usb_serial_class>::set_mav_mode(enum MAV_MODE mavMode);
template void GCS_Mavlink<usb_serial_class>::set_mav_mode_flag(uint8_t mavModeFlag);
template void GCS_Mavlink<usb_serial_class>::delete_mav_mode_flag(uint8_t mavModeFlag);
template void GCS_Mavlink<usb_serial_class>::disarm_mav_mode();
template void GCS_Mavlink<usb_serial_class>::arm_mav_mode();
template void GCS_Mavlink<usb_serial_class>::change_arm_GCS(bool arm);
template void GCS_Mavlink<usb_serial_class>::debug_parameter(const char* str);
template void GCS_Mavlink<usb_serial_class>::debug_parameter(float val, uint8_t& id);
template MAV_STATE GCS_Mavlink<usb_serial_class>::get_mav_state();
template MAV_MODE GCS_Mavlink<usb_serial_class>::get_mav_mode();
template void GCS_Mavlink<usb_serial_class>::set_mav_state(enum MAV_STATE mavState);
template bool GCS_Mavlink<usb_serial_class>::is_gcs_connected();
template void GCS_Mavlink<usb_serial_class>::set_gcs_connection(bool gcsConnection);
template uint8_t GCS_Mavlink<usb_serial_class>::get_system_id();
template void GCS_Mavlink<usb_serial_class>::set_system_id(uint8_t systemId);

