// N Sree Dhyuti
// CED19I027
// Lab 6 : Q4 Sender

// Inclusion of required libraries
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>  

// Main
int main()
{
    // key value of shared memory
    key_t key = 1823;
       
    //SM create
    int shmid = shmget(key, 1024, 0666|IPC_CREAT);
    printf("SM ID : %d\n", shmid);
  	
    char *sm;
    
    //attach SM 
    sm = shmat(shmid, NULL, 0);  
    char msg[50];

    printf("Enter data to write in SM by P1:");
    scanf("%s", msg);
	
    int i = 0;
    char *s = sm;
    for(i = 0; i < strlen(msg); i++)  //copying data into sm
    {
    	*s = msg[i];
    	s++;
    }
    *s  = '\0';
    
    //waiting till p2 reads and write data into sm  	
    while(*sm != '#')
    {
        // # is a flag, if first char in SM is '#' then it means P2 has done reading data 
        sleep(1);
    }
    
    s = sm;
    s++;

    //reading data excpt first character which is # to show that p2 has read data and is now going to write data into sm	
    printf("data read from sm : ");
    printf("%c",*s);
	
    if(*s=='0')
	printf("\nString IS NOT a palindrome");
    else
	printf("\nString IS a palindrome");	
	
    printf("\n");  
 
    shmdt(sm);
    return 0;
}
