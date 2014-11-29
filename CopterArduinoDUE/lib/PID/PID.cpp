#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "PID.h"

/*Constructor (...)*********************************************************
 *    The parameters specified here are those for for which we can't set up 
 *    reliable defaults, so we need to have the user set them.
 ***************************************************************************/
PID::PID(	float* Input,
					float* Output,
					float* Setpoint,
					float* Kp,
					float* Ki,
					float* Kd,
					int ControllerDirection)
		:

			dispKp(Kp),
			dispKi(Ki),
			dispKd(Kd),

			controllerDirection(ControllerDirection),
			ITerm(0),

			oldKp(0),
			oldKi(0),
			oldKd(0)
{

	myOutput = Output;
	myInput = Input;
	mySetpoint = Setpoint;
	inAuto = AUTOMATIC;

	PID::SetOutputLimits(-50, 50);				//default output limit corresponds to
	//the arduino pwm limits

	SampleTime = 10;
	SetTunings(*Kp, *Ki, *Kd);

	PID::SetControllerDirection(ControllerDirection);

	lastTime = millis() - SampleTime;
}

/* Compute() **********************************************************************
 *     This, as they say, is where the magic happens.  this function should be called
 *   every time "void loop()" executes.  the function will decide for itself whether a new
 *   pid Output needs to be computed.  returns true when the output is computed,
 *   false when nothing has been done.
 **********************************************************************************/
bool PID::Compute()
{
	if (!inAuto)
		return false;

	PID::SetTunings(*dispKp, *dispKi, *dispKd);

	unsigned long now = millis();
	unsigned long timeChange = (now - lastTime);
	if (timeChange >= SampleTime) {
		/*Compute all the working error variables*/
		float input = (*myInput) * 180 / M_PI;  //convert to angle
		error = *mySetpoint - input;

		ITerm += (ki * error);

		if (ITerm > outMax)
			ITerm = outMax;
		else if (ITerm < outMin)
			ITerm = outMin;
		dInput = (input - lastInput);

		/*Compute PID Output*/
		float output = kp * error + ITerm - kd * dInput;
		if (output > outMax)
			output = outMax;
		else if (output < outMin)
			output = outMin;
		*myOutput = output;

		/*Remember some variables for next time*/
		lastInput = input;
		lastTime = now;

		return true;
	} else
		return false;
}

void PID::computeDirect()
{
	if (!inAuto)
		return;

	PID::SetTunings(*dispKp, *dispKi, *dispKd);

	/*Compute all the working error variables*/
	float input = (*myInput) * 180 / M_PI;  //convert to angle
	error = *mySetpoint - input;

	ITerm += (ki * error);

	if (ITerm > outMax)
		ITerm = outMax;
	else if (ITerm < outMin)
		ITerm = outMin;
	dInput = (input - lastInput);

	/*Compute PID Output*/
	float output = kp * error + ITerm - kd * dInput;
	if (output > outMax)
		output = outMax;
	else if (output < outMin)
		output = outMin;
	*myOutput = output;

	/*Remember some variables for next time*/
	lastInput = input;
}

/* SetTunings(...)*************************************************************
 * This function allows the controller's dynamic performance to be adjusted. 
 * it's called automatically from the constructor, but tunings can also
 * be adjusted on the fly during normal operation
 ******************************************************************************/
void PID::SetTunings(float Kp, float Ki, float Kd)
{
	if (Kp < 0 || Ki < 0 || Kd < 0)
		return;

	if (Kp == oldKp && Ki == oldKi && Kd == oldKd)
		return;

	oldKp = Kp;
	oldKi = Ki;
	oldKd = Kd;

	double SampleTimeInSec = ((double) SampleTime) / 1000;
	kp = (double) Kp;
	ki = (double) Ki * SampleTimeInSec;
	kd = (double) Kd / SampleTimeInSec;
	if (controllerDirection == REVERSE) {
		kp = (0 - kp);
		ki = (0 - ki);
		kd = (0 - kd);
	}

}

/* SetSampleTime(...) *********************************************************
 * sets the period, in Milliseconds, at which the calculation is performed	
 ******************************************************************************/
void PID::SetSampleTime(int NewSampleTime)
{
	if (NewSampleTime > 0) {
		float ratio = (float) NewSampleTime / (float) SampleTime;
		ki *= ratio;
		kd /= ratio;
		SampleTime = (unsigned long) NewSampleTime;
	}
}

/* SetOutputLimits(...)****************************************************
 *     This function will be used far more often than SetInputLimits.  while
 *  the input to the controller will generally be in the 0-1023 range (which is
 *  the default already,)  the output will be a little different.  maybe they'll
 *  be doing a time window and will need 0-8000 or something.  or maybe they'll
 *  want to clamp it from 0-125.  who knows.  at any rate, that can all be done
 *  here.
 **************************************************************************/
void PID::SetOutputLimits(float Min, float Max)
{
	if (Min >= Max)
		return;
	outMin = Min;
	outMax = Max;

	if (inAuto) {
		if (*myOutput > outMax)
			*myOutput = outMax;
		else if (*myOutput < outMin)
			*myOutput = outMin;

		if (ITerm > outMax)
			ITerm = outMax;
		else if (ITerm < outMin)
			ITerm = outMin;
	}
}

/* SetMode(...)****************************************************************
 * Allows the controller Mode to be set to manual (0) or Automatic (non-zero)
 * when the transition from manual to auto occurs, the controller is
 * automatically initialized
 ******************************************************************************/
void PID::SetMode(int Mode)
{
	bool newAuto = (Mode == AUTOMATIC);
	if (newAuto == !inAuto) { /*we just went from manual to auto*/
		PID::Initialize();
	}
	inAuto = newAuto;
}

/* Initialize()****************************************************************
 *	does all the things that need to happen to ensure a bumpless transfer
 *  from manual to automatic mode.
 ******************************************************************************/
void PID::Initialize()
{
	ITerm = *myOutput;
	lastInput = *myInput * 180 / M_PI;
	if (ITerm > outMax)
		ITerm = outMax;
	else if (ITerm < outMin)
		ITerm = outMin;
}

/* SetControllerDirection(...)*************************************************
 * The PID will either be connected to a DIRECT acting process (+Output leads 
 * to +Input) or a REVERSE acting process(+Output leads to -Input.)  we need to
 * know which one, because otherwise we may increase the output when we should
 * be decreasing.  This is called from the constructor.
 ******************************************************************************/
void PID::SetControllerDirection(int Direction)
{
	if (inAuto && Direction != controllerDirection) {
		kp = (0 - kp);
		ki = (0 - ki);
		kd = (0 - kd);
	}
	controllerDirection = Direction;
}

/* Status Funcions*************************************************************
 * Just because you set the Kp=-1 doesn't mean it actually happened.  these
 * functions query the internal state of the PID.  they're here for display 
 * purposes.  this are the functions the PID Front-end uses for example
 ******************************************************************************/
float PID::GetKp()
{
	return *dispKp;
}
float PID::GetKi()
{
	return *dispKi;
}
float PID::GetKd()
{
	return *dispKd;
}
float PID::GetPterm()
{
	return kp * error;
}
float PID::GetIterm()
{
	return ITerm;
}
float PID::GetDterm()
{
	return -kd * dInput;
}
int PID::GetMode()
{
	return inAuto ? AUTOMATIC : MANUAL;
}
int PID::GetDirection()
{
	return controllerDirection;
}

float PID::getOutMax()
{
	return outMax;
}

float PID::getOutMin() const
{
	return outMin;
}

unsigned long PID::getSampleTime() const
{
	return SampleTime;
}
