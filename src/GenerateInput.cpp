/* 
	CSCI 406: AlgoBowl Project
	Authors: Stephen Agee, Alex Santilli, and Michaela Serpas
	This program generates inputs for the AlgoBowl project.
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


int main (){
	ofstream outputFile;
	outputFile.open("outputFile.txt");
	outputFile << "Writing to file...";
	outputFile.close();

	return 0;
}

