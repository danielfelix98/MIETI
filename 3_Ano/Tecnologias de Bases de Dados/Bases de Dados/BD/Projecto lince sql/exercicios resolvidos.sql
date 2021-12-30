use lince;


 -- Q1
select l.id_pai ,l2.lince , l.id_mae ,l3.id_lince  
             from linces l , linces l2 , linces l3
             where l.id_pai = l2.id_lince and
                  l.id_mae = l3.id_lince;
               
                
            


-- Q2
-- Quais os tecnicos (n_func , funcionario) que , durante o mes de abril de 2015 
-- so fizeram controlos a linces do genero macho 

select *
from tecnicos t
where n_func not in (select c.n_func
                    from controlo c , linces l
                    where l.genero = 'F' and
                    c.id_lince = l.id_lince and 
                    c.data  between "2007-05-01" and "2007-05-30" )
                    
                    and 
                    
                    n_func in (select n_func 
                               from controlo
                                where data  between "2007-05-01" and "2015-05-30");
               


-- Q3

select l.id_lince , l.lince , t.n_func , t.funcionario
from linces l , tecnicos t
where (id_lince , n_func) not in ( select id_lince , n_func
                                   from controlo)
                                   
                                                                                                       
/*
QUAIS OS LINCE (ID_LINCE , LINCE ) QUE DURANTE O DIA DE HOJE NAO SE MOVIMENTARAM
*/
-- contar quantas latitudes diferentes existem
-- se for um pronto ja da

select lin.id_lince , lin.lince
from  linces lin 
where (select count(distinct latitude , longitude)
       from localizacoes loc
       where loc.id_lince = lin.id_lince and 
       loc.data = "2006-05-05") = 1; 
       
       
       
       
       
       
-- Q5
-- nome e genero dos inces em que ambos os progenitores estao vivos
select  lince , genero
from    linces 
where   id_pai in (select id_lince
                   from linces
                   where genero = 'M' and  data_obito is null) and id_mae in (select id_lince
                                                            from linces
                                                            where  data_obito is null)

-- Q6
-- nome e genero dos linces em que apenas um progenitor esta vivo
select  lince , genero
from    linces 
where   id_pai in (select id_lince
                   from linces
                   where genero = 'M' and data_obito is null) and id_mae in (select id_lince
                                                            from linces
                                                            where genero = 'F'  and data_obito is not null)
                                                            
                                                            or (select id_lince
                                                               from linces
                                                               where genero = 'M' and data_obito is not null) and id_mae in (select id_lince
                                                                                                               from linces
                                                                                                               where genero = 'F' and data_obito is null)


       

-- Q7
-- Para cada lince do genero macho (id lince , lince apresentar o numero de filhso de que e pai (n de filhotes)

select id_lince , lince , (select count(*) from linces L2 where L2.id_pai= L1.id_lince) as "Nº filhotes"
from linces L1
where genero = "M" 
                    
                    
                    
                    
-- Q8 
-- quais os linces tipo femea que no ultimo controlo tinha um peso sumerior a media dos controlos anteriores

-- Q8
-- quais os linces tipo femea que no ultimo controlo tinha um peso sumerior a media dos controlos anteriores

-- ultimo peso
select id_lince , lince
from linces l 
where genero= "F" and (select *
                       from controlo c
                        where l.id_lince = c.id_lince and
                        c.data = (select max(data)
                                   from controlo 
                                  where id_lince = l.id_lince)
                                         )
                              
                              
                              >
                              
                              
                              (select AVG(cc.peso)
					            from controlo cc
                               where cc.id_lince = c.id_lince and 
                                    cc.data < (select max(data)
                                              from controlo 
                                               where id_lince = l.id_lince)
                                         );
												