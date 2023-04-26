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
			time = currEvent.getTime();
			
			//check if event creates a change in the wire - if no, discard event
			if (currEvent.getValue() == currEvent.GetEventWire()->getState()) {
				break;
			}


			//fill in gaps with setHistory()
			if (currEvent.GetEventWire() != nullptr) {
				currEvent.GetEventWire()->setHistory(currEvent.getValue(), currEvent.getTime());
				currEvent.GetEventWire()->setState(currEvent.getValue());
			}

			for (auto d : currEvent.GetEventWire()->getDrives()) {
				char state = d->evaluate();
				Wire* w = d->getOutput();
				Event newEvent(w, count++, time + d->getDelay(), state);
				eventQueue.push(newEvent);
			}

			eventQueue.pop();
		
			return time;
		}
	}

	void print(int time, vector<Wire*>& inputWires) {

		time++;

		//-------------	DEBUGGING PURPOSES -----------------------

		for (int i = 1; i < inputWires.size(); i++) {
			cout << "state of wire " << i << ": ";
			cout << inputWires.at(i)->getState() << endl;
		}

		//--------------------------------------------------------


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
				cout << i;
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