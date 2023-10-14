// N Sree Dhyuti
// CED19I027
// OS Lab Endsem : Round Robin Scheduling

// Inclusion of required libraries
#include <stdio.h>

//global variables for ready queue
int front = -1;     
int rear = -1;   

// Queue Structure definition    
struct q
{
    //Function Prototypes
	void (*enqueue) (int* readyq, int x, struct q*, int n); 
    int (*dequeue) (int* readyq, struct q*, int n);       
    int (*isfilled) (int* readyq, struct q*, int n);
    int (*search) (int* readyq, struct q*, int n, int a);
};
//structure variables
void enqueue1(int* readyq, int x, struct q*, int n); 
int dequeue1(int* readyq, struct q*, int n);       
int isfilled1(int* readyq, struct q*, int n);  
int search1(int* readyq, struct q*, int n, int a);

// Function to sort the elements in 4 arrays consecutively : Bubble Sort
// Here arr1 is the array with respect to which the sorting is happening
// Eg : sort (AT, BT, PID, BT1, 1, num -1) means we are sorting the 4 arrays wrt Arrival Time and in the array range 1 to num-1
void sort(float* arr1, float* arr2, float* arr3, int* arr4, int start, int end)
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
		{
			return 1;
		}
	}
	return 0;
}

// Main
int main()
{
    struct q q1;
    // STRUCTURE ENCAPSULATION
    // Assigning Functions to the queue structure
    q1.enqueue = enqueue1;
    q1.dequeue = dequeue1; 
    q1.isfilled = isfilled1; 
    q1.search = search1;

	// Define required variables
	int num, time_quantum, p_flag = 0;
	float current_time = 0, avg_wt = 0, avg_tat = 0;
	
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
	int PID[num];
	float AT[num], BT[num], CT[num], WT[num], TAT[num];
	
	// Check Array : To update the Times left for each processes to reach completion
	float BT1[num];
	
	// Ready Queue - the queue which holds the names of all processes that are to be readily processed
	int readyq[num];

	// Take all necessary inputs from user 
	for(int i = 0; i < num; i++)
	{
		printf("Enter PID :");
		scanf("%d", &PID[i]);
		
		// Arrival time is 0 for all processes as mentioned in question
		AT[i] = 0;
		
		printf("Enter Burst Time of Process %d :", PID[i]);
		scanf("%f", &BT[i]);
		
		BT1[i] = BT[i];	
	}
	
	// As mentioned in the question, time_quantum is set to 2
	time_quantum = 2;
	
	// Sort all processes w.r.t Arrival Time
	sort(AT, BT, BT1, PID, 0, num);	
	
	while(check_array(BT1, num))
	{
		// Find all the processes whose arrival time < current time and enqueue them in ready queue
		int j = 0;
		for(j = 0; j < num; j++)
		{
			if(AT[j] > current_time)
			{
				break;
			}
			// If PID is not present in the queue, then enqueue
			if((!(q1.search(readyq, &q1, num, PID[j]))) && BT1[j] != 0 && PID[j] != p_flag)
			{
				q1.enqueue(readyq, PID[j], &q1, num);
			}
		}
		// Incase the previously processed process is still incomplete, enque it
		if(p_flag != 0)
		{
			if(!(q1.search(readyq, &q1,num, p_flag)))
			{
				q1.enqueue(readyq, p_flag, &q1, num);
			}
		}
		int a;
		// While the ready queue is filled with atleast one process...
		if(q1.isfilled(readyq, &q1, num))
		{
			// Dequeue a process from ready queue
			a = q1.dequeue(readyq, &q1, num);
			
			// Search for that process in the processes arrays using PID
			int i = 0;
			for (i = 0; i < num; i++)
			{
				if (PID[i] == a)
					break;
			}
			
			// Update current time, Time remaining for that process to complete accordingly
			if(BT1[i] > time_quantum)
			{
				current_time = current_time + time_quantum;
				BT1[i] = BT1[i] - time_quantum;
				p_flag = PID[i];
			}
			else
			{
				current_time = current_time + BT1[i];
				BT1[i] = 0;
				p_flag = 0;
				
				// When a process is completed, do all calculations
				CT[i] = current_time;
				TAT[i] = CT[i] - AT[i];
				WT[i] = TAT[i] - BT[i];
				
				avg_wt = avg_wt + (WT[i] / num);
				avg_tat = avg_tat + (TAT[i] / num);
			}
		}
		else
		{
			current_time = current_time + 1;
		}
	}
	
	// Print all details
	
	printf("-----------------------------------------------------------------\n \n");
	printf("PID            AT            BT            CT            TAT            WT\n");		
	for (int i = 0; i < num; i++)
	{	
		printf("%d      %f      %f     %f     %f     %f\n",PID[i], AT[i], BT[i], CT[i], TAT[i], WT[i]);
	}
	printf("-----------------------------------------------------------------\n \n");
	
	printf("Average Waiting Time : %f\n", avg_wt);
	printf("Average Turn Around Time : %f\n", avg_tat);
	
	return 0;			
}

// Structure Encapsulated function to enqueue an element into a queue
void enqueue1(int* readyq, int x, struct q* stk, int n) 
{
    // When queue is empty
	if(front == -1 && rear == -1) 
    {
        front = 0;
        rear = 0;
        readyq[rear] = x;
    }
    // When queue is full
    else if((rear + 1) % n == front) 
    {
        printf("Given circular queue is full.\n");
    }
    else 
    {
        rear = (rear + 1) % n;
        readyq[rear] = x;
    }
}

// Structure Encapsulated function to dequeue an element from a queue
int dequeue1(int* readyq, struct q* stk, int n)  
{
    //When queue is empty
	if(front == -1 && rear == -1) 
    {
        printf("No data has been inputted by user.\n");
        return -1;
    }
    // When only one element is left in queue
    else if(front == rear) 
    {
        int e = front;
        front = -1;
        rear = -1;
        return readyq[e];
    }
    else 
    {
        int e = front;
        front = (front + 1) % n;
        return readyq[e];
    }
}

// Structure Encapsulated function to check if a queue is filled or empty
int isfilled1(int* readyq, struct q* stk, int n) 
{
    //When queue is empty
	if(front == -1 && rear == -1) 
        return 0;
    else                
        return 1;
}

// Structure Encapsulated function to search for a particular element in the queue
int search1(int* readyq, struct q* stk, int n, int a)
{
	if(front == -1 && rear == -1)
		return 0;
	else
	{
		for(int i = front; i <= n; i++)
		{
			if(readyq[i%n] == a)
				return 1;
			i = i % n;
			if(i == rear)
				break;
		}
		return 0;
	}
}
