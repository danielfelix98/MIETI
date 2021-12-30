import java.util.GregorianCalendar;
import java.util.Objects;
import java.util.*;
import java.lang.Iterable;
import java.io.*;
public class Condutor extends Funcionario implements Custo_Ambiental,Serializable{
//Variaveis de instancia
private double sBase;
private double vkm;
private double kms;
private double cst_ambiental_base;
//Construtores
public Condutor( String nom,int numeroc,double sal, double vkm){
super(nom,numeroc,sal);
this.kms=0;
this.vkm=vkm;
sBase=sal;//VER O SAL
}

public Condutor(Condutor cond){
super(cond);
kms=cond.getKms();
vkm=cond.getVkm();
sBase=cond.getSBase();
}
public double getKms(){return kms;}
public void setKms(double kilom){this.kms+=kilom;}
public double getVkm(){return vkm;}
public void setVkm(double vkm){this.vkm=vkm;}
public void setSBase(double sBase){this.sBase=sBase;}
public double getSBase(){return sBase;}

//implementação de abstratos
public  double salario(){
    return sBase+(vkm*kms);}
//public  String toString(){
//   return super.toString()+ "-"+this.sal()+"euros\n";}
public Condutor clone(){return new Condutor(this);}

public void setCustoAmbientalbase(long l){this.cst_ambiental_base=l;}
public double getCustoAmbientalbase(){return cst_ambiental_base;}
public double calcula_custo_ambiental()
    { return this.kms * cst_ambiental_base; }
}

