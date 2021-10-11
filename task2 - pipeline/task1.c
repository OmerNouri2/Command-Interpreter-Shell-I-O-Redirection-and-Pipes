// C program to demonstrate use of fork() and pipe()
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
  
int main(int argc, char **argv)
{
  
  int fd[2];  // Used to store two ends
  pid_t p1, p2;
  int debugMode = 0;

  for(int i=1; i<argc; i++){
      if(strcmp("-D",argv[i])==0)
          debugMode=1;
  }
  if (pipe(fd)==-1)
  {
      fprintf(stderr, "Pipe Failed\n" );
      return 1;
  }
  if(debugMode==1){
    fprintf(stderr, "(parent_process>forking…)\n");
  }
  p1 = fork(); // create chile process
  if(debugMode==1)
    fprintf(stderr, "(parent_process>created process with id: %d)\n", p1);
  
  if (p1 < 0){
      fprintf(stderr, "fork Failed\n" );
      return 1;
  }
  if(p1 == 0){ // child process
      close(STDOUT_FILENO);
      if(debugMode)
        fprintf(stderr,"(child1>redirecting stdout to the write end of the pipe…)\n");
      dup(fd[1]);
      close(fd[1]);
      char* const cmdArr[3] = { "ls", "-l", 0};
      if(debugMode)
        fprintf(stderr,"(child1>going to execute cmd: …)\n");
      execvp(cmdArr[0], cmdArr);
      // we won’t get here unless execvp failed 
      perror("execvp of ls failed\n");
      exit(1);
  }    
  else if (p1 > 0)    // Parent process
  { 
    if(debugMode==1)
      fprintf(stderr, "(parent_process>closing the write end of the pipe…)\n");
   close(fd[1]);
  }

  p2 = fork();
  if (p2 < 0)
  {
    fprintf(stderr, "fork Failed\n" );
    return 1;
  }
  if(p2 == 0){ // child process
    close(STDIN_FILENO);  // Close the standard output. // close(STDIN_FILENO)
    if(debugMode)
      fprintf(stderr,"(child2>redirecting stdin to the read end of the pipe…)\n");
    dup(fd[0]);
    close(fd[0]);
    char* const cmdArr2[4] = {"tail", "-n", "2", 0};
    if(debugMode)
      fprintf(stderr,"(child2>going to execute cmd: …)\n");
    execvp(cmdArr2[0], cmdArr2); 
    // we won’t get here unless execvp failed 
    perror("execvp fail\n");
    exit(1); 
  }
  else if (p2 > 0)    // Parent process
  {
    if(debugMode==1)
      fprintf(stderr, "(parent_process>closing the read end of the pipe…)\n");
    close(fd[0]);
    if(debugMode==1)
      fprintf(stderr, "(parent_process>waiting for child processes to terminate…)\n");
    waitpid(p1, NULL, 0);
    waitpid(p2, NULL, 0);
    if(debugMode==1)
      fprintf(stderr, "(parent_process>exiting…)\n");
    exit(0);
  }


}

  