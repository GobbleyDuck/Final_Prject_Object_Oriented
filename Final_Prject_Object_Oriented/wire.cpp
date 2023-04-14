#include "wire.h"

Wire::Wire(string n = "", int i = 0) {
	name = n;
	state = 'X';
	index = i;
	history = "X";

}

void Wire::printHistory() {
	cout << history << endl;
}

void Wire::addGate(Gate* inputGate) {
	drives.push_back(inputGate);
}
void Wire::setState(char s) {
	state = s;
}
void Wire::setHistory(char inputState, int inputTime) {
	history.at(inputTime) = inputState;
}