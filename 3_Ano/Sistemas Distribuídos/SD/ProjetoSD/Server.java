import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;

public class Server {
	
	ServerSocket ss;
	
	public static void main(String[] args) 
	{
		try {
			new Server();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	private Server() throws IOException
	{
	    ss = new ServerSocket(8888);
		while(true)
		{
			System.out.println("Server waiting for connection on port 8888");
			Socket client1 = ss.accept();
			System.out.println("Received connection from "+client1.getInetAddress()+" on port "+client1.getPort());
			Socket client2 = ss.accept();
			System.out.println("Received connection from "+client2.getInetAddress()+" on port "+client2.getPort());
			ClientHandler ch = new ClientHandler(client1,client2,this);
			ch.start();
		}
	}
	}

class ClientHandler extends Thread {

	Server server;
	Socket s1;
	Socket s2;

	public ClientHandler(Socket s1, Socket s2, Server server)
	{
		this.s1=s1;
		this.s2=s2;
		this.server=server;
	}

	public void run()
	{
		try{

			BufferedReader bi1 = new BufferedReader(new InputStreamReader(s1.getInputStream()));
			BufferedReader bi2 = new BufferedReader(new InputStreamReader(s2.getInputStream()));
			PrintWriter p1 = new PrintWriter(s1.getOutputStream(),true);
			PrintWriter p2 = new PrintWriter(s2.getOutputStream(),true);

			String str1 = "";
			String str2 = "";
			int i=0;
			do
			{
				str1=bi1.readLine();
				str2=bi2.readLine();
				RockPaperScissor rps = new RockPaperScissor(str1,str2);
				i=rps.winner();	
				switch(i)
				{
				case 0 : p1.println("Empate!"); p2.println("Empate!"); p1.flush(); p2.flush(); break;
				case 1 : p1.println("Venceu!"); p2.println("Perdeu!"); p1.flush(); p2.flush(); break;
				case 2 : p2.println("Venceu!"); p2.println("Perdeu!") ;p1.flush(); p2.flush(); break;
				}
					
			p1.flush();
			p2.flush();

			}while((str1.equals("exit"))!=false || (str2.equals("exit"))!=false);

			
						
			
			bi1.close();
			bi2.close();
			s1.close();
			s2.close();		

		}catch (Exception e) {}
	}
}

class RockPaperScissor {

	int winner;
	String play1;
	String play2;
	
	public RockPaperScissor(String play1, String play2)
	{
		
		winner=-1;
		this.play1=play1;
		this.play2=play2;
	}
	public String getPlay1()
	{
		return play1;
	}

	public String getPlay2()
	{
		return play2;
	}

	public int winner()
	{
		if(play1.equals(play2))
		{
			winner=0;
		}
		if((play1.equals("Rock") && play2.equals("Scissor")) || (play1.equals("Scissor") && play2.equals("Paper")) || (play1.equals("Paper") && play2.equals("Rock")))
		{
			winner=1;
		}
		if((play2.equals("Rock") && play1.equals("Scissor")) || (play2.equals("Scissor") && play1.equals("Paper")) || (play2.equals("Paper") && play1.equals("Rock")))
		{
			winner=2;
		}
		return winner;
	}
}
