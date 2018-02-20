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
		bool import_data(string input_filename);
		void run_simulated_annealing();
	private:
		int num_vertices;
		int num_edges;
		vector <vector <int> > adjacency_matrix;

};

int main (){

	Solver solver;
	if (!solver.import_data("InputFiles/stephenTest.txt")){
		cerr << "Failed to import data" << endl;
		return 1;
	}

	solver.run_simulated_annealing();

	return 0;
}

bool Solver::import_data(string input_filename){
	//first we need to read in the file
	ifstream input_file;
	input_file.open(input_filename);
	if (!input_file.is_open()){
		cerr << "Couldn't open the input file" << endl;
		return false;
	}
	//the first line of the file contains number of vertices and edges
	input_file >> num_vertices >> num_edges;

	//next we make the adjacency matrix to store the points and weights
	//it should be nxn where n is the number of vertices 
	vector <vector <int> > temp_adj_matrix(num_vertices, vector<int>(num_vertices));

	while (!input_file.eof()){
		int current_vert, connecting_node, weight;
		input_file >> current_vert >> connecting_node >> weight;
		//we need to subtract 1 since the graph is 1 indexed
		//we also need to add the values to eachother since both are adjacent
		temp_adj_matrix.at(current_vert - 1).at(connecting_node - 1) = weight;
		temp_adj_matrix.at(connecting_node - 1).at(current_vert - 1) = weight;
	}
	adjacency_matrix = temp_adj_matrix;
	input_file.close();
	return true;
}


void Solver::run_simulated_annealing(){
	//define two vectors for the initial guess
	vector <int> side_a (num_vertices/2);
	vector <int> side_b (num_vertices/2);
	//initially, we will guess that we should just split the nodes in half
	for (int i = 0; i < num_vertices/2; i++){
		side_a.at(i)=i;
	}
	for (int i = num_vertices/2; i < num_vertices; i++){
		side_b.at(i-(num_vertices/2))=i;
	}

	//now that we have the split vectors, we find the cost
	//TODO: make this a cost FUNCTION
	int tot_cost = 0;

	for (int a: side_a){
		for (int b: side_b){
			tot_cost += adjacency_matrix[a][b];
		}
	}

	cout << "total cost is: " << tot_cost << endl;
}

