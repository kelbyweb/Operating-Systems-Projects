// Assignment 2: Due July 22nd
// Written by: Kelby Webster (klw231)
// CS 4328 Summer session
// lab2.c
//

//Write a small shell - called shhh - that has the
//following capabilities:
//
//1. Can execute a command with the accompanying arguments.
//2. Recognize multiple pipe requests and handle them.
//3. Recognize redirection requests and handle them.
//4. Type "exit" to quit the shhh shell.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>  // file control options

//define variables
#define READ 0
#define WRITE 1

int main()
{
    //Given code
    char *argv[20], buf[80], n, *p;
    int m, status, inword, continu;
    
    
    
    while(1) {
        inword = 0;
        p = buf;
        m = 0;
        continu = 0;
        
        printf( "\nshhh> ");
        while( ( n = getchar() ) != '\n' || continu ) {
            if( n == ' ' ) {
                if (inword) {
                    inword = 0;
                    *p++ = 0;
                }
            }
            else if ( n == '\n' )
                continu = 0;
            else if ( n == '\\' && !inword )
                continu = 1;
            else {
                if ( !inword ) {
                    inword = 1;
                    argv[m++] = p;
                    *p++ = n;
                }
                else
                    *p++ = n;
            }
        }
        
        *p++ = 0;
        argv[m] = 0;
        
        if( strcmp(argv[0],"exit") == 0 ) exit (0);
        // End of given code
        
        // declare paths
        char *inputPath;
        char *outputPath;
        int arguments[20] = {0};
        
        //Variables for command handling
        int count = 0;
        int pipes = 0;
        int pid = 0;
        int inFlag = 0;
        int outFlag = 0;
        int rightPipe[2];
        int leftPipe[2];
        int index = 0;
        
        // Input redir section
        while(argv[count] != 0) {
            if( strcmp( argv[count], "|") == 0) {
                //pipe handling
                argv[count] = 0;
                arguments[pipes + 1] = count + 1;
                ++pipes;
                }
            else if( strcmp(argv[count], "<" ) == 0) {
                //input redir
                inputPath = strdup(argv[count + 1]);
                argv[count] = 0;
                argv[count + 1] = 0;
                inFlag = 1;
                
                //Increment to allow for output redir
                count++;
                }
            else if( strcmp(argv[count], ">" ) == 0) {
                //output redir
                outputPath = strdup(argv[count + 1]);
                argv[count] = 0;
                argv[count + 1] = 0;
                outFlag = 1;
                
                //Increment to allow for input redir
                count++;
                }
            else
                arguments[count] = count;
            
            ++count;
        }
        
        //Loop through all pipes and execute commands
        for(index; index <= pipes; index++) {
            //Create right pipe
            if( (pipes > 0) && (index != pipes))
                pipe(rightPipe); //right pipe becomes next's child's left pipe
            
            // execute commands
            switch (pid = fork()) {
                case -1:
                    //error
                    perror("The fork has failed!");
                    break;
                case 0:
                    //child process
                    //Redir and execute
                    if ((index == 0) && (inFlag == 1)) {
                        // read in input file
                        int inFile = open(inputPath, O_RDONLY, 0400);
                        if(inFile == -1) {
                            perror("The input file has failed!\n");
                            return(EXIT_FAILURE);
                        }
                        close(READ);
                        dup(inFile);
                        close(inFile);
                    }
                    
                    if ((index == pipes) && (outFlag == 1)) {
                        // create/write output file if it does not exist
                        int outFile = open(outputPath, O_WRONLY | O_CREAT, 0755);
                        if(outFile < 0) {
                            perror("The output file has failed!\n");
                            return(EXIT_FAILURE);
                        }
                        close(WRITE);
                        dup(outFile);
                        close(outFile);
                    }
                    
                    //manage pipes
                    if (pipes > 0) {
                        // 1st child process
                        if (index == 0) {
                            close(WRITE);
                            dup(rightPipe[WRITE]);
                            close(rightPipe[WRITE]);
                            close(rightPipe[READ]);
                            }
                        else if ( index < pipes){
                            // 2nd child process
                            close(READ);
                            dup(leftPipe[READ]);
                            close(leftPipe[READ]);
                            close(leftPipe[WRITE]);
                            close(WRITE);
                            dup(rightPipe[WRITE]);
                            close(rightPipe[READ]);
                            close(rightPipe[WRITE]);
                            }
                        else{
                            // last child process
                            close(READ);
                            dup(leftPipe[READ]);
                            close(leftPipe[READ]);
                            close(leftPipe[WRITE]);
                        }
                    }
                    execvp(argv[arguments[index]], &argv[arguments[index]]);
                    perror("The command failed to execute!\n");
                    break;
                default:
                    // parent process
                    if (index > 0) {
                        close(leftPipe[READ]);
                        close(leftPipe[WRITE]);
                    }
                    
                    leftPipe[READ] = rightPipe[READ];
                    leftPipe[WRITE] = rightPipe[WRITE];
                    
                    // Wait for child
                    wait(&status);
                    break;
            }
        }
    }
    
    return 0;
}
