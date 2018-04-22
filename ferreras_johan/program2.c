#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include "program.h"

//This function calculates the length of the LCS recursively and determines the value of the entry. 
//If two letters in the current entry are the same
//then it adds the arrow DIAGONAL to the arrow table and retrieves the value from the diagonal entry. Otherwise, it
//returns the greater value between the entry above and the entry to the left 
//The inputs are the two strings obtained from the input files, their respective lengths, the LCS table
//and the table that keeps track of the direction of the arrows
int lengthLCS(char* stringX, char* stringY, int lenX, int lenY);

//This function is used to calculate the runtime of an algorithm
//inside of my main function i declared two timeval variables, and using one of the system fuctions
//the obtains the time when the fuction started and when it finished then passes it to this function
//Which substracts finishTime from startTime then formats it in a way that is comprehensible
double runtime(struct timeval* startTime, struct timeval* finishTime);

//This is the function that governs everything else that goes on in the program
//In here we allocate memory for both strings contained in the files and call the function
//that deals with that. In here we also allocate memory for the table used to calculate the
//length of the LCS, allocate memory for the table used to keep track of the arrows, and
// declare and initialize the timeval variables used by the runtime function
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









