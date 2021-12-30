import java.io.IOException;
import java.net.UnknownHostException;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;

public class Client{
	private Socket socket;
	private BufferedReader in;
	private BufferedWriter out;
	private BufferedReader systemIn;
	private String username;

	public Client(String hostname,int porto){
		try{
			this.socket=new Socket(hostname,porto);
			this.in=new BufferedReader(new InputStreamReader(socket.getInputStream()));
			this.out=new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
			this.systemIn=new BufferedReader(new InputStreamReader(System.in));
		}catch(IOException e){
			e.printStackTrace();
		}
	}
	public void welcomeMenu(){
		System.out.print("\033[H\033[2J");
		System.out.println("---------Welcome!---------");
		System.out.println(" [1] Register");
		System.out.println(" [2] Login");
		System.out.println(" [3] Quit");
		System.out.println("--------------------------");
		System.out.print("Pick an option: ");
	}
	public void write(String msg){
		try{
			this.out.write(msg);
			this.out.newLine();
			this.out.flush();
		}catch(Exception e){
			e.printStackTrace();
		}
	}
	public void userPassCicle(String flag,String warning){
		try{
			String response=null;
			String pass=null;
			do{
				System.out.print("* Username: ");
				this.username=this.systemIn.readLine();
				write(this.username);
				System.out.print("* Password: ");
				pass=this.systemIn.readLine();
				write(pass);
				response=this.in.readLine();
				if(!response.equals(flag))
					System.out.println(warning);
			}while(!response.equals(flag));
		}catch(Exception e){
			e.printStackTrace();
		}
	}
	public void gameMenu(){
		System.out.print("\033[H\033[2J");
		System.out.println("---------Welcome "+this.username);
		System.out.println(" [1] Play");
		System.out.println(" [2] Historic");
		System.out.println(" [3] Rank");
		System.out.println(" [4] Logout");		
		System.out.println("--------------------------");
	}
	public void okPause(){
		try{
			String message=null;
			while((message=this.systemIn.readLine())!=null&&!message.equals("ok"))
				write(message);
		}catch(Exception e){
			e.printStackTrace();
		}
	}
	public void gameLaunch(){
		try{
			int quit=0;
			String keyboard=null;
			Thread listener=new Thread(new ClientListener());
			listener.start();
			while(quit!=1){
				gameMenu();
				while(quit!=1 && (keyboard=this.systemIn.readLine())!=null){
					switch(keyboard){
						case "1":
							write("play");
							okPause();
							gameMenu();
							write("kill pick");
							break;
						case "2":
							write("historic");
							okPause();
							gameMenu();
							break;
						case "3":
							write("get rank");
							okPause();
							gameMenu();
							break;
						case "4":
							write("logout");
							quit=1;
							break;
						default:
							System.out.println("Invalid option, try again!");
					}
				}
			}
			welcomeMenu();
		}catch(Exception e){
			e.printStackTrace();
		}
	}
	public void clientStart(){
		try{
			int quit=0;
			String keyboard=null;
			while(quit!=1){
				welcomeMenu();
				while(quit!=1 && (keyboard=this.systemIn.readLine())!=null){
					switch(keyboard){
						case "1":
							write("register");
							System.out.println("---------Register---------");
							userPassCicle("registered","Player already registered.");
							gameLaunch();
							break;
						case "2":
							write("login");
							System.out.println("------Begin Session-------");
							userPassCicle("login executed","Player already online or doesn't exist.");
							gameLaunch();
							break;
						case "3":
							quit=1;
							write("quit");
							System.out.println("See you soon!");
							break;
						default:
							System.out.println("Invalid option, try again!");
					}
				}
			}
			socket.shutdownInput();
			socket.shutdownOutput();
			socket.close();
		}catch(UnknownHostException e){
			System.out.println("ERRO: Server doesn't exist!");
			e.printStackTrace();
		}catch(Exception e){
			System.out.println("ERRO: "+e.getMessage());
			e.printStackTrace();
		}
	}
	public static void main(String[] args){
		Client c=new Client("127.0.0.1",12345);
		c.clientStart();
	}
	public class ClientListener implements Runnable{
		public ClientListener(){}
		public void run(){
			String message;
			try{
				while((message=in.readLine())!=null && !message.equals("kill listener")){
					if(message.equals("ready"))
						write("ready");
					System.out.println(message);
				}
			}catch(IOException e){
				e.printStackTrace();
			}
		}
	}
}