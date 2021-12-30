drop database if exists viatura;

create database viatura;

use viatura;

-- criacao da tabela clientes
-- chave PRIMARY KEY é licenca de conducao
-- POR A LICENCA DE LIGAÇAO EM VARCHAR !!!!!!!!
CREATE TABLE  clientes (
lic_cond    char (10) NOT NULL,
nome        varchar(50) NOT NULL , 
morada      varchar(50) , 

CONSTRAINT ch_prim_clintes
PRIMARY KEY (lic_cond)
);



-- criacao da tabela filiais
-- chave primaria é o codigo da filial
CREATE TABLE filiais(
cod_filial     int NOT NULL,
localidade     VARCHAR(50),

CONSTRAINT ch_prim_filiais
PRIMARY KEY (cod_filial)
);

-- criacao das tabelas  viaturas
-- chave primaria é MATRICULA
-- chave EXT COD_FILIAL ( FILIAIS) 


CREATE TABLE viaturas (
matricula       varchar(30) NOT NULL, 
marca           varchar(15) NOT NULL,
modelo          varchar(15) NOT NULL,
ano             int NOT NULL,
cilindrada      int , 
combust         enum ('Gasolina' , 'Diesel' , 'GPL' , 'Eletrico'),
bandeirada      double,
kilometragem    int,
cod_filial      int,

CONSTRAINT ch_prim_viaturas
PRIMARY KEY (matricula),
-- valor da bandeira tem de ser maior do que 0
CONSTRAINT valor_bandeirada
CHECK (bandeirada > 0),
-- chave extrangeira 
CONSTRAINT ch_estrang_cod_filial
FOREIGN KEY (cod_filial)
REFERENCES filiais (cod_filial)
ON UPDATE CASCADE
ON DELETE SET NULL
);



-- criacao da tabela aluguer
-- bandeirada é o veiculo aplicado com menos de 3 anos de idade

CREATE TABLE Aluguer (
n_aluguer     int NOT NULL,
km_saida      int NOT NULL,
km_entrada    int ,
valor_km      double NOT NULL,
data_entrada  date , 
data_saida    date NOT NULL ,
valor_comb    double NOT NULL,
bandeirada    double ,
lic_cond      char(10) not null , 
matricula     varchar(25), 
filial_saida  int  not null,
filial_entrada int ,

CONSTRAINT ch_primaria_Aluguer 
PRIMARY KEY (n_aluguer),
-- metodo para o km a saida ser menores que km a entrada
CONSTRAINT km_entrada_saida
CHECK (km_saida < km_entrada),
-- valor do combostivel tem de ser maior que 0
CONSTRAINT valor_comb 
CHECK (valor_comb > 0),

CONSTRAINT data_saida_entrada
CHECK (data_entrada > data_saida),

-- valor da bandeira tem de ser maior do que 0
CONSTRAINT valor_bandeirada
CHECK (bandeirada > 0),

-- vai buscar a clientes
CONSTRAINT ch_ext_lic_conducao
FOREIGN KEY (lic_cond)
REFERENCES   clientes (lic_cond)
ON UPDATE CASCADE
ON DELETE RESTRICT,

-- chave extrangeira matricula (viaturas)

CONSTRAINT ch_extr_matricula
FOREIGN  KEY (matricula)
REFERENCES viaturas(matricula)
ON UPDATE CASCADE
ON DELETE RESTRICT,


-- chave extrangeira filial saida 
CONSTRAINT ch_extr_filial_saida
FOREIGN KEY (filial_saida)
REFERENCES filiais(cod_filial)
ON UPDATE CASCADE 
ON DELETE RESTRICT,

-- chave extrangeira filial entrada
-- é uma filial , mas vai buscar , cod_filial a filiais 
CONSTRAINT ch_extr_filial_entrada
FOREIGN KEY (filial_entrada)
REFERENCES filiais(cod_filial)
ON UPDATE CASCADE
ON DELETE RESTRICT 

);


-- criacao da tabela preçario 

CREATE TABLE precario (
limite_inf      int not null , 
limite_sup        int , 
preco_km        double NOT NULL,

CONSTRAINT CH_PRIMARIA_precario
PRIMARY KEY (limite_inf) , 

CONSTRAINT metodo_inf_sup
CHECK (limite_inf < limite_sup)
);
-- criaçao de view 
create view num_alugueres_iniciados_por_agencia ( filial , num_alugueres)
         as (select filial_saida , COUNT(*)
             from Aluguer
             group by filial_saida);
        
        
        -- select *
        -- from num_alugueres_iniciados_por_agencia
        
 -- incerçao de dados na tabela de clientes
INSERT INTO clientes  VALUES ( "25326", "José Magalhaes" , "Braga"), 
                             ( "25330" , "Cristiano Ronaldo" , "Madrid"),
                             ("12354" , "Lucas Garcia" , "Algarve"),
                             ( "15962" , "Antonio Figueiredo" , "Lisboa");
                             
                             
                             
INSERT INTO filiais VALUES (1 , "Guiamaraes"),
                           (2 , "Braga"),
                           (3 , "Aveiro"),
                           (4 , "Porto"),
                           (5 , "Lisboa");                              



  INSERT INTO viaturas VALUES ("13-45-FH" , "VOLVO" , "440GL", 1995 , 1700 , "Gasolina"  , null, 5300, 1),
                             ("23-HA-23" ,"AUDI" , "A4 1.8I" , 2008 , 1800 ,"Gasolina " , 30.0 , 4000 , 2),
                             ("34-JA-78"  , "BMW" , "120d" , 2010 , 1990 ,"Diesel" , 25.0 , 1000 , 1),
                             ("10-10-CQ" , "FIAT" , "Uno 45D" , 1993 , 999 , "Diesel" , null , 25000 , null),
                             ("16-EE-37" ,"HONDA", "CIVIC" , 2007 , 1400 , "Gasolina" , 10.0 , 9000, 4),
                             ("78-IA-12" , "FERRARI", "512 TR" , 2009 , 49000 ,"Gasolina", 75.0 , 6500 , 1); 
                             
                             
                             
  INSERT INTO precario VALUES (0 , 100 , 1.0), 
                              (101 , 250 , 0.8),
                              (201 , 500 , 0.75),
                              (501 , 1000 , 0.6),
                              (1000 , 99999 , 0.5);   
                             
-- alugueres ja terminados
-- alugueres nao terminados

INSERT INTO Aluguer VALUES ( 1 ,  5300 , 6200 , 0.5 ,"2015-05-15" ,"2015-05-05", 20.0 , null , "12354" , "13-45-FH" , 1 ,2),
                           ( 2 , 6500 , 6600 , 1.0  ,"2015-04-14" ,"2015-04-13" , 60.0 , 75.0 , "25326" , "78-IA-12", 2, 2), 
                           ( 3 ,  5300 , 6200 , 0.5 , null ,"2015-05-05", 20.0 , null , "12354" , "13-45-FH" , 1 ,null),
                           ( 4 , 6500 , 6600 , 1.0  ,null ,"2015-04-13" , 60.0 , 75.0 , "25326" , "78-IA-12", 2, null); 



/*
n_aluguer     int NOT NULL,
km_saida      int NOT NULL,
km_entrada    int NOT NULL,
valor_km      double NOT NULL,
data_entrada  date NOT NULL, 
data_saida    date NOT NULL,
valor_comb    double NOT NULL,
bandeirada    double ,
lic_cond      int not null , 
matricula     varchar(25), 
filial_saida  int ,
filIal_entrada int ,
*/
-- QUESTOES!!!
-- Qual e o valor por 320 km a percorridos 
/*
select (preco_km * 100) as "Valor a Pagar"
from precario 
where limite_inf <=100 and limite_sup >=100


-- Q2
select ag.cod_filial , ag.localidade ,(select al.matricula
                                       from Aluguer al
                                       where al.filial_entrada =ag.cod_filial 
                                          and al.valor_km =(select  max (alu.valor_km)
                                                            from Aluguer alu
                                                            where alu.filial_entrada =al.filial_entrada)) as matricula
 
from filiais ag      

*/ 
 -- Q3
 -- condiçao de junçao
 -- vao dar duas , porque tem ambas varios contratos
 -- tem de ser feito em duas fases
 select f.localidade , f.cod_filial
 from filiais f , num_alugueres_iniciados_por_agencia naipa
 where f.cod_filial = naipa.filial and
        naipa.num_alugueres = ( select  max(num_alugueres)
                                from num_alugueres_iniciados_por_agencia)
   
-- Q4
-- Agencias  ja foram pontod e chegada , agencias de entrada , de todas as viaturas
-- que tem bandeirada

 -- tem que se fazer uma divisao
select cod_filial
from filiais
where not exists ( select *
                   from viaturas v
                   where v.bandeirada is null 
                            and not exists ( select * 
                                             from aluguer a
                                             where a.matricula = v.matricula and 
                                             a.filial_entrada = filiais.cod_filial))
                                             

 
 
commit;