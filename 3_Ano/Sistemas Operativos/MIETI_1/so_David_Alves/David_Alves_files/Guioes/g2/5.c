#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{   
    int pid=0,i,status;
    
    for(i=0;i<10;i++)
    {
        if(pid==0)//filho
        {
            printf("%d - PID: %d  PPID: %d\n",i,getpid(),getppid() );
            pid=fork();
        }
        else wait(&status);//pai
    }
    return 0;
}