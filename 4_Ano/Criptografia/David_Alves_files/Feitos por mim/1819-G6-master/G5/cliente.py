# Código baseado em https://docs.python.org/3.6/library/asyncio-stream.html#tcp-echo-client-using-streams
import asyncio
import os
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC
from cryptography.hazmat.primitives import hashes, hmac
from random import choice
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.asymmetric import dh
from cryptography.hazmat.primitives.kdf.hkdf import HKDF
import sys
import time
from random import randint
from ctypes import string_at
from sys import getsizeof
from binascii import hexlify
backend = default_backend()
conn_port = 8888
max_msg_size = 9999


p=99494096650139337106186933977618513974146274831566768179581759037259788798151499814653951492724365471316253651463342255785311748602922458795201382445323499931625451272600173180136123245441204133515800495917242011863558721723303661523372572477211620144038809673692512025566673746993593384600667047373692203583
g=44157404837960328768872680677686802650999163226766694797650810379076416463147265401084491113667624054557335394761604876882446924929840681990106974314935015501571333024773172440352475358750668213444607353872754650805031912866692119819377041901642732455911509867728218394542745330014071040326856846990119719675




class Client:
    """ Classe que implementa a funcionalidade de um CLIENTE. """
    def __init__(self, sckt=None):
        """ Construtor da classe. """
        self.sckt = sckt
        self.msg_cnt = 0
    
       
       
    def process(self, msg=b"-"):
        self.msg_cnt +=1
        test=b'-'
        test1='-1-'
        test2=test1.encode()
        id_cliente=0
        

        if msg == test:
            print('Conexão establecida com o servidor')
            print("Digite o seu id:")
            id_cliente=sys.stdin.read(1)
            id_cliente1=id_cliente.encode()
            self.id_cliente2=id_cliente1
            
            stbyte="-0-"
            stbyte=stbyte.encode()


            self.pn = dh.DHParameterNumbers(p, g)
            parameters = self.pn.parameters(default_backend())
            private_key = parameters.generate_private_key()
            self.public_key_client=private_key.public_key().public_numbers().y
            self.private_key=private_key


            new_msg=stbyte+id_cliente1+str(p).encode()+str(g).encode()+str(self.public_key_client).encode()#mensagem inicial a enviar para o servidor
           
            return new_msg if len(new_msg)>0 else None
           
            process()

        if msg.startswith(test2):
            
            startbyte=msg[0:3]
            public_key_serv=int(msg[3:].decode())

            peer_public_numbers = dh.DHPublicNumbers(public_key_serv,self.pn) 
            peer_key = peer_public_numbers.public_key(default_backend())           
            
            self.shared_key = self.private_key.exchange(peer_key)
            
            derived_key = HKDF(
                algorithm=hashes.SHA512(),
                length=32,
                salt=None,
                info=b'handshake data',
                backend=default_backend()
              ).derive(self.shared_key)
            
            
            self.derived_key=derived_key

            self.key1=self.derived_key[0:16]
            self.key_mac=self.derived_key[16:32]

            print('Escreva a 1ª mensagem a enviar:')
            new = input().encode() 
            iv_c = os.urandom(16)
            cipher = Cipher(algorithms.AES(self.key1), modes.CTR(iv_c), backend=default_backend())
            encryptor = cipher.encryptor()

            ct = encryptor.update(new) + encryptor.finalize()
            #HMAC
            h=hmac.HMAC(self.key_mac,hashes.SHA512(),backend=default_backend())
            h.update(ct)
            mac_sig = h.finalize()
           
            new_msg =iv_c+mac_sig+ct  # mensagem a enviar para o servidor, este necessitara do do salM e do salt2, nos kdfs correspondentes
            
            return new_msg if len(new_msg)>0 else None
            process()

        else:
            mac_serv = msg[16:80]
            iv_s=msg[0:16]
            texto = msg[80:]
            cipher = Cipher(algorithms.AES(self.key1), modes.CTR(iv_s), backend=default_backend())
            decryptor = cipher.decryptor()

            h=hmac.HMAC(self.key_mac,hashes.SHA512(),backend=default_backend())
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
