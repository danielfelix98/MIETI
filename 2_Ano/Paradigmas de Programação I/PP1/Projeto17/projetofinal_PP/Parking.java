import java.util.GregorianCalendar;
import java.util.Objects;
import java.util.*;
import java.lang.Iterable;
import java.io.*;
import java.util.GregorianCalendar;
public class Parking extends Servicos implements Serializable{

private String marca;
private String matricula;
private GregorianCalendar recolha;
private double custo;
private double custo_dia;


    public Parking(long cl, int cf,String m, String mat)
    {
        super(cl, cf);
        this.marca = m;
        this.matricula = mat;
        this.recolha = new GregorianCalendar();
        this.custo = custo();
    }

    public Parking(Parking pk,int dia, int mes, int ano)
    {
        super(pk);
        marca = getMarca();
        matricula = getMatricula();
        custo = getCusto();
        this.recolha = new GregorianCalendar(ano, mes, dia);
    }

    public Parking(Parking pk)
    {
        super(pk);
        marca = getMarca();
        matricula = getMatricula();
        custo = getCusto();
        recolha = getRecolha();
    }
    
    
    public String getMarca() {
        return marca;
    }

    public void setMarca(String marca) {
        this.marca = marca;
    }

    public String getMatricula() {
        return matricula;
    }

    public void setMatricula(String matricula) {
        this.matricula = matricula;
    }

    public GregorianCalendar getRecolha() {
        return recolha;
    }

    public void setRecolha(GregorianCalendar recolha) {
        this.recolha = recolha;
    }

    public double getCusto() {
        return custo;
    }

    public void setCusto(double custo) {
        this.custo = custo;
    }

    public double getCusto_dia() {
        return custo_dia;
    }

    public void setCusto_dia(double custo_dia) {
        this.custo_dia = custo_dia;
    }

    public double custo()
    {
        custo = this.numdias(super.getInicio())*this.getCusto_dia(); 
        return custo;
    }

    public long numdias(GregorianCalendar g)
    {
        long totalmilis = this.recolha.getTimeInMillis() - g.getTimeInMillis();
        
        return totalmilis / (24 * 60 * 60 * 1000);
    }

    public Parking clone()
    {   
        return new Parking(this);
    }  
 
   
}
