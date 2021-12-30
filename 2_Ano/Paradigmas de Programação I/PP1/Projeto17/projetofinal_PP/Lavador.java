import java.util.GregorianCalendar;
import java.util.Objects;
import java.util.*;
import java.lang.Iterable;
import java.io.*;
import java.util.GregorianCalendar;
public class Lavador extends Funcionario implements Serializable{
//Variaveis de instancia
private double sBase;
private double vplavagem;
private double lavagens;
//Construtores
public Lavador( String nom,int numeroc,double sal, double vplavagem){
super(nom,numeroc,sal);
this.lavagens= 0;
this.vplavagem=vplavagem;
sBase=sal;
}

public Lavador(Lavador lav){
super(lav);
lavagens=lav.getLavagens();
vplavagem=lav.getVplavagem();
sBase=lav.getSBase();
}
public double getLavagens(){return lavagens;}
public void setLavagens(double lav){this.lavagens+=lav;}
public double getVplavagem(){return vplavagem;}
public void setVplavagem(double vplavagem){this.vplavagem=vplavagem;}
public void setSBase(double sBase){this.sBase=sBase;}
public double getSBase(){return sBase;}

//implementação de abstratos
public  double salario(){
    return sBase+(vplavagem*lavagens);}
//public  String toString(){
//   return super.toString()+ "-"+this.sal()+"euros\n";}
public Lavador clone(){return new Lavador(this);}
}
