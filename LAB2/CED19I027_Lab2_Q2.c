// N Sree Dhyuti
// CED19I027
// Lab 2 : Q2

// Inclusion of required libraries
#include <stdio.h>


// Function to sort the elements in 3 arrays consecutively : Bubble Sort
// Here arr1 is the array with respect to which the sorting is happening
// Eg : sort (AT, BT, PID, 1, num -1) means we are sorting the 3 arrays wrt Arrival Time and in the array range 1 to num-1
void sort(float* arr1, float* arr2, float* arr3, int start, int end)
{
	int a, b;
	for(a = start; a < end - 1; a++)
	{
		for(b = a; b < end; b++)
		{
			if(arr1[a] > arr1[b])
			{
				float temp;
				// Swap
				temp = arr1[b]; arr1[b] = arr1[a]; arr1[a] = temp;
				
				temp = arr2[b]; arr2[b] = arr2[a]; arr2[a] = temp;
				
				temp = arr3[b]; arr3[b] = arr3[a]; arr3[a] = temp;
			}
		}
	}	
}

// Main
int main()
{
	// Define required variables
	int num, j;
	float current_time=0,avg_wt = 0, avg_tat = 0;
	printf("Number of Processes : ");
	scanf("%d", &num);
	
	// Incase the user types a negative value for num
	if(num < 0)
	{
		printf("Invalid Number of processes. Try again\n");
		main();
	}
	
	// Create arrays for storing Process ID, Arrival Time and Burst Time
	// CT (Completion Time, WT (Waiting Time), TAT (Turn Around Time)
	float PID[num], AT[num], BT[num], CT[num], WT[num], TAT[num];

	
	// Take all necessary inputs from user 
	for(int i = 0; i < num; i++)
	{
		printf("Enter PID :");
		scanf("%f", &PID[i]);
		
		printf("Enter Arrival Time of Process %f :", PID[i]);
		scanf("%f", &AT[i]);
		
		printf("Enter Burst Time of Process %f :", PID[i]);
		scanf("%f", &BT[i]);		
	}
	


	
	for(int i = 0; i < num; i++)
	{
		// Sort the arrays w.r.t Arrival Time 
	    // Bubble Sort used here
		sort(AT,PID,BT,i,num);
		
		while (current_time < AT[i])
		{
			current_time = current_time + 1;
		}
	
	    // Find the process with least BT which has AT <= current_time
	    for(j = i; j < num; j++)
	    {
	    	if(AT[j] > current_time)
	    		break;
		}
		if(i + j - 1 != num)
			j = j - 1;
		
		//Sort the selected range wrt Burst Time
		sort(BT, PID, AT, i, j + 1);
		
		current_time = current_time + BT[i];
		CT[i] = current_time;
	    TAT[i] = CT[i] - AT[i];
	    avg_tat = avg_tat + TAT[i];
	    WT[i] = TAT[i] - BT[i];
	    avg_wt = avg_wt + WT[i];
	}
	
	// Print all details
	
	printf("-----------------------------------------------------------------\n \n");
	printf("PID            AT            BT            CT            TAT            WT\n");		
	for (int i = 0; i < num; i++)
	{	
		printf("%f      %f      %f     %f     %f     %f\n",PID[i], AT[i], BT[i], CT[i], TAT[i], WT[i]);
	}
	printf("-----------------------------------------------------------------\n \n");
	
	printf("Average Waiting Time : %f\n", avg_wt / num);
	printf("Average Turn Around Time : %f\n", avg_tat / num);
	
	return 0;	
}
