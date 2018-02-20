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
#include <random>
using namespace std;

class Solver{
	public:
	//functions
		bool import_data(string input_filename);
		void run_simulated_annealing(int temp_max, int iterations_max);
	private:
	//functions
		int find_cost(vector <int> side_a, vector <int> side_b);
	//variables
		int num_vertices;
		int num_edges;

		vector <vector <int> > adjacency_matrix;
		vector <int> best_side_a;
		vector <int> best_side_b;
		int lowest_cost;
};

int main (){

	Solver solver;
	if (!solver.import_data("InputFiles/inputFile.txt")){
		cerr << "Failed to import data" << endl;
		return 1;
	}

	solver.run_simulated_annealing(1000,10);

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


void Solver::run_simulated_annealing(int temp_max, int iterations_max){
	//define two vectors for the current guess
	vector <int> curr_side_a (num_vertices/2);
	vector <int> curr_side_b (num_vertices/2);
	//initially, we will simply split the nodes in half
	for (int i = 0; i < num_vertices/2; i++){
		curr_side_a.at(i)=i;
	}
	for (int i = num_vertices/2; i < num_vertices; i++){
		curr_side_b.at(i-(num_vertices/2))=i;
	}
	//find the cost of the initial guess
	int curr_cost = find_cost(curr_side_a, curr_side_b);
	//since this is the first iteration, use it as the best case
	best_side_a = curr_side_a;
	best_side_b = curr_side_b;
	lowest_cost = curr_cost;

	for (int i = 0; i < iterations_max; i++){
		//swap a random index from current vectors
		int index_a = rand()%num_vertices/2;
		int index_b = rand()%num_vertices/2;
		vector <int> pot_side_a = curr_side_a;
		vector <int> pot_side_b = curr_side_b;
		pot_side_a.at(index_a) = curr_side_b.at(index_b);
		pot_side_b.at(index_b) = curr_side_a.at(index_a);
		//check if the new cost is less than the current cost
		int cost = find_cost(pot_side_a, pot_side_b);
		//cout << cost << " " << curr_cost << endl;
		if (cost < curr_cost){
			//we should definitely keep it
			curr_cost = cost;
			curr_side_a = pot_side_a;
			curr_side_b = pot_side_b;
			cout << "Found a better cost: " << lowest_cost << endl;
			//it might be the best so far
			if (curr_cost < lowest_cost){
				lowest_cost = curr_cost;
				best_side_a = curr_side_a;
				best_side_b = curr_side_b;
				cout << "Found the best cost: " << lowest_cost << endl;
			}
		}
	}

	cout << "total cost is: " << lowest_cost << endl;
}

int Solver::find_cost(vector <int> side_a, vector <int> side_b){
	int tot_cost = 0;
	for (int a: side_a){
		for (int b: side_b){
			tot_cost += adjacency_matrix.at(a).at(b);
		}
	}
	return tot_cost;
}

