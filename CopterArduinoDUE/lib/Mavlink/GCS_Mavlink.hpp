/*
 * GSC_Mavlink.hpp
 *
 *  Created on: 2.11.2014
 *      Author: Juraj
 */

#ifndef GCS_MAVLINK_HPP_
#define GCS_MAVLINK_HPP_

#include <Mav_Param.hpp>
#include <mavlinkCommon/common/mavlink.h>

class GCS_Mavlink
{
	public:
		GCS_Mavlink()
				: GCS_connection(false),
					next_param(NULL),
					next_id(0),
					param_count(Mav_Param::cout_vars()),
					systemId(100),
//					lastTimeMavlinkReceive(0),
//					lastTimesendHeathbeat(0),
//					lastTimesendAttitude(0),
					lastReceivedHearthbeat(0),
					mav_state(MAV_STATE_BOOT),
					mav_mode(MAV_MODE_PREFLIGHT)
		{

			mav_mode_flag = MAV_MODE_FLAG_MANUAL_INPUT_ENABLED;

		}

		void send_param_list_next();
		void handle_request_param_list();
		void handle_param_request_read(mavlink_message_t *msg);
		void handle_param_set(mavlink_message_t *msg);
		void handle_manual_control(mavlink_message_t *msg);
		void handle_set_mode(mavlink_message_t *msg);

		void send_hearthbeat(	 MAV_STATE mav_state_define,
													 MAV_MODE mav_mode_define,
													 MAV_MODE_FLAG mav_mode_flag_define);
		void send_hearthbeat();
//		void send_hearthbeat_1HZ(enum MAV_STATE mav_state, enum MAV_MODE mav_mode);
//		void send_hearthbeat_1HZ();
		void send_attitude(mavlink_attitude_t &attitude);

		void mavlink_receive();
		void waitGCSconnect();

		enum MAV_MODE getMavMode() const;
		void setMavMode(enum MAV_MODE mavMode);
		enum MAV_MODE_FLAG getMavModeFlag() const;
		void setMavModeFlag(enum MAV_MODE_FLAG mavModeFlag);
		enum MAV_STATE getMavState() const;
		void setMavState(enum MAV_STATE mavState);
		bool isGcsConnection() const;
		void setGcsConnection(bool gcsConnection);

	private:
		bool GCS_connection;
		Mav_Param * next_param;
		uint8_t next_id;
		uint8_t param_count;
		uint8_t systemId;

//		uint32_t lastTimesendHeathbeat;
//		static const uint16_t sendHearthbeat1HZ = 1000;
//
//		uint32_t lastTimesendAttitude;
//		static const uint16_t sendAttitudebeat10HZ = 100;

		uint32_t lastReceivedHearthbeat;

		enum MAV_STATE mav_state;
		enum MAV_MODE mav_mode;
		enum MAV_MODE_FLAG mav_mode_flag;

};

void GCS_Mavlink::mavlink_receive()
{
	mavlink_message_t msg;
	mavlink_status_t status;
	while (Serial.available()) {
		char c = (char) Serial.read();
		if (mavlink_parse_char(MAVLINK_COMM_1, c, &msg, &status)) {
			switch (msg.msgid)
			{
				case MAVLINK_MSG_ID_HEARTBEAT: {
					lastReceivedHearthbeat = millis();
					GCS_connection = true;
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
				case MAVLINK_MSG_ID_MANUAL_CONTROL: {
					handle_manual_control(&msg);
					break;
				}
				default:
					Serial.println(msg.msgid);
					break;
			}
		}
		delay(1);
	}
}

void GCS_Mavlink::waitGCSconnect()
{
	do {
		mavlink_receive();
	} while (!GCS_connection);
}

void GCS_Mavlink::handle_set_mode(mavlink_message_t *msg)
{
	mavlink_set_mode_t set_mode_t;
	mavlink_msg_set_mode_decode(msg, &set_mode_t);
	if (set_mode_t.target_system == systemId) {
		mav_mode = (MAV_MODE) set_mode_t.base_mode;
//		Serial.println(mav_mode);
	}
}

void GCS_Mavlink::send_param_list_next()
{
	if (next_id <= param_count) {
		var_type vtype;
		float value = Mav_Param::get_param_id_value(next_id, &vtype);
		mavlink_message_t msg;
		uint8_t buf[MAVLINK_MAX_PACKET_LEN];
		const char *name;
		name = Mav_Param::get_param_name_id(next_id);
		next_id++;
		mavlink_msg_param_value_pack(	systemId,
																	MAV_COMP_ID_ALL,
																	&msg,
																	name,
																	value,
																	vtype,
																	param_count,
																	next_id);
		uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
		Serial.write(buf, len);
		Serial.flush();
	}
}

void GCS_Mavlink::handle_request_param_list()
{
	next_id = 0;
	for (uint8_t i = 0; i < param_count; i++) {
		send_param_list_next();
//		delay(100);
	}
}

void GCS_Mavlink::handle_param_request_read(mavlink_message_t *msg)
{
	mavlink_param_request_read_t packet;
	mavlink_msg_param_request_read_decode(msg, &packet);
	enum var_type vtype;
	Mav_Param * param;
	param = Mav_Param::find_by_name(packet.param_id, &vtype);
	if (param != NULL) {
		float value = param->cast_to_float_mav(vtype);
		mavlink_msg_param_value_pack(	systemId,
																	MAV_COMP_ID_ALL,
																	msg,
																	packet.param_id,
																	value,
																	vtype,
																	param_count,
																	packet.param_index);
		uint8_t buf[MAVLINK_MAX_PACKET_LEN];
		uint16_t len = mavlink_msg_to_send_buffer(buf, msg);
		Serial.write(buf, len);
	}
}

void GCS_Mavlink::handle_param_set(mavlink_message_t *msg)
{
	Mav_Param *param;
	enum var_type vtype;
	mavlink_param_set_t packet;
	mavlink_msg_param_set_decode(msg, &packet);
	param = Mav_Param::find_by_name(packet.param_id, &vtype);
	if (param != NULL) {
		param->set_value(packet.param_value, &vtype);
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

void GCS_Mavlink::send_hearthbeat( MAV_STATE mav_state_define,
																	 MAV_MODE mav_mode_define,
																	 MAV_MODE_FLAG mav_mode_flag_define)
{

	mav_state = mav_state_define;
	mav_mode = mav_mode_define;
	mav_mode_flag = mav_mode_flag_define;

	mavlink_message_t msg;
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];			// Pack the message
	mavlink_msg_heartbeat_pack(	systemId,
															0,
															&msg,
															MAV_TYPE_QUADROTOR,
															MAV_AUTOPILOT_GENERIC,
															mav_mode,
															mav_mode_flag,
															mav_state);

	// Copy the message to the send buffer
	uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
	Serial.write(buf, len);
	Serial.flush();
}

void GCS_Mavlink::send_hearthbeat()
{
	if ((millis() - lastReceivedHearthbeat) > 3000) {
		GCS_connection = false;
		digitalWrite(13, LOW);
	}

	mavlink_message_t msg;
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];			// Pack the message
	mavlink_msg_heartbeat_pack(	systemId,
															0,
															&msg,
															MAV_TYPE_QUADROTOR,
															MAV_AUTOPILOT_GENERIC,
															mav_mode,
															MAV_MODE_FLAG_SAFETY_ARMED,
															mav_state);

	// Copy the message to the send buffer
	uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
	Serial.write(buf, len);
	Serial.flush();
}

//void GCS_Mavlink::send_hearthbeat_1HZ(enum MAV_STATE mav_state_defined,
//																			enum MAV_MODE mav_mode_defined)
//{
//	if ((millis() - lastTimesendHeathbeat) > sendHearthbeat1HZ) {
//		mavlink_message_t msg;
//		uint8_t buf[MAVLINK_MAX_PACKET_LEN];			// Pack the message
//		mavlink_msg_heartbeat_pack(	systemId,
//																0,
//																&msg,
//																MAV_TYPE_QUADROTOR,
//																MAV_AUTOPILOT_GENERIC,
//																mav_mode_defined,
//																MAV_MODE_FLAG_SAFETY_ARMED,
//																mav_state_defined);
//
//		// Copy the message to the send buffer
//		uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
//		Serial.write(buf, len);
//		Serial.flush();
//		lastTimesendHeathbeat = millis();
//	}
//}
//
//void GCS_Mavlink::send_hearthbeat_1HZ()
//{
//	if ((millis() - lastReceivedHearthbeat) > 3000) {
//		GCS_connection = false;
//		digitalWrite(13, LOW);
//	}
//
//	if ((millis() - lastTimesendHeathbeat) > sendHearthbeat1HZ) {
//		mavlink_message_t msg;
//		uint8_t buf[MAVLINK_MAX_PACKET_LEN];			// Pack the message
//		mavlink_msg_heartbeat_pack(	systemId,
//																0,
//																&msg,
//																MAV_TYPE_QUADROTOR,
//																MAV_AUTOPILOT_GENERIC,
//																mav_mode,
//																MAV_MODE_FLAG_SAFETY_ARMED,
//																mav_state);
//
//		// Copy the message to the send buffer
//		uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
//		Serial.write(buf, len);
//		Serial.flush();
//		lastTimesendHeathbeat = millis();
//	}
//}

void GCS_Mavlink::handle_manual_control(mavlink_message_t *msg)
{
	if (mav_mode == MAV_MODE_MANUAL_ARMED) {
		mavlink_manual_control_t manual_control_t;
		mavlink_msg_manual_control_decode(msg, &manual_control_t);
		if (manual_control_t.target == systemId) {
			Mav_Param::set_value_by_name(	"manual_rcX",
																		map(manual_control_t.x,
																				-710,
																				690,
																				-90,
																				90));
			Mav_Param::set_value_by_name(	"manual_rcY",
																		map(manual_control_t.y,
																				-660,
																				714,
																				-90,
																				90));
			Mav_Param::set_value_by_name(	"manual_rcZ",
																		map(manual_control_t.z,
																				-680,
																				690,
																				1050,
																				1800));
			Mav_Param::set_value_by_name(	"manual_rcR",
																		map(manual_control_t.r,
																				-730,
																				660,
																				-180,
																				180));

//			param_container.manual_rcX = map(manual_control_t.x, -710, 690, -90, 90);
//			param_container.manual_rcY = map(manual_control_t.y, -660, 714, -90, 90);
//			param_container.manual_rcZ = map(	manual_control_t.z,
//																				-680,
//																				690,
//																				1050,
//																				1800);
//			param_container.manual_rcR = map(	manual_control_t.r,
//																				-730,
//																				660,
//																				-180,
//																				180);
//
//		Serial.print(param_container.manual_rcX);		Serial.print(",");
//		Serial.print(param_container.manual_rcY);		Serial.print(",");
//		Serial.println(param_container.manual_rcZ);		//Serial.print(",");
//		Serial.println(param_container.manual_rcR);

		}
	} else {
		Mav_Param::set_value_by_name("manual_rcX", 0);
		Mav_Param::set_value_by_name("manual_rcY", 0);
		Mav_Param::set_value_by_name("manual_rcZ", 0);
		Mav_Param::set_value_by_name("manual_rcR", 0);
	}

}

void GCS_Mavlink::send_attitude(mavlink_attitude_t &attitude)
{
//	if ((millis() - lastTimesendAttitude) > sendAttitudebeat10HZ) {
	mavlink_message_t msg;
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];

	mavlink_msg_attitude_encode(systemId,MAV_COMP_ID_ALL,&msg, &attitude);
	uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
	Serial.write(buf, len);
	Serial.flush();

//		lastTimesendAttitude = millis();
//	}
}

inline enum MAV_MODE GCS_Mavlink::getMavMode() const
{
	return mav_mode;
}

inline void GCS_Mavlink::setMavMode(enum MAV_MODE mavMode)
{
	mav_mode = mavMode;
}

inline enum MAV_MODE_FLAG GCS_Mavlink::getMavModeFlag() const
{
	return mav_mode_flag;
}

inline void GCS_Mavlink::setMavModeFlag(enum MAV_MODE_FLAG mavModeFlag)
{
	mav_mode_flag = mavModeFlag;
}

inline enum MAV_STATE GCS_Mavlink::getMavState() const
{
	return mav_state;
}

inline void GCS_Mavlink::setMavState(enum MAV_STATE mavState)
{
	mav_state = mavState;
}

inline bool GCS_Mavlink::isGcsConnection() const
{
	return GCS_connection;
}

inline void GCS_Mavlink::setGcsConnection(bool gcsConnection)
{
	GCS_connection = gcsConnection;
}

#endif /* GCS_MAVLINK_HPP_ */
