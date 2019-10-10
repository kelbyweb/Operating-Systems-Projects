// Assignment 1: Due July 15th
// Written by: Kelby Webster (klw231)
// CS 4328 Summer session
// sort.c

//2). The second program "sort.c" reads in a list of names from stdin and
//outputs them in an alphabetical order. Assume there are no more than 10
//names and the sequence is read until an EOF is encountered.
//
//For the above example, the output should be:
//
//John
//Mary
//Susan


#include<stdio.h>
#include<string.h>
#define size 100

void alphabetical_order(int n); // alphabetical_order() Function Prototype

int main()
{
    int n;
    
    printf("\n Enter the number of names you want to sort (up to 10): ");
    scanf("%d",&n);
    printf("\n");
    alphabetical_order(n);
    printf("\n");
} // End of main


// alphabetical_order() function
void alphabetical_order(int n)
{
    char list[n][20];
    char temp[20];
    int i,j;
    
    for(i = 0; i < n; i++)
        scanf("%s",list[i]);
    
    for(i = 0; i < n-1; i++)
        for(j = i+1; j < n; j++)
        {
            if(strcmp(list[i], list[j]) >0)
            {
                strcpy(temp, list[i]);
                strcpy(list[i], list[j]);
                strcpy(list[j], temp);
            }
        }
    printf("\n Names sorted in alphabetical order: ");
    for(i = 0; i < n;++i)
    {
        printf("\n %s",list[i]);
    }
}
