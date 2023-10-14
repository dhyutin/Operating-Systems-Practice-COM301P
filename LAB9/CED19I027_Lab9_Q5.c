// N Sree Dhyuti
// CED19I027
// Lab 9 : Q5

// Inclusion of required libraries
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

// Global Variables
int arr[100];
int buffer[20];
int buffer_status[20];
int in = 0;
int out = 0;
int size;
sem_t a1_over,b1_over;

// Thread Functions
void * Thread1(void * arg)
{
    printf("a1 executed!!\n");
    sem_post(&a1_over);
    sem_wait(&b1_over);
    printf("a2 executed!!\n");
    return NULL;
}

void * Thread2(void * arg)
{
    printf("b1 executed!!\n");
    sem_post(&b1_over);
    sem_wait(&a1_over);
    printf("b2 executed!!\n");
    return NULL;
}

// Main
int main()
{
    // Create Threads
    pthread_t t1,t2;
    
    int r;
    
    sem_init(&a1_over,0,0);
    sem_init(&b1_over,0,0);
    
    pthread_create(&t1,NULL,Thread1,NULL);
    pthread_create(&t2,NULL,Thread2,NULL);
    
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
}


