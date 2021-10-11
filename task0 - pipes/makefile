# All Targets
all: exec

# Tool invocations
# Executable "exec" 
exec:  pipe.o
	gcc -g -m32 -Wall -o exec pipe.o

# Depends on the source and header files
pipe.o: pipe.c
	gcc -g -m32 -c -o pipe.o pipe.c 

#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f *.o myShell
