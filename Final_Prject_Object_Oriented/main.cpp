#include "gate.h"
#include "wire.h"
#include <iostream>
#include <fstream>

using namespace std;

/*
* TODO:
* Make it optional for the user to select a file
* 
*/

int main() {
    //TODO: turn wireIndex into an array [3]
    string wireName;
    int wireIndex[3] = {0,0,0};
    int gateDelay;
    vector<Wire> wireVctr;
    vector<Gate> gateVctr;

    ifstream circDoc("input.txt");

    //----------------------------- OPEN TEXT FILE --------------------------------------------

    if (!circDoc.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string inputType;

    //------------------------------- READ FILE --------------------------------------------------

    circDoc >> inputType;

    //validates the name
    if (inputType == "CIRCUIT") {
        string circuitName;
        circDoc >> circuitName;
        cout << "Circuit name: " << circuitName << endl;

        while (circDoc >> inputType) {
            if (inputType == "INPUT" || inputType == "OUTPUT") {
                circDoc >> inputType >> wireName >> wireIndex[0];
                Wire wire(wireName, wireIndex[0]);
                wireVctr.push_back(wire);
            }

            if (inputType == "AND" || inputType == "NAND" || inputType == "OR" || inputType == "XOR" || inputType == "NOT") {
                circDoc >> gateDelay;
                if (inputType != "NOT") {
                    for (int i = 0; i < 3; i++) { circDoc >> wireIndex[i]; }
                    Gate gate(inputType, gateDelay, wireIndex[0], wireIndex[1], wireIndex[2]);
                }
                //TODO: issue with the NOT gate in gate.h initialization
                else {
                    for (int i = 0; i < 2; i++) { circDoc >> wireIndex[i]; }
                    //TODO: finish gate initialization
                    Gate gate();
                }
                gateVctr.push_back(gate);
                
            }
        }
    }

    circDoc.close();
    return 0;
}