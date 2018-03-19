#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "program.h"


void storeStrings(int argc, char** argv, char** stringX, char** stringY){

	//If number of arguments is not 4 then quit the program with an informative message
	if(argc != 4){
		fprintf(stderr, "Incorrect number of arguments.\n");
		exit(1);
	}
	
	//Store information from each file and open them up
	
	//filex.txt to read
	char* inNameX = argv[1];
	FILE* inputX;
	inputX = fopen(inNameX, "r");
	
	//If there was an error while opening files for reading then quit the program
	//with an informative message
	if(inputX == NULL){
		fprintf(stderr, "Error while attempting to read input files.\n");
		exit(1);
	}
	
	//reads string from file in the format specified and stores it to variable then close file
	fscanf(inputX, "%s", *stringX);
	fclose(inputX);
	
	fprintf(stderr, "%s\n", *stringX);
	
	
	
	//filex.txt to read
	char* inNameY = argv[2];
	FILE* inputY;
	inputY = fopen(inNameY, "r");
	
	//If there was an error while opening files for reading then quit the program
	//with an informative message
	if(inputY == NULL){
		fprintf(stderr, "Error while attempting to read input files.\n");
		exit(1);
	}
	
	//reads string from file in the format specified and stores it to variable then close file
	fscanf(inputY, "%s", *stringY);
	fclose(inputY);
	
	fprintf(stderr, "%s\n", *stringY);
	
}





