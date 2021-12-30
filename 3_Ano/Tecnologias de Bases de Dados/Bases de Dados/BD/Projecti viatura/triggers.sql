use viatura;

-- quando acaba o contrato e ha necessidade de terminar o contrato
-- tem que validar os parametros
-- contrato tem de existir , nao pode fechar um contrato que nunca foi aberto
-- agencia tem de existir
-- km que termina tem de ser superior aos km quie foi iniciado
-- viatura passa a estar disponivel


create procedure fechar_contrario (in  aluguer int , filial int , km_termina int , valor_comb decimal (5,2))
begin
    declare data date;
    declare km_comeca int;
    declare matric varchar(25);
    
    select data_entrada , km_saida  , matricula
    into data , km_comeca , matric
    from aluguer 
    where n_aluguer = aluguer;
    
    if ( km_comeca is not null and data is null and agencia_existe(filial) and km_termina > km_comeca) then 
    
    UPDATE aluguer
    set filial_entrada = filial,
        km_entrada = km_termina,
        data_entrada = now(),
        valor_comb = valor_comb ,
        valor_km = valor_kilometragem(km_termina - km_comeca)
        
            where n_aluguer = aluguer;
    
       
           
    
  UPDATE viaturas
    set kimometragemm = km_termina,
        cod_filial = agencia
        where matricula =  matric;
     commit;
    end if; 
    
    end;
    
   
    
     
 -- funçao para saber se a funlaoi existe
 create function agencia_existe(agencia int)
returns bool

begin

declare codigo int;

select cod_filial
into codigo
from filiais
where cod_agencia= agencia;

if ( codigo is null) then return false;
else 
return true;

end if;

end;

call fechar_contrario( 3 , 2 , 7500 , 20.0)

 
      -- trigger
      -- o cliente que fez tres contratos no passado , esses clientes nao devem pagar bandeirada , seja qual for a viatura
      
drop trigger premiar_bons_clientes          


create trigger premiar_bons_clientes
before insert on aluguer
for each row 
begin 

declare num_alugueres int;

select count(*) 
into num_alugueres
from aluguer
where lic_cond = new.lic_cond and data_entrada is not null;

if ( num_alugueres > 1 ) then 
     
     set new.bandeirada = 0 ;


end if;

 
end;
