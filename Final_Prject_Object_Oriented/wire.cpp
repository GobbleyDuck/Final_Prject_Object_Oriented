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
	//if (history.size() >= 2) {
	//	if (history.at(inputState - 1) != '/n') {
	//		history.at(inputTime) = inputState;
	//	}
	//	else {
	//		//loop until reach blank element
	//		for (int i = 0; i < history.size(); i++) {
	//			if (history.at(i) == '/n') {
	//				history.at(i) = inputState;
	//			}
	//		}
	//	}
	//}
	//else {
	//	history.at(inputTime) = inputState;
	//}
	//

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

//void Wire::printWire() {
//	cout << "name: " << name << endl;
//	cout << "state: " << state << endl;
//	cout << "drives: " << endl;
//	for (int i = 0; i < drives.size(); i++) {
//		cout << drives.at(i) << " ";
//	}
//	cout << endl << "index: " << index << endl;
//	cout << "time: " << time << endl;
//}