#include "gate.h"

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

//TODO: make it return something
void Gate::evaluate()const {

}