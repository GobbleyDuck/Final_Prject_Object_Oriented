#include "gate.h"
#include "wire.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <cstdio>
#include <sstream>
#include <string>
#include "event.h"
#include "simulate.h"


using namespace std;

/*
* TODO:
* revise gate constructors to take a dynamic amount of wires
* Create Event - only create a new event if the output changes
* Create Simulate
* Create Print
* Change the vectors to a queue
* get the in variant of 3ns
*/
vector<int> sort(vector<int> inputVctr) {
    vector<int> sortedWires;
    sort(inputVctr.begin(), inputVctr.end());
    for (int i = 0; i < inputVctr.size(); i++) {
        if (inputVctr[i] == i) {
            sortedWires[i] = inputVctr[i];
        }
        else {
            sortedWires[i] = 0;
        }
    }
    return sortedWires;
}




int main() {
    // Declare variables for reading in circuit information
    string wireName;
    string baseFileName;
    string circuitFileName;
    string vectorFileName;
    ifstream circDoc(circuitFileName);
    ifstream vecDoc(vectorFileName);
    int wireIndex;
    int gateDelay;
    vector<Wire*> wireVctr;
    vector<Gate*> gateVctr;
    vector<int> wireIndexes;
    priority_queue<Event> e;
    string inputType;


    // Open input file
    cout << "Enter the file name, excluding the extension type" << endl;
    cin >> baseFileName;
    circuitFileName = baseFileName + ".txt";
    vectorFileName = baseFileName + "_v.txt";
    
    // take in file then append .txt
    // get whole line then use stringstream
    // overload < operator to use priority queue
    // least time comes first
    // second variable to sort - count based on when comes first if time is same


    //----------------------------- OPEN TEXT FILE --------------------------------------------
    // Check if the file was successfully opened
    circDoc.open(circuitFileName);

    if (!circDoc.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    

    //------------------------------- READ FILE --------------------------------------------------
    // Read in the circuit type from the input file
    string input;
    getline(circDoc, input);

        // Check if the circuit type is valid
    if (input.substr(0,7) != "CIRCUIT") {
        cerr << "invalid file name." << endl;
    }

            // Loop through the input file to read in circuit components
    while (!circDoc.eof()) {
        circDoc >> inputType;
        if (inputType == "INPUT" || inputType == "OUTPUT") {
            circDoc >> wireName >> wireIndex;
            // Read in input/output wire information and add it to the wire vector
            Wire* wire = new Wire(wireName, wireIndex);
            wireIndexes.push_back(wireIndex);
            wireVctr.push_back(wire);
            getline(circDoc, inputType);
        }

        if (inputType == "AND" || inputType == "NAND" || inputType == "OR" || inputType == "XOR" || inputType == "NOT") {
            // Read in gate information and add it to the gate vector
            string garbage;
            circDoc >> gateDelay;
            circDoc >> garbage;
            Wire* tempWires[4];
            if (inputType != "NOT") {
                for (int i = 0; i < 3; i++) {
                    circDoc >> wireIndex;
                    //if wire DNE yet, resize 
                    if (wireVctr.size() < wireIndex) {
                        for (int i = wireVctr.size(); i <= wireIndex; i++) {
                            wireVctr.push_back(nullptr);
                            wireVctr.at(i) = new Wire("", i);
                        }
                    }
                    tempWires[i] = wireVctr[wireIndex-1];
                }
                Gate* gate = new Gate(inputType, gateDelay, tempWires[0], tempWires[1], tempWires[2]);
                gateVctr.push_back(gate);
                getline(circDoc, input);
            }
            else {
                for (int i = 0; i < 2; i++) {
                    circDoc >> wireIndex;
                    tempWires[i] = wireVctr[wireIndex];
                }
                Gate* gate = new Gate(inputType, gateDelay, tempWires[0], tempWires[1]);
                gateVctr.push_back(gate);
                getline(circDoc, input);
            }
            string s = "";
            circDoc >> s;
            if (s == "") {
                break;
            }
        }
    }
            
      
        

    // close circuit file
    
    circDoc.close();

    
  
    
   
    
    //open vector file
    
    vecDoc.open(vectorFileName);
    if (!vecDoc.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    //-----------------------------------------Read vector file----------------------------------------------
    string line;
    string title;
    string name;
    int time = -1;
    char value; 
    Wire* wire = nullptr;
    bool correctWire = true;
    

    getline(vecDoc, line);
    if (line.substr(0, 6) != "VECTOR") {
        cerr << "Incorrect file formatting - please fix and try again.";
        return 1;
    }

    getline(vecDoc, line);

    while (!vecDoc.eof()) {
        getline(vecDoc, line);

        vecDoc >> title >> name >> time >> value;
    
        if (title != "INPUT") {
            break;
        }
        if (name == "") { 
            break;
        }
        if (time == -1) {
            break;
        }
        if (value == '/n') {
            break;
        }

        if (value != '0' && value != '1' && value != 'X') {
            break;
        }

        for (int i = 0; i < wireVctr.size(); i++) {
            if (name != wireVctr.at(i)->getName()) {
                correctWire = false;
            }
            else {
                correctWire = true;
                wire = wireVctr.at(i);
                break;
            }
        }
        
        

        //populate event queue
       
        Event newEvent = Event(wire, e.size() + 1, time, value);
        e.push(newEvent);

       /* cout << "count: " << newEvent.getCount() << endl;
        cout << " wire: " << newEvent.GetEventWire() << endl;
        cout <<  "time: " << newEvent.getTime() << endl;
        cout << "value: " << newEvent.getValue() << endl;*/
       

        getline(vecDoc, line);
    }

    vecDoc.close();

    //---------------------------- SIMULATE ---------------------------------------------------------------------



    


    //// while the priority queue still has events in it, read an event, handle it, then delete it
    //while(!e.empty() && time <= 60){

    //    //get top event from queue and creates wire from queue
    //    Event currEvent = e.top();
    //    time = currEvent.getTime();

    //    currEvent.GetEventWire()->setHistory(currEvent.getValue(), currEvent.getTime());
    //    currEvent.GetEventWire()->setState(currEvent.getValue());


    //    e.pop();
    //}

    Simulate s(e);
    s.simulation();

    s.print(time, wireVctr);





    
    return 0;
}