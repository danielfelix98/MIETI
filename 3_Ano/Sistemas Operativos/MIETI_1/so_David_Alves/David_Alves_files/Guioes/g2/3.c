#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    int p, i, status; 
    printf("Olá, eu sou o pai, o meu pid é %d e vou ver nascer os meus 10 filhos...que loucura!!\n", getpid());
    printf("Olá, eu sou a mãe, não tenho pid, mas é só para dizer que os filhos vão sair um de cada vez...\n\n"); 
    for(i=1;i<=10;i++){
    p = fork();

        if(p == 0){//filho
            printf("Olá eu sou o filho nr. %d :: O meu pid é %d::O pid do meu  pai é %d\n", i, getpid(), getppid());
            _exit(i);//Deve-se usar esta com _ pq apenas termina o processo enquanto
            //que exit() invoca _end() tem mais o objetivo de fazer uma limpeza como o return
           
        }

        else {//pai
            int n=wait(&status);//espera que filho termina para criar outro
            int ii=WEXITSTATUS(status);//explicado no 4.c
            printf("O filho nr. %d já terminou de nascer\n",ii);
            
            if(ii==10){
            	printf("Isto foi intenso...\n" );
            }
            
            else{
         		printf("Vamos ver outro a nascer...\n\n");
         	}
        }

    }


    
    return 0;
}
