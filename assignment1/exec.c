// Assignment 1: Due July 15th
// Written by: Kelby Webster (klw231)
// CS 4328 Summer session
// exec.c
//3. Write a program to take a UNIX command from the command line
//and fork() a child to execute it. The command can be a simple
//command like: $ls or $ps, Or it can be a command with options such as
//$ls -t -l. Use argc and argv[] in the main function to pass parameters.
//When the child process is executing the command, the parent process
//simply waits for the termination of the child process. The process
//id of the parent and the child should be printed out using getpid() and
//getppid() functions.

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

//start of main function with command line argument

int main(int argc, char *argv[])

{
    
    //display message if invalid argument are passed
    
    if(argc > 2 || argc < 1)
        
    {
        
        printf("Invalid argument passed\n");
        
    }
    
    //variable data type declaration
    int n;
    int pid;
    int count = 0;
    int status;
    
    //call to fork
    pid = fork();
    
    //if pid is zero then child process will be created
    if(pid == 0)
    {
        printf("The child process is running:\n");
    
    //print the pid and ppid of the process
        
    printf("This is the child process.. pid of the child is %d and parent id is %d\n", getpid(),getppid());
        
    printf("running the %s command..", argv[1]);
        
    system(argv[1]);

    }
    
    //if creation of child failed then print this message
    else if(pid == -1)
    {
        printf("call to fork failed");
    }
    
    else
        
    {
    //wait for child to complete
        wait(&status);
           
    }
    
    return 0;
    
}

