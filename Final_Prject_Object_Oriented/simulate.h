#pragma once
#include "gate.h"
#include "wire.h"
#include "event.h"
#include <iostream>
#include <queue>


using namespace std;

class Simulate {
public:
	
	Simulate(priority_queue<Event> inputQueue) {
		eventQueue = inputQueue;
	}

	int simulation() {
		count = eventQueue.size();
		

		while(!eventQueue.empty() && time <= 60){
			currEvent = eventQueue.top();
			Wire* currWire = currEvent.GetEventWire();
			eventQueue.pop();
			time = currEvent.getTime();
			
			//check if event creates a change in the wire - if no, discard event
			if (currEvent.getValue() == currEvent.GetEventWire()->getState()) {
				continue;
			}


			//fill in gaps with setHistory()
			//currently setting history to current value with time gaps - set to last known value until current time
			//wire pointer to getEventWire
			//time minus 1
			//wire's value, not currEvent value
			if (currEvent.GetEventWire() != nullptr) {
				currWire->setHistory(currWire->getState(), currEvent.getTime() - 1);
				currWire->setState(currEvent.getValue());
			}

			for (auto d : currEvent.GetEventWire()->getDrives()) {
				char state = d->evaluate();
				Wire* w = d->getOutput();
				Event newEvent(w, count++, time + d->getDelay(), state);
				eventQueue.push(newEvent);
			}

			
		
			
		}
		return time;
	}

	void print(int time, vector<Wire*>& inputWires) {

		time++;

		for (int i = 1; i < inputWires.size(); i++) {
			inputWires.at(i)->setHistory(inputWires.at(i)->getState(), time);
		}

		for (int i = 1; i < inputWires.size(); i++) {
			if (inputWires.at(i)->getName() != "") {
				cout << endl << inputWires.at(i)->getName() << "| ";
				inputWires.at(i)->printHistory();
				cout << " |";
			}
		}

		if (time == 62) {
			for (int i = 1; i <= time; i++) {
				cout << "_";
			}
		}
		else {
			for (int i = 2; i <= time; i++) {
				cout << "-";
			}
		}

		for (int i = 0; i < time; i++) {
			if (i > 60) {
				break;
			}
			else if ((i % 5) == 0) {
				cout << i / 5;
			}
			else {
				cout << "-";
			}


			if (time < 59) {
				cout << "--";
			}
		}

		cout << endl;



	}







private:
	priority_queue<Event> eventQueue;
	int time;
	Event currEvent;
	int count;



};