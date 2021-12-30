
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#define READ 0
#define WRITE 1
#define N 32

int main(int argc, char** argv){

	int fd[2],status;
	pipe(fd);
	int pid=fork();

	if(pid==0){
		//PROCESSO FILHO
		printf("FILHO\n");
		close(fd[WRITE]);//fechar o pipe de escrita e o 1 passa a ter o stdout
		dup2(fd[READ],0);//o 0 que era o stdin agora vai ser o fd[0]
		execlp("wc","wc","-l",NULL);//imprime o resultado no 1 que agora e o stdout e atençao q vai receber do 0 o fd0		_exit(0);
		//_exit(0);
	}
	else{
		//PROCESSO PAI
		//wait(&status);
		printf("PAI\n");
		close(fd[READ]);//fecha o pipe de leitura//e o 0 e« o stdin
		dup2(fd[WRITE],1);//o 1 q era stdout agora e fd[1]
		execlp("ls","ls","/home/ubuntu/Desktop/so_/g4",NULL);//ou seja isto vai ser escrito para o 1 que agora e o fd[1] 

	}

	return 0;
}