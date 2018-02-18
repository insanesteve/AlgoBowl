#include <iostream>
#include <fstream>
#include <algorithm> 
#include <vector>
#include <string>
using namespace std;

const string OUTPUT_FILE = "stephenTest.txt";

int main() {
    //create and shuffle nodes from 1 to 600
    vector <int> nodes;
    for (int i = 0; i<= 599; i++){
        nodes.push_back(i+1);
    }
    //random_shuffle(nodes.begin(), nodes.end());

    //create and open output file
    ofstream outFile;
    outFile.open (OUTPUT_FILE);
    int edge_count = 0;
    //for the first 300 nodes
    for (int i = 0; i <= 299; i++){
        //for nodes greater than current node
        for (int j = i+1; j <= 299; j++){
              //connect current node to greater nodes
              outFile << nodes.at(i) << " " <<  nodes.at(j) 
                      << " " << rand()%((50 - 40) + 1) + 40 << "\n";
              //we connected an edge, increment edge counter
              edge_count++;
        }
    }
    //connect node from first group to second group
    outFile << nodes.at(299) << " " << nodes.at(300) << " " << 40 << "\n";
    //we connected an edge, increment edge counter
    edge_count++;
    cout << nodes.at(299) << " " << nodes.at(300) << " " << 40 << endl;
    //for last 300 nodes
      for (int i = 300; i <= 599; i++){
        //for nodes greater than current node
        for (int j = i+1; j <= 599; j++){
              //connect current node to greater nodes
              outFile << nodes.at(i) << " " <<  nodes.at(j) << " " 
                      << rand()%((50 - 40) + 1) + 40 << "\n";
              //we connected an edge, increment edge counter
              edge_count++;
        }
    }
    //close the output file
    outFile.close();

    cout << "Text file name: " << OUTPUT_FILE << " " 
          << nodes.size() << " " << edge_count << endl;
    
    return 0;
}
