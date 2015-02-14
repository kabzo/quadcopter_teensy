#include "CopterTeensy.h"

#include "Sensors.hpp"
#include "AttitudeControl.hpp"
#include "Radio.hpp"
#include "GCS.hpp"

void debug()
{

//	GCS.debugParameter("pitch_stab_pT");
//	GCS.debugParameter("pitch_stab_iT");
//	GCS.debugParameter("pitch_stab_dT");

//	GCS.debugParameter(con.roll_pidOutput._value,0);
//	GCS.debugParameter(con.pitch_pidOutput._value,1);
//	GCS.debugParameter(con.yaw_pidOutput._value,2);

//	GCS.debugParameter("roll_pidOutput");
	GCS.debugParameter("pitch_pidOutput");
//	GCS.debugParameter("yaw_pidOutput");

//	GCS.debugParameter("pitch_pidOutput");
}

Thread::Task Thread::_tasks[] = {
THREADTASK(pidCompute,PID::_deltaTime._value,true),
THREADTASK(sendToGCS_1HZ,1000,true),
THREADTASK(sendToGCS_40HZ,100,true),
THREADTASK(updateRadio,100,true),
THREADTASK(debug,100,true),
THREADTASK(ledStart,500,true),
THREADEND };

uint8_t Thread::_num_tasks = Thread::countTasks();

/******************************************
 ****************SETUP*********************
 ******************************************/

void setup()
{
	Serial.begin(115200); /*start communication*/

//	GCS.waitGCSconnect();
//	ledLeft.negateState();

	motorsQuad.init();

	initRadio();

	initializeImu();

	ledMiddle.negateState();
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

