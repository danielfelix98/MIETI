#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
 
int main(int argc, char* argv[]) {
 
    int input_fd;    /* Input and output file descriptors */
    char buffer[sizeof(char)];      /* Character buffer */
 	int i;

	for (i=1;argv[i]!=NULL;i++)
	{
		input_fd = open (argv [i], O_RDONLY);
		while((read (input_fd, &buffer, sizeof(char))) > 0)
		{
			printf("%s",buffer);
		}
		close (input_fd);
	}
 
    return 0;
}
