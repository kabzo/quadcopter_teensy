/*
 * GSC_Mavlink.hpp
 *
 *  Created on: 2.11.2014
 *      Author: Juraj
 */

#ifndef GCS_MAVLINK_HPP_
#define GCS_MAVLINK_HPP_

#include "Parameters_Init.hpp"

class GCS_Mavlink {
	public:
		GCS_Mavlink()
				: next_param(NULL), next_id(0), param_count(Mav_Param::cout_vars()), systemId(100) {
		}

		void send_param_list_next() {
			var_type vtype;
			float value = Mav_Param::get_param_id_value(next_id, &vtype);
			mavlink_message_t msg;
			uint8_t buf[MAVLINK_MAX_PACKET_LEN];
			const char *name;
			name = Mav_Param::get_param_name_id(next_id);
			next_id++;
			mavlink_msg_param_value_pack(systemId, MAV_COMP_ID_ALL, &msg, name, value, vtype, param_count, next_id);
			uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
			Serial.write(buf, len);

		}

		void send_param_list() {
			for (uint8_t i = 0; i < param_count; i++) {
				send_param_list_next();
				delay(100);
			}
		}

		void handle_param_request_read(mavlink_message_t *msg) {
			mavlink_param_request_read_t packet;
			mavlink_msg_param_request_read_decode(msg, &packet);
			enum var_type vtype;
			Mav_Param * param;
			param = Mav_Param::find_by_name(packet.param_id, &vtype);
			if (param != NULL) {
				float value = param->cast_to_float_mav(vtype);
				mavlink_msg_param_value_pack(systemId, MAV_COMP_ID_ALL, msg, packet.param_id, value, vtype, param_count,
						packet.param_index);
				uint8_t buf[MAVLINK_MAX_PACKET_LEN];
				uint16_t len = mavlink_msg_to_send_buffer(buf, msg);
				Serial.write(buf, len);
			}
		}

		void handle_param_set(mavlink_message_t *msg) {
			Mav_Param *param;
			enum var_type vtype;
			mavlink_param_set_t packet;
			mavlink_msg_param_set_decode(msg, &packet);
			if (param != NULL) {
				param = Mav_Param::find_by_name(packet.param_id, &vtype);
				param->set_value(packet.param_value, &vtype);
				mavlink_msg_param_value_pack(systemId, MAV_COMP_ID_ALL, msg, packet.param_id, param->cast_to_float_mav(vtype),
						vtype, param_count, Mav_Param::get_param_id_name(packet.param_id));
				uint8_t buf[MAVLINK_MAX_PACKET_LEN];
				uint16_t len = mavlink_msg_to_send_buffer(buf, msg);
				Serial.write(buf, len);
			}
		}

		void send_hearthbeat(enum MAV_STATE mav_state, enum MAV_MODE mav_mode) {
			mavlink_message_t msg;
			uint8_t buf[MAVLINK_MAX_PACKET_LEN];			// Pack the message
			mavlink_msg_heartbeat_pack(systemId, 200, &msg, MAV_TYPE_QUADROTOR, MAV_AUTOPILOT_GENERIC,
					mav_mode, MAV_MODE_FLAG_SAFETY_ARMED, mav_state);

			// Copy the message to the send buffer
			uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
			Serial.write(buf, len);
		}

		Mav_Param * next_param;
		uint8_t next_id;
		uint8_t param_count;
		uint8_t systemId;
};

//uint8_t GCS_Mavlink::param_count = Mav_Param::cout_vars();
//uint8_t GCS_Mavlink::next_id = 0;

#endif /* GCS_MAVLINK_HPP_ */
