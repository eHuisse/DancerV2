#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H
#include <Arduino.h>
#include "robot.h"

class State_Machine
{
public:
	State_Machine(robot* beedancer);
	void handle_message(String *input);

private:
	bool _is_sync = false;
	robot* _beedancer;
};

#endif