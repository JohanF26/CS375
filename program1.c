#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include "program.h"

//int getRuntime();

enum Arrow{LEFT, UP, DIAGONAL};

int lengthLCS(char* stringX, char* stringY, int lenX, int lenY, int** tableLCS, enum Arrow** arrowTable);

double runtime(struct timeval* startTime, struct timeval* finishTime);

void printLCS(enum Arrow** arrowTable, char* stringX, int i, int j, FILE* output1);

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
























