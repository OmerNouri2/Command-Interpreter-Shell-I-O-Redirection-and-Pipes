// C program to demonstrate use of fork() and pipe()
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
  
int main()
{
    // There is a use of two pipes
    // First pipe to send input string from parent
  
    int fd[2];  // Used to store two ends
  
    char msg[] = "hello";
    char input_str[100];
    pid_t p;

    if (pipe(fd)==-1)
    {
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }
    

   // scanf("%s", input_str);
    p = fork(); // create chile process
    if (p < 0)
    {
        fprintf(stderr, "fork Failed" );
        return 1;
    }

    if(p == 0){
      close(fd[0]);
      write(fd[1], msg, strlen(msg));
      close(fd[1]);
    }

    
    // Parent process
    else if (p > 0)
    {
      char toPrint[strlen(msg)];
      close(fd[1]);
        int status;
        waitpid(p, &status, 0);
        read(fd[0], toPrint, strlen(msg));
        printf("%s\n" , toPrint);
        // Close both reading ends
        close(fd[0]);
        exit(1);
    }
}

  