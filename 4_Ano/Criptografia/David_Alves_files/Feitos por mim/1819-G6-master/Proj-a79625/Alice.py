#Feito por David Alves em 08-01-2019
from cryptography.fernet import Fernet
import time
key=Fernet.generate_key()
f=Fernet(key)

file=open("key.txt","wb")
file.write(key)
file.close()

print("Ola Alice, bem-vinda ao correio-eletronico seguro!")
print('Escreve uma mensagem a enviar para o Bob:')
reader= input().encode()
print("----------------------------------------")
print("A tua mensagem esta a ser encriptada...")
time.sleep(2)
token = f.encrypt(reader)
print("...")
print ("Mensagem enviada para o Bob: ",reader.decode())

file=open("msg.txt","wb")
file.write(token)
file.close()

