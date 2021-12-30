drop database if exists gestorServico;
create database gestorServico;
use gestorServico;

create table concentrador(
	id_concentrador integer(10) not null auto_increment,
	nome varchar(100),

	primary key (id_concentrador)
);

create table sujeito(
	id_sujeito integer(10) not null auto_increment,
	nome_sujeito varchar(50),

	primary key (id_sujeito)
);

create table amostra(
	id_amostra integer(10) not null auto_increment,
	id_concentrador integer(10),
	id_sujeito integer(10),
	temperatura float(5),
	sensor_simulado boolean,
	ts TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
	acx float(10),
	acy float(10),
	acz float(10),
	grx float(10),
	gry float(10),
	grz float(10),

	primary key (id_amostra),
	foreign key (id_concentrador) references concentrador(id_concentrador),
	foreign key (id_sujeito) references sujeito(id_sujeito)
);

create table sistemaSensor(
	id_sensor integer(10) not null auto_increment,
	sensor_simulado boolean,
	id_sujeito integer(10),
	id_concentrador integer(10),

	primary key (id_sensor),
	foreign key (id_sujeito) references sujeito(id_sujeito),
	foreign key (id_concentrador) references concentrador(id_concentrador)
);

delimiter //
create procedure inserir_amostra (in idconcen int , idsujeito int, temp float,ssimulado binary, Acx float, Acy float, Acz float, Grx float, Gry float, Grz float)
begin
	insert into amostra(id_concentrador, id_sujeito, temperatura, sensor_simulado, acx, acy, acz, grx, gry, grz)
		values(idconcen,idsujeito,temp,ssimulado,Acx,Acy,Acz,Grx,Gry,Grz);
end//
delimiter ;

delimiter //
create procedure inserir_sujeito (in nomesujeito varchar(50))
begin
	insert into sujeito(nome_sujeito)
		values(nomesujeito);
end//
delimiter ;

delimiter //
create procedure inserir_concencentrador (in nom varchar(100))
begin
	insert into concentrador(nome)
		values(nom);
end//
delimiter ;

delimiter //
create procedure inserir_sistemaSensor(in ssimulado boolean, id_s integer(10), id_c integer(10))
begin
	insert into sistemaSensor(sensor_simulado ,	id_sujeito,	id_concentrador)
		values(ssimulado,id_s,id_c);
end//
delimiter ;

delimiter //
create procedure listar_sensores_sujeito (in idsujeito int)
begin
	select id_sensor,sensor_simulado,id_sujeito, id_concentrador from sistemaSensor where id_sujeito = idsujeito;
end//
delimiter ;

ALTER TABLE amostra AUTO_INCREMENT=0;
ALTER TABLE sujeito AUTO_INCREMENT=0;
ALTER TABLE concentrador AUTO_INCREMENT=0;
ALTER TABLE sistemaSensor AUTO_INCREMENT=0;

call inserir_sujeito("sujeito1");
call inserir_concencentrador("concentrador1");
call inserir_sistemaSensor(false, 1, 1);
call inserir_sujeito("sujeito2");
call inserir_concencentrador("concentrador2");
call inserir_sistemaSensor(false, 2, 2);
call inserir_sujeito("sujeito3");
call inserir_concencentrador("concentrador3");
call inserir_sistemaSensor(false, 3, 3);
