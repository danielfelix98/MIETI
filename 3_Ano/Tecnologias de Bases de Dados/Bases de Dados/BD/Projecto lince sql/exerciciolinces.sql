select l.id_lince , l.lince , t.n_func , t.funcionario
from linces l , tecnicos t
where (id_lince , n_func) not in ( select id_lince , n_func
                                   from controlo)