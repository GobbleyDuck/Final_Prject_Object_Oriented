//Natalie Mayfield and Ethan Molsberry
//April 5th, 2023

#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;


class Gate;

class Wire {

public:
	Wire();
	Wire(string, int);	//constructor

	string getName()const { return name; }
	char getState()const { return state; }
	vector<Gate*> getDrives() const { return drives; }
	int getIndex() const { return index; }
	vector<char> getHistory() const { return history; }

	void addGate(Gate*);
	void setState(char);
	void setHistory(char, int);

	void printHistory();

private:
	string name;
	char state;
	vector <Gate*> drives;
	int index;
	vector<char> history = {};
	int time;

};
