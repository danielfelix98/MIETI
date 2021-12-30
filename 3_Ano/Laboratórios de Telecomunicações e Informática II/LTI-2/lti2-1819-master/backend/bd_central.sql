drop database if exists servicoCentral;
create database servicoCentral;
use servicoCentral;

create table concentrador(
	id_concentrador integer(10) not null auto_increment,
	nome varchar(100),

	primary key (id_concentrador)
);

create table area(
	id_area integer(10) not null auto_increment,
	nome_area varchar(100),

	primary key (id_area)
);

create table paciente(
	id_paciente integer(10) not null auto_increment,
	nome_paciente varchar(100),
	morada varchar(100),
	nif integer(100),
	obs_medicas varchar(100),
	telefone integer(100),
	id_area integer(10),

	primary key (id_paciente),
	foreign key (id_area) references area(id_area) on update cascade on delete set null
);

create table leitura(
	id_leitura integer(10) not null auto_increment,
	ts TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
	estado_fisico varchar(100),
	id_paciente integer(10),

	primary key (id_leitura),
	foreign key (id_paciente) references paciente(id_paciente) on update cascade on delete set null
);

create table sistemaSensor(
	id_sistemaSensor integer(10) not null auto_increment,
	sensorSimulado boolean,
	id_paciente integer(10),
	id_concentrador integer(10),

	primary key (id_sistemaSensor),
	foreign key (id_paciente) references paciente(id_paciente) on update cascade on delete set null,
	foreign key (id_concentrador) references concentrador(id_concentrador) on update cascade on delete set null
);

create table tipoUtilizador(
	id_tipoUtilizador integer(10) not null auto_increment,
	tipo varchar(100),

	primary key (id_tipoUtilizador)
);

create table utilizador(
	id_utilizador integer(10) not null auto_increment,
	username varchar(100),
	morada varchar(100),
	mail varchar(100),
	password varchar(100),
	id_tipoUtilizador integer(10),

	primary key (id_utilizador),
	foreign key (id_tipoUtilizador) references tipoUtilizador(id_tipoUtilizador) on update cascade on delete set null
);

delimiter //
create procedure inserir_concentrador (in nom varchar(100))
begin
	insert into concentrador(nome)
		values(nom);
end//
delimiter ;

delimiter //
create procedure inserir_area (in nom varchar(100))
begin
	insert into area(nome_area)
		values(nom);
end//
delimiter ;

delimiter //
create procedure inserir_paciente (in nomePaciente varchar(50), m varchar(100), n integer(100), o varchar(100),
	t integer(100), id_a integer(10))
begin
	insert into paciente(nome_paciente,morada,nif,obs_medicas,telefone,id_area)
		values(nomePaciente,m,n,o,t,id_a);
	call inserir_leitura('Desligado!',(select id_paciente from paciente order by id_paciente desc limit 1));
end//
delimiter ;

delimiter //
create procedure inserir_leitura (in ef varchar(100),	id_s integer(10))
begin
	insert into leitura(estado_fisico ,	id_paciente)
		values(ef,id_s);
end//
delimiter ;

delimiter //
create procedure inserir_sistemaSensor(in ssimulado boolean, id_s integer(10), id_c integer(10))
begin
	insert into sistemaSensor(sensorSimulado ,	id_paciente,	id_concentrador)
		values(ssimulado,id_s,id_c);
end//
delimiter ;

delimiter //
create procedure inserir_tipoUtilizador(in t varchar(100))
begin
	insert into tipoUtilizador(tipo)
		values(t);
end//
delimiter ;

delimiter //
create procedure inserir_utilizador(in u varchar(100), mo varchar(100), ma varchar(100),	
pass varchar(100),	id_t integer(10))
begin
	insert into utilizador(username, morada, mail, password, id_tipoUtilizador)
		values(u,mo,ma,pass,id_t);
end//
delimiter ;

delimiter //
create procedure obter_pacientesEstadoPorArea(in area integer(10))
begin
	-- obter numero de pacientes na area
	declare numPac int;
	select count(*) into numPac from paciente where id_area=area;
	select p.id_area, l.id_leitura, p.id_paciente, p.nome_paciente, l.estado_fisico, l.ts from paciente p, leitura l 
	where id_area=area and l.id_paciente=p.id_paciente order by l.ts desc limit numPac;
end//
delimiter ;

ALTER TABLE concentrador AUTO_INCREMENT=0;
ALTER TABLE area AUTO_INCREMENT=0;
ALTER TABLE paciente AUTO_INCREMENT=0;
ALTER TABLE leitura AUTO_INCREMENT=0;
ALTER TABLE sistemaSensor AUTO_INCREMENT=0;
ALTER TABLE tipoUtilizador AUTO_INCREMENT=0;
ALTER TABLE utilizador AUTO_INCREMENT=0;

call inserir_concentrador('concentrador 1');
call inserir_area('area1');
call inserir_paciente('nome_paciente','morada',123456789,'obs_medicas',987654321,1);
call inserir_sistemaSensor(true ,	1,	1);
call inserir_tipoUtilizador('admin');
call inserir_tipoUtilizador('funcionario');
call inserir_utilizador('admin','rua do admin','admin@admin.com','hashDaPassDoAdmin',1);