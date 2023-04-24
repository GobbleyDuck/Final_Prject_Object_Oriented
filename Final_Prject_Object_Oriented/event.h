

#include <iostream>

#ifndef EVENT_H
#define EVENT_H

#include "wire.h"
#include "gate.h"

using namespace std;


class Event {
public:
	//added new Even constructor
	Event(const vector<Wire>& inputs, const int timings[3]) : inputs(inputs), timings{ timings[0], timings[1], timings[2] } {}

	Event(Wire* w, int c, int t, char v) { 
		wire = w; 
		count = c; 
		time = t;
		value = v;
	}

	/*bool operator<(Event rhs) {
		return time > rhs.time;
	}*/




	vector<Wire> inputs;
	int timings[3];
	int time;
	int count;
	char value;
	Wire* wire;
};

#endif 