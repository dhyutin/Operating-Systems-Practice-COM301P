// N Sree Dhyuti
// CED19I027
// Lab 6 : Q2

// Inclusion of required libraries
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <string.h>

// Main
int main()
{
	// Create a pid for calling fork() function
	pid_t pid;
	
	//Create pipe1 and pipe2
	int p1[2], p2[2];

	if(pipe(p1)== -1 || pipe(p2))     //creating pipe1 and pipe2
	{
		printf("\n Pipe1 not created");
		return 1;
	}
	
	// Take input string from user
	int n;
	printf("Enter the size of integer array : ");
	scanf("%d", &n);

	// int arrays to send and receive messages between parent and child processes
	int p1_send[n], p1_recv[n], p2_send[n], p2_recv[n];
	
	// Create child process using fork
	pid = fork();
	
	// Child Process
	if (pid == 0)
	{
	    //close child read and parent write
	    close(p2[0]);
	    close(p1[1]);
	    
	    // Read the string using pipe
	    read(p1[0], p1_recv, sizeof(p1_recv) + 1);
	    
	    printf("You are in child process. The received array from parent process after sorting is as follows : \n");
	    for(int i = 0; i < n; i++)
	    {
	        printf("%d ", p1_recv[i]);
	        // Making the array in descending order
	        p2_send[n - i - 1] = p1_recv[i];
	    }	
	    printf("\n");
	    
	    // Send the descending order array to parent
	    write(p2[1], p2_send, sizeof(p2_send) + 1);    
	}
	// Parent Process
	else if (pid > 0)
	{
            // Close child write and parent read
            close(p2[1]);
            close(p1[0]);
            
            // Take the array inputs
            for (int i = 0; i < n; i++)
            {
                printf("Enter integer %d : ", i + 1);
                scanf("%d", &p1_send[i]);
            }
            
            // Sort the integer array in ascending order
            for ( int i = 0; i < n - 1; i++)
            {
                for (int j = i + 1; j < n; j++)
                {
                    if (p1_send[i] > p1_send[j])
                    {
                        int temp = p1_send[i];
                        p1_send[i] = p1_send[j];
                        p1_send[j] = temp;
                    }
                }
            }
            
            printf("You are in parent process and ascending order of the integer array is as follows : \n");
            for ( int i = 0; i < n; i++)
            {
                printf("%d ", p1_send[i]);
            }
            printf("\n");
            
            // Write the array and send to child using pipe
            write(p1[1], p1_send, sizeof(p1_send) + 1);
            
            // Receive from child using pipe
            read(p2[0], p2_recv, sizeof(p2_recv) + 1);
            
            printf("Received the descending ordered array from child process. Array is now as follows : \n");
            for ( int i = 0; i < n; i++)
            {
                printf("%d ", p2_recv[i]);
            }
            printf("\n");
	}

	// Error
	else 
	{
	    printf("Error creating a child process\n");
	}
	
	// End program
	return 0;
}
