

# Guião 9
## Enunciado
### Geração de Certificados para a aplicação

Para concluir a aplicação Cliente/Servidor pretende-se gerar os certificados requeridos. Para tal deve
usar qualquer das várias sugestões de software livre disponívies para o efeito - uma escolha óbvia é naturalmente
o `openssl` a que já recorremos antes, mas preferindo podem utilizar uma solução de mais alto nível, como a [EJBCA](https://www.ejbca.org).

Alguns apontadores:
 * http://pki-tutorial.readthedocs.io/en/latest/expert/
 * https://jamielinux.com/docs/openssl-certificate-authority/index-full.html
 * https://roll.urown.net/ca/ca_intermed_setup.html
 
 ## Resolução
Para a criação dos certificados de cliente e servidor bem como dos certificados das autoridades de certificação recorremos ao tutorial presente neste link  https://jamielinux.com/docs/openssl-certificate-authority/index-full.html , sendo que neste directorio está também presente a pasta e subpastas resultantes, a pasta tem o nome de ``root``. De seguida "comprimiu-se" a chave privada usada na criação do certificado do cliente e do servidor, com esses mesmos certificados. O comando utilizado para o servidor.p12 foi:``openssl pkcs12 -export -out server.p12 -inkey www.uminho.pt.key.pem -in servidor.cert.pem -certfile intermediate.cert.pem
 `` e para o cliente.p12 foi: ``openssl pkcs12 -export -out cliente.p12 -inkey www.uminho.pt.key.pem -in cliente.cert.pem -certfile intermediate.cert.pem``. Depois recorrendo ao código _Python_ desenvolvido no guiao 8 alterando apenas alguns parâmetros, tais como acrescentar mais uma leitura  de ficheiro devido ao facto de termos um certificado de root e de intermediate tendo estes os nomes de ``ca-chain.cert`` e  ``ca-chain.cert-inter`` respetivamente.


 ## Instruções de uso
 1.Mover todos os ficheiros para o mesmo directorio
 
 2.Executar a script _python_ servidor.py e de seguida a script cliente.py
 
```
NOTA:Devido ao facto do método de criação de chaves de encriptação utilizado(método do Diffie-Hellman 
da biblioteca cryptography) não ser propriamente imediato, recomenda-se que após se executar cada 
script(servidor e cliente) aguardar cerca de 3  segundos antes de introduzir qualquer dado no cliente.
Como exemplo recomendado sugere-se a introdução dos dados presentes no seguinte exemplo:
```
Cliente1:
```
Conexão establecida com o servidor
Digite o seu id:
1
Escreva a 1ª mensagem a enviar:
ola
Certificado do 'Servidor' verificado com sucesso
Assinatura verificada com sucesso
Mensagem recebida: 'ola'
------------------------------------
```

Cliente2:
```
Conexão establecida com o servidor
Digite o seu id:
2
Escreva a 1ª mensagem a enviar:
boa tarde
Certificado do 'Servidor' verificado com sucesso
Assinatura verificada com sucesso
Mensagem recebida: 'boa tarde'
------------------------------------
```

 
 
 
 
Servidor:
``` 
Certificado do 'Cliente' verificado com sucesso
Utilizador '1' : 'ola'
Certificado do 'Cliente' verificado com sucesso
Utilizador '2' : 'boa tarde'

``` 
 
