#include <iostream>
#include <fstream>
#include <algorithm> 
using namespace std;

int main() {
    int count = 0;
    vector <int> nodes;
    for (int i = 0; i<= 599; i++){
        nodes.push_back(i+1);
    }
  random_shuffle(nodes.begin(), nodes.end());
  ofstream myfile;
  myfile.open ("mehtaHeuristicInput.txt");
  for (int i = 0; i <= 299; i++){
      for (int j = i+1; j <= 299; j++){
            myfile << nodes.at(i) << " " <<  nodes.at(j) << " " << rand()%((50 - 40) + 1) + 40 << "\n";
      }
  }
  myfile << nodes.at(299) << " " << nodes.at(300) << " " << 40 << "\n";
  cout << nodes.at(299) << " " << nodes.at(300) << " " << 40 << endl;
    for (int i = 300; i <= 599; i++){
      for (int j = i+1; j <= 599; j++){
            myfile << nodes.at(i) << " " <<  nodes.at(j) << " " << rand()%((50 - 40) + 1) + 40 << "\n";
      }
  }
  myfile.close();
    
    
for (int i = 0; i < nodes.size(); i++){
    cout << nodes.at(i) << endl;
}
    
    return 0;
}
