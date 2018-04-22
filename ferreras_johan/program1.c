#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include "program.h"

//int getRuntime();

//this enum allows the program to know which entry in the table to use as reference for its value
enum Arrow{LEFT, UP, DIAGONAL};

//This function calculates the length of the LCS by initializing first row and first column to 0
//then, it goes row by row to determinte the value of each entry. If two letters in the current entry are the same
//then it adds the arrow DIAGONAL to the arrow table and retrieves the value from the diagonal entry. Otherwise, it
//returns the greater value between the entry above and the entry to the left 
//The inputs are the two strings obtained from the input files, their respective lengths, the LCS table
//and the table that keeps track of the direction of the arrows
int lengthLCS(char* stringX, char* stringY, int lenX, int lenY, int** tableLCS, enum Arrow** arrowTable);

//This function is used to calculate the runtime of an algorithm
//inside of my main function i declared two timeval variables, and using one of the system fuctions
//the obtains the time when the fuction started and when it finished then passes it to this function
//Which substracts finishTime from startTime then formats it in a way that is comprehensible
double runtime(struct timeval* startTime, struct timeval* finishTime);

//This function is used to print the LCS of the two strings. It uses the arrow table to determine
//which direction to go and which letters from the strings to retrieve to form the LCS. It starts
//at the bottom right corner of the table and moves based on the arrow. If the arrow is diagonal then
//it should call itself recursively on the diagonal entry and print the letter at the respective index to output1.
//This is why i and j are being used, this way we can decrease the size of the LCS that we need to find
void printLCS(enum Arrow** arrowTable, char* stringX, int i, int j, FILE* output1);

//This is the function that governs everything else that goes on in the program
//In here we allocate memory for both strings contained in the files and call the function
//that deals with that. In here we also allocate memory for the table used to calculate the
//length of the LCS, allocate memory for the table used to keep track of the arrows,
// declare and initialize the timeval variables used by the runtime function, and determine what kind of output
// to write to the output file. If the input strings are larger than 10 it will just print the length of the LCS
// and the runtime, otherwise it will print the LCS table to the file
int main(int argc, char** argv){

	//string in filex.txt and length
	char* stringX = (char*) malloc(MAX_BUFFER_SIZE*sizeof(char));
	int lenX;
	
	//string in filey.txt and length
	char* stringY = (char*) malloc(MAX_BUFFER_SIZE*sizeof(char));
	int lenY;
	
	//function that stores the strings from the files in their respective variables
	storeStrings(argc, argv, &stringX, &stringY);
	
	//fprintf(stderr, "%s\n", stringX);
	
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
	
	//Arrow table: allocate two dimensional array of arrows
	//First allocate space for the rows
	enum Arrow** arrowTable = malloc(lenX * sizeof(enum Arrow*));
	
	//error-checking with informative message
	if(tableLCS == NULL || arrowTable == NULL){
		fprintf(stderr, "Error while allocating memory.\n");
		exit(1);
	}
	
	//allocate memory necessary for each row based on the number of columns
	for(int row = 0; row < totalRows; row++){
		tableLCS[row] = malloc(totalColumns * sizeof(int));
		if(row < lenX){
			arrowTable[row] = malloc(lenY * sizeof(enum Arrow));
			//error-checking with informative message
			if(arrowTable[row] == NULL || tableLCS[row] == NULL){
				fprintf(stderr, "Error while allocating memory.\n");
				exit(1);
			}
		}
		
	}
	
	//error-checking for last row
	if(tableLCS[lenX] == NULL){
		fprintf(stderr, "Error while allocating memory.\n");
		exit(1);
	}
	
	//length of LCS
	int lengthOfLCS;
	
	//start the timer after necessary structures have been created
	gettimeofday(&startTime, NULL);
	
	//function to fill up LCS-length table and table of arrows as well as return length of LCS
	lengthOfLCS = lengthLCS(stringX, stringY, lenX, lenY, tableLCS, arrowTable);

	//open output file to write
	output1 = fopen(outName, "w");
	if(output1 == NULL){
		fprintf(stderr, "Error while attempting to write to %s file.\n", outName);
		exit(1);
	}
	
	if(lenX > 10 || lenY > 10){
		//get finishing time and compute runtime
		gettimeofday(&finishTime, NULL);
		totalTime = runtime(&startTime, &finishTime);
		fprintf(output1, "%d\n%.6f seconds.", lengthOfLCS, totalTime);
	} else {
		for(int row = 0; row < totalRows; row++){
			for(int column = 0; column < totalColumns; column++){
				fprintf(output1, "%d ", tableLCS[row][column]);
			}
			fprintf(output1, "\n");
		}
		gettimeofday(&finishTime, NULL);
		totalTime = runtime(&startTime, &finishTime);
		printLCS(arrowTable, stringX, lenX-1, lenY-1, output1);
		
		fprintf(output1, "\n%.6f seconds.", totalTime);
	}
	//close file once we are done writing
	fclose(output1);
	free(stringX);
	free(stringY);
	free(tableLCS);
	free(arrowTable);
	
	
	return 0;
}

int lengthLCS(char* stringX, char* stringY, int lenX, int lenY, int** tableLCS, enum Arrow** arrowTable){
	//tableLCS and arrowTable are pointers to their respective tables, not the tables themselves
	
	int row, column, arrowRow, arrowCol;
	
	for(row = 1; row <= lenX; row++){
		tableLCS[row][0] = 0;
	}
	
	for(column = 0; column <= lenY; column++){
		tableLCS[0][column] = 0;
	}
	
	for(row = 1; row <= lenX; row++){
		arrowRow = row - 1;
		for(column = 1; column <= lenY; column++){
			arrowCol = column - 1;
			if(stringX[row-1] == stringY[column-1]){
				tableLCS[row][column] = tableLCS[row-1][column-1] + 1;
				arrowTable[arrowRow][arrowCol] = DIAGONAL;
			} else if(tableLCS[row-1][column] >= tableLCS[row][column-1]){
				tableLCS[row][column] = tableLCS[row-1][column];
				arrowTable[arrowRow][arrowCol] = UP;
			} else {
				tableLCS[row][column] = tableLCS[row][column-1];
				arrowTable[arrowRow][arrowCol] = LEFT;
			}
		}
	}
	return tableLCS[lenX][lenY];
}

double runtime(struct timeval* startTime, struct timeval* finishTime){
	double retVal;
	
	retVal = (*finishTime).tv_sec - (*startTime).tv_sec;
	retVal += ((*finishTime).tv_usec - (*startTime).tv_usec) / 1000000.0;
	
	return retVal;
}

void printLCS(enum Arrow** arrowTable, char* stringX, int i, int j, FILE* output1){
	if(i==-1 || j==-1){
		return;
	}
	
	if(arrowTable[i][j] == DIAGONAL){
		printLCS(arrowTable, stringX, i-1, j-1, output1);
		fprintf(output1, "%c", stringX[i]);
	} else if(arrowTable[i][j] == UP){
		printLCS(arrowTable, stringX, i-1, j, output1);
	} else{
		printLCS(arrowTable, stringX, i, j-1, output1);
	}

}
























