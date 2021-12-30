from OpenSSL import crypto

serv=crypto.load_pkcs12(open("Servidor.p12","rb").read(),"1234")
cli=crypto.load_pkcs12(open("Cliente.p12","rb").read(),"1234")

cert_serv=serv.get_certificate()
cert_cli=cli.get_certificate()

private_key_serv=serv.get_privatekey()
private_key_cli=cli.get_privatekey()

def Verify():
	CA_cer = crypto.load_certificate(crypto.FILETYPE_ASN1,open('CA.cer','rb').read())
	CA_pem = crypto.dump_certificate(crypto.FILETYPE_PEM, CA_cer)
	store=crypto.X509Store()
	store.add_cert(CA_cer)
	store_c = crypto.X509StoreContext(store, cert_cli)
	store_s = crypto.X509StoreContext(store, cert_serv)
	result_cliente=store_c.verify_certificate()
	
	if result_cliente is None:
		print("Cliente verificado") 

	else:
		print("Cliente nao verificado")

	result_servidor=store_s.verify_certificate()
	
	if result_servidor is None:
		print("Servidor verificado")

	else:
		print("Servidor nao verificado")


Verify()

