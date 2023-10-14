// N Sree Dhyuti
// CED19I027
// Lab 9 : Q2

// Inclusion of required libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Global Variable
int sum;

// Thread Function
void *thread_fn(void *arg)
{
    int n = (intptr_t) arg;
	int i;
	for (i=0; i<=n; i++)
		printf("%d \n",i);
	return NULL;
}

// Main
int main()
{
	// Threads
	pthread_t t1;
	
	// User Inputs
	int n;
	printf("enter value of n: ");
	scanf("%d", &n);
	
	// Create Thread
	pthread_create(&t1, NULL, thread_fn, (void*)n);	
	pthread_join(t1,NULL);
	
	return 0;
}
