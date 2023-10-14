// N Sree Dhyuti
// CED19I027
// Lab 3 : Q1

// Inclusion of required libraries
#include <stdio.h>


// Function to sort the elements in 5 arrays consecutively : Bubble Sort
// Here arr1 is the array with respect to which the sorting is happening
// Eg : sort (AT, BT, PID, P, BT1, 1, num -1) means we are sorting the 5 arrays wrt Arrival time and in the array range 1 to num-1
void sort(float* arr1, float* arr2, float* arr3, float* arr4, float* arr5, int start, int end)
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
				temp = arr4[b]; arr4[b] = arr4[a]; arr4[a] = temp;
				temp = arr5[b]; arr5[b] = arr5[a]; arr5[a] = temp;
			}
		}
	}	
}

// Function to check if an array has all values as zero or not
int check_array(float* arr, int num)
{
	for(int i = 0; i < num; i++)
	{
		if(arr[i] != 0)
			return 1;
	}
	return 0;
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
	
	// Create arrays for storing Process ID, Arrival time and Burst time
	// CT (Completion time, WT (Waiting time), TAT (Turn Around time), P (Priority Value)
	float PID[num], AT[num], BT[num], P[num], CT[num], WT[num], TAT[num];
	
	// Check Array : To update the times left for each processes to reach completion
	float BT1[num];

	// Take all necessary inputs from user 
	for(int i = 0; i < num; i++)
	{
		printf("Enter PID :");
		scanf("%f", &PID[i]);
		
		printf("Enter Arrival time of Process %f :", PID[i]);
		scanf("%f", &AT[i]);
		
		printf("Enter Burst time of Process %f :", PID[i]);
		scanf("%f", &BT[i]);
		
		BT1[i] = BT[i];
		
		printf("Enter Priority Value of Process %f :", PID[i]);
		scanf("%f", &P[i]);		
	}
	printf("OUTPUTS : \n\n");
	// While we have atleast one process which is not completed... 
	while (check_array(BT1, num))
	{
		// Sort the data based on Arrival time 
		sort(AT,BT,PID,P,BT1,0,num);
		
		// Find all the processes whose arrival time < current time
		int j = 0;
		for(j = 0; j < num; j++)
		{
			if(AT[j] > current_time)
				break;
		}
		
		//Sort those processes being considered according to their Priority Value
		// Highest priority element will be in the j-1 th position
		sort(P, AT, BT, PID, BT1, 0, j);
		j = j - 1;
		
		// Find the process which has the highest priority among incomplete processes
		while (BT1[j] == 0)
		{
			j = j - 1;
		}
		
		// Check if two or more processes have the same priority values
		// Incase they do, choose the process with Least Arrival time to reduce the Overall Average Waiting time
		int k = j;
		int min_at = k;
		while (P[k] == P[k - 1])
		{
			if(AT[k] <= AT[min_at] && BT1[k] != 0)
			{
				min_at = k;
			}
			k--;
		}
		if(AT[k] <= AT[min_at] && BT1[k] != 0)
		{
			min_at = k;
		}
		
		BT1[min_at] = BT1[min_at] - 1;
		
		current_time = current_time + 1;
		
		printf("From time = %f to time = %f, \n Undergoing Process %f....\n", current_time - 1, current_time, PID[min_at]);
	    printf("-----------------------------------------------------------------\n \n");
		
		if (BT1[min_at] == 0)
		{
			// Other Calculations
			CT[min_at] = current_time;
			TAT[min_at] = CT[min_at] - AT[min_at];
			WT[min_at] = TAT[min_at] - BT[min_at];
			
			avg_wt = avg_wt + WT[min_at]/num;
			avg_tat = avg_tat + TAT[min_at]/num;
		}
	}
	
	// Print all details
	
	printf("-----------------------------------------------------------------\n \n");
	printf("PID            AT            BT            CT            TAT            WT\n");		
	for (int i = 0; i < num; i++)
	{	
		printf("%f      %f      %f     %f     %f     %f\n",PID[i], AT[i], BT[i], CT[i], TAT[i], WT[i]);
	}
	printf("-----------------------------------------------------------------\n \n");
	
	printf("Average Waiting time : %f\n", avg_wt);
	printf("Average Turn Around time : %f\n", avg_tat);
	
	return 0;	
}
