/* 

RS232 library - https://github.com/Marzac/rs232
Concentrador - lê ficheiros de configuraçao e comunica com sensores (Serial),
envia informaçao interpretada para gestor de Serviço

*/

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
#include <time.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "rs232.h"
#include "api.h"

int readConfig();
void printConfig();
int build_packet_start_sensor(char *str, uint32_t pm, uint32_t pa, uint32_t ns);
int build_packet_start_manager(char *str);
void signalhandler(int signal);
void build_trama_stop(char *str, uint8_t errorId);
void openSerial();
uint16_t getISu(uint16_t iss);
void closeFd();
void init();
int connectSocketManager();

int main(int argc, char const *argv[])
{
	int firstRun = 1;
	//armadilhar sinal
	signal(SIGINT, signalhandler);

	readConfig();

	printConfig();

	init();

	//enumerar as coms para obter coms
	int coms = comEnumerate();
	//abrir porta
	openSerial();
	char str[1024];
	char buf[1024];
	int sizeRead;

	//tempo de espera para fazer a calibraçao
	sleep(2);

	int sizeStartS = build_packet_start_sensor(str, actualConfig.pm, actualConfig.pa, actualConfig.ns);
	//enviar trama de start
	//criar log do start
	time_t ltime;				/* calendar time */
	ltime = time(NULL); /* get current cal time */
	sprintf(buf, "Timestamp: %s", asctime(localtime(&ltime)));
	write(fdlog, buf, strlen(buf));
	comWrite(actualConfig.serialIndex, str, sizeStartS);
	//sleep(2);
	//ciclo de leitura de valores (amostras ou erro), e criaçao de logs
	while (1)
	{
		// ler da Serial com timeout 5s
		sizeRead = comReadBytes(actualConfig.serialIndex, buf, sizeof(buf), SIZEDATAPACKETEMPTY + (actualConfig.ns * SIZEPACKETSAMPLES), 5000);
		if (sizeRead > 0)
		{
			printf("\n"); //printf("SizeRead: %d\n",sizeRead);

			//verificar tipo de trama
			if (buf[0] == DATA)
			{
				if (firstRun == 1)
				{
					actualConfig.ISS = join16(buf + 1);
					actualConfig.ISu = getISu(actualConfig.ISS);
					if (actualConfig.ISu == 0)
					{
						perror("Wrong ISu");
						exit(-1);
					}
					//send start to manager
					int sizeStartM = build_packet_start_manager(str);
					//	open socket
					sockManager = connectSocketManager();
					// send start to manager socket
					send(sockManager, str, sizeStartM, 0);
					firstRun = 0;
					//calculate offsets
					for (int i = 0; i <= 3; i++)
					{
						float val = joinFloat(buf + 16 + (i * 4));
						switch (i % 7)
						{
						case 1: //offset accX
							offX = val - 0;
							printf("X: %f %f  ", val, offX);
							break;
						case 2: //offset accY
							offY = val - 0;
							printf("Y: %f %f  ", val, offY);
							break;
						case 3: //offset accZ
							offZ = val - 1;
							printf("Z: %f %f\n", val, offZ);
							break;
						}
					}
				}
				//se data ler valores
				//escrever para ficheiro output e mostrar valores no ecra
				printf("DATA ISS: %u ISu: %u Timestamp: %u PA: %u NS: %u\n", actualConfig.ISS, actualConfig.ISu, join32(buf + 3), join32(buf + 11), actualConfig.ns);
				sprintf(str, "%u;%u;%u;%u;%u", actualConfig.ISS, actualConfig.ISu, join32(buf + 3), join32(buf + 11), actualConfig.ns);
				write(fdout, str, strlen(str));
				//change buf ISS to ISu
				//	0 - TIPO, 1a2 - ISu, 3a6 - TIMESTAMP, 6a9 - PM, 10a13 - PA, 14 - NS, 15(+n*28) a 42(+n*28) - N1
				split16(buf + 1, actualConfig.ISu);

				uint8_t nsT = actualConfig.ns * 7;
				for (int i = 0; i < nsT; i++)
				{
					float val = joinFloat(buf + 16 + (i * 4));
					switch (i % 7)
					{
					case 0: //temp
						printf(" Temp: %f", val);
						sprintf(str, ";%f", val);
						write(fdout, str, strlen(str));
						break;
					case 1: //offset accX
						printf(" RawAccX: %f AccX: %f", val, val - offX);
						val = val - offX;
						splitFloat(buf + 16 + (i * 4), val);
						sprintf(str, ";%f", val);
						write(fdout, str, strlen(str));
						break;
					case 2: //offset accY
						printf(" RawAccY: %f AccY: %f", val, val - offY);
						val = val - offY;
						splitFloat(buf + 16 + (i * 4), val);
						sprintf(str, ";%f", val);
						write(fdout, str, strlen(str));
						break;
					case 3: //offset accZ
						printf("\nRawAccZ: %f AccZ: %f", val, val - offZ);
						val = val - offZ;
						splitFloat(buf + 16 + (i * 4), val);
						sprintf(str, ";%f", val);
						write(fdout, str, strlen(str));
						break;
					case 4: //gyroX
						printf(" RawGyroX: %f", val);
						sprintf(str, ";%f", val);
						write(fdout, str, strlen(str));
						break;
					case 5: //gyroY
						printf(" RawGyroY: %f", val);
						sprintf(str, ";%f", val);
						write(fdout, str, strlen(str));
						break;
					case 6: //gyroZ
						printf(" RawGyroZ: %f", val);
						sprintf(str, ";%f", val);
						write(fdout, str, strlen(str));
						break;

					default: //restantes
						printf(";%f", val);
						sprintf(str, ";%f", val);
						write(fdout, str, strlen(str));
						break;
					}
				}
				printf("\n");
				write(fdout, "\n", 1);
				//	send data to manager
				send(sockManager, buf, 16 + (28 * actualConfig.ns), 0);
			}
			else if (buf[0] == ERROR)
			{
				//envia erro para log e sai do ciclo
				printf("ERROR\n");
				int tipErr = buf[7];
				time_t ltime;				/* calendar time */
				ltime = time(NULL); /* get current cal time */
				sprintf(str, "ERROR TYPE: %d Timestamp: %s", tipErr, asctime(localtime(&ltime)));
				write(fderr, str, strlen(str));
				//enviar erro para gestor	0-TP 1a2-ISu 3a4-ISS 5a8-TS 9-TipoErro
				buf[0] = ERROR;
				split16(buf + 1, actualConfig.ISu);
				split16(buf + 3, actualConfig.ISS);
				split32(buf + 5, current_timestamp());
				buf[9] = tipErr;
				send(sockManager, buf, 10, 0);
				//fechar
				closeFd();
				//sair do ciclo
				break;
			}
		}
	}
}

int readConfig()
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	fp = fopen(CONFIG_FILE, "r");
	if (fp == NULL)
		return -1;

	read = getline(&line, &len, fp);
	printf("%s\n", line);

	int argSize = 0;
	int tc = NONE;
	char *token = strtok(line, ";");

	// Keep looping while one of the
	// delimiters present in str[].
	while (token != NULL)
	{
		switch (argSize)
		{
		case 0:
			actualConfig.pm = atoi(token);
			break;

		case 1:
			actualConfig.pa = atoi(token);
			break;

		case 2:
			actualConfig.ns = atoi(token);
			break;

		default:
			//check if Serial or UDP
			if ((argSize % 2) == 1)
			{ //tipo de comunicaçao
				if (strcmp(token, "Serial") == 0)
				{
					tc = SERIAL;
				}
				else if (strcmp(token, "UDP") == 0)
				{
					tc = UDP;
				}
				else
				{
					tc = NONE;
				}
			}
			else //porta de comunicaçao
			{
				switch (tc)
				{
				case SERIAL:
					strcpy(actualConfig.portSerial, token);
					break;

				case UDP:
					strcpy(actualConfig.portUDP, token);
					break;

				default:
					break;
				}
			}

			break;
		}
		argSize++;
		token = strtok(NULL, ";");
	}

	fclose(fp);
	if (line)
		free(line);

	//default para cada valor de config
	if (actualConfig.pm == 0) // se zero, atribuir valores default
	{
		actualConfig.pm = PM_DEFAULT;
	}
	if (actualConfig.pa == 0) // se zero, atribuir valores default
	{
		actualConfig.pa = PA_DEFAULT;
	}
	if (actualConfig.ns == 0) // se zero, atribuir valores default
	{
		actualConfig.ns = NS_DEFAULT;
	}

	return 0;
}
void printConfig()
{
	printf("pm: %d, pa: %d, ns: %d\n", actualConfig.pm, actualConfig.pa, actualConfig.ns);
	printf("Serial Port: %s\n", actualConfig.portSerial);
	printf("UDP Port: %s\n", actualConfig.portUDP);
}
void openSerial()
{
	actualConfig.serialIndex = comFindPort(actualConfig.portSerial);
	printf("Index: %d\n", actualConfig.serialIndex);
	if (actualConfig.serialIndex == -1)
	{
		actualConfig.serialIndex = 8;
	}
	printf("Index: %d\n", actualConfig.serialIndex);
	comOpen(actualConfig.serialIndex, 115200);
	sleep(2);
}
void openUDP(int port)
{

	// Creating socket file descriptor
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));

	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(port);

	// Bind the socket with the server address
	if (bind(sockfd, (const struct sockaddr *)&servaddr,
					 sizeof(servaddr)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
}
int build_packet_start_sensor(char *str, uint32_t pm, uint32_t pa, uint32_t ns) // 0-TP, 1a4-TS, 5a8-PM, 9a12-PA, 13-NS
{
	str[0] = (char)2;
	uint32_t ts = current_timestamp();
	split32(str + 1, ts);
	split32(str + 5, pm);
	split32(str + 9, pa);
	str[13] = ns;
	return 14;
}
int build_packet_start_manager(char *str) // 0-TP, 1a4-TS, 5a6-ISu, 7a8-ISS
{
	str[0] = (char)2;
	uint32_t ts = current_timestamp();
	split32(str + 1, ts);
	split16(str + 5, actualConfig.ISu);
	split16(str + 7, actualConfig.ISS);
	return 9;
}
void signalhandler(int signal)
{
	char str[1024];
	build_trama_stop(str, 1);
	comWrite(actualConfig.serialIndex, str, 2);
	//enviar stop para gestor	0-TP 1a2-ISu 3a4-ISS
	str[0] = STOP;
	split16(str + 1, actualConfig.ISu);
	split16(str + 3, actualConfig.ISS);
	send(sockManager, str, 5, 0);
	sleep(2);
	comTerminate();
	closeFd();
	_exit(0);
}
void build_trama_stop(char *str, uint8_t errorId)
{
	str[0] = (char)3;
	str[1] = (char)errorId;
}
uint16_t getISu(uint16_t iss)
{
	// ler ficheiro de config_sujeitos
	// procurar ISS e obter ISu associado
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int next = 0;

	fp = fopen("config_sensor.txt", "r");
	if (fp == NULL)
		return -1;

	read = getline(&line, &len, fp);
	read = getline(&line, &len, fp);
	printf("%s\n", line);

	int argSize = 0;
	int tc = NONE;
	char *token = strtok(line, ";");

	// Keep looping while one of the
	// delimiters present in str[].
	while (token != NULL)
	{
		if ((argSize % 2) == 0)
		{ // par
			//	ISS
			if (atoi(token) == iss)
			{
				next = 1;
			}
		}
		else
		{ // impar
			//	ISu
			if (next == 1)
			{
				return atoi(token);
			}
		}
		argSize++;
		token = strtok(NULL, ";");
	}

	fclose(fp);
	if (line)
		free(line);

	return 0;
}
void init()
{
	fderr = open("error.txt", O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);
	fdout = open("output.txt", O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);
	fdlog = open("log.txt", O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);
}

void closeFd()
{
	close(fderr);
	close(fdout);
	close(fdlog);
	close(sockManager);
	comCloseAll();
}

int connectSocketManager()
{
	struct sockaddr_in address;
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if (inet_pton(AF_INET, ADDR, &serv_addr.sin_addr) <= 0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}
	//	send(sock, hello, strlen(hello), 0);
	return sock;
}