#include <Arduino.h>
#include "state_machine.h"
#include "robot.h"

State_Machine::State_Machine(robot* beedancer)
{
	_beedancer = beedancer
}

void State_Machine::handle_message(String *input)
{
}