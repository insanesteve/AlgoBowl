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
#include <set>
using namespace std;

int main (){

	//first we need to read in the file
	string input_filename = "test.txt";
	//cout << "Enter the input filename: ";
	//cin >> input_filename;
	ifstream inputFile;
	inputFile.open(input_filename);

	int num_vertices;
	int num_edges;
	inputFile >> num_vertices >> num_edges;
	//make the adjacency matrix to store the points and weights
	//it should be nxn where n is the number of vertices 
	//This allows us to map to all other vertices
	vector <vector <int>> adjacency_matrix(num_vertices, vector<int>(num_vertices));
	
	while (!inputFile.eof()){
		int currentVert, connectingNode, weight;
		inputFile >> currentVert >> connectingNode >> weight;
		//we need to use -1 because the graph is 0 indexed
		//we also need to add the values to eachother since both are adjacent
		adjacency_matrix.at(currentVert - 1).at(connectingNode - 1) += weight;
		adjacency_matrix.at(connectingNode - 1).at(currentVert - 1) += weight;
	}

	//define two vectors for the initial guess
	vector <int> sideA (num_vertices/2);
	vector <int> sideB (num_vertices/2);
	//initially, we will guess that we should just split the nodes in half
	//from here forward we will denote node 1 as node 0 to make things simpler
	for (int i = 0; i < num_vertices/2; i++){
		sideA.at(i)=i;
	}
	for (int i = num_vertices/2; i < num_vertices; i++){
		sideB.at(i-(num_vertices/2))=i;
	}

	//now that we have the split vectors, we find the cost
	//TODO: make this a cost FUNCTION
	int tot_cost = 0;

	for (int a: sideA){
		for (int b: sideB){
			tot_cost += adjacency_matrix[a][b];
		}
	}

	cout << "total cost is: " << tot_cost << endl;




	inputFile.close();

	//next we can use the algorithm to find the best split
	//todo: finish this
	//for indices in set, sum across in the matrix

	return 0;
}


