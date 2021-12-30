# _EFAIL_-A falha de segurança no _OpenPGP_ e _S/MIME_
 Actualmente nas comunicações de _e-mail_, as mensagens são encriptadas usando criptografia simétrica, sendo as chaves geradas apenas 
para uma comunicação e são baseadas num segredo partilhado que é negociado no início de cada  comunicação, e por isso usa-se o protocolo
_TLS_ na comunicação  de _e-mail standard_. Contudo  por vezes existem  situações em que as  comunicações necessitam de ser altamente 
confidenciais e o protocolo _TLS_ pode não ser suficiente, (até porque o protocolo _TLS_  deriva do _SSL_, um protocolo que acabou por 
ser  proibído  devido  a  várias  vulnerabilidades  de  segurança,  sobretudo  a  ataques _man-in-the-middle_). Para responder a estas
necessidades e vulnerabilidades do _TLS_, implementaram-se  protocolos  como  o _OpenPGP_ e _S/MIME_ que têm uma encriptação 
_end-to-end_, (sistema de comunicações no  qual  apenas  os  intervenientes  da comunicação podem ter acesso às mensagens, 
não permitindo sequer o _ISP_(fornecedor  de  _internet_)  ter  acesso  às  mesmas). Como nota histórica, Edward Snowden, 
quando contactou a jornalista Laura Poitras sobre  aquilo  que  viria  a  ser  o  grande escândalo da falta de privacidade na internet,
usou _OpenPGP_.


Em 2018, 8 investigadores, que cujo nome deve ser referido, Damian Poddebniak, Christian Dresen, Jens Müller, Fabian Ising, Sebastian 
Schinzel, Simon Friedberger, Juraj Somorovsky e Jörg Schwenk, como parte da sua participação na _USENIX_, descobriram vulnerabilidades 
nos protocolos _OpenPGP_ e _S/MIME_ em comunicações de _e-mail_, o que criou uma grande surpresa na comunidade criptográfica e dividiu 
muitas opiniões, havendo desde aqueles que diziam que  o _OpenPGP_ estava “morto” e não devia ser usado, e aqueles que diziam que o 
problema não estava no _OpenPGP_, mas sim em alguns clientes de _e-mail_ que usam o protocolo. A esta falha foi-lhe atribuído o nome de _EFAIL_, e basicamente retrata o seguinte ataque: numa primeira fase o atacante tem que ter acesso aos _e-mails_ encriptados, (isto pode ser feito através de captura de trafego de uma rede ou atacando contas de _e-mail_, servidores ou computadores, entre outros). O atacante altera o _e-mail_ encriptado, adicionando, (usando _HTML_), conteúdo externo, como por exemplo, imagens colocadas num servidor com um determinado _URL_, e envia-o para a vítima. O cliente de _e-mail_ da vítima desencripta o _e-mail_ e lê o conteúdo externo de um dado _URL_, isto vai fazer com que em alguns clientes de _e-mail_, o texto limpo seja possível de obter pelo atacante. 


Existem dois tipos de ataques _EFAIL_: _direct exfiltration_ e _CBC/CFB Gadget Attack_.

O _direct exfiltration_ funciona da seguinte forma: O atacante cria um novo código _HTML_, constituído por três partes, a primeira 
contém o _URL_ de uma imagem, por exemplo, deixando aberto o atributo _src_ o que faz com que se possa adicionar mais dados a esse 
atributo, e é isso que é feito na segunda parte, esta contém o _e-mail_ encriptado que é assim adicionado ao atribuito _src_ que já 
continha uma imagem, a terceira parte serve apenas para fechar o conteúdo do atributo _src_. De seguida, o atacante envia este _e-mail_ 
para a vítima. O cliente de _e-mail_ da vítima desencripta a segunda parte do _HTML_ enviado e coloca o conteúdo desencriptado das três 
partes num único _HTML_. De seguida o cliente de _e-mail_, vai fazer um pedido ao _URL_ presente na primeira parte do _HTML_ 
desencriptado, codificando todos os  caracteres não imprimíveis, (por exemplo %20 para espaços entre palavras), adiciona ao _URL_ o 
conteúdo da mensagem  desencriptada. Como é óbvio, uma vez que o atacante é administrador do website onde se encontra a imagem e por 
isso poderá ver facilmente quais foram os pedidos feitos ao seu servidor do _website_, podendo assim obter o texto limpo.


O _CBC/CFB Gadget Attack_ é um método, na minha opinião mais lento e complicado, no entanto também pode ser eficaz e deve-se ao facto de 
a cifra utilizada no protocolo _S/MIME_ ser _CBC_, no qual, um atacante pode alterar os blocos de texto limpo, se souber qual o 
texto limpo, o que torna o _S/MIME_ ainda mais vulnerável, uma vez que os _e-mails_ encriptados usando _S/MIME_ geralmente começam 
por “_Content-type: multipart/signed_". Sabendo isto poderá assim tentar-se combinar vários blocos de texto limpo que já conhecemos o 
seu conteúdo, juntamente com blocos de texto cifrado que não sabemos o conteúdo e de seguida desencriptar, como consequência disto, o 
texto limpo fica ilegível, o atacante poderá corrigir isto com a adição de gadgets, (técnicas de alterar a saída de determinadas 
funções), sendo que assim o atacante poderá inserir no meio dos blocos de texto limpo que não conhece, as tags de _HTML_ que inserem a 
leitura de conteúdos externos ao _e-mail_. Este método funciona também no _OpenPGP_, que usa a cifra _CFB_. No entanto ao contrário do 
_S/MIME_, o _OpenPGP_ disponibiliza _Modification Detection Code (MDC)_ que consegue detetar texto limpo modificado, no entanto  estes 
investigadores do _EFAIL_ descobriram que alguns clientes de _e-mail_ simplesmente mostram um aviso quando existe um texto limpo 
modificado e continuam a mostrar o seu conteúdo.


Estes investigadores deixaram algumas recomendações aos fornecedores de clientes de _e-mail_ para evitar estes ataques, algumas delas são: Remover a desencriptação no cliente de _e-mail_, sendo que para isso as chaves privadas de remetente e do destinatário não poderiam estar armazenadas no cliente de _e-mail_, e sendo assim  o cliente de _e-mail_ apenas serveria para enviar e receber mensagens encriptadas, e depois essas mensagens encriptadas seriam desencriptadas numa aplicação à parte, desta forma o atacante não poderia inserir a abertura de conteúdo externo; Desativar o conteúdo ativo presente em _HTML_ ou _JavaScript_, tais como a apresentação de imagens, entre outros;Atualizar os standards do _S/MIME_ e do _OpenPGP_.


O facto do _EFAIL_ ter gerado polémica deve-se também por ter mostrado estas falhas em clientes de _e-mail_ usados por um grande 
número de pessoas. Alguns do clientes de _e-mail_ nos quais se verificaram os ataques _EFAIL_ foram: _Thunderbird_, _Apple Mail_, _iOS Mail_, _GMail_, _Outlook 2016_, _Windows 10 Mail_, entre outros. De todos, aqueles dos quais não se conseguiu obter com sucesso os ataques _EFAIL_ tanto em _S/MIME_ como em _OpenPGP_, são o _Claws_ e o _Mutt_ (curiosamente, não tão populares como aqueles nos quais se conseguiu atacar).

Por tudo isto, e analisados todos os aspetos, na minha opinião, não creio que o _OpenPGP_ ou _S/MIME_ estejam “mortos“, como dizem 
alguns investigadores, sobretudo porque aquilo que se provou foi que o problema não está no _OpenPGP_ ou no _S/MIME_ mas sim nos 
clientes de  _e-mail_. Eu, se tivesse que escolher entre _OpenPGP_ ou _S/MIME_, escolhia _OpenPGP_ para as minhas comunicações sobretudo 
pelo facto de disponibilizar _Modification Detection Code (MDC)_, o que mesmo que em alguns clientes de _e-mail_ apenas seja mostrado um aviso, já é um ganho significativo em relação ao _S/MIME_. No entanto também acho que os mecanismos do _OpenPGP_ e do _S/MIME_(sendo que na minha opinião o _S/MIME_ cairá em desuso) deviam ser atualizados, para dificultar estes ataques _EFAIL_.

---
Fontes:

https://efail.de/

https://en.wikipedia.org/wiki/Transport_Layer_Security

https://en.wikipedia.org/wiki/Pretty_Good_Privacy

https://en.wikipedia.org/wiki/End-to-end_encryption

https://en.wikipedia.org/wiki/S/MIME

---
Como forma de demonstração deste  tipo de ataque, fiz um conjunto de scripts em _python_, e para se poder observarem devem-se seguir os seguintes passos:

1.Executar _script_ Alice.py

2.Escrever nesse programa a mensagem a enviar para o Bob

3.Executar a _script_ EFAIL.py

4.Nesse programa, inserir o endereço para o qual as mensagens vão ser redirecionadas(No meu exemplo eu escolhi efail.pt)

(Verificar que o site digitado é adicionado ao lista.txt)

5.Executar a _script_ cliente_de_email_Bob.py 

6.Verificar que o Bob recebeu a mensagem da Alice 

7.Abrir o ficheiro criado para o endereço digitado no passo 4, e verificar que sao mostradas as mensagens(url+mensagem)
