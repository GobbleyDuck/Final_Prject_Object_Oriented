#include "gate.h"
#include "wire.h"


Gate::Gate(string type, int delay, Wire* input1, Wire* input2, Wire* output) {
	this->type = type;
	this->delay = delay;
	this->output = output;
	setInput(input1);
	setInput(input2);
}

Gate::Gate(string type, int delay, Wire* input1, Wire* output) {
	this->type = type;
	this->delay = delay;
	this->output = output;
	setInput(input1);
}

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
char Gate::evaluate()const {
	//return event or state (enum or char)
	//and gate 
	//change the and and NAND gate instead of seeing if both Inputs are high, check if either are low because that would trump everything else, 
	//than check if either are undefined (which you have) 
	//then if none of those conditions are true, you know the wire is high
	if (type == "AND") {
		if (inputs[0]->getState() == '0' || inputs[1]->getState() == '0') {
			return '1';
		}
		else if (inputs[0]->getState() == 'X' || inputs[1]->getState() == 'X') {
			return 'X';
		}
		else {
			return '0';
		}
	}
	//not gate
	if (type == "NOT") {
		if (inputs[0]->getState() == '1') {
			return '0';
		}
		else if (inputs[0]->getState() == '0') {
			return '1';
		}
		else {
			return 'X';
		}

	}
	//or gate
	//or gate change the checker which checks if both are low to check if either are undefined because that  would trump the low
	if (type == "OR") {
		if (inputs[0]->getState() == '1' || inputs[1]->getState() == '1') {
			return '1';
		}
		else if (inputs[0]->getState() == 'X' || inputs[1]->getState() == 'X') {
			return '0';
		}
		else {
			return 'X';
		}
		
	}

	//xor gate
	if (type == "XOR") {

		//true if outputs diff and false if same
		if (inputs[0]->getState() != inputs[1]->getState()) {
			return '1';
		}
		else if (inputs[0]->getState() == 'X' || inputs[1]->getState() == 'X') {
			return 'X';
		}
		else {
			return '0';
		}


	}

	//nand gate
	//change the and and NAND gate instead of seeing if both Inputs are high, check if either are low because that would trump everything else, 
	//than check if either are undefined (which you have) 
	//then if none of those conditions are true, you know the wire is high
	if (type == "NAND") {
		if (inputs[0]->getState() == '0' || inputs[1]->getState() == '0') {
			return '0';
		}
		else if (inputs[0]->getState() == 'X' || inputs[1]->getState() == 'X') {
			return 'X';
		}
		else {
			return '1';
		}
	}

	//xnor gate

	if (type == "XNOR") {

		//true if both outputs are the same and false if diff
		if (inputs[0]->getState() == 0 && inputs[1]->getState() == 0) {
			return '1';
		}
		else if (inputs[0]->getState() == 'X' && inputs[1]->getState() == 'X') {
			return 'X';
		}
		else if ((inputs[0]->getState() == 'X' && inputs[1]->getState() != '1') || inputs[0]->getState() == '1' && inputs[1]->getState() != 'X') {
			return 'X';
		}
		else {
			return '0';
		}

	}

	//nor gate
	//In the nor do those exact same checks I said for the or gate 
	//but just invert the outputs, and inverting undefined just returns undefined 

	if (type == "NOR") {
		if (inputs[0]->getState() == '0' && inputs[1]->getState() == '0') {
			return '1';
		}
		else {
			return '0';
		}


	}

	return 'X';
}