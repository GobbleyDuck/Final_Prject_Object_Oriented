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
bool Gate::evaluate() const {
    // and gate
    if (type == "AND") {
        for (int i = 0; i < static_cast<int>(inputs.size()); i++) {
            if (!inputs[i]->getState()) {
                return false;
            }
        }
        return true;
    }

    // not gate
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

    // or gate
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
        return output_state;
    }

    // xor gate
    if (type == "XOR") {
        bool output_state = false;
        // true if outputs diff and false if same
        if (inputs[0]->getState() != inputs[1]->getState()) {
            output_state = true;
            output->setState('1');
        }
        else {
            output->setState('0');
        }
        return output_state;
    }

    // nand gate
    if (type == "NAND") {
        bool output_state = false;
        // true if both inputs are a 1, and false otherwise
        if (inputs[0]->getState() == '1' && inputs[1]->getState() == '1') {
            output->setState('0');
            output_state = true;
        }
        else {
            output->setState('1');
        }
        return output_state;
    }

    // xnor gate
    if (type == "XNOR") {
        bool output_state = false;
        // true if both outputs are the same and false if diff
        if (inputs[0]->getState() == inputs[1]->getState()) {
            output_state = true;
            output->setState('1');
        }
        else {
            output->setState('0');
        }
        return output_state;
    }

    return false;
}