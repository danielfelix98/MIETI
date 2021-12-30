#include<unistd.h>
int main()
{
	int c;
	while (read(STDIN_FILENO,&c,1) == 1) //STDIN_FILENO = 0
		write(STDOUT_FILENO,&c,1); //STDOUT_FILENO = 1
	return 0;
}
