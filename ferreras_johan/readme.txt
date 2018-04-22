<<<<<<< HEAD
Instructions:
from the command line just call "make" which will make three executable programs
all three programs are ready to be used as stated in the assignment description
=======
To compile the code just run "make" and a file BestFirstSearch will get created.
This file runs in the format:
Prompt>./BestFirstSearch <inputFileName> <outputFileName>
where both files given to the program are txt files

The data structure used for this program was a Branch and Bound Best First Search
Tree. The way it was implemented was by creating a class for the tree which contains
all the information necessary to do the calculations a B&B Best First Search Tree
needs.

In addition, a priority queue was used to make sure items are retrieved in order
of priority. This priority was based on the bound of the items so that the
item with the largest bound is the first one in the priority queue.

The only class that was used was the BestFirstSearch class and it contained vectors
to store the solutions, weights, and profits, variables to count nodes, and two structures
called node and item which just contained information about each item and node in the tree.
>>>>>>> 13f61407b20f876d790f07e67136c40edecd21fd
