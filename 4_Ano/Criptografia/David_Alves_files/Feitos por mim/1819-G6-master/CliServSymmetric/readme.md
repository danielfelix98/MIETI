# CliServSymmetric
 
 -Neste programa o servidor gera os segredos criptográficos (chaves) de cada cliente.
 -Cada cliente guarda a sua chave, que foi enviada pelo servidor, numa keystore. Para iniciar a comunicação, é necessário derivar uma chave de sessão a partir de uma chave de acesso.
 -O servidor recalcula a chave de acesso do cliente. Em seguida,determinar a chave de sessão.
 

### Resolução e instruções
A resolução deste guião está presente nos ficheiros servidor.py e cliente.py



Instruções:

◆ Mover os ficheiros cliente.py e servidor.py para o mesmo directório 

◆ Executar a script servidor.py e de seguida executar cliente.py

◆ Na execução de cliente.py, inserir o id de utilizador e verificar que foi criado uma keystore única (keystore_id_"nº de utilizador".txt) para esse utilizador

◆ De seguida, enviar a mensagem pretendida e verificar que a mesma aparece no display do servidor

Exemplo:

```
SERVIDOR:
python3 servidor.py
Serving on ('127.0.0.1', 8888)
  (type ^C to finish)

Utilizador '1' : 'ola'
Utilizador '2' : 'bom dia'




CLIENTE1:
python3 cliente.py

Conexão establecida com o servidor
Digite o seu id:
1
Escreva a 1ª mensagem a enviar:
ola 
Palavra-passe verificada com sucesso
Mensagem recebida: 'ola'
------------------------------------
CLIENTE2:
python3 cliente.py
Conexão establecida com o servidor
Digite o seu id:
2
Escreva a 1ª mensagem a enviar:
bom dia
Palavra-passe verificada com sucesso
Mensagem recebida: 'bom dia'
```
