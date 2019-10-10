#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv){
    int pid;
    int status;
    
    pid = fork();
    
    //error
    if(pid < 0){
        printf("There was an issue forking.\n");
        exit(1);
    } else if(pid == 0){
        //Child
        //printf("\nChild process has started.\n");
        printf("Executing %s command.\n", argv[1]);
        printf("Command results:\n");
        
        //have system execute command
        system(argv[1]);
        printf("Child process is complete.\n");
    } else{
        //parent process
        //printf("Parent process has started.\n");
        
        wait(&status);//wait for child to exit and store child's exit status
        
        //print ids of processes
        printf("\nParent process has finished.\n");
        printf("Child process id is: %d and parent process id is: %d.\n", getpid(), getppid());
    }
    
    
    return 0;
}
