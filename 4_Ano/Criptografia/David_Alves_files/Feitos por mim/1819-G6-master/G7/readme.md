# Guião 7

## Enunciado
### Manipulação de Certificados X509

O objectivo nesta semana é o de se investigar formas de validar _cadeias de certificados_ em _Python_, por forma a virmos a utilizar esses certificados na aplicação clente-servidor que temos vindo a implementar. Para tal, disponibiliza-se:

 1. Uma _keystore_ PKCS12 contendo o Certificado (e respectiva chave privada) para o rervidor: [Servidor.p12](Servidor.p12)
 1. Uma _keystore_ PKCS12 contendo o Certificado (e respectiva chave privada) para o cliente: [Cliente.p12](Cliente.p12) 
 1. O Certificado (em formato DER) da CA utilizada: [CA.cer](CA.cer)

Para aceder ao conteúdo das `Keystores` devem utilizar a password "1234" (quer para carregar a `keystore`, quer para aceder à entrada respectiva (o `alias` é `Cliente1` e `Servidor` para as keystores `Cliente.p12` e `Servidor.p12` respectivamente).

Numa primeira fase, utilizaremos ferramentas de domínio público directamente na linha-de-comando. Concretamente, utilizaremos o [openSSL](https://www.openssl.org), e em particular os sub-comandos [`pkcs12`](https://www.openssl.org/docs/manmaster/man1/openssl-pkcs12.html) e [`verify`](https://www.openssl.org/docs/manmaster/man1/verify.html) (ver respectiva documentação).

Uma vez ultrapassado esse passo, vamos considerar como transpor esse método de validação para o _Python_, por forma a ser usável na aplicação que temos vindo a desenvolver. A dificuldade é que as bibliotecas que temos vindo a utilizar não dispõe dessa funcionalidade, pelo que se sugere a instalação/utilização da biblioteca [PyOpenSSL](https://pyopenssl.org/en/stable/index.html).

Referências adicionais:
 - http://www.yothenberg.com/validate-x509-certificate-in-python/
 - http://aviadas.com/blog/2015/06/18/verifying-x509-certificate-chain-of-trust-in-python/

---

### Explicação dos Comandos utilizados

Os comandos utilzados na _bash_ estão disponíveis no ficheiro "comandos"

Comando para converter Servidor.p12 para o formato .pem:

`openssl pkcs12 -in Servidor.p12 -out file_serv.pem`


Comando para converter Cliente.p12 para o formato .pem: 

`openssl pkcs12 -in Cliente.p12 -out file_cli.pem`


Comando para converter o certificado CA.cer para o formato .pem:

`openssl x509 -inform der -in CA.cer -out certificate.pem`


Comando para concatenar o file_cli.pem com o certificate.pem e guardar o resultado em trust_serv.pem:

`cat file_serv.pem certificate.pem > trust_serv.pem`


Comando para concatenar o file_serv.pem com o certificate.pem e guardar o resultado em trust_cli.pem:

`cat file_cli.pem certificate.pem > trust_cli.pem`

Comando para verificar o trust_serv.pem com o certificate.pem:

`openssl verify -CAfile trust_serv.pem certificate.pem`

Comando para verificar o trust_cli.pem com o certificate.pem:

`openssl verify -CAfile trust_cli.pem certificate.pem`
