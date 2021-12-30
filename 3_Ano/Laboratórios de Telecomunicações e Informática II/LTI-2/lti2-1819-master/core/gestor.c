#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <my_global.h>
#include <mysql.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "api.h"
#include <fcntl.h>
#include <errno.h>

#define HOST "localhost"
#define USER "root"
#define PASS ""
#define DB "gestorServico"

#define NAMOSTRAS 20
#define CONFIG_GESTOR "config_gestor.txt"

#define QUEDA 0
#define AGITADO 1
#define ANDAMENTO 2
#define PARADO 3

#define PIPE "ui_server"

void inserirAmostra(int Isu, float temp, int simulado, float Acx, float Acy, float Acz, float Grx, float Gry, float Grz);
void amostrasSujeito(int id_sujeito, float amostras[NAMOSTRAS][7]);
int interpretarAmostra(float amostras[NAMOSTRAS][7]);
int readConfig();
int postLeitura(char *estado, int id_sujeito);

uint32_t graphTime = 0;

int main()
{
	readConfig();

	//pipes ui-server
	int pip[2];
	pipe(pip);

	printf("aqui\n");
	// criar fork para UI
	if (fork() == 0)
	{ // child UI
		printf("UI process\n");

		close(pip[1]);

		int flags = fcntl(pip[0], F_GETFL, 0);
		if (fcntl(pip[0], F_SETFL, flags | O_NONBLOCK))
			printf("FAIL fcntl\n"); // some kind of fail

		float amostras[NAMOSTRAS][7];
		while (1)
		{
			sleep(1);

			// verificar se recebeu do pipe
			int count;
			char buffer[1024];
			count = read(pip[0], buffer, 1024);
			if (count < 0 && errno == EAGAIN)
			{
				// If this condition passes, there is no data to be read
				for (int i = 0; i < actualConfig.numSujeitos; i++)
				{
					printf("Sujeito %d %s\t", actualConfig.sujeito[i], actualConfig.area[i]);
					if (actualConfig.sujeitoAtivos[actualConfig.sujeito[i]] == true)
					{
						// sujeito ativo
						amostrasSujeito(actualConfig.sujeito[i], amostras);
						switch (interpretarAmostra(amostras))
						{
						case QUEDA:
							printf("!QUEDA!\t");
							postLeitura("Queda!", actualConfig.sujeito[i]);
							break;

						case AGITADO:
							printf("!AGITADO!\t");
							postLeitura("Agitado!", actualConfig.sujeito[i]);
							break;

						case ANDAMENTO:
							printf("ANDAMENTO\t");
							postLeitura("Andamento", actualConfig.sujeito[i]);
							break;

						case PARADO:
							printf("PARADO\t\t");
							postLeitura("Parado", actualConfig.sujeito[i]);
							break;
						}
					}
					else
					{
						// sujeito inativo
						printf("!DESLIGADO!\t");
						postLeitura("Desligado!", actualConfig.sujeito[i]);
					}
				}
				printf("\n");
			}
			else if (count >= 0)
			{
				// Otherwise, you're good to go and buffer should contain "count" bytes.
				int suj = atoi(buffer + 1);
				if (buffer[0] == 'i')
				{
					actualConfig.sujeitoAtivos[suj] = true;
				}
				else if (buffer[0] == 'o')
				{
					actualConfig.sujeitoAtivos[suj] = false;
				}
			}
			else
			{
				// Some other error occurred during read.
				printf("ERRO A LER DO PIPE!\n");
			}
		}

		/* printf("\n AMOSTRAS: \n");
		for(int i=0;i<NAMOSTRAS;i++){
			for(int j=0; j<7; j++){
				printf("%f ",amostras[i][j]);
			}
			printf("\n");
		} */
	}
	// parent process
	else
	{
		int server_sockfd, client_sockfd;
		int server_len, client_len;
		struct sockaddr_in server_address;
		struct sockaddr_in client_address;

		server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

		server_address.sin_family = AF_INET;
		server_address.sin_addr.s_addr = htonl(INADDR_ANY);
		server_address.sin_port = htons(PORT);
		server_len = sizeof(server_address);
		bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

		/* Create a connection queue, ignore child exit details and wait for
	clients. */

		listen(server_sockfd, 5);

		signal(SIGCHLD, SIG_IGN);

		close(pip[0]);

		while (1)
		{
			char buf[1024];

			// printf("server waiting\n");

			/* Accept connection. */

			client_len = sizeof(client_address);
			client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, (socklen_t *)&client_len);

			/* Fork to create a process for this client and perform a test to see
	whether we're the parent or the child. */

			if (fork() == 0)
			{

				/* If we're the child, we can now read/write to the client on
	client_sockfd.
	The five second delay is just for this demonstration. */

				//ler conteudo recebido
				int ISu;
				int size = read(client_sockfd, &buf, 1024);
				if (size > 0)
				{
					printf("%d\n", (uint8_t)buf[0]);
					usleep(10);
					//trama de inicio? 0-TIPO, 1a4-TIMESTAMP, 5a6-ISu, 7a8-ISS
					if (buf[0] == (char)START)
					{ //trama START
						printf("START\n");
						ISu = join16(buf + 5);
						//	definir sujeito como ativo
						char bpip[64];
						sprintf(bpip, "i%d", ISu);
						write(pip[1], bpip, strlen(bpip));

						//ciclo de leitura de dados recebidos
						while (1)
						{
							int size = read(client_sockfd, &buf, 1024);
							if (size > 0)
							{
								// trama de dados? 0 - TIPO, 1a2 - ISu, 3a6 - TIMESTAMP, 7a10 - PM, 11a14 - PA, 15 - NS, 16(+n*28) a 43(+n*28) - N1
								if (buf[0] == DATA)
								{
									int ISu = join16(buf + 1);
									float vals[7];
									// imprimir dados recebidos
									//printf("ISu: %d TS: %d PM: %d PA: %d NS: %d \n", join16(buf + 1), join32(buf + 3), join32(buf + 7), join32(buf + 11), buf[15]);
									for (int j = 0; j < buf[15]; j++)
									{
										int c = 0;
										for (int i = j * 7; i < (j * 7) + 7; i++)
										{
											vals[c] = joinFloat(buf + 16 + (i * 4));
											//printf("%f ", vals[c]);
											c++;
										}
										// guardar dados em bd
										inserirAmostra(ISu, vals[0], 0, vals[1], vals[2], vals[3], vals[4], vals[5], vals[6]);
										// printf("%.2f;%.2f;%.2f;%.2f;%.2f;%.2f",vals[1],vals[2],vals[3],vals[4],vals[5],vals[6]);
										// printf("\n");
									}
								}
								else if (buf[0] == STOP)
								{
									//handle stop
									//	definir sujeito como inativo
									char bpip[64];
									sprintf(bpip, "o%d", ISu);
									write(pip[1], bpip, strlen(bpip));
								}
								else if (buf[0] == ERROR)
								{
									//handle erro
									//	definir sujeito como inativo
									char bpip[64];
									sprintf(bpip, "o%d", ISu);
									write(pip[1], bpip, strlen(bpip));
								}
							}
							else
							{
								//	definir sujeito como inativo
								char bpip[64];
								sprintf(bpip, "o%d", ISu);
								write(pip[1], bpip, strlen(bpip));
								close(pip[1]);
								close(client_sockfd);
								exit(0);
							}
						}
					}
				}
				else
				{
					close(client_sockfd);
					exit(0);
				}
			}

			/* Otherwise, we must be the parent and our work for this client is
	finished. */

			else
			{
				close(client_sockfd);
			}
		}
	}
}

void inserirAmostra(int Isu, float temp, int simulado, float Acx, float Acy, float Acz, float Grx, float Gry, float Grz)
{

	MYSQL conexao;

	char query[2048];
	MYSQL *conn;
	conn = mysql_init(NULL);
	mysql_real_connect(conn, HOST, USER, PASS, DB, 0, NULL, 0);
	sprintf(query, "call inserir_amostra(%d, %d, %f, %d, %f, %f, %f, %f, %f, %f);", Isu, Isu, temp, simulado, Acx, Acy, Acz, Grx, Gry, Grz);
	int res = mysql_query(conn, query);
	if (!res)
	{
		//printf("Registros inseridos %llu\n", mysql_affected_rows(conn));
	}
	else
		printf("Erro na inserção %d : %s\n", mysql_errno(conn), mysql_error(conn));
	mysql_close(conn);
}

void amostrasSujeito(int id_sujeito, float amostras[NAMOSTRAS][7])
{
	MYSQL conexao;
	MYSQL_RES *resp;
	MYSQL_ROW linhas;
	MYSQL_FIELD *campos;
	char query[1024];
	sprintf(query, "select temperatura,acx,acy,acz,grx,gry,grz from amostra where id_sujeito = %d order by id_amostra desc limit %d;", id_sujeito, NAMOSTRAS);
	int conta; //Contador comum
	mysql_init(&conexao);
	if (mysql_real_connect(&conexao, HOST, USER, PASS, DB, 0, NULL, 0))
	{
		if (mysql_query(&conexao, query))
			printf("Erro: %s\n", mysql_error(&conexao));
		else
		{
			resp = mysql_store_result(&conexao); //recebe a resposta
			if (resp)														 //se houver resposta
			{
				//passa os dados dos campos para a variável campos
				//escreve na tela os nomes dos campos dando
				//um tab somente
				campos = mysql_fetch_fields(resp);
				for (conta = 0; conta < mysql_num_fields(resp); conta++)
				{
					// printf("|");
					// printf("%s", (campos[conta]).name);
					// printf("|\t   ");
				}

				// printf("\n");
				// printf("---------------------------------------\n");

				//enquanto retonrnar registros, conta até o
				//número de colunas que a tabela tem e escreve na
				//tela com um tab, depois pula a linha e tenta
				//pegar outro registro
				int i = 0;
				while ((linhas = mysql_fetch_row(resp)) != NULL)
				{
					for (conta = 0; conta < mysql_num_fields(resp); conta++)
					{
						//printf("%s  \t", linhas[conta]);
						amostras[i][conta] = atof(linhas[conta]);
					}
					//printf("\n");
					i++;
				}
			}
			mysql_free_result(resp); //limpa a variável do resultado: resp
		}
		mysql_close(&conexao);
	}
	else
	{
		printf("Conexao Falhou\n");
		if (mysql_errno(&conexao))
			printf("Erro %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
	}
}

int interpretarAmostra(float amostras[NAMOSTRAS][7])
{
	int fdAcc = open("graphAcc.csv", O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);
	int fdGyro = open("graphGyro.csv", O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);
	char str[1024];
	float vetorAcc[NAMOSTRAS];
	vetorAcc[0] = sqrt((amostras[0][1] * amostras[0][1]) + (amostras[0][2] * amostras[0][2]) + (amostras[0][3] * amostras[0][3]));
	float menor = vetorAcc[0], maior = vetorAcc[0];
	float vetorGyro[NAMOSTRAS];
	vetorGyro[0] = sqrt((amostras[0][4] * amostras[0][4]) + (amostras[0][5] * amostras[0][5]) + (amostras[0][6] * amostras[0][6]));
	float mediaGyro = vetorGyro[0];
	for (int i = 1; i < NAMOSTRAS; i++)
	{
		vetorAcc[i] = sqrt((amostras[i][1] * amostras[i][1]) + (amostras[i][2] * amostras[i][2]) + (amostras[i][3] * amostras[i][3]));
		vetorGyro[i] = sqrt((amostras[i][4] * amostras[i][4]) + (amostras[i][5] * amostras[i][5]) + (amostras[i][6] * amostras[i][6]));
		sprintf(str, "%d,%.2f\n", (uint32_t)graphTime, vetorAcc[i]);
		write(fdAcc, str, strlen(str));
		sprintf(str, "%d,%.2f\n", (uint32_t)graphTime, vetorGyro[i]);
		write(fdGyro, str, strlen(str));
		graphTime += 200;
		if (vetorAcc[i] > maior)
		{
			maior = vetorAcc[i];
		}
		if (vetorAcc[i] < menor)
		{
			menor = vetorAcc[i];
		}
		mediaGyro += vetorGyro[i];

		if (vetorAcc[i - 1] < 0.6)
		{
			if (vetorAcc[i] < vetorAcc[i - 1])
			{
				// printf("\nQUEDA!!!!!!\n");
				// sleep(1);
				return QUEDA;
			}
		}
	}
	close(fdAcc);
	close(fdGyro);
	float amplitudeAcc = maior - menor;
	mediaGyro = mediaGyro / NAMOSTRAS;

	// printf("Acc:%.2f Gyro:%.2f\n", amplitudeAcc, mediaGyro);

	if (amplitudeAcc > 1.6 && mediaGyro > 150)
	{
		// printf("\nAGITADO\n");
		return AGITADO;
	}
	else if (amplitudeAcc > 0.5 && mediaGyro > 50)
	{
		// printf("\nANDAMENTO\n");
		return ANDAMENTO;
	}
	else
	{
		// printf("\nPARADO\n");
		return PARADO;
	}
}

int readConfig()
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	fp = fopen(CONFIG_GESTOR, "r");
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
		{
			//	id sujeito
			actualConfig.sujeito[actualConfig.numSujeitos] = atoi(token);
		}
		else
		{
			//	nome area
			strcpy(actualConfig.area[actualConfig.numSujeitos], token);
			printf("%d;%s\n", actualConfig.sujeito[actualConfig.numSujeitos], actualConfig.area[actualConfig.numSujeitos]);
			actualConfig.numSujeitos++;
		}
		argSize++;
		token = strtok(NULL, ";");
	}

	fclose(fp);
	if (line)
		free(line);

	return 0;
}

int postLeitura(char *estado, int id_sujeito)
{
	// post command: curl -d "estado_fisico=ESTADO&id_paciente=ID_SUJEITO" -X POST http://localhost:8080/leituras
	char command[1024];

	sprintf(command, "curl -s -d \"estado_fisico=%s&id_paciente=%d\" -X POST http://localhost:8080/leituras > /dev/null", estado, id_sujeito);
	return system(command);
}