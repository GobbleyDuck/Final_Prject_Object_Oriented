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
			
			// the code commented out below is altogether incorrect, use the comments
			// I've written that follow to get back on track - KAS
			// check if event creates a change in the wire - if no, discard event
			// if (currEvent.getValue() == currWire->getState()) {
			// 	continue;
			// }

			// currWire may drive a Gate (or Gates). If it does, the simulation
			// needs to determine if the output of the Gate will change based on
			// the change to currWire. Therefore, we need to do the following:
			// 1. Loop over all the Gates that currWire drives
			// 2. Within this loop determine what the output of the Gate is
			//    presently, that is, without the change to currWire. Name that
			//    output value something like presentOutput.
			// 3. Also within the loop determine what the output of the Gate
			//    would be if we used the new value for the currWire, rather than
			//    the present value. Name that output value futureOutput
			// 4. Then compare presentOutput with futureOutput. If they are
			//    different, then we need to insert the futureOutput event in the
			//    simulation queue. The event is:
			//      Event(outputWire, count, time+Gate.delay, futureOutput)

			// the event wire should never be nullptr, so the if is unnecessary - KAS
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