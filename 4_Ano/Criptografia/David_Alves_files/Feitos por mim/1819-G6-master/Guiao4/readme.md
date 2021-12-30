# Guião 4
### Enunciado
#### Refinamentos sobre o guião anterior

Por forma a melhorar as características da implementação do guião da semana passada em termos de segurança e usabilidade, pretende-se refinar a respectiva solução para incorporar as soluções analisadas na última aula. Seguem-se as principais características dessas propostas:

 - O servidor é responsável por gerar, na fase de inicialização do sistema, segredos criptográficos para cada um dos clientes. Nesta fase assume-se a existência de canais de comunicação seguros entre o servidor e clientes.
 - Os clientes armazenam o segredo (chave de acesso) recebido do servidor numa 'keystore'. Quando pretenderem iniciar uma ligação, derivam uma chave de sessão a partir dessa chave de acesso.
 - O servidor, ao estabelecer ligação com um cliente, irá recalcular a chave de acesso do respectivo cliente e a partir dessa chave calcular a chave de sessão da respectiva ligação.

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
