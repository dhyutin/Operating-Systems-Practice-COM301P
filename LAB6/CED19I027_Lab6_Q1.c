// N Sree Dhyuti
// CED19I027
// Lab 6 : Q1

// Inclusion of required libraries
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>

// Main
int main()
{
	// Create a pid for calling fork() function
	pid_t pid;
	
	//Create pipe1 and pipe2
	int p1[2], p2[2];
	
	// Strings to send and receive messages between parent and child processes
	char p1_send[100], p1_recv[100];
	int p2_send, p2_recv;

	if(pipe(p1)== -1 || pipe(p2))     //creating pipe1 and pipe2
	{
		printf("\n Pipe1 not created");
		return 1;
	}
	
	// Take input string from user
	printf("Enter string : ");
	scanf("%s",p1_send);
	
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
	    
	    // Calculate ASCII SUM
	    int i = 0, j = 0;
	    
	    for (i = 0; p1_recv[i] != '\0'; i++)
	    {
	        j = j  + p1_recv[i];
	    }
	    
	    p2_send = j;
	    
	    write(p2[1], &p2_send, sizeof(p2_send) + 1);	    
	}
	// Parent Process
	else if (pid > 0)
	{
            // Close child write and parent read
            close(p2[1]);
            close(p1[0]);
            
            write(p1[1], p1_send, sizeof(p1_send) + 1);
            
            read(p2[0], &p2_recv, sizeof(p2_recv) + 1);
            
            printf("ASCII sum of the string = %d\n", p2_recv);
	}
	
	// Error
	
	else 
	{
	    printf("Error creating a child process\n");
	}
	
	// End program
	return 0;
}
