// N Sree Dhyuti
// CED19I027
// Lab 6 : Q4 Receiver

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
    printf("SM ID : %d\n",shmid);
  	
    char *sm;
    //attach SM
    sm = shmat(shmid, NULL, 0);
    
    char msg[50];
    
    // Read data from sm
    printf("data read from SM by P2: %s \n",sm);
    
    int l = strlen(sm);
    char *s = sm;
    char *m = sm;

    int i = 0;
    for(i = 0; i < l; i++)
    {
    	msg[i] = *s;
    	s++;
    }
    
    // flag to make p1 wait till it writes data into sm
    *m = '$';  
    m++;
    
    int flg = 1;
    
    for(i = 0; i < (l / 2); i++)
    {
    	if(msg[i] != msg[l - i - 1])
    	{
    		flg = 0;
    		*m = '0';
    		break;    	
    	}  		
    }
    
    if(flg)
    	*m = '1';
    	
    m++;
    *m  = '\0';
    
    // p1 will resume once it detects #
    *sm = '#';
    
    //deatach sm  
    shmdt(sm);  
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}

