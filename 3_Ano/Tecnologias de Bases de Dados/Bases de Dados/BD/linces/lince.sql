DROP DATABASE IF EXISTS lince;

CREATE DATABASE lince;

USE lince;

CREATE TABLE Tecnicos (
    n_func              int,
    funcionario         char(50),
    PRIMARY KEY(n_func)
    );
    
CREATE TABLE Linces (
    id_lince            int,
    lince               varchar(50),
    genero              char(1),
    data_nac            char(10),
    data_ob             char(10),
    id_pai              int,
    id_mae              int,
    PRIMARY KEY (id_lince),
    FOREIGN KEY (id_pai)
    REFERENCES Linces (id_lince)
    on update cascade,
    FOREIGN KEY (id_mae)
    REFERENCES Linces (id_lince)
    on update cascade
    );
    
CREATE TABLE Localizacoes (
    data                char(10),
    hora                varchar(8),
    latitude            int,
    longitude           int,
    id_lince            int,
    PRIMARY KEY (id_lince, data, hora),
    FOREIGN KEY (id_lince)
    REFERENCES Linces (id_lince)
    on update cascade
    );
    
CREATE TABLE Controlos (
    data                char(10),
    peso                decimal(5,2),
    estado_saude        char(10),
    id_lince            int,
    n_func              int,
    PRIMARY KEY (id_lince,data),        
    FOREIGN KEY (id_lince)
    REFERENCES Linces (id_lince),
    FOREIGN KEY (n_func)
    REFERENCES  Tecnicos (n_func)
    on update cascade
    );
    

INSERT INTO Tecnicos VALUES (1,"Oliverio Sosua"),(12,"Jesualdo Mota");
INSERT INTO Linces VALUES (2,"Gaspar","M","2011-01-21",null,null,null),(3,"Pintas","F","2011-07-11",null,null,null),(1,"Simba","M","2012-01-12",null,2,3);
INSERT INTO Localizacoes VALUES ("2013-02-12","23:09:01",12,23,1),("2014-12-14","22:44:50",44,123,2),("2014-11-15","12:45:24",123,65,3);
INSERT INTO Controlos VALUES ("2011-09-11",11.6,"BOM",2,12),("2014-07-23",20.0,"MAU",1,1);