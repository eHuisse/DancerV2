#include "stepper.h"
#include "motion_control.h"
#include <Tic.h>
#include "calibration.h"

void calibrationXY(Stepper* StepperX, Stepper* StepperY, DebouncedInput* xSwitch, DebouncedInput* ySwitch)
{
	findOrigine(StepperX, xSwitch, true);
	StepperX->setPosition(0.002);
	delay(1000);
	findOrigine(StepperY, ySwitch, true);
	StepperY->setPosition(0.002);
	delay(1000);
	findOrigine(StepperX, xSwitch, true);
	StepperX->setPosition(0.002);
	delay(1000);
	StepperY->setPosition(0.0615 - 0.0343);
	StepperX->setPosition(0.075 - 0.0442);

}

float findOrigine(Stepper* Stepper, DebouncedInput* switchPin, bool setWhenFound)
{
	delay(200);
	const int repeat = 3;
	float switchPlus[3] = {0.,0.,0.};
	float switchMinus[3] = {0.,0.,0.};
	float switchAverage[3] = {0.,0.,0.};
	float current_position = 0.;
	float average_origine = 0.;

	//Find first the border
	Stepper->setVelocity(-0.005);

	//While we don't find it
	while(!switchPin->falling()){switchPin->read();}

	Stepper->haltAndHold();
	delay(100);

	//We do it repeat time for averging
	for(int i = 0 ; i < repeat ; i++)
	{
		Stepper->setVelocity(0.001);
		while(!switchPin->rising()){switchPin->read();}
		Stepper->haltAndHold();
		delay(200);

		switchPlus[i] = Stepper->getPos();

		Stepper->setVelocity(-0.001);
		while(!switchPin->falling()){switchPin->read();}
		Stepper->haltAndHold();
		delay(200);

		switchMinus[i] = Stepper->getPos();
	}

	//Computing an average
	for(int i = 0 ; i < repeat ; i++)
	{
		switchAverage[i] = (switchPlus[i] + switchMinus[i]) / 2.;
	}
	for(int i = 0 ; i < repeat ; i++)
	{
		average_origine += switchAverage[i];
	}

	average_origine = average_origine / (float)repeat;
	current_position = Stepper->getPos();
	Stepper->setPosition(average_origine);
	delay(1000);
	if(setWhenFound)
	{
		Stepper->haltAndSetPosition(0);
	}
	return current_position;
}