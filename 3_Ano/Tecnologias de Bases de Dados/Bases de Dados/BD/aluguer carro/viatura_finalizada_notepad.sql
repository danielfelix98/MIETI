drop database if exists viatura;

create database viatura;

use viatura;

-- criacao da tabela clientes
-- chave PRIMARY KEY é licenca de conducao

CREATE TABLE  clientes (
lic_cond    int NOT NULL,
nome        varchar(50) NOT NULL , 
morada      varchar(50) NOT NULL, 

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
marca           char(15) NOT NULL,
modelo          char(15) NOT NULL,
ano             int NOT NULL,
cilindrada      int NOT NULL, 
combust         char (30) NOT NULL,
bandeirada      double,
kilometragem    int NOT NULL,
cod_filial      int NOT NULL,

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
ON DELETE RESTRICT
);



-- criacao da tabela aluguer
-- bandeirada é o veiculo aplicado com menos de 3 anos de idade

CREATE TABLE Aluguer (
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


 -- incerçao de dados na tabela de clientes
INSERT INTO clientes  VALUES ( 25326 , "José Magalhaes" , "Braga"), 
                             ( 25330 , "Cristiano Ronaldo" , "Madrid"),
                             (12354 , "Lucas Garcia" , "Algarve"),
                             ( 15962 , "Antonio Figueiredo" , "Lisboa");
                             
                             
                             
INSERT INTO filiais VALUES (1 , "Guiamaraes"),
                           (2 , "Braga"),
                           (3 , "Aveiro"),
                           (4 , "Porto"),
                           (5 , "Lisboa");                              



  INSERT INTO viaturas VALUES ("13-45-FH" , "VOLVO" , "440GL", 1995 , 1700 , "Gasolina"  , null, 5300, 1),
                             ("23-HA-23" ,"AUDI" , "A4 1.8I" , 2008 , 1800 ,"Gasolina " , 30.0 , 4000 , 2),
                             ("34-JA-78"  , "BMW" , "120d" , 2010 , 1990 ,"Diesel" , 25.0 , 1000 , 1),
                             ("10-10-CQ" , "FIAT" , "Uno 45D" , 1993 , 999 , "Diesel" , null , 25000 , 3),
                             ("16-EE-37" ,"HONDA", "CIVIC" , 2007 , 1400 , "Gasolina" , 10.0 , 9000, 4),
                             ("78-IA-12" , "FERRARI", "512 TR" , 2009 , 49000 ,"Gasolina", 75.0 , 6500 , 1); 
                             
                             
                             
  INSERT INTO precario VALUES (1 , 100 , 1.0), 
                              (101 , 250 , 0.8),
                              (201 , 500 , 0.75),
                              (500 , 1000 , 0.6),
                              (1000 , NULL , 0.5);   
                             

INSERT INTO Aluguer VALUES ( 1 ,  5300 , 6200 , 0.5 ,"2015-05-15" ,"2015-05-05", 20.0 , null , 12354 , "13-45-FH" , 1 ,2),
                           ( 2 , 6500 , 6600 , 1.0  ,"2015-04-14" ,"2015-04-13" , 60.0 , 75.0 , 25326 , "78-IA-12", 2, 2); 


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



commit;




SElect cod_filial
From filiais ag
where not exists (select *
                    From viaturas v
                    where bandeirada > 0 and
                    not exists (select  *
                                from Aluguer al
                                where al.matricula=v.matricula and
                                       al.filial_entrada = ag.cod_filial))
                                      
                                      
Select * from filiais
Select * from viaturas
Select * from Aluguer
Select * from precario
Select * from clientes



create function preco_por_km (km int)
returns decimal(3,2)
begin

        declare ppkm decimal(3,2);
        
        select preco_km
        into ppkm
        from precario
        where lim_inf <= km and lim_sup >= km;
        
        return ppkm
        
        
        
end; 



select preco_por_km(350);       