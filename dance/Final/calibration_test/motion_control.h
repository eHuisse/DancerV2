#ifndef MOTION_CONTROL_H
#define MOTION_CONTROL_H
#include <Arduino.h>
#include "stepper.h"
#include "robot.h"

class Motion_control
{
public:
	Motion_control(robot* beedancer);
	void goto_target(float x, float y, float z);
	void calibrate();
	bool is_calibrate();
	bool is_calibrating();
	void resetTimeout();
	void init();

private:
	robot* _beedancer;
  	void _controller();
  	bool _in_calibration;
};
#endif
