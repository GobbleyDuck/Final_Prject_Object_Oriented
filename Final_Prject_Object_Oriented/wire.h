//Natalie Mayfield and Ethan Molsberry
//April 5th, 2023

#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;


class Gate;

class Wires {

public:
	Wires(string n = "", char v = '\0', Gate* gate = nullptr, int i = 0, string h = "");	//constructor

	string getName()const { return name; }
	char getValue()const { return value; }
	vector<Gate*> getDrives() const { return drives; }
	int getIndex() const { return index; }
	string getHistory() const { return history; }

	void addGate(vector <Gate*>);
	void setState(string);
	void setHistory(string, int);

	void printHistory();

private:
	string name;
	string state;
	vector <Gate*> drives;
	int index;
	string history;
	int time;

};
