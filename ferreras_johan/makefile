<<<<<<< HEAD
all:	program1 program2 program3

program1:	program1.o program.o
			gcc -o program1 program1.o program.o
			
program1.o:	program1.c
			gcc -Wall -c program1.c
			
program2:	program2.o program.o
			gcc -o program2 program2.o program.o
			
program2.o:	program2.c
			gcc -Wall -c program2.c
			
program3:	program3.o program.o
			gcc -o program3 program3.o program.o
			
program3.o:	program3.c
			gcc -Wall -c program3.c
			
program.o:	program.c
			gcc -Wall -c program.c
			
clean:
			rm -f *.o program1 program2 program3
=======
all:	Driver

Driver: Driver.o BestFirstSearch.o
	 			g++ Driver.o BestFirstSearch.o -o BestFirstSearch
Driver.o:	Driver.cpp
					g++ -c Driver.cpp

BestFirstSearch.o:	BestFirstSearch.cpp
										g++ -c BestFirstSearch.cpp

clean:
				rm -f *.o BestFirstSearch
>>>>>>> 13f61407b20f876d790f07e67136c40edecd21fd
