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
              

              