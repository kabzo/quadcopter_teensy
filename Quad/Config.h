#ifndef CONFIG_H_
#define CONFIG_H_
#define TRUE 1
#define FALSE 0

//***********************PID***********************//
#define MAX_PID 50
#define MIN_PID -MAX_PID
#define PIDTIME 10
//***********************PID***********************//


#define TIMESENDDATA 20

//***********************MotorESC.h***********************//
#define MAX_SIGNAL 2000
#define MIN_SIGNAL 1000
#define MPINBL 5
#define MPINBR 4
#define MPINFR 6
#define MPINFL 7

#define THROTTLE_MIN 1000
#define CALIBRATEESC 0	//0 = initialize, 1 = calibrate, 2 = reset
//***********************MotorESC.h***********************//













#endif /* CONFIG_H_ */
