#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h> 
#include <unistd.h>
int main()
{
  int i , pid=1 , status;
    for(i=0; i<10 ; i++){
        if(pid){
        pid = fork();
        }
        else break;
    }

    if(pid!=0){//pai
        for(i=1; i<=10; i++){
            wait(&status);//guarda em status o q vem do exit dp filho
            printf("Proocesso-filho nr. %d terminou,ppid:%d\n",  WEXITSTATUS(status),pid);//imprime o que esta em em status(WEXITSTATUS(status))
        }
    }
    else{//filho
            printf("Processo-filho nr. %d pid: %d  ppid: %d\n", i,  getpid() ,getppid());
            _exit(i);//este i corresponde ao i de quando o proocesso foi criado
    }
    
    return 0;
}







/*Quando se faz fork ele cria na verdade 2 processos um filho e um pai
O fork replica o estado por isso tambem replica o valor do i no for*/