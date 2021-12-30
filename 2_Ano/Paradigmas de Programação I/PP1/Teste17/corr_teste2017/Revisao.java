
/**
 * Write a description of class Revisao here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Revisao extends Servico
{
    private static double valor = 10.5;
    
    public static double getValor()
    { return valor;}
    
    // instance variables - replace the example below with your own
    private int tempo;

    /**
     * Constructor for objects of class Revisao
     */
    public Revisao(int c, int cc, int t)
    {
        // initialise instance variables
        super(c,cc);
        this.tempo = t;
    }

    public int getTempo()
    { return this.tempo;}
    
    public double custo()
    { return this.tempo * Revisao.valor * super.tam_presta();}
    
    public Revisao clone()
    {
        Revisao temp = new Revisao(super.getCodigo(),super.getCli(),this.tempo);
        for(Integer i: super.getListaPrest())
            temp.add(i);
           
        return temp;
    }
}