#include "CopterTeensy.h"

#include "Sensors.hpp"
#include "Radio.hpp"
#include "GCS.hpp"
#include "Stabilize.hpp"

void debug()
{
	uint8_t i = 1;

	GCS.debug_parameter(attitudeControl.get_rate_output().ROLL,i);
	GCS.debug_parameter(attitudeControl.get_rate_output().PITCH,i);
	GCS.debug_parameter(attitudeControl.get_rate_output().YAW,i);

	GCS.debug_parameter(attitudeControl.get_stab_output().ROLL,i);
	GCS.debug_parameter(attitudeControl.get_stab_output().PITCH,i);
	GCS.debug_parameter(attitudeControl.get_stab_output().YAW,i);

	GCS.debug_parameter(attitudeControl.get_actual_angles().ROLL,i);
	GCS.debug_parameter(attitudeControl.get_actual_angles().PITCH,i);
	GCS.debug_parameter(attitudeControl.get_actual_angles().YAW,i);

	GCS.debug_parameter(attitudeControl.get_actual_rates().z,i);
	GCS.debug_parameter(attitudeControl.get_actual_rates().y,i);
	GCS.debug_parameter(attitudeControl.get_actual_rates().x,i);




}

void ledStart()
{
	ledMiddle.startLed();
	ledLeft.startLed();
	ledRight.startLed();
}

Thread::Task Thread::_tasks[] = {
THREADTASK(stabilize,252,true),
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

	GCS.wait_gcs_connect();

	init_radio();

	init_imu();

	motorsQuad.init();

	ledMiddle.negateState();

	attitudeControl.get_stab_pid().ROLL->set_active(false);
	attitudeControl.get_stab_pid().PITCH->set_active(false);
	attitudeControl.get_stab_pid().YAW->set_active(false);

	attitudeControl.get_rate_pid().PITCH->set_active(false);
	attitudeControl.get_rate_pid().YAW->set_active(false);



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

