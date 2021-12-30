#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdio.h>

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
	int d1, d2, d3;
	char c;
	
	d2 = open("saida.txt", O_WRONLY | O_CREAT, 0666);
	dup2(d2,1);
	
	d3 = open("erros.txt", O_RDWR | O_CREAT, 0666);
	dup2(d3,2);
		
	d1 = open("password.txt", O_RDWR);
	if(d1==-1)
        {
                perror("erro no open fich pw...");
                return -1;
        }
    
    dup2(d1,0);


	while((read(0, &c, sizeof(char)))>0)
	{
		write(1, &c, sizeof(char));
	}

	close(d1);
	close(d2);
	close(d3);

	return 1;	
}
