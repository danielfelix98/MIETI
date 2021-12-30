#include <HardwareSerial.h>
#include <MPU6050_tockn.h>
#include <Wire.h>
#include "BluetoothSerial.h"
BluetoothSerial ESP_BT;

MPU6050 mpu6050(Wire);

#define ISS 1
#define SIZEPACKETSAMPLES 28
#define SIZEDATAPACKETEMPTY 16
#define SIZEERRORPACKET 8
#define MAXNS 36 //16+(28*36)=1024
//valores default
#define PM_DEFAULT 1000		 //ms
#define PA_DEFAULT 1000000 //micro sec
#define NS_DEFAULT 1			 //numero de amostras

void split32(char *buffer, uint32_t value);
void split16(char *buffer, uint16_t value);
uint16_t join16(char *buffer);
uint32_t join32(char *buffer);
void splitFloat(char *buffer, float value);
float joinFloat(char *bufffer);
void putValuesOnPacket(char *buf);
void constructDataPacket(uint8_t *buf);
void constructErrorPacket(uint8_t *buf, uint8_t idError);
uint32_t currentTimestamp();

typedef union {
	float number;
	uint8_t bytes[4];
} FLOATUNION_t;

typedef union {
	uint16_t number;
	uint8_t bytes[2];
} UINT16UNION_t;

typedef union {
	uint32_t number;
	uint8_t bytes[4];
} UINT32UNION_t;

uint8_t packet[1024];
uint32_t pm;
uint32_t pa;
uint8_t ns;

uint16_t sizePacket = 0;
uint32_t startTS = 0;
uint32_t initialTS = 0;
bool error = false;

void setup()
{

	ESP_BT.begin("SS1");
	Wire.begin();
	mpu6050.begin();
	mpu6050.calcGyroOffsets(false);
}

void loop()
{
	if (ESP_BT.available())
	{
		//ler trama
		ESP_BT.readBytes(packet, 14);
		// verificar tipo de trama
		if (packet[0] == 2) //trama de START
		{
			//obter timestamp trama e actual
			startTS = join32((char *)&packet[1]);
			initialTS = millis();

			//obter pm, pa e ns
			pm = join32((char *)&packet[5]);
			pa = join32((char *)&packet[9]);
			ns = packet[13];

			//ver se usa valores default
			if (pm == 0) // se zero, atribuir valores default
			{
				pm = PM_DEFAULT;
				error = false;
			}
			if (pa == 0) // se zero, atribuir valores default
			{
				pa = PA_DEFAULT;
				error = false;
			}
			if (ns == 0) // se zero, atribuir valores default
			{
				ns = NS_DEFAULT;
				error = false;
			}

			//verificar se parametros sao validos
			if (ns > 1)
			{
				if (pm < ((pa / 1000) * (ns - 1)))
				{
					// erro: pm nao aceitavel (id: 1)
					constructErrorPacket(packet, 1);
					sizePacket = SIZEERRORPACKET;
					ESP_BT.write(packet, sizePacket);
					error = true;
				}
				else if (ns > MAXNS)
				{
					// erro: ns maior que o valor maximo (id: 2)
					constructErrorPacket(packet, 2);
					sizePacket = SIZEERRORPACKET;
					ESP_BT.write(packet, sizePacket);
					error = true;
				}
				else
				{
					error = false;
				}
			}

			if (error == false)
			{
				//ciclo de envio
				//for(int i=0;i<1; i++) //envia 1 vez
				while (1) //envia sempre
				{					//constroi e envia trama, se Serial.available, ver se recebeu STOP, se sim break do ciclo
					constructDataPacket(packet);
					sizePacket = SIZEDATAPACKETEMPTY;
					for (int i = 0; i < ns; i++)
					{
						//leitura
						putValuesOnPacket(packet + sizePacket);
						//esperarPA
						delay(pa / 1000);
						sizePacket += SIZEPACKETSAMPLES;
					}
					//enviar trama
					ESP_BT.write(packet, sizePacket);
					//se recebeu STOP sai do ciclo
					if (ESP_BT.available())
					{
						ESP_BT.readBytes(packet, 2);
						if (packet[0] == 3)
						{
							break;
						}
					}
				}
			}
		}
	}
}
void putValuesOnPacket(uint8_t *buf)
{
	mpu6050.update();
	float temp = mpu6050.getTemp();
	float ax = mpu6050.getAccX();
	float ay = mpu6050.getAccY();
	float az = mpu6050.getAccZ();
	float gx = mpu6050.getGyroX();
	float gy = mpu6050.getGyroY();
	float gz = mpu6050.getGyroZ();
	memcpy(buf, &temp, 4);
	memcpy(buf + 4, &ax, 4);
	memcpy(buf + 8, &ay, 4);
	memcpy(buf + 12, &az, 4);
	memcpy(buf + 16, &gx, 4);
	memcpy(buf + 20, &gy, 4);
	memcpy(buf + 24, &gz, 4);
}
void constructDataPacket(uint8_t *buf)
{
	buf[0] = (uint8_t)0; //TIPO: DATA
	uint16_t iss = ISS;	//id sistema sensor
	memcpy(buf + 1, &iss, 2);
	uint32_t ts = currentTimestamp(); //timestamp
	memcpy(buf + 3, &ts, 4);
	memcpy(buf + 7, &pm, 4);	//periodo entre mensagem (PM)
	memcpy(buf + 11, &pa, 4); //periodo de amostragem (PA)
	memcpy(buf + 15, &ns, 1); //numero de amostras
}
uint32_t currentTimestamp()
{
	// calcular ts desde start mais ts de enviado do concentrador
	return (millis() - initialTS) + startTS; //timestamp
}
void constructErrorPacket(uint8_t *buf, uint8_t idError)
{
	buf[0] = (uint8_t)1; //TIPO: ERROR
	uint16_t iss = ISS;	//id sistema sensor
	memcpy(buf + 1, &iss, 2);
	uint32_t ts = currentTimestamp(); //timestamp
	memcpy(buf + 3, &ts, 4);
	memcpy(buf + 7, &idError, 1);
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