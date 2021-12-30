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
    genero       enum ("F" , "M"),
    data_nasc    date,
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
    id_lince       int  ,
    data           date ,
    hora           time ,
    latitude       double not null,
    longitude      double not null,
    
    CONSTRAINT ch_prim_local
        PRIMARY KEY (id_lince ,data, hora),
        
     CONSTRAINT ch_estr_local
     FOREIGN KEY (id_lince)
     REFERENCES linces (id_lince)   
     ON UPDATE CASCADE
     ON DELETE RESTRICT
          );

     
          
               
                    
-- criacao da tabel controlo
create table controlo(
    id_lince      int ,
    data          date,
    n_func        int not null,
    peso          double not null,
    estado_saude  char(10) not null,
    
    CONSTRAINT ch_prim_contr
        PRIMARY KEY (id_lince,data),
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
          (103 , "Lord" , "M" , "2014-05-05" , null , 100 , 102);
          
          
INSERT INTO localizacoes
    VALUES(100, "2006-05-05", "15:24:56",  20.20 , 30.50),
          (102, "2006-05-06", "16:25:58", 20.30,  35.60),
          (100, "2006-05-07", "15:24:56",  20.20 , 30.50),
          (102, "2006-05-07", "16:25:58", 20.30,  35.60),
          (100, "2006-05-08", "15:24:56",  20.20 , 30.50),
          (102, "2006-05-08", "16:25:58", 20.30,  35.60);
 
  
   
     INSERT INTO controlo
    VALUES(100, "2007-05-06", "1", 11.45, "BOM"),
          (102 , "2008-02-06" ,"2" , 12.85 , "BOM"),
          (103, "2007-04-06", "1", 11.45, "BOM"),
          (102 , "2008-05-06" ,"2" , 12.85 , "BOM"),
          (100, "2007-05-09", "1", 12.45, "BOM"),
          (102 , "2008-05-10" ,"2" , 14.85, "BOM"),
          (100, "2007-05-11", "1", 13.45, "BOM"),
          (102 , "2008-05-13" ,"2" , 14.85 , "BOM");





commit;    
    
    