#include "stepper.h"
#include <Arduino.h>
#include <Tic.h>

Stepper::Stepper(int addr) : TicI2C(addr)
{
	_addr = addr;
	_position = 0.;	// Actual Position of the stepper in um
	_position_step = 0;	// Actual Position of the stepper in steps
	
}

void Stepper::init()
{
	exitSafeStart();
	setTargetVelocity(0);
	delay(10);
	_micro_step = getMicro_step();
}

int Stepper::m2step(float m)
{
	return (int)(m / _step_m_ratio * _micro_step);
}

float Stepper::step2m(int steps)
{
	return steps / _micro_step * _step_m_ratio;
}

float Stepper::getPos()
{
	_position_step = getCurrentPosition();
	_position = step2m(_position_step);
	return _position;
}

int Stepper::getPos_step()
{
	_position_step = getCurrentPosition();
	_position = step2m(_position_step);
	return _position_step;
}

int Stepper::getMicro_step()
{
	switch(getStepMode())
	{
		case TicStepMode::Microstep1:   return 1;
		case TicStepMode::Microstep2:   return 2;
		case TicStepMode::Microstep4:   return 4;
		case TicStepMode::Microstep8:   return 8;
		case TicStepMode::Microstep16:   return 16;
		case TicStepMode::Microstep32:   return 32;
		default : return -1;
	}
}

void Stepper::setVelocity(float target)
{
	// target in m.s-1
	int Vstep = (int)(target/(_step_m_ratio*(1./_micro_step))*10000); //Vs = Vt/(Ls.Us)*step10000
	// Vs = Step speed
	// Vt = target speed
	// Ls = Length of step
	// Us = micro_step (1/16;1/32)
	// TIC : speed measure in step per 10000s
	setTargetVelocity(Vstep);
}

void Stepper::setPosition(float target, bool blocking)
{
	// target in m.s-1
	setTargetPosition(m2step(target));
	if(blocking)
	{
		while(getCurrentPosition() != m2step(target)){vTaskDelay(10);}
	}
}
