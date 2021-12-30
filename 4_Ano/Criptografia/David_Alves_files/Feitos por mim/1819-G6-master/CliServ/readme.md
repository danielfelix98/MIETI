# CliServ

Para inicializar o programa deve-se esperar 3 segundos, após a execução do servidor e do cliente. Caso contrário ocorre erro na criação da chave pública, não sendo possível realizar a conver são para inteiro. Em seguida encontra-se representado o erro.

```
ValueError: invalid literal for int() with base 10: '5220593785710147243340623460306947491632444526889522112018837332829933370379984402989304847637028603210956953798480719707854526888662897107122645518400131464226047061466182382785068035755137808992457
```

## Proposta de resolução
Para a criação dos certificados de cliente e servidor bem como dos certificados das autoridades de certificação recorremos ao tutorial presente neste link  https://jamielinux.com/docs/openssl-certificate-authority/index-full.html , sendo que neste directorio está também presente a pasta e subpastas resultantes, a pasta tem o nome de ``root``. De seguida "comprimiu-se" a chave privada usada na criação do certificado do cliente e do servidor, com esses mesmos certificados. O comando utilizado para o servidor.p12 foi:``openssl pkcs12 -export -out server.p12 -inkey www.uminho.pt.key.pem -in servidor.cert.pem -certfile intermediate.cert.pem
 `` e para o cliente.p12 foi: ``openssl pkcs12 -export -out cliente.p12 -inkey www.uminho.pt.key.pem -in cliente.cert.pem -certfile intermediate.cert.pem``. Depois recorrendo ao código _Python_ desenvolvido no guiao 8 alterando apenas alguns parâmetros, tais como acrescentar mais uma leitura  de ficheiro devido ao facto de termos um certificado de root e de intermediate tendo estes os nomes de ``ca-chain.cert`` e  ``ca-chain.cert-inter`` respetivamente.Para criação de chaves de encriptação usamos o método presente na biblioteca _diffie-hellman_ do _cryptography_.E para a criação de chaves de assinatura usamos a biblioteca RSA do _cryptography_ sendo que para serem geradas novas chaves pode-se executar a script genkeypair.py  presente neste diretório.


### Exemplo de execução
1. Mover todos os ficheiros para a mesma diretoria
2. Executar o servidor.py e em seguida o cliente.py

```
Servidor
  Serving on ('127.0.0.1', 8888)
    (type ^C to finish)

  Certificado do 'Cliente' verificado com sucesso
  Utilizador '1' : 'ola'
  Certificado do 'Cliente' verificado com sucesso
  Utilizador '1' : 'Bom dia'
 
Cliente
  Conexão establecida com o servidor
  Digite o seu id:
  1
  Escreva a 1ª mensagem a enviar:
  ola
  Certificado do 'Servidor' verificado com sucesso
  Assinatura verificada com sucesso
  Mensagem recebida: 'ola'
  ------------------------------------
  Escreva a nova mensagem a enviar:
  Bom dia
  Certificado do 'Servidor' verificado com sucesso
  Assinatura verificada com sucesso
  Mensagem recebida: 'Bom dia'
  ```

  
  
