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
			return false;
		}
		else if (inputs[0]->getState() == '0') {
			output->setState('1');
			return true;
		}
		else {
			output->setState('X');
			return false;
		}

	}
	//or gate
	if (type == "OR") {
		for (int i = 0; i < inputs.size(); i++) {
			if (inputs[i]->getState() == '1') {
				output->setState('1');
				return true;
			}
			else if (inputs[i]->getState() == 'X') {
				output->setState('1');
				return true;
			}
			else {
				output->setState('0');
				return false;
			}
		}
		
	}

	//xor gate
	if (type == "XOR") {

		//true if outputs diff and false if same
		if (inputs[0]->getState() != inputs[1]->getState()) {
			output->setState('1');
			return true;
		}
		else {
			output->setState('0');
			return false;
		}


	}

	//nand gate
	if (type == "NAND") {
		// false if both inputs are a 1, and true otherwise
		if (inputs[0]->getState() == 0 || inputs[1]->getState() == 0) {
			output->setState('0');
			return false;
		}
		else {
			output->setState('1');
			return true;
		}
	}

	//xnor gate

	if (type == "XNOR") {

		//true if both outputs are the same and false if diff
		if (inputs[0]->getState() == inputs[1]->getState()) {
			output->setState('1');
			return true;
		}
		else {
			output->setState('0');
			return false;
		}

	}

}