 

import java.util.GregorianCalendar;

public abstract class Servicos 
{
private int Ncont;
private long CodC;
private GregorianCalendar inicio;

    public Servicos (long cc, int cf)
    {
        this.Ncont = cf;
        this.CodC = cc;
        this.inicio = new GregorianCalendar();
    }
  
   public Servicos (Servicos serv)
    {
        Ncont = getNcont();
        CodC = getCodC();
        inicio = getInicio();
    }


    public int getNcont() {return Ncont;}
    public long getCodC() {return CodC;}
    //public String getMatricula(){return matricula;
    public GregorianCalendar getInicio() { return (GregorianCalendar)this.inicio.clone();  }
   
    public abstract double custo();
    public abstract Servicos clone();
    
    
}

