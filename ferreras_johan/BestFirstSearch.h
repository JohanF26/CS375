#include <iostream>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <queue>

using namespace std;

class BestFirstSearch{

  public:
    struct node{
      int weight;
      int profit;
      int level;
      float profPerWeight;

      //define less than operator for nodes so that PQ can use them
      friend bool operator<(const node& left, const node& right){
        return left.profPerWeight > right.profPerWeight;
      }
    };

    struct item{
      node itemNode;
      float bound;
      vector<node> itemPath;

      friend bool operator<(const item& left, const item& right){
        return left.bound < right.bound;
      }

    };

    BestFirstSearch(ifstream&);
    void procedureKnap();
    float bound(item v);

    //getters
    int getProblemSize();
    item getLastItem();
    int getMaxProfit();
    int getNodes();
    int getLeafNodes();
    vector<node> getSolutionPath();

  private:
    //stream from input file
    ifstream& inputFile;

    //information about the problem
    int problemSize;
    int weightLimit;

    //vector containing items
    vector<node> items;

    //first compute the max possible value and the last item added to the solution
    //so that we can follow its path to find the items in the solution
    int maxProfit;
    item lastItem;

    //keep track of nodes visited and how many leaf nodes
    int nodesVisited;
    int leafNodesVisited;

    //arrays to calculate the profits and the weights of each item
    vector<int> weights;
    vector<int> profits;

};
