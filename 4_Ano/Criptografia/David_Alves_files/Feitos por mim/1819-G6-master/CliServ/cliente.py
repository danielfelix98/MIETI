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
import re
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
from OpenSSL import crypto
from cryptography import x509
import ssl, socket
from base64 import (
    b64encode,
    b64decode,
)

backend = default_backend()
conn_port = 8888
max_msg_size = 9999

p=99494096650139337106186933977618513974146274831566768179581759037259788798151499814653951492724365471316253651463342255785311748602922458795201382445323499931625451272600173180136123245441204133515800495917242011863558721723303661523372572477211620144038809673692512025566673746993593384600667047373692203583
g=44157404837960328768872680677686802650999163226766694797650810379076416463147265401084491113667624054557335394761604876882446924929840681990106974314935015501571333024773172440352475358750668213444607353872754650805031912866692119819377041901642732455911509867728218394542745330014071040326856846990119719675


with open("Client_priv_key.bin", "rb") as key_file:
        client_private_key = serialization.load_pem_private_key(
            key_file.read(),
            password=None,
            backend=default_backend()
        ) 

with open("Server_public_key.bin", "rb") as key_file2:    ##key public do cliente proveniente do script gerador
        public_server = serialization.load_pem_public_key(
            key_file2.read(),
            backend=default_backend()
        )  
     
##SSL##
cli_SSL=crypto.load_pkcs12(open("Cliente.p12","rb").read(),"uminho")#abrir ficheiro do cliente
cert_cli=cli_SSL.get_certificate()#certificado
cert_cli_pem=crypto.dump_certificate(crypto.FILETYPE_PEM, cert_cli)#texto do certificado do cliente#3021
cert_cryptography=x509.load_pem_x509_certificate(cert_cli_pem,default_backend())

private_key=cli_SSL.get_privatekey()#chave privada do cliente a partir do cert
private_key_pem=crypto.dump_privatekey(crypto.FILETYPE_PEM, private_key)

private_key_cli_SSL= serialization.load_pem_private_key(private_key_pem, None, default_backend())

#CA_ROOT
CA_cer = crypto.load_certificate(crypto.FILETYPE_PEM,open('ca-chain.cert.pem','rb').read())#certificado CA
CA_pem = crypto.dump_certificate(crypto.FILETYPE_PEM, CA_cer)#certificado CA em pem

#CA_INTERMEDIATE
CA_inter_cer = crypto.load_certificate(crypto.FILETYPE_PEM,open('ca-chain.cert-inter.pem','rb').read())#certificado CA
CA_inter_pem = crypto.dump_certificate(crypto.FILETYPE_PEM, CA_cer)#certificado CA em pem

#CRIACAO DA STORE
store=crypto.X509Store()

#ADICIONA A STORE OS DOIS CERTIFICADOS
store.add_cert(CA_cer)
store.add_cert(CA_inter_cer)

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

            #print("public key length:", len(str(self.public_key_client)))#308
            new_msg=stbyte+id_cliente1+(str(self.public_key_client)).encode()+cert_cli_pem#mensagem inicial a enviar para o servidor
           
            return new_msg if len(new_msg)>0 else None
           
            process()

        if msg.startswith(test2):
            
            startbyte=msg[0:3]
            public_key_serv=int(str(msg[3:311].decode()))
            cert_serv_txt=msg[311:]#certificado do server

            cert_serv =cert_serv_txt 

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
            

            #assinar mensagem
            signature_c = private_key_cli_SSL.sign(
                new,
                padding.PSS(
                    mgf=padding.MGF1(hashes.SHA256()),
                    salt_length=padding.PSS.MAX_LENGTH
                ),
                hashes.SHA256()
            )


            #print(len(signature))#256

            ct = encryptor.update(new) + encryptor.finalize()
            
            #HMAC
            h=hmac.HMAC(self.key_mac,hashes.SHA512(),backend=default_backend())
            h.update(ct)
            mac_sig = h.finalize()
           
            new_msg =iv_c+mac_sig+signature_c+cert_cli_pem+ct  # mensagem a enviar para o servidor, este necessitara do do salM e do salt2, nos kdfs correspondentes
            
            return new_msg if len(new_msg)>0 else None
            process()

        else:
            mac_serv = msg[16:80]
            iv_s=msg[0:16]
            signature_s=msg[80:336]
            cert_serv_pem=msg[336:2548]
            texto = msg[2548:]
            
            ##certificado em cryptography
            cert_cryptography_s=x509.load_pem_x509_certificate(cert_serv_pem,default_backend())
            public_serv_SSL=cert_cryptography_s.public_key()    



            cipher = Cipher(algorithms.AES(self.key1), modes.CTR(iv_s), backend=default_backend())
            decryptor = cipher.decryptor()

            h=hmac.HMAC(self.key_mac,hashes.SHA512(),backend=default_backend())
            h.update(texto)
            mac_sig = h.finalize() 
           

            txt=decryptor.update(texto) + decryptor.finalize()
            msg=txt.decode()
    
            
            #converte do cryptography para pyopenSSL
            cert_serv_object=crypto.load_certificate( 
                crypto.FILETYPE_PEM, 
                cert_cryptography_s.public_bytes(serialization.Encoding.PEM)) 
            

            store_s=crypto.X509StoreContext(store,cert_serv_object)
    
            subject = cert_serv_object.get_subject()
            issued_to = subject.CN #autor do certificado

            result_servidor=store_s.verify_certificate()#Verfica o certificado do servidor

            if result_servidor is None:
                if(issued_to =='Servidor'):
                    print("Certificado do %r verificado com sucesso" % issued_to)
    
            else:
                print("ERRO: Certificado do Servidor nao verificado")
                writer.close()

            public_serv_SSL.verify(
                signature_s,
                txt,
                padding.PSS(
                    mgf=padding.MGF1(hashes.SHA256()),
                    salt_length=padding.PSS.MAX_LENGTH
                ),
                hashes.SHA256()
            )


            if(mac_sig==mac_serv):
                
                print("Assinatura verificada com sucesso")    
                print('Mensagem recebida: %r' % (msg))
                print("------------------------------------")
                print('Escreva a nova mensagem a enviar:')
                new = input().encode()
                iv_c = os.urandom(16)
                cipher = Cipher(algorithms.AES(self.key1), modes.CTR(iv_c), backend=default_backend())
                encryptor = cipher.encryptor()
                ct = encryptor.update(new) + encryptor.finalize()
                #assinar
                
                signature = private_key_cli_SSL.sign(
                    new,
                    padding.PSS(
                        mgf=padding.MGF1(hashes.SHA256()),
                        salt_length=padding.PSS.MAX_LENGTH
                    ),
                    hashes.SHA256()
                )
        

                new_msg= iv_c+mac_sig+signature+cert_cli_pem+ct
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
