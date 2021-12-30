# Guião 1
### Enunciado
##### Aplicação de exemplo: Cifra autenticada de Ficheiro

Pretende-se cifrar o conteúdo de um ficheiro, assegurando a
*confidencialidade* e *integridade* dos dados lá armazenados.
Para o efeito deve o mecanismo de cifra autenticada _Fernet_,
disponibilizada pela biblioteca _cryptography_.

### Resolução e instruções
A resolução deste guião está presente no ficheiro g01.py

Instruções:

◆ Mover os ficheiros g01.py e para_encriptar.txt para o mesmo directório 

◆ Executar a script g01.py e verificar que são imprimidos: o conteúdo da mensagem a encriptar, a mensagem encriptada, e a mensagem colocada no ficheiro desencriptado.txt

◆ Verificar que foi criado (se não existir) um ficheiro chamado desencriptado.txt com o mesmo conteúdo da mensagem para encriptar

- - -
Observações:

Se apenas se quiser encriptar o ficheiro basta no código de g01.py alterar na última de código, onde está decrypt() e substituir por encrypt(), e pode-se verificar qual o conteúdo da mensagem a enviar e o conteúdo da mensagem encriptada.
- - -
