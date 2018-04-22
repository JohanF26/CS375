#include <iostream>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include "BestFirstSearch.h"

using namespace std;

int main(int argc, char* argv[]){
  //start file stream with the command line inputs
  ifstream input(argv[1]);

  if(input.is_open()){
    BestFirstSearch* newBestFS = new BestFirstSearch(input);
    input.close();
    newBestFS->procedureKnap();
    //printf("max profit: %d nodes visited: %d leaf: %d\n", newBestFS->getMaxProfit(), );
    vector<BestFirstSearch::node> solutions = newBestFS->getSolutionPath();

    //open output file stream and check if it is open
    ofstream output(argv[2]);
    if(output.is_open()){
      //send data to output file (n, maxProfit, solutionSize)
      output << newBestFS->getProblemSize() << "," << newBestFS->getMaxProfit() << "," << solutions.size() << endl;
      //send visited nodes and leaf nodes to output file
      output << newBestFS->getNodes() << "," << newBestFS->getLeafNodes() << endl;
      for(int i = 0; i < solutions.size(); i++){
        output << solutions.at(i).weight << "," << solutions.at(i).profit << endl;
      }
      output.close();
    }
  }

  return 0;
}
