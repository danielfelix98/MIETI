# Código baseado em https://docs.python.org/3.6/library/asyncio-stream.html#tcp-echo-client-using-streams
import asyncio
import os
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC
from cryptography.hazmat.primitives import hashes, hmac

backend = default_backend()
conn_cnt = 0
conn_port = 8888
max_msg_size = 9999

file=open("key.txt","wb");
backend=default_backend()
salt=os.urandom(16)

kdf = PBKDF2HMAC(     
    algorithm=hashes.SHA256(),
    length=32,
    salt=salt,
    iterations=100000,
    backend=backend
)

key=kdf.derive(b"mypassword")

key1=key[0:16]   
key_mac=key[16:32] 

file.write(key)
file.close()

class ServerWorker(object):
    """ Classe que implementa a funcionalidade do SERVIDOR. """
    def __init__(self, cnt, addr=None):
        """ Construtor da classe. """
        self.id = cnt
        self.addr = addr
        self.msg_cnt = 0
    def process(self, msg):
        """ Processa uma mensagem (`bytestring`) enviada pelo CLIENTE.
            Retorna a mensagem a transmitir como resposta (`None` para
            finalizar ligação) """
        self.msg_cnt += 1
            
        iv_cl = msg[0:16]
        mac_cli=msg[16:48]
        texto=msg[48:]    

        cipher = Cipher(algorithms.AES(key1), modes.CTR(iv_cl), backend=backend)
        decryptor = cipher.decryptor()
        txt=decryptor.update(texto) 
        
        print('%d : %r' % (self.id,txt.decode()))
        
        iv_s = os.urandom(16)
        cipher = Cipher(algorithms.AES(key1), modes.CTR(iv_s), backend=backend)
        encryptor = cipher.encryptor()
        ct = encryptor.update(txt) + encryptor.finalize()
        ####################################
        #HMAC
        h=hmac.HMAC(key_mac,hashes.SHA256(),backend=default_backend())
        h.update(ct)
        mac_serv = h.finalize() 
        new_msg = iv_s+mac_serv+ct
        ########################
        return new_msg if len(new_msg)>0 else None


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
