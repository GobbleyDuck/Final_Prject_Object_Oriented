#pragma once
#include <iostream>
#include "wire.h"

using namespace std;


class Event {
public:

	Event(Wire* w, int c, int t, char v) { 
		wire = w; 
		count = c; 
		time = t;
		value = v;
	}

	bool operator<(Event rhs) {
		return time > rhs.time;
	}





	int time;
	int count;
	char value;
	Wire* wire;
};