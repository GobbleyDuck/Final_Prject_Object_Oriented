#include "gate.h"
#include "wire.h"
#include <iostream>
#include <fstream>
#include <algorithm>


using namespace std;

/*
* TODO:
* Make it optional for the user to select a file
* revise gate constructors to take a dynamic amount of wires
* Create Vector
* Create Event
* Create Simulate
* Create Print
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
    int wireIndex[3] = { 0,0,0 };
    int gateDelay;
    vector<Wire> wireVctr;
    vector<Gate> gateVctr;
    vector<int> wireIndexes;

    // Open input file
    ifstream circDoc("input.txt");

    //----------------------------- OPEN TEXT FILE --------------------------------------------
    // Check if the file was successfully opened
    if (!circDoc.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string inputType;

    //------------------------------- READ FILE --------------------------------------------------
    // Read in the circuit type from the input file
    circDoc >> inputType;

    // Check if the circuit type is valid
    if (inputType == "CIRCUIT") {
        string circuitName;
        circDoc >> circuitName;
        cout << "Circuit name: " << circuitName << endl;

        // Loop through the input file to read in circuit components
        while (circDoc >> inputType) {
            if (inputType == "INPUT" || inputType == "OUTPUT") {
                // Read in input/output wire information and add it to the wire vector
                circDoc >> inputType >> wireName >> wireIndex[0];
                Wire wire(wireName, wireIndex[0]);
                wireIndexes.push_back(wireIndex[0]);
                wireVctr.push_back(wire);
            }
            

            if (inputType == "AND" || inputType == "NAND" || inputType == "OR" || inputType == "XOR" || inputType == "NOT") {
                // Read in gate information and add it to the gate vector
                circDoc >> gateDelay;
                Wire tempWires[4];
                if (inputType != "NOT") {
                    for (int i = 0; i < 3; i++) {
                        circDoc >> wireIndex[i];
                        tempWires[i] = wireVctr[wireIndex[i]];
                    }
                    Gate gate(inputType, gateDelay, &tempWires[0], &tempWires[1], &tempWires[2]);
                    gateVctr.push_back(gate);
                }
                else {
                    for (int i = 0; i < 2; i++) {
                        circDoc >> wireIndex[i];
                        tempWires[i] = wireVctr[wireIndex[i]];
                    }
                    Gate gate(inputType, gateDelay, &tempWires[0], &tempWires[1]);
                    gateVctr.push_back(gate);
                }
            }
        }
    }

    // Close input file
    circDoc.close();
    return 0;
}