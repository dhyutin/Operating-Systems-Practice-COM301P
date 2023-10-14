// N Sree Dhyuti
// CED19I027
// Lab 5 : Q4 Client

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
    char msg[100];
    int status, pid1, pid2;
}*ptr;

// Function to print message received from Server
void handler(int signum) 
{
    //if TRUE, then client received message from server
    if (signum == SIGUSR2) 
    {
        printf("Received message from Server: ");
        puts(ptr->msg);
    }
}
 
int main()
{
    //process id of client
    int pid = getpid();
  
    //key value of SM
    int key = 14534;
    
    //while loop break codn
    int codn = 0;
    
    //create SM
    int shmid = shmget(key, sizeof(struct memory), IPC_CREAT | 0666);
  
    //attach SM
    ptr = (struct memory*)shmat(shmid, NULL, 0);
  
    //store the pid of client in SM
    ptr->pid2 = pid;
  
    ptr->status = NotReady;
 
    signal(SIGUSR2, handler);
  
    //runs while 1 time.
    while (codn < 1) 
    {
        sleep(1);
  
        // taking input from client
        printf("CLient: ");
        fgets(ptr->msg, 100, stdin);
        ptr->status = Ready;
  
        //sending the message to server using kill
        kill(ptr->pid1, SIGUSR1);
  
        while (ptr->status == Ready)
            continue;
        codn++;
    }
  
    shmdt((void*)ptr);
    return 0;
}