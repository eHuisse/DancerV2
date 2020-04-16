#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H
#include <Arduino.h>
#include <queue>
#include "robot.h"
#include "calibration.h"

class State_Machine
{
public:
	State_Machine(robot* beedancer);
	void handle_message(String *input);
	void step();
	void connect();
	String getValue(String data, char separator, int index);

private:
	bool _is_synchronized = false;
	bool _is_calibrated = false;
	robot* _beedancer;
	const int _buffer_size = 10;
	const int _instruction_size = 10;
	std::queue<std::vector<float>> instruction_queue;
};

#endif