

#include <iostream>

#ifndef EVENT_H
#define EVENT_H

#include "wire.h"
#include "gate.h"

using namespace std;


class Event {
public:
	//constructors:
	Event(Wire* w, int c, int t, char v) { 
		wire = w; 
		count = c; // event number (event1, event2...) 
		time = t;
		value = v; // high or low
	}

	//getters: CHANGE TIMING TO A DIF NAME
	vector<Wire> getIntputs() { return inputs; }
	int getTiming(int i) { return timings[i]; }
	int getTime() { return time; }
	int getCount() { return count; }
	char getValue() { return value; }
	Wire* GetEventWire() { return wire; }


	bool operator<(const Event& rhs) const { return time < rhs.time;}

	//the painfull stuff :(
	bool evaluateGateDelay(vector<int> wireIndexes, vector<Gate>& gateVctr);

	char makeQueue(Gate tempGate, Wire tempWire, Event newEvent);
	

private:
	vector<Wire> inputs;
	int timings[3];
	int time;
	int count;
	char value;
	Wire* wire;
};

#endif 