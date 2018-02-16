/* 
	CSCI 406: AlgoBowl Project

	Authors: Stephen Agee, Alex Santilli, and Michaela Serpas

	This program takes in the input file (which represents a graph
	with nodes and weighted edges) and finds a good way to split
	the graph into two while intersecting the lowest amount of 
	weight.  
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

//each edge has the node that it points to and the weight of the path.
struct edge {
	int node;
	int weight;
};

int main (){

	//first we need to read in the file
	string input_filename = "InputFiles/inputfile.txt";
	//cout << "Enter the input filename: ";
	//cin >> input_filename;
	ifstream inputFile;
	inputFile.open(input_filename);

	int num_vertices;
	int num_edges;
	inputFile >> num_edges >> num_vertices;

	vector <vector <edge>> adjacency_list(num_vertices);
	while (!inputFile.eof()){
		int current_node;
		edge edge_to_insert;
		inputFile >> current_node >> edge_to_insert.node >> edge_to_insert.weight;
		adjacency_list.at(current_node).push_back(edge_to_insert);
	}
	cout << num_edges << " " << num_vertices << endl;
	for (int i = 0; i < adjacency_list.size(); i++){
		for (int j = 0; j < adjacency_list.at(i).size(); j++){
			cout << i << " " << adjacency_list.at(i).at(j).node << " " << adjacency_list.at(i).at(j).weight << endl;
		}
	}
	inputFile.close();

	//next we can use the algorithm to find the best split
	//todo: finish this

	return 0;
}


