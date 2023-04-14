#include "gate.cpp"
#include "wire.cpp"
#include <iostream>
#include <fstream>			//includes both ifstream and ofstream

using namespace std;


int main(){
	string wireName;
	int wireIndex;
	int gateDelay;

	ifstream circDoc;
	circDoc.open("input.txt");

	if (!circDoc.is_open()) {		//return error message if file not opened properly
		cerr << "Error opening file";
		return 1;
	}

	string inputType;

	circDoc >> inputType;

	if (inputType == "CIRCUIT") {
		//what do we do with the first line...?

	}
	

	//for wires - would it be better to just get the entire line, put it into a string, then parse the data from there?
	circDoc >> inputType;
	if (inputType == "INPUT" || inputType == "OUTPUT") {
		circDoc >> inputType >> wireName >> wireIndex;
		Wire(wireName, wireIndex);
	}

	//for gates 
	circDoc >> inputType;
	if (inputType == "AND" || inputType == "NAND" || inputType == "OR" || inputType == "XOR" || inputType == "NOT") {
		circDoc >> inputType >> gateDelay;
		//set gate type to inputType
		//set gate delay to gateDelay
		//take in inputs and put into inputs vector
		//take in last int on line and set to wire* output
	}

	











	circDoc.close();				//need to close document at end
	return 0;
}

