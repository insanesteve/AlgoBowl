#include <iostream>
#include <fstream>
using namespace std;

int main (int argc, char* argv[]){

	if (argc < 4){
		cout << "Usage: " << argv[0] << " FILEPATH1" << " FILEPATH2" << " FILEPATH3" << endl;
		return 1;
	}
	string filenames[3];

	filenames[0] = argv[1];
	filenames[1] = argv[2];
	filenames[2] = argv[3];

	ifstream file_1, file_2, file_3;
	file_1.open(filenames[0]);
	file_2.open(filenames[1]);
	file_3.open(filenames[2]);
	if (!(file_1.is_open()) && (file_2.is_open()) && file_3.is_open()){
		cout << "Error opening a file." << endl;
		return 1;
	}

	int cost[3];
	
	string best_name;

	file_1 >> cost[0];
	file_2 >> cost[1];
	file_3 >> cost[2];

	int best_cost = cost[0];
	int best_index = 0;
	for (int i = 1; i < 3; i++){
		if (cost[i] > best_cost){
			best_cost = cost[i];
			best_index = i;
		}
	}

	cout << "Best file is :" << filenames[best_index] << endl;

	return 0;	
}