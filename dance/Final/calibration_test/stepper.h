#ifndef STEPPER_H
#define STEPPER_H
#include <Arduino.h>
#include <Tic.h>

class Stepper: public TicI2C
{
public:
	Stepper(int addr);
	int m2step(float m);
	float step2m(int steps);
	float getPos();
	int getPos_step();
	int getMicro_step();
	void setVelocity(float target);
	void setPosition(float target);
	void init();

private:
	float _position;
	int _position_step;
	const float _step_m_ratio = 0.00001; //One step = 10um
	int _addr;
	int _micro_step;
};

#endif