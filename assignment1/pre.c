// Assignment 1: Due July 15th
// Written by: Kelby Webster (klw231)
// CS 4328 Summer session
// pre.c
//

#include<stdio.h>

int main()
{
    
    //declaring a 2d char array to store names of 10 students
    
    char studentNames[10][20];
    
    //declaring an array to store scores of 10 students
    
    double scores[10];
    
    //current count of students
    
    int count=0;
    
    printf("Enter name and gpa scores. To stop, press Ctrl+D :\n");
    //looping until eof is triggered (or when scanf does not read 2 values)
    
    //the read values are stored in the arrays
    
    
    
    while(scanf("%s %lf",&studentNames[count],&scores[count])==2){
        
        //incrementing count
        
        count++;
        
        //if the count reached 10, exiting loop automatically
        
        if(count==10){
            
            break;
            
        }
        
    }
    
    //now looping through the arrays
    
    for(int i=0;i<count;i++){
        
        //if score of current student is greater than or equal to 3, printing
        
        //his/her name
        
        if(scores[i]>=3.0){
            
            printf("%s\n",studentNames[i]);
            
        }
        
    }
    
    return 0;
    
}

