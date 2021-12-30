use lince;


create procedure registar_controlo( in lince int , dataRegisto date , n_funcionario int , peso double ,saude char(10))

begin 
declare n_func int ;
declare peso_lince double;
declare estado char(10);

select  n_func , peso , estado_saude
into n_funcionario , peso_lince, estado
from controlo
where data= dataregisto and id_lince = lince;

if( vivo(lince) and  funcionario_ativo(n_funcionario) ) then 

update controlo
set n_func = n_funcionario ,
    peso=peso,
    estado_saude = saude
    
    where id_lince = lince;
    commit;
    end if; 
    
    end;



drop function funcionario_ativo

create function funcionario_ativo(func int)
returns bool

begin 
declare nome varchar(20);

select funcionario 
into nome 
from tecnicos
where n_func= func ;

if(nome is not null) then
return true;
else
return false;
end if;
end;
