// N Sree Dhyuti
// CED19I027
// Lab 9 : Q4

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

pthread_mutex_t binary;
sem_t full;
sem_t empty;

// Thread Functions
void * Producer(void * arg)
{
    int check = 1;
    int produce,r;
    for(int i = 0; i < size; i++)
    {
       produce = arr[i];
       sem_wait(&empty);
       pthread_mutex_lock(&binary);
       buffer[in] = produce;
       printf("The producer produced item %d\n",buffer[in]);
       in = (in + 1) % 20;
       pthread_mutex_unlock(&binary);
       sem_post(&full);
       sleep(2);
    }
    return NULL;
}

void * Consumer(void * arg)
{
    int check = 1;
    int r,consume;
    for(int i = 0; i < size; i++)
    {
       sem_wait(&full);
       pthread_mutex_lock(&binary);
       consume = buffer[out];
       out = (out + 1) % 20;
       printf("The consumer consumed %d\n", consume);
       pthread_mutex_unlock(&binary);
       sem_post(&empty);
       sleep(2);
    }
    return NULL;
}

// Main
int main()
{
    // Create Threads
	pthread_t t1, t2;
	
    int r;
    printf("Enter the No of elements to insert in buffer : ");
    scanf("%d",&size);
    printf("Enter the elements in buffer : \n");
    for(int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }
    
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, 5);
    
    pthread_create(&t1, NULL, Producer, NULL);
    pthread_create(&t2, NULL, Consumer, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}

