package RPS;

import java.io.*;
import java.net.*;

public class RPSClient{


  public static void main (String []args) throws IOException,UnknownHostException
	{
  	Socket cs;
    String continues;
    BufferedReader sin = new BufferedReader(new InputStreamReader(System.in));

    do
    {
      cs = new Socket("localhost",RPSProtocol.PORT);

  		PrintWriter out = new PrintWriter(cs.getOutputStream(),true);
  		BufferedReader in = new BufferedReader(new InputStreamReader(cs.getInputStream()));

  		String myResponse, serverResponse;
      String[] splitResponse = new String[2];

      //Waiting for players
      System.out.println("\n\nBem vindo ao Pedra,Papel e Tesoura Online\n\nA aguardar por adversário...");

      while( (serverResponse = in.readLine()) != null){

        splitResponse = serverResponse.split(RPSProtocol.MSG_SEP);
        int responseType = Integer.parseInt(splitResponse[0]);

        switch(responseType){
          case RPSProtocol.START:
            //game start, place your bet
            int myResponseInt=0;
            System.out.println("\nO jogo começou, escolhe a tua aposta (Tesoura-1, Papel-2, Pedra-3):");
            while(myResponseInt<1 || myResponseInt>3){

              myResponse = sin.readLine();
              try{
                myResponseInt = Integer.parseInt(myResponse);
              }catch(NumberFormatException nfe){
                myResponseInt=0;
              }
              if(myResponseInt<1 || myResponseInt>3){
                System.out.println("Introduziste um valor incorreto, tenta outra vez!");
              }
            }
            out.println(""+RPSProtocol.BET+RPSProtocol.MSG_SEP+myResponseInt);
            System.out.println("\nA aguardar resposta do adversário.");
          break;

          case RPSProtocol.RESULT:
            int result = Integer.parseInt(splitResponse[1]);
            switch(result){
              case RPSProtocol.WIN:
                System.out.println("\nParabéns, ganhaste!");
              break;

              case RPSProtocol.LOSE:
                System.out.println("\nPerdeste, não desanimes!");
              break;

              case RPSProtocol.TIE:
                System.out.println("\nEmpate!");
              break;
            }
          break;
        }
        if(responseType==RPSProtocol.END)
        {
          System.out.println("\n"+splitResponse[1]);
          break;
        }
      }
  		in.close();
  		out.close();
  		cs.close();

      System.out.println("\nPretendes continuar a jogar? (S-Sim, Outra tecla qualquer-Não)");
      continues=sin.readLine();

    }while(continues.toUpperCase().equals("S"));

    sin.close();
	}
}
