use viatura;




-- desenvolver a funçao preco_por_km
-- que dado um determinado valor em km, retorna o preco a pagar por cada km percorrido
-- desenvolver uma outra funlçao "valor_kilometragem que 
-- utilizando a funçao antererior retorna o total a pagar

CREATE FUNCTION preco_por_kilometro(km int)
returns decimal (3,2)
begin

declare aux decimal(3,2);

select preco_km
into aux
from precario 
where limite_inf <= km and limite_sup >= km;

return (aux);
      
end;

select preco_por_kilometro(1001)



-- valor da kilometragem 
-- agora ja usamos preco por kilometro_V2
create function valor_kilometragem (km int)
returns decimal (6,2)
begin 

return (km * preco_por_kilometro_V2(km));
end;

select valor_kilometragem (1000)

-- fazer codigo de maneira a que evitemos o acesso a tabela precario 
-- criacao de uma nova funçao 
-- usando o case
-- substituimos a tabela de precario!!

CREATE FUNCTION preco_por_kilometro_V2(km int)
returns decimal (3,2)
begin

declare aux decimal(3,2);

case 
    when (km >= 1 and km <= 100 ) then set aux = 1.00;
     when (km >= 101 and km <= 200 ) then set aux = 0.8;
      when (km >= 201 and km <= 500  ) then set aux = 0.75;
       when (km >= 501 and km <= 1000 ) then set aux = 0.6;    
         else set aux = 0.5;
        end case;

return (aux);
      
end;

-- usar a estrutura if else

CREATE FUNCTION preco_por_kilometro_V3(km int)
returns decimal (3,2)
begin

declare aux decimal(3,2);

   if (km >= 1 and km <= 100 )  then set aux = 1.00;
    elseif (km >= 101 and km <= 200 ) then set aux = 0.8;
      elseif (km >= 201 and km <= 500  ) then set aux = 0.75;
       elseif (km >= 501 and km <= 1000 ) then set aux = 0.6;    
         else set aux = 0.5;
       
         end if;

return (aux);
      
end;

select preco_por_kilometro_V3(1001)

-- procedimento abrir contrato , como os parametris minimos de entrada 
-- criar uma nova entrada de aluguer 
-- parametros minimos
-- atraves disso conseguimos saber aqueles o parametros
-- depois o valor da viatura começa a estar a null
-- pois ja nao existe la o carro
create procedure abrir_contrato (in cliente char(10) , viatura varchar(25))
begin 
    declare agencia_s , kms int;
    declare bandeir decimal (4,2);

    select bandeirada , kilometragem , cod_filial
    into bandeir , kms , agencia_s
    from viaturas
    where matricula = viatura;  
    if(agencia_s is not null and cliente_valido(cliente)) then      
        insert into aluguer (lic_cond , matricula , filial_saida , km_saida , data_saida , bandeirada)
            values (cliente , viatura , agencia_s , kms, now() , bandeir); 
        
        UPDATE viaturas
        set cod_filial = null 
    where matricula=viatura;

        commit;
    end if;
end;



-- criacao da funcao para saber se determinado cliente pertence a tabela
create function cliente_valido(cliente char(10))
returns bool

begin

declare aux varchar(50);


select nome
into aux
from clientes 
where lic_cond = cliente;

if ( aux is null) then 
return false;
else 
return true ;
end if;

end;




--select * from viaturas
--select * from clientes