import java.util.GregorianCalendar;
import java.util.Objects;
import java.util.*;
import java.lang.Iterable;
import java.io.*;
public class Mecanicos extends Funcionario implements Serializable{
//Variaveis de instancia
private double sBase;
//Construtores
public Mecanicos( String nom,int numeroc,double sal)
{
super(nom,numeroc,sal);
sBase = sal;
}

public Mecanicos(Mecanicos mec){
super(mec);
sBase = getSBase();
}


public void setSBase(double sBase){this.sBase=sBase;}
public double getSBase(){return sBase;}

//implementação de abstratos
public  double salario(){
    return sBase;}

public Mecanicos clone(){return new Mecanicos(this);}
}