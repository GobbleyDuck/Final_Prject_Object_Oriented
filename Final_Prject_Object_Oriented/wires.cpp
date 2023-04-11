#include "wire.h"

Wires::Wires(int i = 0, string n = "") {
	name = n;
	state = 'X';
	index = i;
	history = "X";

}

void Wires::printHistory() {
	cout << history << endl;
}

void Wires::addGate(Gate* inputGate) {
	drives.push_back(inputGate);
}
void Wires::setState(char s) {
	state = s;
}
void Wires::setHistory(char inputState, int inputTime) {
	history.at(inputTime) = inputState;
}