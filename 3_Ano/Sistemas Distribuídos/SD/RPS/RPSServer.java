package RPS;

import java.io.*;
import java.net.*;
import java.util.*;

public class RPSServer
{
	public static void main(String[] args) throws IOException{
/*		ArrayList<Socket> playersQueue = new ArrayList<Socket>();
		ServerSocket ss = new ServerSocket(RPSProtocol.PORT);
		while(true){
			playersQueue.add(ss.accept());
			if(playersQueue.size()==2){
				new Thread(new GameControl(playersQueue.get(0),playersQueue.get(1))).start();
				playersQueue.clear();
			}
		}*/

		ServerSocket ss = new ServerSocket(RPSProtocol.PORT);
    Socket cs = null;
    Socket css = null;

    while(true){
      cs = ss.accept();
      css = ss.accept();
			System.out.println("2 accept");
      new Thread (new GameControl(cs,css)).start();
    }
	}
}

class GameControl implements Runnable{
	Socket p1;
	Socket p2;

	GameControl(Socket cs1, Socket cs2){
		p1 = cs1;
		p2 = cs2;
	}

	public String checkRPS(String player,String otherPlayer){
		String response=null;
		int play1=Integer.parseInt(player);
		int play2=Integer.parseInt(otherPlayer);

		if((play1%3 +1) == play2)
			response=RPSProtocol.RESULT+RPSProtocol.MSG_SEP+RPSProtocol.WIN;
		else
			if((play2%3+1)==play1)
				response=RPSProtocol.RESULT+RPSProtocol.MSG_SEP+RPSProtocol.LOSE;
			else
				response=RPSProtocol.RESULT+RPSProtocol.MSG_SEP+RPSProtocol.TIE;

		return response;
	}

	public String startRPS(){
		String response= RPSProtocol.START+RPSProtocol.MSG_SEP+"start";
		return response;
	}

	public void run(){
		try {
			System.out.println("Nova thread");
      		PrintWriter out1 = new PrintWriter(p1.getOutputStream(), true);
      		BufferedReader in1 = new BufferedReader( new InputStreamReader(p1.getInputStream() ) );
			PrintWriter out2 = new PrintWriter(p2.getOutputStream(), true);
      		BufferedReader in2 = new BufferedReader( new InputStreamReader(p2.getInputStream() ) );
      		String response1,response2;

			//start game
			out1.println(startRPS());
			out2.println(startRPS());
			if(((response1=in1.readLine())!=null)&&((response2=in2.readLine())!=null))
			{
				//check bets
				String[] splitResponse1 = response1.split(RPSProtocol.MSG_SEP);
				int responseType1 = Integer.parseInt(splitResponse1[0]);
				String bet1="",bet2="";

				switch(responseType1){
					case RPSProtocol.BET:
						bet1 = splitResponse1[1];
					break;

				}

				String[] splitResponse2 = response2.split(RPSProtocol.MSG_SEP);
				int responseType2 = Integer.parseInt(splitResponse2[0]);

				switch(responseType2){
					case RPSProtocol.BET:
						bet2 = splitResponse2[1];
						//send results
						out1.println(checkRPS(bet1,bet2));
						out2.println(checkRPS(bet2,bet1));
					break;
				}

			}
			else
			{
				if(response1==null)
					out2.println(""+RPSProtocol.END+RPSProtocol.MSG_SEP+"O seu adversário abandonou o jogo!");
				else
					out1.println(""+RPSProtocol.END+RPSProtocol.MSG_SEP+"O seu adversário abandonou o jogo!");
			}

	      	in1.close();
	      	out1.close();
	      	p1.close();
		  	in2.close();
	      	out2.close();
	      	p2.close();
    	}
    	catch(IOException e){
      		e.printStackTrace();
    	}
	}

}
