#ifndef CONFIG_H_
#define CONFIG_H_
#define TRUE 1
#define FALSE 0
//***********************BOARD***********************//
#define ARDUINODUE
//#define ARDUINONANO
//***********************BOARD***********************//


//***********************PID***********************//
#define MAX_PID 50
#define MIN_PID -MAX_PID
#define PIDTIME 20
//***********************PID***********************//


#define TIMESENDDATA 40

//***********************MotorESC.h***********************//
#define MAX_SIGNAL 2000
#define MIN_SIGNAL 1000
#define MPINBL 5
#define MPINBR 4
#define MPINFR 6
#define MPINFL 7

#define THROTTLE_MIN 1000
#define CALIBRATEESC FALSE

//***********************MotorESC.h***********************//













#endif /* CONFIG_H_ */
