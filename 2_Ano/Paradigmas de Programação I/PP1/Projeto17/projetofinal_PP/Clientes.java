
 

import java.util.Objects;
import java.util.GregorianCalendar;
import java.util.Objects;
import java.util.*;
import java.lang.Iterable;
import java.io.*;
import java.util.GregorianCalendar;
public class Clientes implements Serializable {
    
    private long codigo;
    private String nome;
    private GregorianCalendar data_adesao;
    private double valor_gasto;

    public Clientes(long codigo, String nome) {
        this.codigo = codigo;
        this.nome = nome;
        this.data_adesao = new GregorianCalendar();
        this.valor_gasto = 0;
    }

    public Clientes(Clientes c){
    codigo=c.getCodigo();
    nome=c.getNome();
    data_adesao=c.getData_adesao();
    valor_gasto=c.getValor_gasto();
}
    public long getCodigo() {
        return codigo;
    }

    public void setCodigo(long codigo) {
        this.codigo = codigo;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public GregorianCalendar getData_adesao() {
        return data_adesao;
    }

    public void setData_adesao(int dia, int mes, int ano) {
        this.data_adesao = new GregorianCalendar();
    }

    public double getValor_gasto() {
        return valor_gasto;
    }

    public void setValor_gasto(double valor_gasto) {
        this.valor_gasto += valor_gasto;
    }

    @Override
    public String toString() {
        return "Clientes{" + "codigo=" + codigo + ", nome=" + nome + ", data_adesao=" + data_adesao + ", valor_gasto=" + valor_gasto + '}';
    }
    
    public Clientes clone()
    {
        return new Clientes (this); // return new Clientes (this); ?
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
        final Clientes other = (Clientes) obj;
        if (Double.doubleToLongBits(this.codigo) != Double.doubleToLongBits(other.codigo)) {
            return false;
        }
        if (Double.doubleToLongBits(this.valor_gasto) != Double.doubleToLongBits(other.valor_gasto)) {
            return false;
        }
        if (!Objects.equals(this.nome, other.nome)) {
            return false;
        }
        if (!Objects.equals(this.data_adesao, other.data_adesao)) {
            return false;
        }
        return true;
    }
    
    
    
    
}
