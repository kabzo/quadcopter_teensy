#include "CopterTeensy.h"

#include "AttitudeControl.hpp"
#include "Radio.hpp"
#include "GCS.hpp"

void debug()
{
	GCS.debugParameter("pitch_pidOutput");
//	GCS.debugParameter("manual_rcZ");
}

Thread::Task Thread::_tasks[] = {
THREADTASK(sendToGCS_1HZ,1000,true),
		THREADTASK(sendToGCS_40HZ,300,true),
		THREADTASK(updateRadio,100,true),
//	THREADTASK(debug,300,true),

		THREADEND
		};

uint8_t Thread::_num_tasks = Thread::countTasks();

void initCopter()
{

	Serial.begin(115200); /*start communication*/

	GCS.waitGCSconnect();

	ledLeft.negateState();

//	motorsInit();
	initRadio();

	initializeImu();
	imu.startDMP();
	ledMiddle.negateState();


}

/******************************************
 ****************SETUP*********************
 ******************************************/

void setup()
{

	initCopter();

}
uint32_t time = 0;

/******************************************
 ****************LOOP**********************
 ******************************************/
void loop()
{
	imu.update(	param_container.vectorGyro,
							param_container.vectorAcc,
							param_container.vectorMag,
							param_container.vectorYpr);

	pidCompute();

//	setMotorsSpeed();

	Thread::run(micros());

	GCS.mavlink_receive();

	ledStart();
}

