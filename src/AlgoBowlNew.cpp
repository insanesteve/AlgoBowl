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

class Solver{
	public:
		Solver(string inputFilename){
			this->inputFilename = inputFilename;
		}
		void ImportData();
		void DoAlgorithm();
	private:
		string inputFilename;
		int num_vertices;
		int num_edges;
		vector <vector <int> > adjacency_matrix;

};

int main (){

	Solver input1("InputFiles/stephenTest.txt");
	input1.ImportData();
	input1.DoAlgorithm();

	return 0;
}

void Solver::ImportData(){
	//first we need to read in the file
	ifstream inputFile;
	inputFile.open(inputFilename);
	if (!inputFile.is_open()){
		cerr << "Couldn't open the file" << endl;
		return;
	}
	//the first line of the file contains number of vertices and edges
	inputFile >> num_vertices >> num_edges;
	//make the adjacency matrix to store the points and weights
	//it should be nxn where n is the number of vertices 
	//This allows us to map to all other vertices
	//will need to be set as class vector
	vector <vector <int> > temp_matrix(num_vertices, vector<int>(num_vertices));

	while (!inputFile.eof()){
		int currentVert, connectingNode, weight;
		inputFile >> currentVert >> connectingNode >> weight;
		//we need to use -1 because the graph is 0 indexed
		//we also need to add the values to eachother since both are adjacent
		temp_matrix.at(currentVert - 1).at(connectingNode - 1) = weight;
		temp_matrix.at(connectingNode - 1).at(currentVert - 1) = weight;
	}
	adjacency_matrix = temp_matrix;
	inputFile.close();
}


void Solver::DoAlgorithm(){
	//define two vectors for the initial guess
	vector <int> sideA (num_vertices/2);
	vector <int> sideB (num_vertices/2);
	//initially, we will guess that we should just split the nodes in half
	//from here forward we will denote node "1" as node "0" to make things simpler
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
}



