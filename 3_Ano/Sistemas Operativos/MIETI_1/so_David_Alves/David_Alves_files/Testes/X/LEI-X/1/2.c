#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h> 
#include <string.h>
#include <fcntl.h>
#include <errno.h>

void termina(){
	//Mata pai e filhos
	kill(0, 9); 
}

int main(int argc, char **argv){
	
	
	int result=0;
	int falhou;
	
	//Quando clicarem em CTRL + C termina o pai e filho
	signal(SIGINT, termina);
	
	do{
		
		//Faz o fork e executa o filho
		if (!fork()){
			execlp("renovaveisnodia","renovaveisnodia",NULL);
			
			//Caso o exec dê erro.
			exit(EXIT_FAILURE);
		}
		
		//Espera que o filho termine
		wait(&result);
		
		//Não sei se necessito dos 2. Penso que com o WIFEXITED conseguiria resolver o problema
		falhou = WIFEXITED(result);
		result = WEXITSTATUS(result);
		
	}while(result == EXIT_FAILURE || !falhou);
	
	return (EXIT_SUCCESS);
}