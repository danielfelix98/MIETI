#include <signal.h>
#include <sys/types.h>
#include <stdio.h>

int main(int argc, char *argv[])
{	
	int i = 1,p;
	while(i < argc) //houver args
	{
		if((p = fork()) == 0)
		{
			execl(argv[i],argv[i],NULL);
		} else {
			kill(SIGSTOP,p);
		}
		i++;
	}
	return 0;
}


/*

criar vários processos e cada um executa um comando.
paramos todos os processos logo que eles são criados
ativamos os sinais, alarme, sigchild
ciclo enquanto que houver filhos vivos
quando o alarme toca, parar o processo ativo e ativar o próximo

quando nã temos argumentos o mais fácil é usar o execl
ver diferenças entre os exec's


guardar pid's dos filhos num array

sigchld -> SEMPRE QUE MORRE UM FILHO

*/