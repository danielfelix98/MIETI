# coding= utf-8
from cryptography.fernet import Fernet

key=Fernet.generate_key()  #geração da chave de encriptação, é necessário conhece-la também para desencriptar a mensagem
f=Fernet(key)

def encrypt():    #função utilizada para encriptação
	file=open("para_encriptar.txt","rb")  #abertura do ficheiro no modo leitura
	reader = file.read()         #colocação do conteúdo do ficheiro na variável reader
	print ("mensagem a encriptar: ")
	print(reader)
	token = f.encrypt(reader)       #encriptação da mensagem
	print("mensagem encriptada: ")
	print(token)
	return token        #retorno da emnsagem encriptada

def decrypt():
	write_file=open("desencriptado.txt","wb") #criaçao (se não existir) e abertura do ficheiro em modo escrita
	token=encrypt()#mensagem encriptada
	writer=f.decrypt(token) #desencriptação da mensagem
	write_file.write(writer) #escrita da mensagem desencriptada no ficheiro desencriptado.txt
	print("Mensagem desencriptada colocada no ficheiro: ")
	print(writer)

decrypt()  #execução da função para desemcriptar, no entanto esta função invoca a função de encriptação, sendo esta executada primeiramente.
	   #Isto porque para desemcriptar é necessário que já tenhamos uma mensagem encriptada, a função "encrypt" retorna a mensagem encriptada
