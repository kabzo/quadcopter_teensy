#include "CopterTeensy.h"

#include "Sensors.hpp"
#include "Radio.hpp"
#include "GCS.hpp"
#include "Stabilize.hpp"

void debug()
{

//	GCS.debug_parameter(attitudeControl.get_rate_pid().ROLL->get_d_term(), 0);



//	GCS.debug_parameter(attitudeControl.get_rate_pid().YAW->get_error() / 100, 0);

//	GCS.debug_parameter(attitudeControl.get_rate_output().ROLL / 10, 1);
//	GCS.debug_parameter(attitudeControl.get_rate_output().PITCH / 10, 2);
//	GCS.debug_parameter(attitudeControl.get_rate_output().YAW / 10, 3);
//
//	GCS.debug_parameter(attitudeControl.get_stab_output().ROLL / 10, 4);
//	GCS.debug_parameter(attitudeControl.get_stab_output().PITCH / 10, 5);
	GCS.debug_parameter(attitudeControl.get_stab_output().YAW, 6);



//	GCS.debug_parameter(attitudeControl.get_actual_angles().ROLL / 100, 7);
//	GCS.debug_parameter(attitudeControl.get_actual_angles().PITCH / 100, 8);
//	GCS.debug_parameter(attitudeControl.get_actual_angles().YAW / 100, 9);

//	GCS.debug_parameter(attitudeControl.get_target_angles().ROLL / 100, 10);
//	GCS.debug_parameter(attitudeControl.get_target_angles().PITCH / 100, 11);
//	GCS.debug_parameter(attitudeControl.get_target_angles().YAW / 100, 12);

//	GCS.debug_parameter(attitudeControl.get_actual_rates().z / 100, 13);
//	GCS.debug_parameter(attitudeControl.get_actual_rates().y / 100, 14);
//	GCS.debug_parameter(attitudeControl.get_actual_rates().x / 100, 15);

//	GCS.debug_parameter(imu.calAccel.x, 16);
//	GCS.debug_parameter(imu.calAccel.y, 17);
//	GCS.debug_parameter(imu.calAccel.z, 18);

}

Thread::Task tasks[] = {
THREADTASK(stabilize,AttitudeControl::_pid_frequency,true),
THREADTASK(sendToGCS_1HZ,1000,true),
THREADTASK(sendToGCS_40HZ,200,true),
THREADTASK(update_radio,100,true),
THREADTASK(debug,100,true),
THREADEND
};


/******************************************
 ***************SETUP*********************
 ******************************************/
void setup()
{

	Serial.begin(115200);

	GCS.init(var_info);

	Thread::load_tasks(tasks);

//	GCS.wait_gcs_connect();

	init_radio();

	init_imu();

	motorsQuad.init();

	leds.negate_state(R);

}

uint32_t last;
/******************************************
 ****************LOOP**********************
 ******************************************/
void loop() // takes around 112 us
{
	uint32_t now = micros();

	if(imu.read_raw() == 0){
//				Serial.println((now - last)/1000);
//				last = now;
	}

//	if (imu.read_dmp() == SUCCESFULL)
//	{
////		Serial.println((now - last)/1000);
////		last = now;
//	}

	Thread::run(now);

	leds.actualize_leds();

	GCS.mavlink_receive();

}

