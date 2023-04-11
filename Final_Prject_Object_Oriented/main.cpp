#include "gate.cpp"
#include "wire.cpp"
#include <iostream>
#include <fstream>			//includes both ifstream and ofstream

using namespace std;


int main(){
	ifstream circDoc;
	circDoc.open("input.txt");

	if (circDoc.is_open() == false) {		//return error message if file not opened properly
		cerr << "Error opening file";
	}

						












	circDoc.close();				//need to close document at end
	return 0;
}

