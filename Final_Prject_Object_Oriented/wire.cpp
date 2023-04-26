#include "wire.h"

Wire::Wire(string n = "", int i = 0) {
	name = n;
	state = 'X';
	index = i;

}
Wire::Wire() {
	name = "";
	state = 'X';
	index = 0;

}

void Wire::printHistory() {
	for (int i = 0; i < history.size(); i++) {
		cout << history.at(i) << endl;
	}
}

void Wire::addGate(Gate* inputGate) {
	drives.push_back(inputGate);
}
void Wire::setState(char s) {
	state = s;
}
void Wire::setHistory(char inputState, int inputTime) {
	if (history.size() >= 2) {
		if (history.at(inputState - 1) != '/n') {
			history.at(inputTime) = inputState;
		}
		else {
			//loop until reach blank element
			for (int i = 0; i < history.size(); i++) {
				if (history.at(i) == '/n') {
					history.at(i) = inputState;
				}
			}
		}
	}
	else {
		history.at(inputTime) = inputState;
	}

}