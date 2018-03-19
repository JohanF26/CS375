all:	program1

program1:	program1.o program.o
			gcc -o program1 program1.o program.o
			
program1.o:	program1.c
			gcc -Wall -c program1.c
			
program.o:	program.c
			gcc -Wall -c program.c
			
clean:
			rm -f *.o program1
