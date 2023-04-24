#pragma once
#include "wire.h"
#include <string>
#include <vector>

using namespace std;

class Wire;

class Gate {
public:
	//constructors
	Gate(string type, int delay, Wire* input1, Wire* input2, Wire* output) {
		this->type = type;
		this->delay = delay;
		this->output = output;
		setInput(input1);
		setInput(input2);
	};
	
	Gate(string type, int delay, Wire* input1, Wire* output) {
		this->type = type;
		this->delay = delay;
		this->output = output;
		setInput(input1);
	};

	//getters
	int getDelay()const {return delay;}

	Wire* getInput(int input)const {return inputs[input];}

	Wire* getOutput()const {return output;}

	//function prototypes
	void setType(string type);
	void setDelay(int delay);
	void setInput(Wire* input);
	bool evaluate()const;

	//TODO: returnVal evaluate(parms)

private:
	string type;
	int delay;
	Wire* output;
	vector<Wire*> inputs;
};
