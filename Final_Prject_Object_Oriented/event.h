

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
	int getTime() { return time; }
	int getCount() { return count; }
	char getValue() { return value; }
	Wire* GetEventWire() { return wire; }


	bool friend operator<(const Event& lhs, const Event& rhs) {
		if (lhs.time == rhs.time) {
			return lhs.count > rhs.count;
		}
		else {
			return lhs.time > rhs.time;
		}
	}

	

private:
	int time;
	int count;
	char value;
	Wire* wire;
};

#endif 