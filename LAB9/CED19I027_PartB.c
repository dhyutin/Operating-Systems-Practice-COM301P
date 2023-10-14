// N Sree Dhyuti
// CED19I027
// OS Lab Endsem : Part B : Producer Consumer

// Inclusion of required libraries
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Global Variables
pthread_t tid[2];

int counter;
int num = 1;
pthread_mutex_t lock;
  
void* func(void* arg)
{
    pthread_mutex_lock(&lock);
  
    unsigned long i = 0;
    counter += 1;
    if(counter == 1)
    {
    	printf("\n Word %d", num);
    printf("\n Searching primary Meaning\n");
    for (i = 0; i < (0xFFFFFFFF); i++);

    printf("\n Primary Meaning Searched\n");
    pthread_mutex_unlock(&lock);
  
    return NULL;
    }
    if (counter == 2)
    {
    printf("\n Searching secondary Meaning\n");
    for (i = 0; i < (0xFFFFFFFF); i++);
  
    printf("\n Secondary Meaning Searched\n");
    pthread_mutex_unlock(&lock);
  
    return NULL;
    }
    
}

// Main
int main(void)
{
    int i = 0;
    int err;

    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n Error\n");
        return 1;
    }
  
    while (i < 2) {
        err = pthread_create(&(tid[i]),NULL,&func, NULL);
        if (err != 0)
        {
        	printf("\nThread can't be created",strerror(err));
		}
        i++;
    }

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_mutex_destroy(&lock);

    return 0;
}
