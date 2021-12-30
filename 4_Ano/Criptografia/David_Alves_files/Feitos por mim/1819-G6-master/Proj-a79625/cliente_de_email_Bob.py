#Feito por David Alves em 08-01-2019
from cryptography.fernet import Fernet
import time

file=open("key.txt","rb")
key=file.read()
file.close()
print("Ola Bob, bem-vindo ao teu cliente-de-email seguro")


f=Fernet(key)
file2=open("msg.txt","rb")
ler=file2.read()
print("Bob, tens uma nova mensagem, enviada pela Alice:")
print("A desencriptar a mensagem...")
print("...")


text=ler[0:100]
site=ler[200:]
texto=f.decrypt(text)
time.sleep(2)
print("Alice:",texto.decode())
print("--------------------------------------------------")
file2.close()

sitef=open("%s"  %  site.decode(),"a")
t=texto.decode()
y=t.replace(" ", "%20")
y1=y.replace("?", "%_3F")
y2=y1.replace("@","%40")
new=site.decode()+"/"+y2
sitef.write("\n")
sitef.write(new)
sitef.close()

f=Fernet(key)
file3=open("msg.txt","rb")
texto2=f.decrypt(file3.read())
file3.close()
