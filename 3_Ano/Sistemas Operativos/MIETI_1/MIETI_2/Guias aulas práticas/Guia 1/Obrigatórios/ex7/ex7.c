#include<unistd.h>

struct buffer_t{
	int fd;	
	char prin[1024];
	char sec[1024];
};

int create_buffer(int filedes,struct buffer_t *buffer,ssize_t nbyte)
{

}

int destroy_buffer(struct buffer_t *buffer)
{

}

ssize_t readln(struct buffer_t *bufer,void **buf)
{
	
}

int main()
{
	
	return 0;
}
