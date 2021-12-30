#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "rs232.h"
#include "api.h"

uint32_t current_timestamp()
{
	struct timeval te;
	gettimeofday(&te, NULL); // get current time
	return (uint32_t)te.tv_sec;
}
void split32(char *buffer, uint32_t value)
{
	UINT32UNION_t aux;
	aux.number = value;
	for (int i = 0; i < 4; i++)
	{
		buffer[i] = aux.bytes[i];
	}
}
void split16(char *buffer, uint16_t value)
{
	UINT16UNION_t aux;
	aux.number = value;
	for (int i = 0; i < 2; i++)
	{
		buffer[i] = aux.bytes[i];
	}
}
uint16_t join16(char *buffer)
{
	UINT16UNION_t aux;
	for (int i = 0; i < 2; i++)
	{
		aux.bytes[i] = buffer[i];
	}
	return aux.number;
}
uint32_t join32(char *buffer)
{
	UINT32UNION_t aux;
	for (int i = 0; i < 4; i++)
	{
		aux.bytes[i] = buffer[i];
	}
	return aux.number;
}
void splitFloat(char *buffer, float value)
{
	FLOATUNION_t aux;
	aux.number = value;
	for (int i = 0; i < 4; i++)
	{
		buffer[i] = aux.bytes[i];
	}
}
float joinFloat(char *bufffer)
{
	FLOATUNION_t aux;
	for (int i = 0; i < 4; i++)
	{
		aux.bytes[i] = bufffer[i];
	}
	return aux.number;
}