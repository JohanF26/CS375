#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include "program.h"

double runtime(struct timeval* startTime, struct timeval* finishTime);
int initLCS(int** tableLCS, char* stringX, char* stringY, int lenX, int lenY);
int lookUpLCS(int** tableLCS, char* stringX, char* stringY, int i, int j);

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
	//for(int h = 0; h <= strlen(stringX); h++){
	//	for(int k = 0; k <= strlen(stringY); k++){
	//		printf("%d", tableLCS[h][k]);
	//	}
	//	printf("\n");
	//}
	return lookUpLCS(tableLCS, stringX, stringY, lenX, lenY);

}

int lookUpLCS(int** tableLCS, char* stringX, char* stringY, int i, int j){
	if(i < 0 || j < 0){ //end of recursion, base case
		return 0;
	}
	//fprintf(stderr, "Aye3\n");
	if(stringX[i] == stringY[j]){
		//We know diagonal down increases by one
		//if this value has not been updated we need to find values in table that have
		if(tableLCS[i][j] == -1){ //initial value and means has not been updated
			//fprintf(stderr, "Aye\n");
			tableLCS[i+1][j+1] = lookUpLCS(tableLCS, stringX, stringY, i-1, j-1) + 1;
		} else{
		//otherwise we can just return the diagonal entry incremented
			//fprintf(stderr, "Aye2 %d %d\n", i, j);
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
