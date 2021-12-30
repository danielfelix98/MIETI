 

import java.util.Objects;
import java.util.GregorianCalendar;
import java.util.Objects;
import java.util.*;
import java.lang.Iterable;
import java.io.*;
import java.util.GregorianCalendar;

public class LongTerm implements Serializable
{
 
    private HashMap<Long,Clientes> tabela_clientes;
    private HashMap<Integer,Funcionario> tabela_funcionario;
    private HashMap<Long,Servicos> tabela_servicos;
    private HashMap<Long,ArrayList<Servicos>> cliente_servicos;
    private long codigoc = 1;
    private long codigos = 1;
    private double Custo_Ambiental_total;
    //private int op;

    public LongTerm() 
    {
        this.tabela_clientes = new HashMap<Long,Clientes>();
        this.tabela_funcionario = new HashMap<Integer,Funcionario>();
        this.tabela_servicos = new HashMap<Long,Servicos>();
        this.cliente_servicos = new HashMap<Long,ArrayList<Servicos>>();
    }
    
       public  void  inserir_cliente(Clientes novo) throws CustomExcep
    {
        if(this.tabela_clientes.containsValue(novo.getCodigo()))
            throw new CustomExcep("Cliente já existe!");
        else
            {this.tabela_clientes.put(codigoc,novo.clone());
            codigoc++;}
    }
  
      public void inserir_funcionario(Funcionario novof) throws CustomExcep
    {
        if(this.tabela_funcionario.containsKey(novof.getNcontribuinte()))
            throw new CustomExcep("Funcionário já existe!");
        else
            this.tabela_funcionario.put(novof.getNcontribuinte(), novof.clone());
    }
    
      public void inserir_servico(Servicos novos)
    {
        this.tabela_servicos.put(codigos, novos.clone());
        codigos++;
    }   
    
      public void save()
      {
          try{
              File file = new File("C:\\Empdatabase.db");
              file.createNewFile();
              FileOutputStream fOut = new FileOutputStream(file);
              ObjectOutputStream oOut = new ObjectOutputStream(fOut);
              oOut.writeObject(this);
              oOut.flush();
              oOut.close();
                } catch (Exception e)
                    {e.printStackTrace();}
      }   
       
    public Funcionario getFunc(int nc)
    {
        if(this.tabela_funcionario.containsKey(nc))
            return this.tabela_funcionario.get(nc).clone();
        else
            return(null);
    }
  
  
    public Clientes getCliente(long cod)
    {   
        if(this.tabela_clientes.containsKey(cod))
            return this.tabela_clientes.get(cod).clone();
        else
            return(null);
    }
    
    public void criar_lista_servicos()
    {
        for(Servicos s: this.tabela_servicos.values())
        {
            if(cliente_servicos.containsKey(s.getCodC()))  
                cliente_servicos.get(s.getCodC()).add(s.clone());
            else
            {  
                ArrayList<Servicos> x = new ArrayList<Servicos>();
                x.add(s.clone());
                cliente_servicos.put(s.getCodC(),x);
            }
        }
    }

    public ArrayList<Servicos> cliente_servicos(Long l)
    {
        ArrayList<Servicos> temp = new ArrayList<Servicos>();
        if(cliente_servicos.containsKey(l))
            {temp = cliente_servicos.get(l);}
        else
            return null;
    return temp;
    }
    
    public int lavador_mais_rendimento()
    {
        double maior_rend = 0;
        int temp=0;
            for(Funcionario f: this.tabela_funcionario.values())
            {
                if(f instanceof Lavador)
                if(((Lavador)f).getSalario() > maior_rend)
                { 
                    maior_rend = f.getSalario();
                    temp = f.getNcontribuinte();
                }
            }
        return temp;
     }
  
    public long n_dias_estacionado(String s)
    {
        long ndias = 0;
        for(Servicos s1: this.tabela_servicos.values())
        {
            if(s1 instanceof Parkvallet)
            if(((Parkvallet)s1).getMatricula().equals(s))
           
                ndias += ((Parkvallet)s1).getNdias();
        }
        return ndias;
    }
    
    public long total_salarios()
    {
        long sal_lavador = 0;
        long sal_mecanico = 0;
        long sal_condutor = 0;
        long tot_salarios;
        
        for (Funcionario f: this.tabela_funcionario.values())
            {
                switch(f.getClass().getName())
                {
                    case "Lavador":     sal_lavador += f.salario();
                                        break;
                                        
                    case "Mecanicos":   sal_mecanico +=  f.salario();
                                        break;
                                        
                    case "Condutor":    sal_condutor += f.salario();
                                        break;
                }
            }
         tot_salarios = sal_lavador + sal_mecanico + sal_condutor;
         System.out.println("Total de salários:");
         System.out.println("Lavadores: "+sal_lavador);
         System.out.println("Mecanicos: "+sal_mecanico);
         System.out.println("Condutires:"+sal_condutor);
         System.out.println("Total:"+tot_salarios);
        return tot_salarios;
    }
    
    public Condutor menos_km()
    {
        double min_km = 0;
        Condutor temp = new Condutor(null);
        for(Funcionario f: this.tabela_funcionario.values())
            {
                if(f instanceof Condutor)
                if(((Condutor)f).getKms() < min_km)
                    {
                        min_km = ((Condutor)f).getKms();
                        temp = ((Condutor)f).clone();
                    }   
            }
        return temp;
    }
    
    public Map<Integer,ArrayList<Servicos>> mecanico_servicos()
    {
        HashMap<Integer,ArrayList<Servicos>> temp = new HashMap<Integer,ArrayList<Servicos>>();
        for(Servicos s: this.tabela_servicos.values())
            {
                if(s instanceof Inspeçao)
                 if(temp.containsValue(s.getNcont()))
                    temp.get(s.getNcont()).add(s.clone());
                else
                {
                    ArrayList<Servicos> x = new ArrayList<Servicos>();
                    x.add(s.clone());
                    temp.put(s.getNcont(),x);
                }
            }
        return temp;
    }
    
    
    public ArrayList<String> cliente_funcionario(String s)
    {
        long ncliente = 0;
        ArrayList<String> temp = new ArrayList<String>();
        ArrayList<Servicos> temp1 = new ArrayList<Servicos>();
        for (Clientes c: this.tabela_clientes.values())
            {
               
                if(c.getNome().equals(s))
                    ncliente = c.getCodigo();
            }
        
        temp1=cliente_servicos.get(ncliente);
        

    
         
        for(Funcionario f: this.tabela_funcionario.values())
        {
          for(int i=0;i<temp1.size();) 
          {
              if(f.getNcontribuinte() == temp1.get(i).getNcont())
              {
                  if (temp.contains(f.getNome()))
                  {
                      i++;
                  }
                  else
                  {
                    temp.add(f.getNome());
                    i++;
                  }
              }
          }
        }
        return temp;
    }  
    
    @Override
    public int hashCode() {
        int hash = 5;
        return hash;
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
        final LongTerm other = (LongTerm) obj;
        if (!Objects.equals(this.tabela_clientes, other.tabela_clientes)) {
            return false;
        }
        if (!Objects.equals(this.tabela_funcionario, other.tabela_funcionario)) {
            return false;
        }
        if (!Objects.equals(this.tabela_servicos, other.tabela_servicos)) {
            return false;
        }
        return true;
    }
    
     public double calcula_custo_ambiental()
        {
            for(Funcionario f: this.tabela_funcionario.values())
            {
                if(f instanceof Custo_Ambiental)
                Custo_Ambiental_total += ((Custo_Ambiental)f).calcula_custo_ambiental();
            }
            
            for(Servicos s: this.tabela_servicos.values())
            {   if(s instanceof Custo_Ambiental )
                Custo_Ambiental_total += ((Custo_Ambiental)s).calcula_custo_ambiental();
               // if( s instanceof Lavagens)
                //Custo_Ambiental_total += ((Lavagens)s).calcula_custo_ambiental();
                //if(s instanceof Parkvallet)
                //Custo_Ambiental_total += ((Parkvallet)s).calcula_custo_ambiental();
            }
      return Custo_Ambiental_total;
        }
    
    
     public void ins_cliente()
    {
        System.out.println("N CONTRIBUINTE:");
        long cod = read_long();    
        System.out.println("NOME CLIENTE:");
        Scanner inputclient = new Scanner(System.in);
        String nome = inputclient.next();
        Clientes client = new Clientes(cod, nome);
        try {
             this.inserir_cliente(client);
        }
        catch(CustomExcep e){
        }
      
    }
    
  public void ins_func()
    {
      System.out.println("ESCOLHA O TIPO DE FUNCIONARIO");
      System.out.println("1 - LAVADOR");
      System.out.println("2 - CONDUTOR");
      System.out.println("3 - MECANICO");
      int op = read_int();
      
      do{
          switch(op)
      {
        case 1:
                System.out.println("N CONTRIBUINTE");
                int cod1 = read_int();
                System.out.println("NOME FUNCIONARIO");
                Scanner inputfunc1 = new Scanner(System.in);
                String nome1 = inputfunc1.next();
                System.out.println("SALARIO BASE");
                double sal1 = read_double();
                System.out.println("SALARIO POR LAVAGEM");
                double sal_lav1 = read_double();
                Lavador lav = new Lavador(nome1,cod1,sal1,sal_lav1);
                try {
                    this.inserir_funcionario(lav);}
                    catch(CustomExcep e){}
                break;
        case 2:
                System.out.println("N CONTRIBUINTE");
                int cod2 = read_int();
                System.out.println("NOME FUNCIONARIO");
                Scanner inputfunc2 = new Scanner(System.in);
                String nome2 = inputfunc2.next();
                System.out.println("SALARIO BASE");
                double sal2 = read_double();
                System.out.println("SALARIO POR KM");
                double sal_km2 = read_double();
                Condutor cond = new Condutor(nome2,cod2,sal2,sal_km2);
                try{
                this.inserir_funcionario(cond);}
                catch(CustomExcep e){}
                break;
        case 3:
                System.out.println("N CONTRIBUINTE");
                int cod3 = read_int();
                System.out.println("NOME FUNCIONARIO");
                Scanner inputfunc3 = new Scanner(System.in);
                String nome3 = inputfunc3.next();
                System.out.println("SALARIO BASE");
                double sal3 = read_double();
                Mecanicos mec = new Mecanicos( nome3,cod3,sal3);
                 try{
                this.inserir_funcionario(mec);}
                catch(CustomExcep e){}
                
                break;
      }
     
      
      
    } while(op!=0);
   }
   public void ins_serv()
   {
      System.out.println("ESCOLHA O TIPO DE SERVIÇO");
      System.out.println("1 - LAVAGEM");
      System.out.println("2 - INSPEÇÂO");
      System.out.println("3 - PARKING");
      System.out.println("4 - PARKING DE LONGO TERMO");
      int op = read_int();
     do{
      switch(op)
      {
        case 1:
              System.out.println("N CONTRIBUINTE FUNCIONARIO");
                int codf = read_int();
              System.out.println("N CONTRIBUINTE CLIENTE");
                long codc = read_long();
              System.out.println("TEMPO DE LAVAGEM");
                double tmp = read_double();
              System.out.println("QUANTIDADE DE AGUA GASTA");
              double qt_agua = read_double();
              Lavagens lav = new Lavagens(codc, codf, tmp, qt_agua);
              this.inserir_servico(lav);
              break;
        case 2:
               System.out.println("N CONTRIBUINTE FUNCIONARIO");
                int codf2 = read_int();
              System.out.println("N CONTRIBUINTE CLIENTE");
                long codc2 = read_long();
              System.out.println("MUDA DE OLEO");
                int md_oleo2 = read_int();
              System.out.println("LITROS DE OLEO");
                double qt_oleo2 = read_double();
              Inspeçao insp = new Inspeçao(codc2, codf2, md_oleo2, qt_oleo2);
              this.inserir_servico(insp);
              break;
                
        case 3:
               System.out.println("N CONTRIBUINTE FUNCIONARIO");
                int codf3 = read_int();
              System.out.println("N CONTRIBUINTE CLIENTE");
                long codc3 = read_long();
                System.out.println("MATRICULA");
                Scanner input3 = new Scanner(System.in);
                String mat3 = input3.next();
                System.out.println("MARCA");
                Scanner marca3 = new Scanner(System.in);
                String marc3 = marca3.next();
                Parking park= new Parking(codc3,codf3,mat3,marc3);
                this.inserir_servico(park);
                break;
        case 4:
               System.out.println("N CONTRIBUINTE FUNCIONARIO");
                int codf4 = read_int();
               System.out.println("N CONTRIBUINTE CLIENTE");
                long codc4 = read_long();
               System.out.println("DIA");
               int dia4= read_int();
               System.out.println("MES");
               int mes4=read_int();
               System.out.println("ANO");
               int ano4=read_int();
               System.out.println("DISTANCIA DO LOCAL DE ENTREGA");
               double dist4=read_double();
               Parkvallet parkv= new Parkvallet(codc4,codf4,dia4,mes4,ano4,dist4);
                this.inserir_servico(parkv);
                break;
        default:
              System.out.println("ERRO");
              break;
      }
    }  while(op!=0);
    
    
    
   }
  
  
  
  public void listar_serv(){
      System.out.println("N CONTRIBUINTE CLIENTE");
      long ncont = read_long();
      ArrayList<Servicos> lista = cliente_servicos.get(ncont);
      for( Servicos s: lista){
        s.toString();}
    
    }
    
 
  
   public long read_long()
   {
     Scanner inputcod = new Scanner(System.in);
     long cod;
       do{
        try
        {
             cod = Long.parseLong(inputcod.next());
        }
        catch(NumberFormatException e){
            System.out.println("INVÀLIDO!");            cod = -1;
        }
       }while (cod<0);
     return cod;
   }
  
   public int read_int()
   {
     Scanner inputcod = new Scanner(System.in);
     int cod;
       do{
        try
        {
             cod = Integer.parseInt(inputcod.next());
        }
        catch(NumberFormatException e){
            System.out.println("INVÀLIDO!");            cod = -1;
        }
       }while (cod<0);
     return cod;
   }
  
   public Double read_double()
   {
     Scanner inputcod = new Scanner(System.in);
     double cod;
       do{
        try
        {
             cod = Double.parseDouble(inputcod.next());
        }
        catch(NumberFormatException e){
            System.out.println("INVÀLIDO!");            cod = -1;
        }
       }while (cod<0);
     return cod;
   }
  
}

  


        
         
         
        



