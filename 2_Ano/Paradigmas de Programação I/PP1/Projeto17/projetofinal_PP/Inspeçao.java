 

import java.util.GregorianCalendar;
import java.util.Objects;
import java.util.*;
import java.lang.Iterable;
import java.io.*;
import java.util.GregorianCalendar;

public class Inspeçao extends Servicos implements Custo_Ambiental, Serializable{
    
    private double custo;
    private int muda_oleo;
    private double litros_oleo;
    private double cst_ambiental_base;

    public Inspeçao(long cc, int cf, int muda_oleo, double litros_oleo) 
    {
        super(cc,cf);
        this.custo = custo();
        this.muda_oleo = muda_oleo;
        this.litros_oleo = litros_oleo;
        
    }
    
    public Inspeçao(Inspeçao in)
    {
        super(in);
        muda_oleo = getMuda_oleo();
        litros_oleo = getLitros_oleo();
        custo = getCusto();
    }
    
    public double custo()
    {
        custo = 0;
        return custo;
    }
    
    public double getCusto() {
        return custo;
    }

    public void setCusto(double custo) {
        this.custo = custo;
    }

    public int getMuda_oleo() {
        return muda_oleo;
    }

    public void setMuda_oleo(int muda_oleo) {
        this.muda_oleo = muda_oleo;
    }

    public double getLitros_oleo() {
        return litros_oleo;
    }

    public void setLitros_oleo(double litros_oleo) {
        this.litros_oleo = litros_oleo;
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
        final Inspeçao other = (Inspeçao) obj;
        if (Double.doubleToLongBits(this.custo) != Double.doubleToLongBits(other.custo)) {
            return false;
        }
        if (this.muda_oleo != other.muda_oleo) {
            return false;
        }
        return Double.doubleToLongBits(this.litros_oleo) == Double.doubleToLongBits(other.litros_oleo);
    }

    public String toString() {
        return "Inspecoes{" + "custo=" + custo + ", muda_oleo=" + muda_oleo + ", litros_oleo=" + litros_oleo + '}';
    }

    public Inspeçao clone()
    {
        return new Inspeçao(this);
    }
    
    public void setCustoAmbientalbase(long l){this.cst_ambiental_base=l;}
    public double getCustoAmbientalbase(){return cst_ambiental_base;}
    public double calcula_custo_ambiental()
    {
        return this.litros_oleo * cst_ambiental_base;
    }
}