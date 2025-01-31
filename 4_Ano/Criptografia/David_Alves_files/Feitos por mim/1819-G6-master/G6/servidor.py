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
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography.hazmat.primitives.serialization import load_pem_public_key
from cryptography.hazmat.primitives.asymmetric import padding
from cryptography.hazmat.primitives import serialization
backend = default_backend()
conn_cnt = 0
conn_port = 8888
max_msg_size = 9999

p=99494096650139337106186933977618513974146274831566768179581759037259788798151499814653951492724365471316253651463342255785311748602922458795201382445323499931625451272600173180136123245441204133515800495917242011863558721723303661523372572477211620144038809673692512025566673746993593384600667047373692203583
g=44157404837960328768872680677686802650999163226766694797650810379076416463147265401084491113667624054557335394761604876882446924929840681990106974314935015501571333024773172440352475358750668213444607353872754650805031912866692119819377041901642732455911509867728218394542745330014071040326856846990119719675


with open("Server_priv_key.bin", "rb") as key_file:
        server_private_key = serialization.load_pem_private_key(
            key_file.read(),
            password=None,
            backend=default_backend()
        ) 

with open("Client_public_key.bin", "rb") as key_file2:    ##key public do cliente proveniente do script gerador
        public_client = serialization.load_pem_public_key(
            key_file2.read(),
            backend=default_backend()
        )  



class ServerWorker(object):
    """ Classe que implementa a funcionalidade do SERVIDOR. """
    def __init__(self, cnt, addr=None):
        """ Construtor da classe. """
        self.id = cnt
        self.addr = addr
        self.msg_cnt = 0
        
    def process(self, msg):
        stbyte="-0-"
        stbyte1=stbyte.encode()
       
        if msg.startswith(stbyte1):
            self.msg_cnt += 1
            self.id_cliente=msg[3:4]
            public_key_client=int(msg[4:].decode())  
       
            id_c=self.id_cliente
            pn = dh.DHParameterNumbers(p, g)
            parameters = pn.parameters(default_backend())
              
            private_key = parameters.generate_private_key()
            public_key=private_key.public_key()
            public_key_serv=private_key.public_key().public_numbers().y  
       
            peer_public_numbers=dh.DHPublicNumbers(public_key_client,pn)
            peer_key=peer_public_numbers.public_key(default_backend())
            shared_key=private_key.exchange(peer_key)  

            derived_key = HKDF(
                algorithm=hashes.SHA512(),
                length=32,
                salt=None,
                info=b'handshake data',
                backend=default_backend()
              ).derive(shared_key)
           

            startb='-1-'
            new_msg=startb.encode()+str(public_key_serv).encode()
              
            self.key1=derived_key[0:16]
            self.key_mac=derived_key[16:32]  

            return new_msg
            process()

        else:
            
            
            self.msg_cnt += 1
            iv_cl = msg[0:16]  #apos o envio da priḿeira mensagem de texto, sao divididos os parametros que a constituem
            mac_cli=msg[16:80]
            signature=msg[80:336]  
            texto=msg[336:]  
            
            cipher = Cipher(algorithms.AES(self.key1), modes.CTR(iv_cl), backend=backend)
            decryptor = cipher.decryptor()
            txt=decryptor.update(texto)
          

            public_client.verify(
                signature,
                txt,
                padding.PSS(
                    mgf=padding.MGF1(hashes.SHA256()),
                    salt_length=padding.PSS.MAX_LENGTH
                ),
                hashes.SHA256()
            )

            print('Utilizador %r : %r' % (self.id_cliente.decode(),txt.decode()))
            
            iv_s = os.urandom(16)
            cipher = Cipher(algorithms.AES(self.key1), modes.CTR(iv_s), backend=backend)
            encryptor = cipher.encryptor()
            ct = encryptor.update(txt) + encryptor.finalize()


            ####################################
            #HMAC
            h=hmac.HMAC(self.key_mac,hashes.SHA512(),backend=default_backend())
            h.update(ct)
            mac_serv = h.finalize() 

            #assinar
            signature_s = server_private_key.sign(
                txt,
                padding.PSS(
                    mgf=padding.MGF1(hashes.SHA256()),
                    salt_length=padding.PSS.MAX_LENGTH
                ),
                hashes.SHA256()
            )

            new_msg = iv_s+mac_serv+signature_s+ct
       
            return new_msg if len(new_msg)>0 else None
            process()
       
                
#
#
# Funcionalidade Cliente/Servidor
#
# obs: não deverá ser necessário alterar o que se segue
#

@asyncio.coroutine
def handle_echo(reader, writer):
    global conn_cnt
    conn_cnt +=1
    addr = writer.get_extra_info('peername')
    srvwrk = ServerWorker(conn_cnt, addr)                
    data = yield from reader.read(max_msg_size)
    while True:
        if not data: continue
        if data[:1]==b'\n': break
        data = srvwrk.process(data)
        if not data: break
        writer.write(data)
        yield from writer.drain()
        data = yield from reader.read(max_msg_size)
    print("[%d]" % srvwrk.id)
    writer.close()



def run_server():
    loop = asyncio.get_event_loop()
    coro = asyncio.start_server(handle_echo, '127.0.0.1', conn_port, loop=loop)
    server = loop.run_until_complete(coro)
    # Serve requests until Ctrl+C is pressed
    print('Serving on {}'.format(server.sockets[0].getsockname()))
    print('  (type ^C to finish)\n')
    try:
        loop.run_forever()
    except key1boardInterrupt:
        pass
    # Close the server
    server.close()
    loop.run_until_complete(server.wait_closed())
    loop.close()
    print('\nFINISHED!')

run_server()
