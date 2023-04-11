#include "gate.h"
#include "wire.h"

void Gate::setType(string type) {
	this->type = type;
}

void Gate::setDelay(int delay) {
	this->delay = delay;
}

//TODO: make setInput take in multiple parameters
void Gate::setInput(Wire* input) {
	inputs.push_back(input);
}

//TODO: make Wire class complete (causing issues)
bool Gate::evaluate()const {
	//and gate
	if (type == "AND") {
		for (int i = 0; i < inputs.size(); i++) {
			if (!inputs[i]->getState()) {
				return false;
			}
		}
		return true;
	}
	//not gate
	if (type == "NOT") {
		if (inputs[0]->getState() == '1') {
			output->setState('0');
		}
		else if (inputs[0]->getState() == '0') {
			output->setState('1');
		}
		else {
			output->setState('X');
		}
	}
	//or gate
	if (type == "OR") {
		bool output_state = false;
		for (int i = 0; i < inputs.size(); i++) {
			if (inputs[i]->getState() == '1') {
				output_state = true;
				break;
			}
			else if (inputs[i]->getState() == 'X') {
				output_state = true;
			}
		}
		if (output_state) {
			output->setState('1');
		}
		else {
			output->setState('0');
		}
	}

}