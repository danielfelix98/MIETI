# Código baseado em https://docs.python.org/3.6/library/asyncio-stream.html#tcp-echo-client-using-streams
import asyncio
import os
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC
from cryptography.hazmat.primitives import hashes, hmac
from random import choice
import sys
import time

backend = default_backend()
conn_cnt = 0
conn_port = 8888
max_msg_size = 9999


def password(tamanho): #random MasterPassword, permite que para cada sessao exista uma passord diferente, gerada a partir da string caracteres
    caracteres='dwee3233eeb232jjhhjjshdahdu2huei12h3uh21uassdsad123'
    senha=''
    for char in range(tamanho):
        senha+=choice(caracteres)
    return senha     


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
        msg1=msg[0:]
        if msg.startswith(stbyte1):
            self.msg_cnt += 1
          
            salt_master=os.urandom(16)
            self.id_cliente=msg[3:]

            kdf_master = PBKDF2HMAC(     
            algorithm=hashes.SHA256(),
            length=16,
            salt=salt_master,
            iterations=100000,
            backend=backend)
            
            self.MasterPassword=str.encode(password(16)) # gera a MasterPassword e converte para bytes
            id_c=self.id_cliente
            clikey=kdf_master.derive(id_c+self.MasterPassword) #clikey utilizada na rececao da primeira mensagem da sessao, quando o servidor recebe um caracter definido por 
            #self.clikeys.append(clikey)
            keystore_file=open('keystore_id_%s.txt' % str(self.id_cliente.decode()), 'wb') #permite fazer a associação deuma keystore a um único cliente, de acordo com o seu id
            keystore_file.write(salt_master+clikey)    #keystore constituido pelo salt + clikey
            keystore_file.close()
            new_msg='ola'
            new_msg1=new_msg.encode()
            return new_msg1
            process()
        else:
            self.msg_cnt += 1
            iv_cl = msg[0:16]  #apos o envio da priḿeira mensagem de texto, sao divididos os parametros que a constituem
            mac_cli=msg[16:48]
            saltM=msg[48:64]
            salt2=msg[64:80]
            texto=msg[80:]    

            kdf = PBKDF2HMAC(          #KDF utilizando o salt proveniente do cliente-> este salt foi produzido pelo servidor e enviado para ocliente
                algorithm=hashes.SHA256(),
                length=16,
                salt=saltM,
                iterations=100000,
                backend=backend)


            clikey2=kdf.derive(self.id_cliente+self.MasterPassword) 

            kdf2 = PBKDF2HMAC(     
                algorithm=hashes.SHA256(),
                length=32,
                salt=salt2,
                iterations=100000,
                backend=backend)

            sessionkey=kdf2.derive(clikey2)  # sessionkey derivada da clikey2 que resultou da darivacao efetuada com o KDF 

            self.key1=sessionkey[0:16]    # a sessionKey e utilizada na cifra e no hmac, sendo dividida em duas keys
            self.key_mac=sessionkey[16:32] 

            cipher = Cipher(algorithms.AES(self.key1), modes.CTR(iv_cl), backend=backend)
            decryptor = cipher.decryptor()
            txt=decryptor.update(texto)
            print('Utilizador %r : %r' % (self.id_cliente.decode(),txt.decode()))
            
            iv_s = os.urandom(16)
            cipher = Cipher(algorithms.AES(self.key1), modes.CTR(iv_s), backend=backend)
            encryptor = cipher.encryptor()
            ct = encryptor.update(txt) + encryptor.finalize()
            ####################################
            #HMAC
            h=hmac.HMAC(self.key_mac,hashes.SHA256(),backend=default_backend())
            h.update(ct)
            mac_serv = h.finalize() 
            new_msg = iv_s+mac_serv+saltM+salt2+ct
            ########################
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