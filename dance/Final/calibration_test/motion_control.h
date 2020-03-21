#ifndef MOTION_CONTROL_H
#define MOTION_CONTROL_H
#include <Arduino.h>
#include "stepper.h"

class Motion_control
{
public:
	Motion_control(Stepper* StepperX, Stepper* StepperY, Stepper* StepperT);
	void goto_target(float x, float y, float z);
	void calibrate();
	bool is_calibrate();
	bool is_calibrating();
	void resetTimeout();
private:
  	Stepper* _StepperX;
  	Stepper* _StepperY;
  	Stepper* _StepperT;
  	void _controller();
  	bool _in_calibration;

};
#endif
