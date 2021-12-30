#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	mkfifo("fifo",0666);
	return 0;
}