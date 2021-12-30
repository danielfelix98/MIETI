# Guião 2
### Enunciado
##### Refinamento do guião 1

No guião da semana passada fez-se uso da cifra autenticada `Fernet` que
garante simultaneamente ('i') a confidencialidade dos dados e ('ii') a
integridade da informação. Neste curso interessa-nos perceber como é que
essas propriedades podem ser estabelecidas a partir das várias técnicas
criptográficas disponível. Assim, nesta semana iremos realizar a mesma
funcionalidade recorrendo directamente de uma cifra simétrica e de um
MAC. Sugere-se a utilização de `ChaCha20` como cifra, e de `HMAC-Sha256`
como MAC.

Do ponto de vista de segurança, o aspecto mais crítico no guião da
semana passada é o tratamento dado aos segredos criptográficos
utilizados. De facto, e para além de se certificar que se recorre
sempre a um **gerador de números aletórios seguro**, é em geral
desaconselhado armazenar segredos criptográficos em ficheiros sem
qualquer protecção.

Existem duas estratégias para evitar gravar esses ficheiros desprotegidos:

 1. Evitar a necessidade de se armazenar a chave. Para isso, considera-se
 um mecanismo seguro que permita gerar um segredo criptográfico a partir
 de uma _password_ ou _passphrase_ (que naturalmente não podem ser utilizadas
 directamente como chaves criptográficas). Para o efeito faz-se uso das
 designadas _Password Based Key Derivation Functions (PBKDF)_.
 1. Armazenar o ficheiro de forma protegida, no que se designa
 habitualmente por *KeyStore*. Na realidade, esta estratégia acaba por
 partilhar muitos dos requisitos da apresentada antes, porque para
 protegermos a 'KeyStore' irá ter de (internamente) usar uma cifra
 autenticada, e para isso de um novo segredo. Mas, tal como no ponto anterior,
 esse segredo é geralmente gerado a partir de uma _password_.
 
Pretende-se assim adicionar à funcionalidade pedida no guião anterior
a protecção dos segredos de acordo com a primeira das estratégias
apresentadas. 

Sugestões:

 * Como mecanismo de PBKDF, utilize o `PBKDF2`
 
 
### Resolução e instruções

A resolução deste guião está presente no ficheiro g02.py

Instruções:

◆ Mover os ficheiros g02.py e para_encriptar.txt para o mesmo directório 

◆ Executar a script g02.py e verificar que são imprimidos: o conteúdo da mensagem a encriptar, a mensagem encriptada, e a mensagem desencriptada

◆ Verificar que foi criado (se não existir) um ficheiro chamado msg_encriptada.txt que vai servir para ler o conteúdo da mensagem após a encriptação e a partir daí desencriptar e um outro chamado desencriptado.txt com o mesmo conteúdo da mensagem desencriptada.
