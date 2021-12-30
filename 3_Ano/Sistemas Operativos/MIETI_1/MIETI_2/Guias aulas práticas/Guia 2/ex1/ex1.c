#include <unistd.h>
#include <sys/wait.h>

int main()
{
	pid_t p1,p2;
	p1 = getpid();
	p2 = getppid();
	printf("sou eu: %d\n",p1);
	printf("meu pai é: %d\n",p2);	
	return 0;
}
