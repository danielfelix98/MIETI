import java.io.*;
public class Main 
{
    public static void main(String[] args)
    {
        Menu menu = new Menu();
        LongTerm lterm = read();
        int op;
        do{
            op  = menu.mainMenu();
        switch(op){
            case 1:
                lterm.ins_cliente();
                break;
            case 2:
                lterm.ins_func();
                break;
            case 3:
                lterm.ins_serv();
                break;
         /*   case 4:
                lterm.pesq_func();
                break;
            case 5:
                lterm.pesq_cliente();
                break;*/
            case 6:
                lterm.listar_serv();
                break;/*
            case 7:
                lterm.lav_mais_rend();
                break;
            case 8:
                lterm.ndias_estac();
                break;
            case 9:
                lterm.tot_sal();
                break;
            case 10:
                lterm.men_km();
                break;
            case 11:
                lterm.n_serv_meca();
                break;*/
        }}
       while (op!=0);
       lterm.save();
    }
   
    
    
    public static LongTerm read()
    {
        LongTerm lt = null;
        FileInputStream fIn;
        ObjectInputStream oIn;
        try{
            File file = new File("C:\\Empdatabase.db");
            if(!file.exists())
                lt = new LongTerm();
            else
                {
                    fIn = new FileInputStream(file);
                    oIn = new ObjectInputStream(fIn);
                    lt = (LongTerm) oIn.readObject();
                    oIn.close();
                }
            }
        catch (Exception e)
            {e.printStackTrace();}
    return lt;
    }
    
}