// N Sree Dhyuti
// CED19I027
// Lab 4 : Q1

// Inclusion of required libraries
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;
	pid = fork();
	pid = fork();
	printf("hi\n");
	
	return 0;
}

