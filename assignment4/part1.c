//
// Assignment 4: Due August 5th
// Written by: Kelby Webster (klw231)
// CS 4328 Summer session
// part1.c
//
// Write a program that takes a reference string and the number
// of frames as inputs to simulate page replacement algorithms.
// Suppose the maximum length of a reference string is 20 and there are 5 diffent
// numbers of pages. Randomly generate a reference string, e.g. 2 1 3 4 5 2 3 ...
// Take the number of frames as an input. Find out the different number of page
// faults using the Optimal and LRU algorithms.  If there is a tie, use the FIFO
// algorithm to break the tie. Print out the page replacement process and you
// can see how LRU differs from the optimal.



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>  // for srand call


// function to show frame table
void displayFrame(int arr[], int size)
{
    int i;
    
    for(i = 0; i < size; i++)
        printf("%d ", arr[i]);
    
        printf("\n");
}


void optimal(int arr[], int size, int frameNumber)
{
    // declare variables
    int frame[frameNumber];
    int i, j, k;
    int index = 0;
    int count;
    int farthest;
    int pageFault = 0;
    bool page[6] = {false};
    
    // looping through all pages in the reference string
    for( i = 0; i < size; i++)
    {
        // Check if there is a valid frame and current page
        if(index < frameNumber && !page[arr[i]])
        {
            frame[index++] = arr[i];
            page[arr[i]] = true;
            
            // Increment page fault
            pageFault++;
        }
        // Check if no valid frame and value not in page
        else if(index >= frameNumber && !page[arr[i]])
        {
            // variables
            count = 0;
            bool visited[6] = {false};
            
            // increment page fault
            pageFault++;
            
            // loop through pages to check ahead
            for (j = i + 1; ; j++)
            {
                // last frame
                if(count == frameNumber || j == size)
                    break;
                
                // If next page is present and has page value
                if(page[arr[j]] && !visited[arr[j]])
                {
                    farthest = arr[j];
                    visited[arr[j]] = true;
                    count++;
                }
            
            }
                // Display number being replaced
                printf("%d will be replaced\n", farthest);
                page[farthest] = false;
            
                // loop through frames
                for (k = 0; k < frameNumber; k++)
                {
                    if(frame[k] == farthest)
                        break;
                }
                // put page number into frame
                frame[k] = arr[i];
                page[arr[i]] = true;
            }
            // display current state
            displayFrame(frame, index);
        }
    
    int pageHit = 20 - pageFault;
    printf("\nPage fault = %d\nPage hit = %d \n\n", pageFault, pageHit);
    
}


void LRU(int arr[], int size, int frameNumber)
{
    // declare variables
    int frame[frameNumber];
    int i, j, k;
    int index = 0;
    int count;
    int lru;
    int pageFault = 0;
    bool page[6] = {false};
    
    // For every page number in the reference string
    for(i = 0; i < size; i++)
    {
        // Check if there is a valid frame open and current page not present
        if((index < frameNumber) && (!page[arr[i]]))
        {
            //Put page number in frame and mark value as true
            frame[index++] = arr[i];
            page[arr[i]] = true;
            
            // Increment page fault
            pageFault++;
        }
        // Check if no valid frame and value not in page
        else if((index >= frameNumber) && (!page[arr[i]]))
        {
            // variables
            count = 0;
            bool visited[6] = {false};
            
            // increment page fault
            pageFault++;
            
            // check for least recently used/previous page value
            for(j = i-1; ; j--)
            {
                // first frame
                if((count == frameNumber) || (j < 0))
                    break;
                
                // If page and its not a previously visited page
                if(page[arr[j]] && !visited[arr[j]])
                {
                    // assign as LRU and mark true
                    lru = arr[j];
                    visited[arr[j]] = true;
                    count++;
                }
            }
            
            // Display number being replaced
            printf("%d will be replaced\n", lru);
            page[lru] = false;
            
            // loop through frames
            for(k = 0; k < frameNumber; k++)
            {
                if(frame[k] == lru)
                    break;
            }
            // put page number into frame
            frame[k] = arr[i];
            page[arr[i]] = true;
            
        }
        // display current state
        displayFrame(frame, index);
        
    }
    
    int pageHit = 20 - pageFault;
    printf("\nPage fault = %d\nPage hit = %d \n\n", pageFault, pageHit);
    
}

void FIFO(int arr[], int size, int frameNumber)
{
    // declare variables
    int frame[frameNumber];
    int i;
    int index = 0;
    int pageFault = 0;
    bool page[6] = {false};
    
    for(i = 0; i < size; i++)
    {
        // if page is not found
        if(!page[arr[i]])
        {
            pageFault++;
            
            // replacement scheme
            if(index >= frameNumber)
            {
                printf("%d will be replaced\n", frame[index%frameNumber]);
                page[frame[index%frameNumber]] = false;
            }
            
            // page now true/able to be found later
            frame[index%frameNumber] = arr[i];
            index++;
            page[arr[i]] = true;
        }
        
        if(index < frameNumber)
            displayFrame(frame, index);
        
        else displayFrame(frame, frameNumber);
        
    }
    int pageHit = 20 - pageFault;
    printf("\nPage fault = %d\nPage hit = %d \n\n", pageFault, pageHit);
}


int main()
{

    int frameNumber = 0;
    // prompt user for frame number
    printf("Enter frame number : ");
    scanf("%d", &frameNumber);
    
    int i;
    int arr[frameNumber];
    bool page[6] = {false};
    
    // make array for random reference string
    int randomArray[20];
    // creates random numbers each time program is called
    srand(time(0));
    
    for(i = 0; i < 20; i++)
    {
        // assigning random numbers to reference string array
        randomArray[i] = rand()%5+1;
    }
    
    // display reference string
    displayFrame(randomArray, 20);
    printf("\n");
    
    // display page replacement
    printf("//////////OPTIMAL//////////\n");
    optimal(randomArray, 20, frameNumber);
    
    printf("//////////LRU//////////\n");
    LRU(randomArray, 20, frameNumber);
    
    printf("//////////FIFO//////////\n");
    FIFO(randomArray, 20, frameNumber);
    
    
    return 0;
}
