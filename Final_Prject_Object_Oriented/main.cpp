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

void createWire(string wn, int wi, vector<Wire*>& w) {
    if (w.size() <= wi) {
        w.resize(wi + 1, NULL);
    }
    if (w[wi] == NULL) {
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
    string circuitName;
    int w1;
    int w2;
    int w3;
    int wIndices[4] = { 0,0,0, 0};

    circDoc >> garbage >> circuitName;
    circDoc >> inputType;
    // Loop through the input file to read in circuit components
    while (!circDoc.eof()) {
        if (inputType == "INPUT" || inputType == "OUTPUT") {
            circDoc >> wireName >> wireIndex;
            // Read in input/output wire information and add it to the wire vector

            createWire(wireName, wireIndex, wireVctr);

            circDoc >> inputType;
        }


        if (inputType == "AND" || inputType == "NAND" || inputType == "OR" || inputType == "XOR" || inputType == "NOT" || inputType == "NOR") {
            // Read in gate information and add it to the gate vector
            circDoc >> gateDelay >> garbage;

            if (inputType != "NOT") {
                circDoc >> wIndices[1] >> wIndices[2] >> wIndices[3];
                createWire(to_string(wIndices[1]), wIndices[1], wireVctr);
                createWire(to_string(wIndices[2]), wIndices[2], wireVctr);
                createWire(to_string(wIndices[3]), wIndices[3], wireVctr);

                Gate* gate = new Gate(inputType, gateDelay, wireVctr.at(wIndices[1]), wireVctr.at(wIndices[2]), wireVctr.at(wIndices[3]));
                gateVctr.push_back(gate);
                wireVctr[wIndices[1]]->addGate(gate);
                wireVctr[wIndices[2]]->addGate(gate);
                circDoc >> inputType;
            }
            else {
                circDoc >> wIndices[1] >> wIndices[2];

                createWire(to_string(wIndices[1]), wIndices[1], wireVctr);
                createWire(to_string(wIndices[2]), wIndices[2], wireVctr);

                Gate* gate = new Gate(inputType, gateDelay, wireVctr.at(wIndices[1]), wireVctr.at(wIndices[2]));
                gateVctr.push_back(gate);
                wireVctr[wIndices[1]]->addGate(gate);
                circDoc >> inputType;
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
    


    vecDoc >> garbage >> garbage;
    vecDoc >> title; // get first line of data

    while (!vecDoc.eof()) {


        vecDoc >> name >> time >> value; // get the rest of the line
    
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


        for (int i = 1; i < wireVctr.size(); i++) {
            if (wireVctr.at(i) == nullptr){
                continue;
            }
            else if ((name == wireVctr.at(i)->getName())) {
                wire = wireVctr.at(i);
                continue;
            }
        }
        

        
        
        
        //populate event queue
       
        Event newEvent = Event(wire, e.size() + 1, time, value);
        e.push(newEvent);
       

        vecDoc >> title; // get next line of data
    }

    vecDoc.close();

    //---------------------------- SIMULATE ---------------------------------------------------------------------



    Simulate s(e);

    time = s.simulation();

    s.print(time, wireVctr);


    if (time > 60) {
        time = 60;
    }
    

    cout << "Circuit Name : " << circuitName << endl;
    cout << "Time elapsed: " << time << endl;





    //// Delete Wire objects
    //for (auto wire : wireVctr) {
    //    delete wire;
    //}

    //// Delete Gate objects
    //for (auto gate : gateVctr) {
    //    delete gate;
    //}

    return 0;
}
