  
import java.util.GregorianCalendar;
import java.util.Objects;
import java.util.*;
import java.lang.Iterable;
import java.io.*;
import java.util.GregorianCalendar;
import java.util.GregorianCalendar;
public class Lavagens extends Servicos implements Custo_Ambiental,Serializable {
    
    private double tempo_lavagem;
    private double qtd_agua;
    private double custo_minuto = 1;
    private double custo_litro = 2;
    private double custo;
    private double cst_ambiental_base;
  
    public Lavagens(long cl, int cf,double tempo_lavagem, double qtd_agua) 
    {
        super(cl,cf);
        this.tempo_lavagem = tempo_lavagem;
        this.qtd_agua = qtd_agua;
        this.custo = custo();
    }
    
    public Lavagens(Lavagens la)
    {
        super(la);
        tempo_lavagem=getTempo_lavagem();
        qtd_agua = getQtd_agua();
        custo = getCusto();
     }

    public double getTempo_lavagem() {
        return tempo_lavagem;
    }

    public void setTempo_lavagem(double tempo_lavagem) {
        this.tempo_lavagem = tempo_lavagem;
    }
    
    public void setCusto_minuto (double Custo_Minuto)
    {
        this.custo_minuto = Custo_Minuto;
    }

    public double getCusto_minuto() {
        return custo_minuto;
    }
    
    public double getQtd_agua() {
        return qtd_agua;
    }

    public void setQtd_agua(double qtd_agua) {
        this.qtd_agua = qtd_agua;
    }

    public void setCusto_litro(double custo_litro) {
        this.custo_litro = custo_litro;
    }
    
    public double getCusto_litro() {
        return custo_litro;
    }
    
    public double getCusto()
    {
        return custo;
    }
    
    public double custo()
    {
        custo = (this.getQtd_agua() * this.getCusto_litro())+(this.getTempo_lavagem() * this.getCusto_minuto());
        return custo;
    }

    @Override
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
        final Lavagens other = (Lavagens) obj;
        if (Double.doubleToLongBits(this.tempo_lavagem) != Double.doubleToLongBits(other.tempo_lavagem)) {
            return false;
        }
        return Double.doubleToLongBits(this.qtd_agua) == Double.doubleToLongBits(other.qtd_agua);
    }


    @Override
    public String toString() {
        return "Lavagens{" + "tempo_lavagem=" + tempo_lavagem + ", qtd_agua=" + qtd_agua + ",custo" + custo+'}';
    }
    
    @Override
    public Lavagens clone()
    {   
        return new Lavagens(this);
    }  
      
    public void setCustoAmbientalbase(long l){this.cst_ambiental_base=l;}
    public double getCustoAmbientalbase(){return cst_ambiental_base;}
    public double calcula_custo_ambiental()
    {
        return this.qtd_agua * cst_ambiental_base;
    }      
}


   
    
    
      
     


