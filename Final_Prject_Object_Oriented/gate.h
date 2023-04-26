#pragma once
#include "wire.h"
#include "event.h"
#include <string>
#include <vector>

using namespace std;

class Wire;

class Gate {
public:
	//constructors
	Gate(string type, int delay, Wire* input1, Wire* input2, Wire* output);
	
	Gate(string type, int delay, Wire* input1, Wire* output); 

	//getters
	int getDelay()const {return delay;}

	Wire* getInput(int input)const {return inputs[input];}

	Wire* getOutput()const {return output;}

	//function prototypes
	void setType(string type);
	void setDelay(int delay);
	void setInput(Wire* input);
	char evaluate()const;

	//TODO: returnVal evaluate(parms)

private:
	string type;
	int delay;
	Wire* output;
	vector<Wire*> inputs;
};
