
/**
 * Write a description of class Servico here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */

import java.util.*;
public abstract class Servico
{
 
private int codigo;  // código do serviço 
private int codCli;   // código do cliente
ArrayList<Integer> prestadores;  // lista de códigos de prestadores
	
	Servico(int c, int cl)
	{ this.codigo = c; this.codCli = cl; this.prestadores = new ArrayList<Integer>();}

public int getCodigo()
{ return this.codigo;} 
public int getCli()
{ return this.codCli;}

public List<Integer> getListaPrest()
{   ArrayList<Integer> temp = new ArrayList<Integer>();
     for(Integer c: this.prestadores)
             temp.add(c);
      return temp;
}

public int tam_presta()
{ return prestadores.size(); }

public void add(Integer c)
{ this.prestadores.add(c); } 

	public abstract double custo();
	public abstract Servico clone();

}


