# Guião 5
### Enunciado
#### Protocolo *Diffie-Hellman*

Pretende-se implementar o protocolo de acordo de chaves *Diffie-Hellman*. Para tal,
iremos fazer uso da funcionalidade oferecida pela biblioteca `cryptography`, em particular
da classe [`dh`](https://cryptography.io/en/latest/hazmat/primitives/asymmetric/dh/).

Relembre a sequência de mensagens trocadas no protocolo *Diffie-Hellman*:

 1. Alice → Bob : g<sup>x</sup>
 1. Bob → Alice : g<sup>y</sup>
 1. Alice, Bob : K<sup>master</sup> = g<sup>(x*y)</sup>

Onde `g` é um gerador de um grupo cíclico de ordem prima `p`, `x` e `y` são elementos aleatórios do grupo, e `K<sup>master</sup>` é o segredo estabelecido pelo protocolo, que deve ser usado para derivar as chaves criptográficas requeridas (e.g. recorrendo à função de hash `SHA-512`). 

Se facilitar, podem começar por considerar os seguintes parâmetros na definição do grupo:

```
P = 99494096650139337106186933977618513974146274831566768179581759037259788798151499814653951492724365471316253651463342255785311748602922458795201382445323499931625451272600173180136123245441204133515800495917242011863558721723303661523372572477211620144038809673692512025566673746993593384600667047373692203583
G = 44157404837960328768872680677686802650999163226766694797650810379076416463147265401084491113667624054557335394761604876882446924929840681990106974314935015501571333024773172440352475358750668213444607353872754650805031912866692119819377041901642732455911509867728218394542745330014071040326856846990119719675
```


Instruções:

◆ Mover os ficheiros cliente.py e servidor.py para o mesmo directório 

◆ Executar a script servidor.py e de seguida executar cliente.py

◆ De seguida, enviar a mensagem pretendida e verificar que a mesma aparece no display do servidor

NOTA:Neste protocolo, não haverá ficheiros com dados do cliente e/ou servidor, tendo-se verificado corretamente que tal como pretendido ambos os lados(cliente e servidor), conseguem através de parâmetros partilhados entre eles e parâmetros privados criar uma mesma chave, a que por conveniência poderá chamar-se chave de sessão.

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
