#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include "program.h"

int lengthLCS(char* stringX, char* stringY, int lenX, int lenY);
double runtime(struct timeval* startTime, struct timeval* finishTime);

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
	
	//start the timer after necessary structures have been created
	gettimeofday(&startTime, NULL);
	
	//Get length of LCS
	int lengthOfLCS = lengthLCS(stringX, stringY, lenX-1, lenY-1);

	gettimeofday(&finishTime, NULL);
	totalTime = runtime(&startTime, &finishTime);
	
	//open file to write
	output1 = fopen(outName, "w");
	if(output1 == NULL){
		fprintf(stderr, "Error while attempting to write to %s file.\n", outName);
		exit(1);
	}

	fprintf(output1, "%d\n%.6f seconds.", lengthOfLCS, totalTime);
	fclose(output1);
	free(stringX);
	free(stringY);
	
	return 0;

}

int lengthLCS(char* stringX, char* stringY, int lenX, int lenY){
	if(lenX == -1 || lenY == -1){
		return 0;
	}
	
	//if they are equal call recursively on diagonal + 1
	if(stringX[lenX] == stringY[lenY]){
		return lengthLCS(stringX, stringY, lenX-1, lenY-1) + 1;
	
	} else {
		int boxUp = lengthLCS(stringX, stringY, lenX-1, lenY);
		int boxLeft = lengthLCS(stringX, stringY, lenX, lenY-1);
		//if square above is greater then choose its value
		if(boxUp > boxLeft){
			return boxUp;
		} else {
			return boxLeft;
		}
	}

}

double runtime(struct timeval* startTime, struct timeval* finishTime){
	double retVal;
	
	retVal = (*finishTime).tv_sec - (*startTime).tv_sec;
	retVal += ((*finishTime).tv_usec - (*startTime).tv_usec) / 1000000.0;
	
	return retVal;
}









