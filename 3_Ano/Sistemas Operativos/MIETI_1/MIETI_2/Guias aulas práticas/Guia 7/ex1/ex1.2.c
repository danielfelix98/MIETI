#include <signal.h>
#include <sys/types.h>
#include <stdio.h>

int tempo = 0;
int times = 0;

void alarme()
{
	alarm(1);
	tempo++;
}

void quit()
{
	printf("O utilizador carregou %d vezes.\n",times);
	_exit(0);	
}

void touch()
{
	printf("O tempo é %d.\n",tempo);
	times++;
}

int main()
{	
	signal(SIGALRM,alarme);
	signal(SIGQUIT,quit);
	signal(SIGINT,touch);

	alarm(1);

	while (1)
	{
		pause();
	}
	return 0;
}