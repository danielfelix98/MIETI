# Guião 3

## Enunciado

### Refinamentos sobre o guião anterior

Por forma a melhorar as características da implementação do guião da semana passada em termos de segurança e usabilidade, pretende-se refinar a respectiva solução para incorporar as soluções analisadas na última aula. Seguem-se as principais características dessas propostas:

 - O servidor é responsável por gerar, na fase de inicialização do sistema, segredos criptográficos para cada um dos clientes. Nesta fase assume-se a existência de canais de comunicação seguros entre o servidor e clientes.
 - Os clientes armazenam o segredo (chave de acesso) recebido do servidor numa 'keystore'. Quando pretenderem iniciar uma ligação, derivam uma chave de sessão a partir dessa chave de acesso.
 - O servidor, ao estabelecer ligação com um cliente, irá recalcular a chave de acesso do respectivo cliente e a partir dessa chave calcular a chave de sessão da respectiva ligação.

---

### Instruções de uso

1.Executar a script servidor.py e de seguida a script cliente.py 

2.Escrever as mensagens no cliente e verificar que estas são imprimidas no servidor.

NOTA: Neste programa o id que identifica os vários clientes é automaticamente atribuído, recorremos para que isso acontecesse ao contador de ligação que já estava definido no código fornecido pelo professor.
