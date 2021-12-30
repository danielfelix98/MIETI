import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.*;

public class Cliente
{
	Socket s = null;
	
	public static void main(String[] args) 
	{
		try {
			new Cliente();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	private Cliente() throws IOException
	{
		
		System.out.println("Bem-vindo ao jogo RockPaperScissor. \nIntroduza uma das seguintes opções para jogar: ");
		System.out.print("Rock (Pedra) || Paper (Papel) || Scissor (Tesoura). Para sair, introduza >exit<\n --> ");

		s = new Socket(InetAddress.getLocalHost(),8888);

		Thread t1 = new Thread(new ThreadedSendToServer(s));
		Thread t2 = new Thread(new ThreadedReadFromServer(s));	
		
		t2.start();
		t1.start();
		

	}
}

class ThreadedReadFromServer implements Runnable{

	Socket s;
	BufferedReader br;
	
	public ThreadedReadFromServer(Socket s)
	{
		this.s = s;
	}
	
	public void run()
	{
		String str="";
		try {
			br = new BufferedReader(new InputStreamReader(s.getInputStream()));
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		try {
			while((str=br.readLine())!=null) //ler do socket
			{
				System.out.println(str); //escrever p/ ecra msg lida
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
		
	} //fim run
}

class ThreadedSendToServer implements Runnable {

	Socket s=null;
	PrintWriter pw = null;
	BufferedReader br = null;


public ThreadedSendToServer(Socket s)
{
		this.s=s;
	
}

public void run()
{

	String str = "";
	/*if(s.isConnected())
	{
		System.out.println("Client connected to "+s.getInetAddress() + " on port "+s.getPort());
	}*/
	
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	
	
	try {
		pw = new PrintWriter(s.getOutputStream(),true); //escreve p/ socket
	} catch (IOException e) {
		e.printStackTrace();
	}
	
	while(true)
	{
				
			try {
				str=br.readLine(); //lê do teclado
			} catch (IOException e) {
				e.printStackTrace();
			}
			pw.println(str);
			pw.flush();
			
			if(str.equals("exit")) //escrever exit para sair do while
			{
				break;
			}
		
	}
	try {
		s.close();
	} catch (IOException e) {
		e.printStackTrace();
	}
}

}
