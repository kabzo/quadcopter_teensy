#include "CopterTeensy.h"

#include "Sensors.hpp"
#include "Radio.hpp"
#include "GCS.hpp"
#include "Stabilize.hpp"

void debug()
{

	GCS.debug_parameter(attitudeControl.get_rate_output().ROLL,1);
	GCS.debug_parameter(attitudeControl.get_rate_output().PITCH,2);
	GCS.debug_parameter(attitudeControl.get_rate_output().YAW*0.1,3);

	GCS.debug_parameter(attitudeControl.get_stab_output().ROLL/100,4);
	GCS.debug_parameter(attitudeControl.get_stab_output().PITCH/100,5);
	GCS.debug_parameter(attitudeControl.get_stab_output().YAW/100,6);

	GCS.debug_parameter(attitudeControl.get_actual_angles().ROLL/100,7);
	GCS.debug_parameter(attitudeControl.get_actual_angles().PITCH/100,8);
	GCS.debug_parameter(attitudeControl.get_actual_angles().YAW/100,9);

	GCS.debug_parameter(attitudeControl.get_target_angles().ROLL/100,10);
	GCS.debug_parameter(attitudeControl.get_target_angles().PITCH/100,11);
	GCS.debug_parameter(attitudeControl.get_target_angles().YAW/100,12);

	GCS.debug_parameter(attitudeControl.get_actual_rates().z/100,13);
	GCS.debug_parameter(attitudeControl.get_actual_rates().y/100,14);
	GCS.debug_parameter(attitudeControl.get_actual_rates().x/100,15);




}

void ledStart()
{
	ledMiddle.startLed();
	ledLeft.startLed();
	ledRight.startLed();
}

Thread::Task Thread::_tasks[] = {
THREADTASK(stabilize,5,true),
THREADTASK(sendToGCS_1HZ,1000,true),
THREADTASK(sendToGCS_40HZ,100,true),
THREADTASK(update_radio,100,true),
THREADTASK(debug,100,true),
THREADTASK(ledStart,500,true),
THREADEND };

uint8_t Thread::_num_tasks = Thread::countTasks();

/******************************************
 ****************SETUP*********************
 ******************************************/

void setup()
{
	GCS.init(var_info);

//	GCS.wait_gcs_connect();

	init_radio();

	init_imu();

	motorsQuad.init();

	ledMiddle.negateState();

//	attitudeControl.get_stab_pid().ROLL->set_active(false);
//	attitudeControl.get_stab_pid().PITCH->set_active(false);
//	attitudeControl.get_stab_pid().YAW->set_active(false);
//
//	attitudeControl.get_rate_pid().ROLL->set_active(false);
//	attitudeControl.get_rate_pid().PITCH->set_active(false);
//	attitudeControl.get_rate_pid().YAW->set_active(false);
}

/******************************************
 ****************LOOP**********************
 ******************************************/
void loop() // takes around 112 us
{
	imu.read();

	Thread::run(micros());

	GCS.mavlink_receive();

}

