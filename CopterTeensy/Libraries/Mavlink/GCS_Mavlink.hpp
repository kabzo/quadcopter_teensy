/*
 * GSC_Mavlink.hpp
 *
 *  Created on: 2.11.2014
 *      Author: Juraj
 */

#ifndef GCS_MAVLINK_HPP_
#define GCS_MAVLINK_HPP_

#include <Mav_Param.hpp>

template<class T>
class GCS_Mavlink
{
public:
	GCS_Mavlink(T& serTarget) :
					_serial(serTarget),
					_GCS_connection(false),
					_next_param(NULL),
					_next_id(0),
					_param_count(Mav_Param::_num_vars_all),
					_systemId(100),
					_quedParam(0),
					_lastReceivedHearthbeat(0),
					_mav_state(MAV_STATE_BOOT),
					_mav_mode(MAV_MODE_PREFLIGHT)

	{

//		_serial = serTarget;
		_mav_mode_flag = MAV_MODE_FLAG_MANUAL_INPUT_ENABLED;
		_mav_mode_flag |= MAV_MODE_FLAG_STABILIZE_ENABLED;
		_mav_mode_flag |= MAV_MODE_FLAG_CUSTOM_MODE_ENABLED;
	}

	void init(const Mav_Param::Info *info);

	void handle_request_param_list();
	void handle_param_request_read(mavlink_message_t *msg);
	void handle_param_set(mavlink_message_t *msg);
	void handle_manual_control(mavlink_message_t *msg);
	void handle_set_mode(mavlink_message_t *msg);
	void handle_mission_request_list(mavlink_message_t *msg);
	void handle_mission_count(mavlink_message_t *msg);
	void handle_request_data_stream(mavlink_message_t *msg);
	void handle_command_long(mavlink_message_t *msg);

	void send_param_list_next();
	void send_hearthbeat(	MAV_STATE mav_state_define,
												MAV_MODE mav_mode_define,
												uint8_t mav_mode_flag_define);
	bool send_hearthbeat();
	void send_attitude(mavlink_attitude_t &attitude);
	void send_scaled_imu(mavlink_scaled_imu_t &scaled_imu);
	void send_rc_channels_raw(mavlink_rc_channels_raw_t &rc_channels_raw);
	void send_rc_channels_scaled(mavlink_rc_channels_scaled_t &rc_channels_scaled);

	void mavlink_receive();
	void wait_gcs_connect();

	void set_mav_mode(enum MAV_MODE mavMode);
	void set_mav_mode_flag(uint8_t mavModeFlag);
	void delete_mav_mode_flag(uint8_t mavModeFlag);

	void disarm_mav_mode();
	void arm_mav_mode();

	void change_arm_GCS(bool arm);

	void debug_parameter(const char* str);
	void debug_parameter(float val, uint8_t id);

	MAV_STATE get_mav_state();
	MAV_MODE get_mav_mode();

	void set_mav_state(enum MAV_STATE mavState);
	bool is_gcs_connected();
	void set_gcs_connection(bool gcsConnection);

	uint8_t get_system_id();
	void set_system_id(uint8_t systemId);

	T& _serial;
private:

	bool _GCS_connection;
	Mav_Param * _next_param;
	uint8_t _next_id;
	uint8_t _param_count;
	uint8_t _systemId;
	uint16_t _quedParam;

	uint32_t _lastReceivedHearthbeat;

	enum MAV_STATE _mav_state;
	enum MAV_MODE _mav_mode;
	uint8_t _mav_mode_flag;
};

typedef usb_serial_class usb;
typedef HardwareSerial bluetooth;

typedef GCS_Mavlink<usb> GCS_USB;
typedef GCS_Mavlink<bluetooth> GCS_BLUETOOTH;

#endif /* GCS_MAVLINK_HPP_ */
