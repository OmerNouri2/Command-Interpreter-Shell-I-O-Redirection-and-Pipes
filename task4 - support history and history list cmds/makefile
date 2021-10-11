# All Targets
all: exec

# Tool invocations
# Executable "exec" 
exec: task3.o LineParser.o
	gcc -g -m32 -Wall -o exec task3.o LineParser.o

# Depends on the source and header files
task3.o: task3.c
	gcc -g -m32 -c -o task3.o task3.c 

LineParser.o: LineParser.c
	gcc -g -m32 -c -o LineParser.o LineParser.c 

#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f *.o exec
