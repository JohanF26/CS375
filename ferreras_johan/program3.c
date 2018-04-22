#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include "program.h"

//This function is used to calculate the runtime of an algorithm
//inside of my main function i declared two timeval variables, and using one of the system fuctions
//the obtains the time when the fuction started and when it finished then passes it to this function
//Which substracts finishTime from startTime then formats it in a way that is comprehensible
double runtime(struct timeval* startTime, struct timeval* finishTime);

//initLCS() initializes the table/array used for the memoization algorithm
//basically what this does is fill up the table with impossible values (-1) while
//putting 0 in all of the first row and in all of the first column like
//we have done in the previous LCS programs
	//tableLCS: table to index LCS values
	//stringX: string retrieved from first input file
	//stringY: string retrieved from second input file
	//lenX: length of stringX
	//lenY: length of stringY
int initLCS(int** tableLCS, char* stringX, char* stringY, int lenX, int lenY);

//lookUpLCS is a function that recursively calculates the LCS of stringX and stringY, 
// the input strings from the input files, through memoization
//This algorithm takes advantage of already determined values and calculates new ones
//only when necessary. If an entry in the table is -1 then it needs to calculate a new
//value for that entry. Once it finishes recursively going through both strings it reaches
//the end of the function. Input variables i and j are used to determine the LCS of a "substring""
//of the current strings then passes it down the table (hence why it is top-down)
int lookUpLCS(int** tableLCS, char* stringX, char* stringY, int i, int j);

//This is the function that governs everything else that goes on in the program
//In here we allocate memory for both strings contained in the files and call the function
//that deals with that. In here we also allocate memory for the table used to calculate the
//length of the LCS, declare and initialize the timeval variables used by the runtime function,
//and write the results to a file
int main(int argc, char** argv){

	//string in filex.txt and length
	char* stringX = (char*) malloc(MAX_BUFFER_SIZE*sizeof(char));
	int lenX;
	
	//string in filey.txt and length
	char* stringY = (char*) malloc(MAX_BUFFER_SIZE*sizeof(char));
	int lenY;
	
	//function that stores the strings from the files in their respective variables
	storeStrings(argc, argv, &stringX, &stringY);
	
	//store the lengths
	lenX = strlen(stringX);
	lenY = strlen(stringY);

	//output1.txt
	char* outName = argv[3];
	FILE* output1;
	
	//time calculating variables
	struct timeval startTime, finishTime;
	double totalTime;
	
	//We fill up first row and first column with 0
	int totalRows = lenX+1;
	int totalColumns = lenY+1;
	
	//LCS length table: allocate two dimensional array of ints
	//First allocate space for the rows
	int** tableLCS = malloc(totalRows * sizeof(int*));
	
	if(tableLCS == NULL){
		fprintf(stderr, "Error while allocating memory.\n");
		exit(1);
	}

	for(int row = 0; row < totalRows; row++){
		tableLCS[row] = malloc(totalColumns * sizeof(int));
		if(tableLCS[row] == NULL){
			fprintf(stderr, "Error while allocating memory.\n");
			exit(1);
		}
	}
	
	//length of LCS
	int lengthOfLCS;
	
	//start the timer after necessary structures have been created
	gettimeofday(&startTime, NULL);
	lengthOfLCS = initLCS(tableLCS, stringX, stringY, lenX, lenY);
	
	//open file for writing
	output1 = fopen(outName, "w");
	
	gettimeofday(&finishTime, NULL);
	totalTime = runtime(&startTime, &finishTime);
	fprintf(output1, "%d\n%.6f seconds.", lengthOfLCS, totalTime);
	
	//close writing to file
	fclose(output1);
	//free allocated memory
	free(stringX);
	free(stringY);
	free(tableLCS);
	
	return 0;
	
}

int initLCS(int** tableLCS, char* stringX, char* stringY, int lenX, int lenY){
	for(int row = 0; row <= lenX; row++){
		for(int column = 0; column <= lenY; column++){
			
			//despite filling in -1 for unknown values we still need to put 0 whenever row or column = 0
			if(row == 0 || column == 0){
				tableLCS[row][column] = 0;
			} else{
				tableLCS[row][column] = -1; //initialize the array to impossible value
			}
		}
	}
	
	return lookUpLCS(tableLCS, stringX, stringY, lenX-1, lenY-1);

}

int lookUpLCS(int** tableLCS, char* stringX, char* stringY, int i, int j){
	if(i < 0 || j < 0){ //end of recursion, base case
		
		return 0;
	}
	
	if(stringX[i] == stringY[j]){
		//We know diagonal down increases by one
		//if this value has not been updated we need to find values in table that have
		//then send it up to the previous call
		if(tableLCS[i][j] == -1){ //initial value and means has not been updated
			tableLCS[i+1][j+1] = lookUpLCS(tableLCS, stringX, stringY, i-1, j-1) + 1;
		} else{
		//otherwise we can just return the diagonal entry incremented
			return lookUpLCS(tableLCS, stringX, stringY, i-1, j-1) + 1;
		}
	
	} else{
		int boxUp = lookUpLCS(tableLCS, stringX, stringY, i-1, j);
		int boxLeft = lookUpLCS(tableLCS, stringX, stringY, i, j-1);
		//if the value has not been updated find a value that has
		if(tableLCS[i][j] == -1){
			if(boxUp > boxLeft){
				tableLCS[i+1][j+1] = boxUp;
			} else {
				tableLCS[i+1][j+1] = boxLeft;
			}
		} else{
			//if square above is greater then choose its value
			if(boxUp > boxLeft){
				return boxUp;
			} else{
				return boxLeft;
			}
		
		}
		
	}
	
}

double runtime(struct timeval* startTime, struct timeval* finishTime){
	double retVal;
	
	retVal = (*finishTime).tv_sec - (*startTime).tv_sec;
	retVal += ((*finishTime).tv_usec - (*startTime).tv_usec) / 1000000.0;
	
	return retVal;
}


















