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

#ifdef TEENSY
#include <Led.hpp>
#endif

class GCS_Mavlink
{
public:
	GCS_Mavlink() :
					GCS_connection(false),
					next_param(NULL),
					next_id(0),
					param_count(Mav_Param::_num_vars_all),
					systemId(100),
					lastReceivedHearthbeat(0),
					mav_state(MAV_STATE_BOOT),
					mav_mode(MAV_MODE_PREFLIGHT)
	{

		mav_mode_flag = MAV_MODE_FLAG_MANUAL_INPUT_ENABLED;
		mav_mode_flag |= MAV_MODE_FLAG_STABILIZE_ENABLED;
		mav_mode_flag |= MAV_MODE_FLAG_CUSTOM_MODE_ENABLED;

	}

	void handle_request_param_list();
	void handle_param_request_read(mavlink_message_t *msg);
	void handle_param_set(mavlink_message_t *msg);
	void handle_manual_control(mavlink_message_t *msg);
	void handle_set_mode(mavlink_message_t *msg);

	void send_param_list_next();
	void send_hearthbeat(MAV_STATE mav_state_define, MAV_MODE mav_mode_define, uint8_t mav_mode_flag_define);
	bool send_hearthbeat();
	void send_attitude(mavlink_attitude_t &attitude);
	void send_scaled_imu(mavlink_scaled_imu_t &scaled_imu);
	void send_rc_channels_raw(mavlink_rc_channels_raw_t &rc_channels_raw);
	void send_rc_channels_scaled(mavlink_rc_channels_scaled_t &rc_channels_scaled);

	void mavlink_receive();
	void waitGCSconnect();

	enum MAV_MODE getMavMode() const;
	void setMavMode(enum MAV_MODE mavMode);
	void setMavModeFlag(uint8_t mavModeFlag);
	void deleteMavModeFlag(uint8_t mavModeFlag);

	enum MAV_STATE getMavState() const;
	void setMavState(enum MAV_STATE mavState);
	bool isGcsConnection() const;
	void setGcsConnection(bool gcsConnection);
	uint8_t getSystemId() const;
	void setSystemId(uint8_t systemId);
	void disarmMavMode();
	void armMavMode();

	void changeArmGCS(bool arm);

	void debugParameter(const char* str);
	void debugParameter(float val,uint8_t id);


private:
	bool GCS_connection;
	Mav_Param * next_param;
	uint8_t next_id;
	uint8_t param_count;
	uint8_t systemId;

	uint32_t lastReceivedHearthbeat;

	enum MAV_STATE mav_state;
	enum MAV_MODE mav_mode;
	uint8_t mav_mode_flag;

};



inline bool GCS_Mavlink::isGcsConnection() const
{
	return GCS_connection;
}

inline enum MAV_MODE GCS_Mavlink::getMavMode() const
{
	return mav_mode;
}

#endif /* GCS_MAVLINK_HPP_ */
