#ifndef FUNC_H
#define FUNC_H

#define SIZES 256
#define SIZEM 512
#define SIZEL 1024
#define DATA 0
#define ERROR 1
#define START 2
#define STOP 3
#define CONFIG_FILE "config.txt"
#define NONE 0
#define SERIAL 1
#define UDP 2
#define SIZEPACKETSAMPLES 28
#define SIZEDATAPACKETEMPTY 16
#define MAXNS 36 //16+(28*36)=1024
//valores default
#define PM_DEFAULT 1000 //ms
#define PA_DEFAULT 1000000 //micro sec
#define NS_DEFAULT 1 //numero de amostras

#define ADDR "127.0.0.1"
#define PORT 7778

#include<stdint.h>
#include<stdbool.h>

uint32_t current_timestamp();
int build_packet_start_sensor(char *str, uint32_t pm, uint32_t pa, uint32_t ns);
int build_packet_start_manager(char *str);
void signalhandler(int signal);
void build_trama_stop(char *str, uint8_t errorId);
void split32(char *buffer, uint32_t value);
void split16(char *buffer, uint16_t value);
uint16_t join16(char *buffer);
uint32_t join32(char *buffer);
void splitFloat(char *buffer, float value);
float joinFloat(char *bufffer);

//vars para udp
struct sockaddr_in servaddr, cliaddr;
int sockfd;

//vars offsets
float offX, offY, offZ;

//vars socket
int sockManager;

//ficheiros
int fderr,fdout,fdlog;

//estruturas para conversao de bytes
typedef union
{
 float number;
 uint8_t bytes[4];
} FLOATUNION_t;

typedef union
{
 uint16_t number;
 uint8_t bytes[2];
} UINT16UNION_t;

typedef union
{
 uint32_t number;
 uint8_t bytes[4];
} UINT32UNION_t;

//Estrutura de configuraçoes
typedef struct config{
  uint32_t pm; //periodo entre mensagens
	uint32_t pa; //periodo de amostragem
	uint8_t ns; //numero de amostras
	// int nSerial; //numero de sensores Serial
	char portSerial[SIZES];
	int serialIndex;
	// int nUDP; //numero de sensores UDP
	char portUDP[SIZES];
	uint16_t ISu;
	uint16_t ISS;
	char area[SIZES][SIZES];
	int sujeito[SIZES];
	int numSujeitos;
	bool sujeitoAtivos[SIZES];
} config;

config actualConfig;

#endif