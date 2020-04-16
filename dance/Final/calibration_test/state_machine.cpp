#include <Arduino.h>
#include <queue>
#include "state_machine.h"
#include "robot.h"
#include "calibration.h"

State_Machine::State_Machine(robot* beedancer)
{
	_beedancer = beedancer;
}

void State_Machine::handle_message(String* input)
{
	String xval = getValue(*input, ':', 0);
	String yval = getValue(*input, ':', 1);

	std::vector<float> instruction_vector (_instruction_size);

	for(int i = 0 ; i < _instruction_size ; i++){
		instruction_vector[i] = getValue(*input, ':', i).toFloat();
	}
	*input = "";

	instruction_queue.push(instruction_vector)
}

void State_Machine::step()
{
	if(!_is_synchronized){
		connect();
	}
}

void State_Machine::connect()
{

}

String State_Machine::getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
