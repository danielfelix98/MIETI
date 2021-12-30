# Guião 6
### Enunciado
#### Protocolo *Station-to-Station* simplificado

Pretende-se complementar o programa com o acordo de chaves *Diffie-Hellman* para incluir a funcionalidade
análoga à do protocolo *Station-to-Station*. Recorde que nesse protocolo é adicionado uma troca de assinaturas:

1. Alice → Bob : g<sup>x</sup>
1. Bob → Alice : g<sup>y</sup>, Sig<sub>B</sub>(g<sup>x</sup>, g<sup>y</sup>)
1. Alice → Bob :  Sig<sub>A</sub>(g<sup>x</sup>, g<sup>y</sup>)
1. Alice, Bob : K = g<sup>(x*y)</sup>

De notar que um requisito adicional neste protocolo é a manipulação de pares de chaves assimétricas para realizar as assinaturas digitais (e.g. RSA). Para tal deve produzir um pequeno programa que gere os pares de chaves para cada um dos intervenientes e os guarde em ficheiros que serão lidos pela aplicação Cliente/Servidor.

Sugestão: comece por isolar as "novidades" requeridas pelo guião, nomeadamente:
  1. criação do par de chaves para a assinatura e utilização dos métodos para ''assinar'' e ''verificar''

  1. gravar as chaves públicas/privadas em ficheiro
  
  1. integrar as assinaturas no protocolo _Diffie-Hellman_

---

Instruções:

◆ Mover os ficheiros cliente.py, servidor.py e genkeypair.py para o mesmo directório 

◆ Executar a script genkeypair.py e verificar que são criados os ficheiros correspondentes às chaves privadas e publicas do cliente e do  servidor

◆Executar a script servidor.py e de seguida executar cliente.py

◆ De seguida, enviar a mensagem pretendida e verificar que a mesma aparece no display do servidor

NOTA: Caso uma assinatura não tenha sido verificada com sucesso é gerada uma _exception_ e o programa termina de imediato

---
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
Assinatura verificada com sucesso
Mensagem recebida: 'ola'
------------------------------------
CLIENTE2:
python3 cliente.py
Conexão establecida com o servidor
Digite o seu id:
2
Escreva a 1ª mensagem a enviar:
bom dia
Assinatura verificada com sucesso
Mensagem recebida: 'bom dia'
```

