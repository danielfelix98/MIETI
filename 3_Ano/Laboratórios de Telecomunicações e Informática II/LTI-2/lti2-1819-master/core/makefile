all:
	gcc gestor.c api.c -l mysqlclient -o gestor -lm -I/usr/include/mysql
	gcc concentrador.c api.c rs232-linux.c -o concentrador