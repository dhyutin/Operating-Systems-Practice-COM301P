// N Sree Dhyuti
// CED19I027
// Lab 5 : Q2

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
	char p1_send[100], p1_recv[100], p2_send[100], p2_recv[100];

	if(pipe(p1)== -1 || pipe(p2))     //creating pipe1 
	{
		printf("\n Pipe1 not created");
		return 1;
	}
	
	// Fork function call 
	pid = fork();	
	
	// For Child Process    
	if (pid == 0)
	{
	    //close child read and parent write
	    close(p2[0]);
	    close(p1[1]);  
	    
	    // Receive string
	    read (p1[0], p1_recv, sizeof(p1_recv) + 1);
	    
	    char childstr[100];
	    printf("Enter child string : ");
	    scanf("%s",childstr);
	    
	    // Concatenate
	    strcpy(p2_send, p1_recv);
	    strcat(p2_send, childstr);
	    
	    // Send the reversed string
	    write(p2[1], p2_send, sizeof(p2_send) + 1);

	}
	// Error
	else if (pid < 0)
	{
	    printf("Failed to execute fork() for a while. \n");
	}
	// For Parent Process
	else
	{
	    //Close parent read (p1[0]) and child write (p2[1])
	    close(p2[1]);
	    close(p1[0]);
	    
	    // User Inputs
	    printf("Enter parent string : ");
	    scanf("%s",p1_send);
	    
	    // Send string
	    write(p1[1], p1_send, sizeof(p1_send)+1);
	    
	    // Receive reversed string from child
	    read(p2[0], p2_recv, sizeof(p2_recv) + 1);  //parent reading from pipe2
	    printf("Received concatenated string :  %s\n",p2_recv); 
	}

	return 0;
}