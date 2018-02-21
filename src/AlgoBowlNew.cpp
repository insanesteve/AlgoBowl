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
#include <cmath>
using namespace std;

class Solver{
	public:
	//functions
		bool import_data(string input_filename);
		void run_simulated_annealing(int temp_max, int iterations_max);
		bool output_to_file(string output_filename);
	private:
	//functions
		int find_cost(vector <int> side_a, vector <int> side_b);
		int find_new_cost(int old_cost, vector<int> old_a, vector<int> old_b, vector<int> new_a, vector<int> new_b, int rand_a, int rand_b);
	//variables
		int num_vertices;
		int num_edges;

		vector <vector <int> > adjacency_matrix;
		vector <int> best_side_a;
		vector <int> best_side_b;
		int lowest_cost;
};

int main (){
	//seed for random to ensure randomness
	srand(time(0));

	string inputFilename = "input1.txt";
	Solver solver;
	//import the data into the solver
	if (!solver.import_data("InputFiles/" + inputFilename)){
		cerr << "Failed to import data" << endl;
		return 1;
	}

	//run simulated annealing (temp_max, max_iterations)
	solver.run_simulated_annealing(100,100);

	//output the data
	if (!solver.output_to_file("OutputFiles/" + inputFilename)){
		cerr << "Failed to write output file" << endl;
		return 1;
	}

	return 0;
}

bool Solver::import_data(string input_filename){
	//open the input file
	ifstream input_file;
	input_file.open(input_filename);
	if (!input_file.is_open()){
		cerr << "Couldn't open the input file" << endl;
		//returns to main to let it know something failed
		return false;
	}

	//the first line of the file must contain number of vertices and edges
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
	//success!
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

	//now we start the looping algorithm
	for (int current_temp = temp_max; current_temp > 0; current_temp--){
		//print statements to track current temperature, at least for now
		cout << "Temperature is: " << current_temp << endl;
		//loop for iterations_max at each temperature value
		for (int i = 0; i < iterations_max; i++){
			//swap a random index from current vectors
			int rand_a = rand()%num_vertices/2;
			int rand_b = rand()%num_vertices/2;
			vector <int> new_side_a = curr_side_a;
			vector <int> new_side_b = curr_side_b;
			new_side_a.at(rand_a) = curr_side_b.at(rand_b);
			new_side_b.at(rand_b) = curr_side_a.at(rand_a);
			//find the new cost
			int cost = find_cost(new_side_a, new_side_b);
			//definitions for simulated annealing
			//prob_number is the random double from 0-1
			//current_exp is the exponential value to determine probability
			double prob_number = (double)(rand()%10000)/10000;
			double current_exp = exp(((curr_cost - cost)/current_temp));
			//if the cost is better than the current cost, we should keep the swap
			//note that it is also set for sideways hill climbing (<"=")
			if (cost <= curr_cost){
				curr_cost = cost;
				curr_side_a = new_side_a;
				curr_side_b = new_side_b;
				//it also might be the best so far
				if (curr_cost < lowest_cost){
					lowest_cost = curr_cost;
					best_side_a = curr_side_a;
					best_side_b = curr_side_b;
					//print the current best cost, at least for now	
					cout << "found best: " << lowest_cost << endl;
				}
			}
			//if the current swap is worse, but within our probability margin, we still keep it
			else if (current_exp > prob_number){
				curr_cost = cost;
				curr_side_a = new_side_a;
				curr_side_b = new_side_b;
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

int Solver::find_new_cost(int old_cost, vector<int> old_a, vector<int> old_b, vector<int> new_a, vector<int> new_b, int rand_a, int rand_b){
	int new_cost = old_cost;
	for (int b: old_b){
		//we need to remove the old cost from the swapped a to all items in b
		new_cost = new_cost - adjacency_matrix.at(rand_a).at(b);
	}
	cout << "New Cost1: " << new_cost << endl;
	for (int a: old_a){
		//we need to remove all but the index we already counted, or else we would double count
		if (a != rand_a)
		new_cost = new_cost - adjacency_matrix.at(a).at(rand_b);
	}
	cout << "New Cost2: " << new_cost << endl;
	//now we add the cost from the swap to the new cost
	for (int b: new_b){
		new_cost += adjacency_matrix.at(rand_a).at(b);
	}
	cout << "New Cost3: " << new_cost << endl;
	for (int a: new_a){
		if (a != rand_a)
		new_cost += adjacency_matrix.at(a).at(rand_b);
	}
	cout << "New Cost4: " << new_cost << endl;
	return new_cost;
}

bool Solver::output_to_file(string output_filename){
	ofstream output_file;
	output_file.open(output_filename);
	if (!output_file.is_open()){
		cerr << "Failed to open the output file" << endl;
		return false;
	}

	output_file << lowest_cost << endl;
	for (int a: best_side_a){
		output_file << a + 1 << " ";
	}
	output_file << endl;
	for (int b: best_side_b){
		output_file << b + 1 << " ";
	}
	output_file.close();

	return true;
}


