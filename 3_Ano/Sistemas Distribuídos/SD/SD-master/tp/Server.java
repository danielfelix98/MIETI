import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class Server{
	private ServerSocket servsocket;
	private int port;
	private GameServer gameserver;

	public Server(int port){
		this.port=port;
		this.gameserver=new GameServer();
	}
	public void startServer(){
		try{
			System.out.println("#### SERVER ####");
			this.servsocket=new ServerSocket(this.port);
			while(true){
				System.out.println("Waiting for connection...");
				Socket socket=servsocket.accept();
				System.out.println("Player connect. Starting login thread.");
				ServerWorker sw=new ServerWorker(socket,gameserver);
				new Thread(sw).start();
			}
		}catch(IOException e){
			e.printStackTrace();
		}
	}
	public static void main(String[] args){
		Server s=new Server(12345);
		s.startServer();
	}
}