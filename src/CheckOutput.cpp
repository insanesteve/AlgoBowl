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
using namespace std;

int find_cost(vector <int> side_a, vector <int> side_b);
//need this to be global so we can access it
vector <vector <int> > adjacency_matrix;

int main (int argc, char* argv[]){

	//get the filename from the command line and notify if one was not inserted
	if (argc < 3){
		cerr << "Usage: " << argv[0] << " RESOURCE FILENAME" << " INPUT FILENAME" << endl;
		return 1;
	}
	//set the filename
	string resource_filename = argv[1];
	string input_filename = argv[2];

	
	int num_vertices;
	int num_edges;

	int proposed_cost;
	vector <int> proposed_a;
	vector <int> proposed_b;

	ifstream input_file;
	input_file.open(resource_filename);
	if (!input_file.is_open()){
		cerr << "Couldn't open the resource file" << endl;
		return 0;
	}
	//the first line of the file contains number of vertices and edges
	input_file >> num_vertices >> num_edges;

	//next we make the adjacency matrix to store the points and weights
	//it should be nxn where n is the number of vertices 
	vector <vector <int> > temp_adj_matrix(num_vertices, vector<int>(num_vertices));

	//while (!input_file.eof()){
	for (int i = 0; i < num_edges; i++){
		int current_vert, connecting_node, weight;
		input_file >> current_vert >> connecting_node >> weight;
		//cout << current_vert << " " << connecting_node << " " << weight << endl;
		//we need to subtract 1 since the graph is 1 indexed
		//we also need to add the values to eachother since both are adjacent
		temp_adj_matrix.at(current_vert - 1).at(connecting_node - 1) = weight;
		temp_adj_matrix.at(connecting_node - 1).at(current_vert - 1) = weight;
	}
	adjacency_matrix = temp_adj_matrix;
	input_file.close();

	/*for (vector<int> outside : adjacency_matrix){
		for (int inside: outside){
			cout << inside << " ";
		}
		cout << endl;
	}*/
	input_file.open(input_filename);
	if (!input_file.is_open()){
		cerr << "Couldn't open the input file" << endl;
		return 0;
	}
	
	input_file >> proposed_cost;

	for (int i = 0; i < num_vertices/2; i++){
		int temp_int;
		input_file >> temp_int;
		proposed_a.push_back(temp_int - 1);
	}

	for (int i = 0; i < num_vertices/2; i++){
		int temp_int;
		input_file >> temp_int;
		proposed_b.push_back(temp_int - 1);
	}

	int calculated_cost = find_cost(proposed_a, proposed_b);
	cout << "Input File: " << input_filename << endl;
	cout << "Proposed cost: " << proposed_cost << endl;
	cout << "Calculated cost: " << calculated_cost << endl;
	if (proposed_cost == calculated_cost){
		cout << "Outputs are a MATCH!" << endl;
	}
	else cout << "Uh oh, looks like something went wrong" << endl;

	cout << endl;

	return 0;
}



int find_cost(vector <int> side_a, vector <int> side_b){
	int tot_cost = 0;
	for (int a: side_a){
		for (int b: side_b){
			tot_cost += adjacency_matrix.at(a).at(b);
		}
	}
	return tot_cost;
}
