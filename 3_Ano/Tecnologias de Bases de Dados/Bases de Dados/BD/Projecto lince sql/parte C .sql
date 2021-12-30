use lince;

-- procedimento para agendar controlo
drop procedure Agendar_Controlo

create procedure Agendar_Controlo(in  lince int , data_controlo date )
begin 

    if( vivo(lince) and data_controlo >= curdate()) then 
 
 insert into controlo(id_lince , data)
    values(lince, data_controlo);
    
    commit;
    end if;
    end;
    
    
   
 

-- ver se esta vivo
drop function vivo
create function vivo (lince int)
returns bool

begin 
declare numeroLince int;
declare data date;
declare nome varchar(10);

select id_lince , data_obito , lince
into numeroLince , data , nome
from linces
where id_lince = lince ;


if( data is null  and nome is not null) then
return true ;
else
return false;
end if;
end;




-- questao 5 utilizando a funçaio

select lince , genero
from linces
where vivo(id_pai) and vivo(id_mae)


-- questa 6

select lince , genero
from linces
where not vivo(id_pai) and vivo (id_mae) or  not vivo(id_mae) and vivo(id_pai) 

