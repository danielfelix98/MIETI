# Código baseado em https://docs.python.org/3.6/library/asyncio-stream.html#tcp-echo-client-using-streams
import asyncio
import socket
import asyncio
import os
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import hashes, hmac
from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC

backend = default_backend()
conn_port = 8888
max_msg_size = 9999

file=open("key.txt","rb")
key=file.read()
key1=key[0:16]
key_mac=key[16:32]
file.close()

backend=default_backend()
salt=os.urandom(16)



class Client:
    """ Classe que implementa a funcionalidade de um CLIENTE. """
    def __init__(self, sckt=None):
        """ Construtor da classe. """
        self.sckt = sckt
        self.msg_cnt = 0
    
    def process(self, msg=b""):
        self.msg_cnt +=1

        iv_serv = msg[0:16]
        mac_serv=msg[16:48]
        texto = msg[48:]
        test=b""
        
        if msg is test:
            print('Mensagem recebida(%d): %r' % (1 , msg.decode()))
            print('Escreva a nova mensagem a enviar:')
            new = input().encode()
              
            iv_c = os.urandom(16)
            cipher = Cipher(algorithms.AES(key1), modes.CTR(iv_c), backend=backend)
            encryptor = cipher.encryptor()

            ct = encryptor.update(new) + encryptor.finalize()
            #HMAC
            h=hmac.HMAC(key_mac,hashes.SHA256(),backend=default_backend())
            h.update(ct)
            mac_sig = h.finalize()
            new_msg =iv_c+mac_sig+ct

           
            return new_msg if len(new_msg)>0 else None
            process()

        else:

            cipher = Cipher(algorithms.AES(key1), modes.CTR(iv_serv), backend=backend)
            decryptor = cipher.decryptor()

            h=hmac.HMAC(key_mac,hashes.SHA256(),backend=default_backend())
            h.update(texto)
            mac_sig = h.finalize() 

            txt=decryptor.update(texto) + decryptor.finalize()
            msg=txt.decode()

            if(mac_sig==mac_serv):
                
                print("Palavra-passe verificada com sucesso")    
                print('Mensagem recebida(%d): %r' % (self.msg_cnt , msg))
                print("------------------------------------")
                print('Escreva a nova mensagem a enviar:')
                
                new = input().encode()
                iv_c = os.urandom(16)
                cipher = Cipher(algorithms.AES(key1), modes.CTR(iv_c), backend=backend)
                encryptor = cipher.encryptor()
                ct = encryptor.update(new) + encryptor.finalize()
                new_msg= iv_c+mac_sig+ct
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
