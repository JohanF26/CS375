#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <algorithm>
#include "string"
#include "BestFirstSearch.h"

using namespace std;

//consturctor for the BestFirstSearch class that takes
//the address of an input file stream as input
//we assume the input file stream is open since it was checked in the
//driver file
BestFirstSearch::BestFirstSearch(ifstream& input)
    : inputFile(input)
{
  //initialize these variables to 0
  maxProfit = 0;
  problemSize = 0;
  weightLimit = 0;
  nodesVisited = 0;
  leafNodesVisited = 0;

  //string to store the current line in the file
  string currentLine;

  //store problem size with , as a delimeter of when to stop
  getline(inputFile, currentLine, ',');
  istringstream inputStream(currentLine);
  inputStream >> problemSize;

  //store weight limit
  getline(inputFile, currentLine);
  istringstream inputStream2(currentLine);
  inputStream2 >> weightLimit;

  //this getline loop gets every itme before the comma
  while(getline(inputFile, currentLine, ',')){
    //node weight and profit
    node u;

    //store weight
    istringstream inputStream(currentLine);
    inputStream >> u.weight;

    //store profit, this getline gets the item after the comma
    getline(inputFile, currentLine);
    istringstream inputStream2(currentLine);
    inputStream2 >> u.profit;

    //calculate the ratio of profit pet weight to sort in descending order
    u.profPerWeight = (float)(u.profit/u.weight);

    //add to a vector of items so it can be sorted
    items.push_back(u);

    //printf("Weight: %d Profit: %d p/w: %f\n", u.weight, u.profit, u.profPerWeight);
  }
  //sort the items in the items vector
  sort(items.begin(), items.end());
  //place the weights and profits in a separate reference vector since the ones
  //stored in the items themselves might be modified (profits add up)
  for(int i = 0; i < problemSize; i++){
    weights.push_back(items.at(i).weight);
    profits.push_back(items.at(i).profit);
  }
}

void BestFirstSearch::procedureKnap(){
  //create a priority queue for the nodes and initialize it to be empty
  priority_queue<item> PQ;
  if(!PQ.empty()){
    printf("Priority Queue was not empty.\n");
    exit(1);
  }

  //create nodes u and v and initialize v's fields to 0 so that it is the root
  item u,v;
  v.itemNode.level = 0;
  v.itemNode.profit = 0;
  v.itemNode.weight = 0;

  //calculate the bound for vector v
  v.bound = bound(v);

  //enqueue v into PQ
  PQ.push(v);

  //continue removing items from the queue until it is empty
  while(!PQ.empty()){
    //remove vector with best bound
    v = PQ.top();
    PQ.pop();
    //printf("best bound: %f\n", v.bound);

    //expand node v if the bound is greater than the max profit
    //this tells us if the node is promising
    if(v.bound > maxProfit){
      u.itemNode.level = v.itemNode.level+1;

      //"yes" child
      //-1 because indexing starts at 0
      u.itemNode.weight = v.itemNode.weight + weights.at(u.itemNode.level-1);
      u.itemNode.profit = v.itemNode.profit + profits.at(u.itemNode.level-1);
      u.itemPath = v.itemPath;
      //add previous item to item path
      u.itemPath.push_back(items.at(u.itemNode.level-1));
      //mark the node visited or not

      //if we have not surpassed weight limit and have a better profit
      //update the profit
      if((u.itemNode.weight <= weightLimit) && (u.itemNode.profit > maxProfit)){
        maxProfit = u.itemNode.profit;
        //the last item updating the max profit is the last item in the solution
        lastItem = u;
      }

      //if the bound of this node is greater than the max profit add it to
      //the priority queue, otherwise it is not feasible so it is a leaf node
      u.bound = bound(u);
      if(u.bound > maxProfit){
        PQ.push(u);
      } else{
        leafNodesVisited++;
      }

      //"No" child
      u.itemNode.weight = v.itemNode.weight;
      u.itemNode.profit = v.itemNode.profit;
      u.itemPath = v.itemPath;
      u.bound = bound(u);

      //if after calculating the bound it is still promising add it to the
      //priority queue, otherwise it is a leaf node
      if(u.bound > maxProfit){
        PQ.push(u);
      } else{
        leafNodesVisited++;
      }
      //every node that gets processed counts
      nodesVisited++;
    } else{
      //if the bound is less than the maxProfit it is not feasible so it is
      //a leaf node
      leafNodesVisited++;
    }
  }
  //after finishing the while loop the number of nodes visited is the number
  //of nodes added to the priority queue plus those not added (leaf nodes)
  nodesVisited+=leafNodesVisited;
}

//the purpose of this function is to calculate the bound of the given node
//(largest possible profit of the current solution path)
//it works by adding up the profits of the nodes after the current node
//as long as we have not gone through every item and we have not surpassed the
//capacity of the knapsack
//one thing to note is that it uses the knapsack with fractios algorithm as a basis
//for how it computes the upper bound
//no assumptions are made about the parameters but we need this item to calculate
//its bound
float BestFirstSearch::bound(item v){
  //the bound is initially this items profit
  float bound = (float) v.itemNode.profit;
  //iterate through items after current item
  int i = v.itemNode.level;
  int currentWeight = v.itemNode.weight;
  float itemFrac;

  if(v.itemNode.weight < weightLimit){
    //if we have not reached the end of this problem
    //and if adding this item to the knapsack does not surpass the weight limit
    while((i < problemSize) && ((currentWeight + weights.at(i)) <= weightLimit)){
      //update weight limit with weight of i
      currentWeight += weights.at(i);
      bound += profits.at(i);
      i++;
    }
    if(i < problemSize){
      //add a fraction of the item to the knapsack
      itemFrac = ((float)(weightLimit-currentWeight)/weights.at(i));
      currentWeight = weightLimit;
      bound += (float)(profits.at(i)*itemFrac);
    }
    //printf("bound: %f weightLimit: %d\n", bound, weightLimit);
  } else{
    bound = 0;
  }
  return bound;
}

//this is just a getter function with the purpose of returning
//the maximum profit calculated by the Best First Seach Tree
//it does so by returning the value stored in the private variable maxProfit
int BestFirstSearch::getMaxProfit(){
  return (int) maxProfit;
}

//this is just a getter function with the purpose of returning
//the size of the problem obtained from the input file
//it does so by returning the value stored in the private variable problemSize
int BestFirstSearch::getProblemSize(){
  return problemSize;
}

//this is just a getter function with the purpose of returning
//the total number of nodes visited by the Best First Seach algorithm
//it does so by returning the value stored in the private variable nodesVisited
//this variable is calculated by counting nodes added to the queue and nodes not added
int BestFirstSearch::getNodes(){
  return nodesVisited;
}

//this is just a getter function with the purpose of returning
//the leaf nodes visited by the Best First Seach algorithm
//it does so by returning the value stored in the private variable leafNodesVisited
//this is calculated by counting the nodes not added to the priority queue
int BestFirstSearch::getLeafNodes(){
  return leafNodesVisited;
}

//this is just a getter function with the purpose of returning
//a vector containing the nodes of the items in the solution to the 0/1 kanpsack
//as solved by the Best First Seach Tree algorithm
//it does so by returning the path taken by the last item to update the maxProfit
vector<BestFirstSearch::node> BestFirstSearch::getSolutionPath(){
  return lastItem.itemPath;
}
