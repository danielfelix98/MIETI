 
import java.util.GregorianCalendar;
import java.util.Objects;
import java.util.*;
import java.lang.Iterable;
import java.io.*;
import java.util.GregorianCalendar;
public class Parkvallet extends Servicos implements Custo_Ambiental,Serializable {
    
private String matricula;    
private double dist_entrega;         
//private double distrecolha;  usado no caso da distancia ser diferente NYI
private double custo_deslocacao;
private GregorianCalendar recolha;
private double custo;
private double custo_dia;
private double custo_km;
private double cst_ambiental_base;
private long ndias;
  
    public Parkvallet(long cl, int cf,int dia, int mes, int ano, double d)
    {
        super(cl,cf);
        matricula = getMatricula();
        custo = custo();
        this.recolha = new GregorianCalendar(ano, mes, dia);
        dist_entrega = d;
    }
    
    public Parkvallet(Parkvallet pk)
    {
        super(pk);
        matricula = getMatricula();
        custo = getCusto();
        recolha = getRecolha();
        dist_entrega = getDist_entrega();
    }

    public String getMatricula() {
        return matricula;
    }

    public void setMatricula(String matricula) {
        this.matricula = matricula;
    }

    public double getDist_entrega() {
        return dist_entrega;
    }

    public void setDist_entrega(double dist_entrega) {
        this.dist_entrega = dist_entrega;
    }

    public double getCusto_deslocacao() {
        return custo_deslocacao;
    }

    public double custo_des() { custo_deslocacao = dist_entrega * custo_km;
                                return custo_deslocacao;}
    
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
    
    
@Override
    public double custo()
    {
        custo = this.numdias(super.getInicio())*this.getCusto_dia()+this.custo_des();
        return custo;
    }
    
        public long numdias(GregorianCalendar g)
    {
        long totalmilis = this.recolha.getTimeInMillis() - g.getTimeInMillis();
        
        ndias = totalmilis / (24 * 60 * 60 * 1000);
        return ndias;
    }
    
    public long getNdias()
    { return ndias; }
    
@Override
    public Parkvallet clone()
    {   
        return new Parkvallet(this);
    }  
    public void setCustoAmbientalbase(long l){this.cst_ambiental_base=l;}
    public double getCustoAmbientalbase(){return cst_ambiental_base;}
    public double calcula_custo_ambiental()
    {
        return this.dist_entrega * cst_ambiental_base;
    }
}
