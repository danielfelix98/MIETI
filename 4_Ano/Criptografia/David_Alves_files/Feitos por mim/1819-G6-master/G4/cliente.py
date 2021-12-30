# Código baseado em https://docs.python.org/3.6/library/asyncio-stream.html#tcp-echo-client-using-streams
import asyncio
import socket
import asyncio
import os
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import hashes, hmac
from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC
import sys
backend = default_backend()
conn_port = 8888
max_msg_size = 9999
'''
file=open("key.txt","rb")
key=file.read()
key1=key[0:16]
key_mac=key[16:32]
file.close()
'''
backend=default_backend()


class Client:
    """ Classe que implementa a funcionalidade de um CLIENTE. """
    def __init__(self, sckt=None):
        """ Construtor da classe. """
        self.sckt = sckt
        self.msg_cnt = 0
    
    def process(self, msg=b"-"):
        self.msg_cnt +=1
 
        iv_serv = msg[0:16]
        mac_serv = msg[16:48]
        #id_cl = msg[48:49]#49
        saltMM=msg[48:64]#nao vai ser usado, apenas para garantir que nao ocorrem erros, estap divididos para diferencia-los
        salt_2=msg[64:80]#nao vai ser usado, apenas para garantir que nao ocorrem erros
        texto = msg[80:]
        test=b'-'
        test1='ola'
        test2=test1.encode()
        id_cliente=0
        if msg == test:
            print('Conexão establecida com o servidor')
            print("Digite o seu id:")
            #id_cliente = input().encode()
            
            id_cliente=sys.stdin.read(1)
            id_cliente1=id_cliente.encode()#tamanho 34(fixo)
            self.id_cliente2=id_cliente1
            
            stbyte="-0-"
            stbyte=stbyte.encode()

            new_msg=stbyte+id_cliente1 #mensagem inicial a enviar para o servidor
            #print(new_msg[0:1])
           
            return new_msg if len(new_msg)>0 else None
            #msg=b""
            process()

        if msg == test2:
            self.salt2=os.urandom(16)  #salt2, utilizado no sessionkdf
            backend=default_backend()
            keystore=open('keystore_id_%s.txt' % str(self.id_cliente2.decode()), 'rb')
            ler=keystore.read()
            keystore.close()
            self.saltM=ler[0:16]
            clikey=ler[16:]

            sessionkdf = PBKDF2HMAC(     
                algorithm=hashes.SHA256(),
                length=32,
                salt=self.salt2,
                iterations=100000,
                backend=default_backend())
            

            sessionkey=sessionkdf.derive(clikey) #derivacao sa sessionket
            self.key1=sessionkey[0:16]           #divisao desta para utilizacao na cifra e no hmac       
            self.key_mac=sessionkey[16:32]       #
            print('Escreva a 1ª mensagem a enviar:')
            new = input().encode() 
            iv_c = os.urandom(16)
            cipher = Cipher(algorithms.AES(self.key1), modes.CTR(iv_c), backend=default_backend())
            encryptor = cipher.encryptor()

            ct = encryptor.update(new) + encryptor.finalize()
            #HMAC
            h=hmac.HMAC(self.key_mac,hashes.SHA256(),backend=default_backend())
            h.update(ct)
            mac_sig = h.finalize()
            
            new_msg =iv_c+mac_sig+self.saltM+self.salt2+ct  # mensagem a enviar para o servidor, este necessitara do do salM e do salt2, nos kdfs correspondentes
           
            return new_msg if len(new_msg)>0 else None
            process()

        else:

            cipher = Cipher(algorithms.AES(self.key1), modes.CTR(iv_serv), backend=default_backend())
            decryptor = cipher.decryptor()

            h=hmac.HMAC(self.key_mac,hashes.SHA256(),backend=default_backend())
            h.update(texto)
            mac_sig = h.finalize() 
           

            txt=decryptor.update(texto) + decryptor.finalize()
            msg=txt.decode()

            if(mac_sig==mac_serv):
                
                print("Palavra-passe verificada com sucesso")    
                print('Mensagem recebida: %r' % (msg))
                print("------------------------------------")
                print('Escreva a nova mensagem a enviar:')
                new = input().encode()
                iv_c = os.urandom(16)
                cipher = Cipher(algorithms.AES(self.key1), modes.CTR(iv_c), backend=default_backend())
                encryptor = cipher.encryptor()
                ct = encryptor.update(new) + encryptor.finalize()
                new_msg= iv_c+mac_sig+self.saltM+self.salt2+ct
                return new_msg if len(new_msg)>0 else None
                process()
            else:
                print("Erro na verificação da palavra-passe")   
                
            
          
#
#
# Funcionalidade Cliente/Servidor
#
# obs: não deverá ser necessário alterar o que se segue
#

@asyncio.coroutine
def tcp_echo_client(loop=None):
    if loop is None:
        loop = asyncio.get_event_loop()

    reader, writer = yield from asyncio.open_connection('127.0.0.1', conn_port, loop=loop)
    addr = writer.get_extra_info('peername')
    client = Client(addr)
    msg = client.process()
    while msg:
        writer.write(msg)
        msg = yield from reader.read(max_msg_size)
        if msg :
            msg = client.process(msg)
        else:
            break
    writer.write(b'\n')
    print('Socket closed!')
    writer.close()

def run_client():
    loop = asyncio.get_event_loop()
    loop.run_until_complete(tcp_echo_client())


run_client()
