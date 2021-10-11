# All Targets
all: exec

# Tool invocations
# Executable "exec" 
exec: task2.o LineParser.o
	gcc -g -m32 -Wall -o exec task2.o LineParser.o

# Depends on the source and header files
task2.o: task2.c
	gcc -g -m32 -c -o task2.o task2.c 

LineParser.o: LineParser.c
	gcc -g -m32 -c -o LineParser.o LineParser.c 

#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f *.o exec
