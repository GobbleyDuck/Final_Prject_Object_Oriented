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
		cout << history.at(i);
	}
	cout << endl;
}

void Wire::addGate(Gate* inputGate) {
	drives.push_back(inputGate);
}
void Wire::setState(char s) {
	state = s;
}
void Wire::setHistory(char inputState, int inputTime) {

	if (inputState == '0') {
		for (int i = history.size(); i < inputTime; i++) {
			history += "_";
		}
	}
	else if (inputState == '1') {
		for (int i = history.size(); i < inputTime; i++) {
			history += "-";
		}
	}
	else if (inputState == 'X') {
		for (int i = history.size(); i < inputTime; i++) {
			history += "X";
		}
	}

	if (history.size() > 60) {
		for (int i = history.size() - 1; i > 60; i--) {
			history.pop_back();
		}
	}
}
