
# Guião 8
## Enunciado
### Finalização do protocolo StS usando certificados

No guião desta semana vamos concluir a implementação do protocolo _Station_to_Station_ fazendo uso de certificados X509. Para tal vamos incorporar a funcionalidade explorada no último guião (validação dos certificados), por forma a assegurar a cada um dos intervenientes que fazem uso da chave pública correcta na verificação da assinatura.

Concretamente, o protocolo a implementar irá ser então:
1. Alice → Bob : g<sup>x</sup>
1. Bob → Alice : g<sup>y</sup>, Sig<sub>B</sub>(g<sup>x</sup>, g<sup>y</sup>), Cert<sub>B</sub>
1. Alice → Bob :  Sig<sub>A</sub>(g<sup>x</sup>, g<sup>y</sup>), Cert<sub>A</sub>
1. Alice, Bob : K = g<sup>(x*y)</sup>

Note que os pares de chave a utilizar neste guião são os fornecidas nas _keystores_ PKCS12 fornecidos no guião 7.

Intruções de utilização:
  
1.Mover os ficheiros cliente.py, servidor.py e genkeypair.py para a mesma deretoria

2.Execuitar a script genkeypair.py e verificar verificar que são criados os ficheiros correspondentes às privada e pública

3.Executar o servidor e em seguida o cliente
  
  ---
  Exemplo de execução:
  
  Cliente
  ```
  Conexão establecida com o servidor
Digite o seu id:
3
Escreva a 1ª mensagem a enviar:
ola
Certificado do 'Servidor' verificado com sucesso
Assinatura verificada com sucesso
Mensagem recebida: 'ola'
------------------------------------
Escreva a nova mensagem a enviar:
Boa tarde
Certificado do 'Servidor' verificado com sucesso
Assinatura verificada com sucesso
Mensagem recebida: 'Boa tarde'
------------------------------------
Escreva a nova mensagem a enviar:
```

Servidor 

```
Serving on ('127.0.0.1', 8888)
  (type ^C to finish)

Certificado do 'Cliente' verificado com sucesso
Utilizador '3' : 'ola'
Certificado do 'Cliente' verificado com sucesso
Utilizador '3' : 'Boa tarde'

```
