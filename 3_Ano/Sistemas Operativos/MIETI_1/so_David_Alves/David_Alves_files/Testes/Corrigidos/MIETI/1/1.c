#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>


int main(int argc, char * argv[]){
	int fd=open("pid.out",O_CREAT|O_TRUNC|O_WRONLY,0666);
	int status;
	int pid;
	int pids[argc];
	int i=0;

	for(int i=1;i<argc;i++){
		pid=fork();//novo
		if (pid==0){//filho
			dup2(fd,1);//redireciona o stout para o fich
			close(fd);//fecha o fich
			execlp(argv[i],argv[i],NULL);	//executa os args e imprime para o fich
			perror("erro");//caso nao execute imprime erro
			_exit(-1);//caso nao execute imprime o -1

		}
		
		pids[i]=pid;//adiciona o pid array de inteiros de pids executados
		printf("%d: E\n",pid);//mostra o pid 
	}

	while(i<argc-1){//ciclo de todos os args
		int pid_=wait(&status);//pai espera que filhos acabem (pid_ retorna o pid do filho q acabou)
		
		if(WEXITSTATUS(status)==0){//se acabaram com exito(exec retorna 0 para o status caso tenha sido bem executado e -1 caso nao)
			printf("%d: S\n",pid_ );//imprime pid do filho q acabou
			//printf("%d\n",WEXITSTATUS(status) );
			i++;//incrementa
		}


		else{// se nao acabaram com exito
			for(int i=0;i<argc-1;i++){//ciclo para executar todos os args
				if(pid_==pids[i]){//verifica que o filho q acabou esta na lista daqueles que ja tinham sido executados
					execlp(argv[i],argv[i],NULL);// re-executa
				}
			}
			printf("%d: R\n", pid_);
		}

	}

}
