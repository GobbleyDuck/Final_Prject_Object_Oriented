#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <cstdio>
#include <sstream>
#include <string>
#include "event.h"
#include "simulate.h"
#include "gate.h"
#include "wire.h"


using namespace std;

/*
* TODO:
* revise gate constructors to take a dynamic amount of wires
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

    getline(circDoc, input);

            // Loop through the input file to read in circuit components
    while (!circDoc.eof()) {
        stringstream ss(input);
        ss >> inputType;
        if (inputType == "INPUT" || inputType == "OUTPUT") {
            ss >> wireName >> wireIndex;
            // Read in input/output wire information and add it to the wire vector
            Wire* wire = new Wire(wireName, wireIndex);
 //           wireIndexes.push_back(wireIndex);
            wireVctr.push_back(wire);
            getline(circDoc, input);
        }

        if (inputType == "AND" || inputType == "NAND" || inputType == "OR" || inputType == "XOR" || inputType == "NOT" || inputType == "NOR") {
            // Read in gate information and add it to the gate vector
            string garbage;
            ss >> gateDelay >> garbage;
            Wire* tempWires[4];
            if (inputType != "NOT") {
                for (int i = 0; i < 3; i++) {
                    ss >> wireIndex;
                    //if wire DNE yet, resize 
                    if (wireVctr.size() < wireIndex) {
                        for (int i = wireVctr.size(); i <= wireIndex; i++) {
                            wireVctr.push_back(nullptr);
                            wireVctr.at(i) = new Wire("", i);
                        }
                    }
                   tempWires[i] = wireVctr[wireIndex-1];
                }
                Gate* gate = new Gate(inputType, gateDelay, wireVctr.at(0), wireVctr.at(1), wireVctr.at(3));
                gateVctr.push_back(gate);
                getline(circDoc, input);
            }
            else {
                for (int i = 0; i < 2; i++) {
                    ss >> wireIndex;
                    if (wireVctr.size() < wireIndex) {
                        for (int i = wireVctr.size(); i <= wireIndex; i++) {
                            wireVctr.push_back(nullptr);
                            wireVctr.at(i) = new Wire("", i);
                        }
                    }
                    tempWires[i] = wireVctr[wireIndex];
                }
                Gate* gate = new Gate(inputType, gateDelay, wireVctr.at(0), wireVctr.at(1));
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

 //   getline(vecDoc, line);

    while (!vecDoc.eof()) {
        getline(vecDoc, line);
        stringstream ss(line);
        ss >> title >> name >> time >> value;

        //at this point, it's taking the line A 4 1....?
    
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
                wireVctr.at(i)->setState(value);
                break;
            }
        }
        
        
        
        //populate event queue
       
        Event newEvent = Event(wire, e.size() + 1, time, value);
        e.push(newEvent);
       

        getline(vecDoc, line);
    }

    vecDoc.close();

    //---------------------------- SIMULATE ---------------------------------------------------------------------

    //-------------DEBUGGING PURPOSES------------------------
    for (int i = 0; i < wireVctr.size(); i++) {
        cout << "state of wireVctr wire at " << i << ": ";
        cout << wireVctr.at(i)->getState() << endl;
    }
    //--------------------------------------------------------


    Simulate s(e);
    s.simulation();

    s.print(time, wireVctr);





    
    return 0;
}
