// N Sree Dhyuti
// CED19I027
// Lab 6 : Q3

// Inclusion of required libraries
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include <math.h>

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
	    
	    // Check if it is armstrong number or not
	    char temp[25];
	    int s, t, l, r;
	    
	    for (int i = 0; i < n; i++)
	    {
	        s = 0;
	        t = p1_recv[i];
	        sprintf(temp, "%d", t);
	        l = strlen(temp);
	        
	        while(t > 0)
	        {
	            r = t % 10;
	            s = s + pow(r, l);
	            t = t / 10;
	        }
	        
	        if (s == p1_recv[i])
	            p2_send[i] = 1;
	        else
	            p2_send[i] = 0;
	    }
	    
	    // Send the array to parent
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
            
            printf("You are in parent process and integer array is as follows : \n");
            for ( int i = 0; i < n; i++)
            {
                printf("%d ", p1_send[i]);
            }
            printf("\n");
            
            // Write the array and send to child using pipe
            write(p1[1], p1_send, sizeof(p1_send) + 1);
            
            // Receive from child using pipe
            read(p2[0], p2_recv, sizeof(p2_recv) + 1);
            
            printf("Binary Array is now as follows : \n");
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
