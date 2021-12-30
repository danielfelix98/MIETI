import java.util.GregorianCalendar;
import java.util.Objects;
import java.util.*;
import java.lang.Iterable;
import java.io.*;
public abstract class Funcionario implements Serializable{
//Variaveis de instancia
private String nome;
private int nContribuinte;
private double salario;
private GregorianCalendar dataContrato;

//Construtores
public Funcionario(String nom,int numeroc, double sal){
    nome=nom;
    nContribuinte=numeroc;
    salario=sal;
    dataContrato= new GregorianCalendar(); 
}

public Funcionario(Funcionario func){
    nome=func.getNome();
    nContribuinte=func.getNcontribuinte();
    salario=func.getSalario();
    dataContrato=func.getDatacontrato();
   }
   
public String getNome(){return nome;}
public void setNome(String nm){nome=nm;}
public void setSalario(double salar){salario=salar;}
public double getSalario(){return salario;}
public GregorianCalendar getDatacontrato(){return dataContrato;}
//public void setDatacontrato(GregorianCalendar date){dataContrato = new GregorianCalendardate;}
public int getNcontribuinte(){return nContribuinte;}
public void setNcontribuinte(int nc){nContribuinte=nc;}


public String toString() {
        return "Funcionario{" + "codigo=" + nContribuinte + ", nome=" + nome + ", salario=" + salario + ", data_Contrato=" + dataContrato + '}';
    }
      public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final Funcionario other = (Funcionario) obj;
        if (this.nContribuinte != other.nContribuinte) {
            return false;
        }
        if (Double.doubleToLongBits(this.salario) != Double.doubleToLongBits(other.salario)) {
            return false;
        }
        if (!Objects.equals(this.nome, other.nome)) {
            return false;
        }
        if (!Objects.equals(this.dataContrato, other.dataContrato)) {
            return false;
        }
        return true;
    }
//Métodos abstratos
public abstract double salario();
public abstract Funcionario clone();
}
