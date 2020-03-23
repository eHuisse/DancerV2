#ifndef CALIBRATION_H
#define CALIBRATION_H
#include <Arduino.h>
#include <Tic.h>
#include <DebounceInput.h>

void calibrationXY(Stepper* StepperX, Stepper* StepperY, DebouncedInput* xSwitch, DebouncedInput* ySwitch);

float findOrigine(Stepper* Stepper, DebouncedInput* switchPin, bool setWhenFound = false);

#endif