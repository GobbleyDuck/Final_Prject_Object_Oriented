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
			if (currEvent.getValue() == currWire->getState()) {
				continue;
			}



			if (currEvent.GetEventWire() != nullptr) {
				currWire->setHistory(currWire->getState(), currEvent.getTime() - 1);
				currWire->setState(currEvent.getValue());
			}

			
			//check to see if the event is the same as the value of the wire 
			//because you already created that wire pointer so may as well use it instead of the event part 
			for (auto d : currWire->getDrives()) {
				char state = d->evaluate();
				Wire* w = d->getOutput();
				Event newEvent(w, count++, time + d->getDelay(), state);
				eventQueue.push(newEvent);
			}

			
		
			
		}
		return time;
	}

	void print(int time, vector<Wire*>& inputWires) {

		this->time = time;
		
		for (int i = 1; i < inputWires.size(); i++) {
			if (inputWires.at(i) == nullptr) {
				continue;
			}
			inputWires.at(i)->setHistory(inputWires.at(i)->getState(), time);
		}

		for (int i = 1; i < inputWires.size(); i++) {
			if (inputWires.at(i) == nullptr) {
				continue;
			}
			if (inputWires.at(i)->getName() != "") {
				cout << endl << inputWires.at(i)->getName() << "| ";
				inputWires.at(i)->printHistory();
				cout << " |";
			}
		}


		for (int i = 0; i < time + 1; i++) {
			if (i > 60) {
				break;
			}
			else if ((i % 5) == 0) {
				cout << i / 10;
			}
			else {
				cout << "-";
			}
		}

		cout << endl << "  ";

		for (int i = 0; i < time + 1; i++) {
			if (i > 60) {
				break;
			}
			else if ((i % 5) == 0) {
				cout << i % 10;
			}
			else {
				cout << " ";
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