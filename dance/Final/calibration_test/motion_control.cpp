#include "motion_control.h"
#include <Arduino.h>
#include "stepper.h"
#include "esp_timer.h"

Motion_control::Motion_control(Stepper* StepperX, Stepper* StepperY, Stepper* StepperT)
{
	_StepperX = StepperX;
	_StepperY = StepperY;
	_StepperT = StepperT;
	_in_calibration = false;
}

void Motion_control::goto_target(float x, float y, float z)
{

}

void Motion_control::calibrate()
{
	while(true)
	{
		_StepperX->setVelocity(0.000);
		delay(500);
		_StepperX->setVelocity(0.000);
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
	_StepperX->resetCommandTimeout();
	_StepperY->resetCommandTimeout();
	_StepperT->resetCommandTimeout();
}	

void Motion_control::init()
{
	_StepperX->init();
	_StepperY->init();
	_StepperT->init();
}