
 

import java.util.Objects;
import java.util.GregorianCalendar;
import java.util.Objects;
import java.util.*;
import java.lang.Iterable;
import java.io.*;
import java.util.GregorianCalendar;
public class Menu implements Serializable
{
public Menu(){
       
}
  
    public int mainMenu(){
         Scanner input = new Scanner(System.in);
         int escolha;
         Clientes client1;
         
    
         do{
         System.out.println("********GESTAO DE PARQUES DE LONGA DURACAO********");
         System.out.println("---------------MENU----------------------");
         System.out.println("...........ESCOLHA A OPCAO..............");
         System.out.println("[1]INSERIR CLIENTE");
         System.out.println("[2]INSERIR FUNCIONARIO");
         System.out.println("[3]INSERIR SERVICO");
         System.out.println("[4]PESQUISAR FUNCIONARIO");
         System.out.println("[5]PESQUISAR CLIENTE");
         System.out.println("[6]LISTAR SERVICOS");
         System.out.println("[7]LAVADOR COM MAIS RENDIMENTO");
         System.out.println("[8]NUMERO DE DIAS QUE CARRO ESTEVE ESTACIONADO");
         System.out.println("[9]TOTAL DE SALARIOS");
         System.out.println("[10]CONDUTOR COM MENOS KM");
         System.out.println("[11]NUMERO DE SERVICOS DE MECANICO");
         System.out.println("[0] Sair");
         escolha = input.nextInt();
       
        return escolha;
    }while (escolha!=0);

}
   
}
  