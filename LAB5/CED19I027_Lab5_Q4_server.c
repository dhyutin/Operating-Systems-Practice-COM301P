// N Sree Dhyuti
// CED19I027
// Lab 5 : Q4 Server

// Inclusion of required libraries
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
  
#define FILLED 0
#define Ready 1
#define NotReady -1
  
struct memory 
{
    //message
    char msg[100]; 
    //pids of both processes and status for synchronization
    int status, pid1, pid2;
}*ptr;

// Function to print message from client
void handler(int signum)
{
    // if TRUE, then server receives a message from client
    if (signum == SIGUSR1) 
    {
        printf("Received message from CLient: ");
        puts(ptr->msg);
    }
}
  
int main()
{
    // pid for server
    int pid = getpid();
    
    // key value of shared memory
    int key = 14534;
   
    //while loop condition
    int codn = 0;
     
    //SM create
    int shmid = shmget(key, sizeof(struct memory), IPC_CREAT | 0666);
  
    //attach SM
    ptr = (struct memory*)shmat(shmid, NULL, 0);
  
    //store the process id of server in SM
    ptr->pid1 = pid;
    ptr->status = NotReady;
   
    // calling the signal function using signal type SIGUSER1
    signal(SIGUSR1, handler);
  
    while (codn < 1) 
    {
        while (ptr->status != Ready)
            continue;
        sleep(1);
  
        //input from server
        printf("Server: ");
        fgets(ptr->msg, 100, stdin);
  
        ptr->status = FILLED;

        //sending the message to client using kill function
        kill(ptr->pid2, SIGUSR2);
        codn++;
    }
  
    shmdt((void*)ptr);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}