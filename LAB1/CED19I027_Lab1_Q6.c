// N Sree Dhyuti
// CED19I027
//Lab 1 : Q6 
// Inclusion of required libraries
#include <stdio.h>

// Main
int main()
{
	// Define required variables
	//integer variable : "num" and integer-array variable : "arr"
	int num, arr[] = {1, 2, 3, 4, 5, 6};
	
	// Pointer 
	int *pointer;
	
	// Assign value to the integer
	num = 15;
	
	// Pointer is storing the address of the integer "num". '&' implies address.
	pointer = &num;
	
	printf("PRINT THE VALUE AND ADDRESS OF INTEGER VARIABLE \n \n");
	
	// Print the "value being" pointed by the pointer.
	printf("Value of the integer variable = %d \n", *pointer);
	
	// Print the address of integer which is stored in "pointer"
	printf("Address of the integer variable = %d \n", pointer);
	
	printf("-----------------------------------------------------------------\n \n");
	
	// Find size of the array. 'size_t' is a data type that measures the size of the variables handled in bytes.
	size_t arr_size = sizeof(arr) / sizeof(arr[0]);
	
	// "pointer" now points to the integer array
    pointer = arr;

	printf("ACCESSING ELEMENTS OF ARRAY USING POINTERS \n \n");
	// Accessing elements using pointers
	for ( int i = 0; i < arr_size; i++)
	{
		printf("Value of array element %d = %d \n", i, *(pointer + i));
		printf("Address of array element %d = %d \n \n", i, (pointer + i));
	}
	
	return 0;
}
