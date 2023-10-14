// N Sree Dhyuti
// CED19I027
// Lab 9 : Q1

// Inclusion of required libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


int sum[5];

// Thread Function
void *thread_fn (void * arg)
{
    int id = (intptr_t) arg;
    int start = id * 200;
    int i;

    for(i = 1; i <= 200; i++)
    {
	    sum[id] += (i + start);
    }
    return NULL;
}

// Main
int main()
{
    pthread_t t1, t2, t3, t4, t5;

    pthread_create(&t1, NULL, thread_fn, (void *)0);
    pthread_create(&t2, NULL, thread_fn, (void *)1);
    pthread_create(&t3, NULL, thread_fn, (void *)2);
    pthread_create(&t4, NULL, thread_fn, (void *)3);
    pthread_create(&t5, NULL, thread_fn, (void *)4);


    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);
    
    int final_sum = sum[0] + sum[1] + sum[2] + sum[3] + sum[4];
    printf("%d\n", final_sum);
    return 0;
}
