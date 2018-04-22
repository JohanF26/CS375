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
