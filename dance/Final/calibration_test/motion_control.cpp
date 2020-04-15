#include "motion_control.h"
#include <Arduino.h>
#include "stepper.h"
#include "esp_timer.h"
#include "robot.h"

Motion_control::Motion_control(robot* beedancer)
{
	_beedancer = beedancer;
	_in_calibration = false;
}

void Motion_control::goto_target(float x, float y, float z)
{

}

void Motion_control::calibrate()
{
	while(true)
	{
		_beedancer->StepperX->setVelocity(0.000);
		delay(500);
		_beedancer->StepperX->setVelocity(0.000);
		delay(500);
	}
}

bool Motion_control::is_calibrate()
{

}

bool Motion_control::is_calibrating()
{

}

void Motion_control::_controller()
{

}

void Motion_control::resetTimeout()
{
	_beedancer->StepperX->resetCommandTimeout();
	_beedancer->StepperY->resetCommandTimeout();
	_beedancer->StepperT->resetCommandTimeout();
}	

void Motion_control::init()
{
	_beedancer->StepperX->init();
	_beedancer->StepperY->init();
	_beedancer->StepperT->init();
}