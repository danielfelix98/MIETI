#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
 
int main(int argc, char* argv[]) {
 
	int k = atoi(argv[1]);
    char buffer[k];      /* Character buffer */

	while((read (0, &buffer, k)) > 0)
	{
		write(1,buffer,k);
		printf("\n");
	}
 
    return 0;
}
