
/**
 * Write a description of class Lavagem here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Lavagem extends Servico
{
    private static double valor = 1.5;
    
    public static double getValor()
    { return valor;}
    
    // instance variables - replace the example below with your own
    private int agua;
    private int tempo;

    /**
     * Constructor for objects of class Lavagem
     */
    public Lavagem(int c, int cc, int a, int t)
    {
        super(c,cc);
        this.agua = a;
        this.tempo = t;
        
    }

    public int getAgua()
    { return this.agua;}
    public int getTempo()
    { return this.tempo;}
    
    public double custo()
    { return this.agua * Lavagem.valor;}
    
    public Lavagem clone()
    {
        Lavagem temp = new Lavagem(super.getCodigo(),super.getCli(),this.agua,this.tempo);
        for(Integer i: super.getListaPrest())
            temp.add(i);
           
        return temp;
    }
}
