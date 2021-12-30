# coding= utf-8
import os
from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC
from cryptography.hazmat.primitives.ciphers import Cipher,algorithms,modes
from cryptography.hazmat.backends import default_backend

from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import hashes, hmac

backend = default_backend()
salt=os.urandom(16)

kdf = PBKDF2HMAC(     
    algorithm=hashes.SHA256(),
    length=64,
    salt=salt,
    iterations=100000,
    backend=backend
)

key=kdf.derive(b"mypassword")   #as duas linhas a seguir permitem dividir esta key em duas, para o ChaCha e para o HMAC
key1=key[0:32]   #key ChaCha
key_mac=key[32:64] #key HMAC

def ChaCha_HMAC():
#ChaCha20
	reader=read() #invocação da funcao read, para ler o conteudo do ficheiro que se pretende encriptar
	nonce=os.urandom(16)  #utilizar apenas uma vez com uma unica chave, de forma a nao comprometer a seguranca da mensagem
	algorithm = algorithms.ChaCha20(key1, nonce)
	cipher=Cipher(algorithm,mode=None,backend=default_backend())
	encryptor=cipher.encryptor()
	cd=encryptor.update(reader)  #texto encriptado da mensagem proveniente do ficheiro 
##HMAC
	h=hmac.HMAC(key_mac,hashes.SHA256(),backend=default_backend())
	h.update(cd)
	h.finalize()
	msg = key + nonce + salt + cd  # Juncao de todos os parametros que se pretendem enviar na mensagem criptografada
	print("Mensagem encriptada: ")
	print(msg)
	f=open("msg_encriptada.txt","wb") #abertura do ficheiro em modo escrita
	f.write(msg) 
	f.close() #terminio da utilizacao do ficheiro, permitindo ao sistema a sua implementacao noutro local

def read():
	file=open("para_encriptar.txt","rb") #abertura do ficheiro em modo leitura
	reader=file.read()
	print("Para encriptar:")
	print(reader)
	file.close()
	return reader  

def desencriptar():
	e=open("msg_encriptada.txt","rb")
	encrypted=e.read()
	e.close()

	key=encrypted[0:64]   
	key_ChaCha=key[0:32]  #separacao da chave utilizada no ChaCha20
	nonce=encrypted[64:80]
	salt=encrypted[80:96] 
	mens=encrypted[96:]  #o texto encriptado encontra-se a partir desta posicao

	algorithm = algorithms.ChaCha20(key_ChaCha, nonce)
	cipher=Cipher(algorithm,mode=None,backend=default_backend())

	decryptor = cipher.decryptor()
	desenc=decryptor.update(mens) 
	f=open("desencriptado.txt","wb") #abertura do ficheiro em modo escrita
	print("Desencriptado:")
	print(desenc)
	f.write(desenc)
	f.close()

ChaCha_HMAC()
desencriptar()
