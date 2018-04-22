all:	Driver

Driver: Driver.o BestFirstSearch.o
	 			g++ Driver.o BestFirstSearch.o -o BestFirstSearch
Driver.o:	Driver.cpp
					g++ -c Driver.cpp

BestFirstSearch.o:	BestFirstSearch.cpp
										g++ -c BestFirstSearch.cpp

clean:
				rm -f *.o BestFirstSearch
