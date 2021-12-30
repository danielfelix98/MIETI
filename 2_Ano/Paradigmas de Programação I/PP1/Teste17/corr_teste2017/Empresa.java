
/**
 * Write a description of class Empresa here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */

import java.util.*;
public class Empresa
{
    private HashMap<Integer,Servico> lista;
    /**
     * Constructor for objects of class Empresa
     */
    public Empresa()
    {
        this.lista = new HashMap<Integer,Servico>();
    }
    
    public void add(Servico s) throws Except1
    {
        if(this.lista.containsKey(s.getCodigo()))
            throw new Except1();
        else
            this.lista.put(s.getCodigo(),s.clone());
    }
    
    // 2.3
    public String mais_prestadores()
    {
        String a = "";
        int conta = 0;
        for(Servico s: this.lista.values())
            if(s.tam_presta() > conta)
            { conta = s.tam_presta(); a = s.getClass().getName();}
        
        return a;
    }
    // em alternativa também seria aceita a seguinte interpretação:
    // ( contar todos os colaboradores de todos os serviços e escolher
    //   o tipo com mais).
    public String mais_prestadores2()
    {
        int contaL = 0, contaR = 0;
        for(Servico s: this.lista.values())
            if(s.getClass().getName().equals("Lavagem"))
                contaL += s.tam_presta();
            else
                contaR += s.tam_presta();
            
        
        return (contaL > contaR ? "Lavagem" : "Revisao");
    }
    
    // 2.4
    public Map<Integer,ArrayList<Servico>> cliente_servicos()
    {
        HashMap<Integer,ArrayList<Servico>> temp = new HashMap<Integer,ArrayList<Servico>>();
        for(Servico s: this.lista.values())
        {
            if(temp.containsKey(s.getCli()))  // já existe?
                temp.get(s.getCli()).add(s.clone());
            else
            {   // faz novo elemento
                ArrayList<Servico> x = new ArrayList<Servico>();
                x.add(s.clone());
                temp.put(s.getCli(),x);
            }
        }
        
        return temp;
    }
    
    // 2.5 
    public Map<Integer,TreeSet<Integer>> prestadores_clientes()
    {
        HashMap<Integer,TreeSet<Integer>> temp = new HashMap<Integer,TreeSet<Integer>>();
        for(Servico s: this.lista.values())
            for(Integer i: s.getListaPrest())
            {
                if(temp.containsKey(i))  // já existe?
                    temp.get(i).add(s.getCli());
                else
                {   // adiciona novo elemento
                    TreeSet<Integer> x = new TreeSet<Integer>();
                    x.add(s.getCli());
                    temp.put(i,x);
                }
            }
            
        return temp;
    }
    
    // 2.6
    public int prestador_maior_valor()
    {
        HashMap<Integer,Double> temp = new HashMap<Integer,Double>();
        
        for(Servico s: this.lista.values())
            for(Integer i: s.getListaPrest())
                if(temp.containsKey(i))
                {
                    double cc = s.custo() + temp.get(i);
                    temp.put(i,cc);
                }
                else
                    temp.put(i,s.custo());
    
    
        // calcular máximo
        double max = 0;
        int imax = 0;
        for(Integer i: temp.keySet())
        {
            double v = temp.get(i);
            if(v > max)
            { imax = i; max = v;}
        }
    
        return imax;
    }
}