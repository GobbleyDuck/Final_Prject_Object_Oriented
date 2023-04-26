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
* get the in variant of 3ns work
*/

void createWire(string wn, int wi, vector<Wire*>& w) {
    if (w.size() <= wi) {
        w.resize(wi + 1, NULL);
    }
    if (w[wi] != NULL) {
        w[wi] = new Wire(wn, wi);
    }
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
    string garbage;
    int w1;
    int w2;
    int w3;
    int wIndices[3];

    circDoc >> garbage >> garbage;
    circDoc >> inputType;
    // Loop through the input file to read in circuit components
    while (!circDoc.eof()) {
        if (inputType == "INPUT" || inputType == "OUTPUT") {
            circDoc >> wireName >> wireIndex;
            // Read in input/output wire information and add it to the wire vector

 //           createWire(wireName, wireIndex, wireVctr);

            circDoc >> inputType;
        }


        if (inputType == "AND" || inputType == "NAND" || inputType == "OR" || inputType == "XOR" || inputType == "NOT" || inputType == "NOR") {
            // Read in gate information and add it to the gate vector
           circDoc >> gateDelay >> garbage;
 
            if (inputType != "NOT") {
                circDoc >> w1 >> w2 >> w3;
                createWire(to_string(w1), w1, wireVctr);
                createWire(to_string(w2), w2, wireVctr);
                createWire(to_string(w3), w3, wireVctr);

                //for (int i = 0; i < 3; i++) {
                //    circDoc >> wIndices[i];
                //    //if wire DNE yet, resize
                //    // may not work with internal wires - KAS
                //    if (wireVctr.size() < wireIndex) {
                //        for (int i = wireVctr.size(); i <= wireIndex; i++) {
                //            wireVctr.push_back(nullptr);
                //            wireVctr.at(i) = new Wire("", i); // only if its nullptr - KAS
                //        } // swap this line with the one above - KAS
                //    }
               //    tempWires[i] = wireVctr[wireIndex-1];
                }
                Gate* gate = new Gate(inputType, gateDelay, wireVctr.at(0), wireVctr.at(1), wireVctr.at(2));
                gateVctr.push_back(gate);
                wireVctr[wIndices[0]]->addGate(gate);
                wireVctr[wIndices[1]]->addGate(gate);
                circDoc >> inputType;
            }
            else {

                circDoc >> wIndices[0] >> wIndices[1];
                circDoc >> w1 >> w2;
                createWire(to_string(w1), w1, wireVctr);
                createWire(to_string(w2), w2, wireVctr);

                /*if (wireVctr.size() < wireIndex) {
                    for (int i = wireVctr.size(); i <= wireIndex; i++) {
                        wireVctr.push_back(nullptr);
                        wireVctr.at(i) = new Wire("", i);
                    }
                }*/

            }
                Gate* gate = new Gate(inputType, gateDelay, wireVctr.at(0), wireVctr.at(1));
                gateVctr.push_back(gate);
                wireVctr[wIndices[0]]->addGate(gate);
                circDoc >> inputType;
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
    


    vecDoc >> garbage >> garbage;
    vecDoc >> title; // get first line of data
    while (!vecDoc.eof()) {
        //getline(vecDoc, line);
        //stringstream ss(line);
        vecDoc >> name >> time >> value; // get the rest of the line

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
       

        vecDoc >> title; // get next line of data
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
