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

from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import serialization

from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.asymmetric import rsa

def par_server():
	private_key = rsa.generate_private_key(
		public_exponent=65537,
		key_size=2048,
		backend=default_backend()
	)


	public_key = private_key.public_key()

	pemPublicKey = public_key.public_bytes(
	    encoding=serialization.Encoding.PEM,
		format=serialization.PublicFormat.SubjectPublicKeyInfo
	)



	pemPrivateKey = private_key.private_bytes(
		encoding=serialization.Encoding.PEM,
		format=serialization.PrivateFormat.TraditionalOpenSSL,
		encryption_algorithm=serialization.NoEncryption()
	)



	file1=open("Server_priv_key.bin","wb")
	file1.write(pemPrivateKey)
	file1.close()


	file2=open("Server_public_key.bin","wb")
	file2.write(pemPublicKey)
	file2.close()


def par_cliente():
		
	private_key = rsa.generate_private_key(
		public_exponent=65537,
		key_size=2048,
		backend=default_backend()
	)


	public_key = private_key.public_key()

	pemPublicKey = public_key.public_bytes(
	    encoding=serialization.Encoding.PEM,
		format=serialization.PublicFormat.SubjectPublicKeyInfo
	)



	pemPrivateKey = private_key.private_bytes(
		encoding=serialization.Encoding.PEM,
		format=serialization.PrivateFormat.TraditionalOpenSSL,
		encryption_algorithm=serialization.NoEncryption()
	)



	file3=open("Client_priv_key.bin","wb")
	file3.write(pemPrivateKey)
	file3.close()


	file4=open("Client_public_key.bin","wb")
	file4.write(pemPublicKey)
	file4.close()


par_cliente()
par_server()