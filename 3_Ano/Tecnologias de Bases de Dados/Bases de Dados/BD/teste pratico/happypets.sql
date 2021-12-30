drop database if exists happypets;

create database happypets;

use happypets;
-- craicao da tabela cliente
create table cliente(
    n_cli          int NOT NULL,
    nome_cli     varchar(20),
    email_cli   varchar(50),
    tel_cli     varchar(9),
    morada      varchar(50),
    
    CONSTRAINT ch_prim_cliente
    PRIMARY KEY (n_cli)
        
    );
    -- criacao da tabela animal

create table animal(
    n_ani     int NOT NULL,
    nome_ani        varchar (20)NOT NULL,
    genero       enum ("F" , "M"),
    data_nasc    date,
    categoria   varchar(20),
    n_cli       int NOT NULL,
    CONSTRAINT ch_prim_animal
        PRIMARY KEY (n_ani, n_cli),
    CONSTRAINT set_genero 
    CHECK (genero in ('M' , 'F')),
    CONSTRAINT set_categoria
    CHECK (categoria in ('caninos', 'felinos', 'aves', 'peixes' , 'repteis', 'outros')), 
    CONSTRAINT ch_estr_animal
    FOREIGN KEY (n_cli)
    REFERENCES cliente (n_cli)
  	);
    
             
                    
-- criacao da tabel veterinario
create table veterinario(
    n_vet      int ,
    nome_vet          varchar(50),
    preco_h_vet       int,
    CONSTRAINT ch_prim_veterinario
        PRIMARY KEY (n_vet) 
             
    );
    
    
-- criacao da tabel auxiliar
create table auxiliar(
    n_aux             int ,
    nome_aux         varchar(50),
    preco_h_aux       int,
   
    
        CONSTRAINT ch_prim_auxiliar
        PRIMARY KEY (n_aux)
        
    );
    
    
    

    
    
    
  -- criacao da tabel stock
create table stock(
    cod_prod      int ,
    designacao        varchar(20),
    preco       int,
   
    
    CONSTRAINT ch_prim_stock
        PRIMARY KEY (cod_prod)
       
    );  
    
 
    
    
    
-- craicao da tabela cirurgia
create table cirurgia(
    n_cirurgia      int,
    n_ani       int,
    dia        int ,
    hora_ini    varchar(8) ,
    mes       varchar(10),
    ano          int,
    duracao     int,
    n_vet       int,
    n_aux       int,
    
    CONSTRAINT ch_prim_n_cirurgia
        PRIMARY KEY (n_cirurgia),   
     CONSTRAINT ch_estr_cirugia
     FOREIGN KEY (n_ani) REFERENCES animal (n_ani),
     FOREIGN KEY (n_vet) REFERENCES veterinario (n_vet),
     FOREIGN KEY (n_aux) REFERENCES auxiliar (n_aux)
          
     ON UPDATE CASCADE
     ON DELETE RESTRICT 
         
          ); 
    
   -- criacao da tabel consumo
create table consumo(
    n_cirurgia      int ,
    cod_prod      int ,
    quantidade      int,
   
    
        CONSTRAINT ch_prim_consumo
        PRIMARY KEY (n_cirurgia),
        CONSTRAINT ch_estr_consumo
        FOREIGN KEY (n_cirurgia) REFERENCES cirurgia (n_cirurgia),
        FOREIGN KEY (cod_prod) REFERENCES stock (cod_prod)
        
      ON UPDATE CASCADE
     ON DELETE RESTRICT
    );    
    
    
    
    
    
    
INSERT INTO cliente
    VALUES(1, "Antonio","antonio@hotmail.com","963214578","rua da liberdade"),
          (2, "Carlos","carlos@hotmail.com","968745123","rua da lua"),
          (3, "Maria","maria@hotmail.com","912343678","rua da universidade");
          
INSERT INTO animal
    VALUES(100, "Simba", "M", "2005-05-05", "canino", 1),
          (102, "Pituxa", "F", "2005-06-06", "felino", 3),
          (103 , "Tareco" , "M" , "2014-05-05" , "aves", 2);
 INSERT INTO veterinario
    VALUES(1, "Dra. Marta Leao", 30),
          (2 , "Manel", 32),
          (3, "Pedro", 34);  
          
      
  INSERT INTO auxiliar
    VALUES(1, "Antonio Melro", 20),
          (2 , "Joao" , 22),
          (3, "Afonso", 24);                          

    


INSERT INTO stock
    VALUES(123,"Anestesia Forte",12),
            (321, "Compressa tipo XPTO",5),
            (12, "Betadine", 2);
            

            
            INSERT INTO cirurgia
    VALUES(1,100, 5, "15:24:56", "Maio" , 2006 ,3 , 1, 1),
          (2,102, 10, "20:00:56", "Julho" , 2007 ,2 ,2 ,1),
          (3,103, 2, "12:44:25", "Março" , 2006 ,4 , 3, 3),
          (4,102, 20, "11:00:01", "Novembro" , 2007 ,7 ,2 ,1);
          
                                
INSERT INTO consumo
    VALUES(1, 123,  1),
          (2 , 321,  2),
          (3, 123, 1),
          (4, 12,3);

commit;  



    