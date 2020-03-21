#ifndef STEPPER_H
#define STEPPER_H
#include <Arduino.h>
#include <Tic.h>

class Stepper: public TicI2C
{
public:
	Stepper(int addr);
	int um2step(int um);
	int step2um(int steps);
	int getPos_um();
	int getPos_step();
	int getMicro_step();
	void setVelocity(float target);
	void init();

private:
	int _position_um;
	int _position_step;
	const float _step_um_ratio = 0.00001; //One step = 10um
	int _addr;
	int _micro_step;
};

#endif