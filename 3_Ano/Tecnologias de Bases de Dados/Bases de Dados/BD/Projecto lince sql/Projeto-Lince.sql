drop database if exists lince;

create database lince;

use lince;
-- craicao da tabela tecnicos
create table tecnicos(
    n_func          int,
    funcionario     varchar(20),
    
    CONSTRAINT ch_prim_tecnico
    PRIMARY KEY (n_func)
        
    );
    -- criacao da tabela linces

create table linces(
    id_lince     int NOT NULL,
    lince        varchar (20)NOT NULL,
    genero       varchar(10) not null,
    data_nasc    date NOT NULL,
    data_obito   date,
    id_pai       int,
    id_mae       int,
    
    CONSTRAINT ch_prim_linces
        PRIMARY KEY (id_lince),
    CONSTRAINT met_genero 
    CHECK (genero in ('M' , 'F')),
    -- lince pai
    CONSTRAINT ch_estr_linces_pai
    FOREIGN KEY (id_pai)
    REFERENCES linces (id_lince)
    ON UPDATE CASCADE
    ON DELETE RESTRICT,        
    -- lince mae
    CONSTRAINT ch_estr_linces_mae
    FOREIGN KEY (id_mae)
    REFERENCES linces (id_lince)
    ON UPDATE CASCADE
    ON DELETE RESTRICT

			);
    
-- craicao da tabela localizaçoes 
-- id lince primary key
create table localizacoes(
    id_lince       int not null,
    data           date not null,
    hora           time not null,
    latitude       char(10) not null,
    longitude      char(10) not null,
    
    CONSTRAINT ch_prim_local
        PRIMARY KEY (id_lince),
        
    CONSTRAINT ch_sec_locali
        UNIQUE (data),
        
    CONSTRAINT ch_sec_localiz
        UNIQUE (hora),
        
     CONSTRAINT ch_estr_local
     FOREIGN KEY (id_lince)
     REFERENCES linces (id_lince)   
     ON UPDATE CASCADE
     ON DELETE RESTRICT
          );

     
          
               
                    
-- criacao da tabel controlo
create table controlo(
    id_lince      int not null,
    data          date not null,
    n_func        int not null,
    peso          char(10),
    estado_saude  char(10),
    
    CONSTRAINT ch_prim_contr
        PRIMARY KEY (id_lince),
        
    CONSTRAINT ch_sec_control
        UNIQUE (data),
        -- chave extr lince
    CONSTRAINT ch_estr_id_lince
        FOREIGN KEY (id_lince)
        REFERENCES linces (id_lince)
        ON UPDATE CASCADE
        ON DELETE RESTRICT,    
     -- ch extrangeira n_func
    CONSTRAINT ch_estr_nfunc
        FOREIGN KEY (n_func)
        REFERENCES tecnicos (n_func)
        ON UPDATE CASCADE
        ON DELETE RESTRICT    
    );
    
    
INSERT INTO tecnicos
    VALUES(1, "Antonio"),
          (2, "Carlos"),
          (3, "Maria");
          
INSERT INTO linces
    VALUES(100, "Simba", "M", "2005-05-05", null, NULL, NULL),
          (102, "Kiara", "F", "2005-06-06", null, NULL, NULL),
          (103 , "Lord" , "M" , "2014-05-05" , null , 100 , 102); -- é filho dos Linces de cima
          
INSERT INTO localizacoes
    VALUES(100, "2006-05-05", "15:24:56", "2258S", "6532N"),
          (102, "2006-05-06", "16:25:58", "5668O", "5689E");

INSERT INTO controlo
    VALUES(100, "2007-05-06", "1", "11,45kg", "BOM");



commit;    
    
    
