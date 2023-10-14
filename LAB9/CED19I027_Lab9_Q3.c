// N Sree Dhyuti
// CED19I027
// Lab 9 : Q3

// Inclusion of required libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Size of array
int n = 0;

// Thread Function 
void *myThreadFun(void *vargp)
{
	sleep(1);

	int* array = vargp;
	
	// Initiating a result variable which can be returned to main()
	int *  result = malloc(sizeof(int));
	
	printf("Inside the thread \n");
	
	// Calculate array sum
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum = sum + array[i];
	}
	
	*result = sum;
	
	printf("Sum is calculated and sent to main function!\n");
	// Return sum to main
	return (void*) result;
}

// Main
int main()
{
	// Create a thread
	pthread_t thread_id;
	
	printf("Inside Main Function before thread began....\n");
	
	int * result;
	
	// Taking inputs from user
	printf("Enter size of array : ");
	scanf("%d", &n);
	
	while(n < 2)
	{
		printf("Size of array should be greater than 2!!\n RESTARTING PROGRAM\n");
		main();
	}
	
	int array[n];
	
	for (int i = 0; i < n; i++)
	{
		printf("Enter array value %d : ", i + 1);
		scanf("%d", &array[i]);
	}
	
	int * ptr = array;
	
	// Pass the array to thread function using pointers
	pthread_create(&thread_id, NULL, myThreadFun, ptr);
	
	// The return value of thread will be stored in "result" variable
	pthread_join(thread_id, (void**) &result);
	
	printf("Inside Main Function after thread began....\n");
    printf("SUM = %d\n", *result);
    
	exit(0);
}
