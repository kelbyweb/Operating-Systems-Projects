//
// Assignment 3: Due July 29th
// Written by: Kelby Webster (klw231)
// CS 4328 Summer session
// part2.c
//
// b. Write the program again considering the mutual exclusion. Run the
//program several times to show that mutual exclusion is guaranteed.


#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>


// struct for award
struct awardAmount
{
    int currentAmount;
    int given;
};

// create instance of struct
struct awardAmount award;

// student function
void student (char c);

// create mutex for mutual exclusion
pthread_mutex_t mutex;

int main()
{
    // starting values
    award.currentAmount = 4000;
    award.given = 0;
    
    // create threads
    pthread_t thread1, thread2, thread3;
    
    // initialize threads
    pthread_create(&thread1, NULL, (void *(*)(void *)) student, (void*) '1');
    pthread_create(&thread2, NULL, (void *(*)(void *)) student, (void*) '2');
    pthread_create(&thread3, NULL, (void *(*)(void *)) student, (void*) '3');
    
    // have threads wait for completion of other threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    
    
    printf("Total amount awarded: $ %d \n\n", award.given);
    
    pthread_exit(0);
}


void student(char c)
{
    // initialize variables
    int total = 0;
    int temp;
    
    // lock for mutual exclusion
    pthread_mutex_lock(&mutex);
    
    // loop while there is still money available
    while( 0 < award.currentAmount)
    {
        // adjust award amount
        temp = ceil(award.currentAmount * 0.25);
        // increment current amount
        award.currentAmount = award.currentAmount - temp;
        // increment total amount remaining
        total = total + temp;
        // show results
        printf("%c = %d \n", c, temp);
        
        // sleep
        sleep(1);
        
        // unlock mutex
        pthread_mutex_unlock(&mutex);
    }
    
    award.given = award.given + total;
}
