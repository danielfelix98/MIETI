import java.io.IOException;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;

public class ServerWorker implements Runnable{
	private Socket socket;
	private BufferedReader in;
	private BufferedWriter out;
	private GameServer gameserver;
	private Player player;
	private Game game;
	
	public ServerWorker(Socket socket,GameServer gameserver){
		try{
			this.socket=socket;
			this.gameserver=gameserver;
			this.in=new BufferedReader(new InputStreamReader(socket.getInputStream()));
			this.out=new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
		}catch(IOException e){
			e.printStackTrace();
		}
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
	public void close(){
		try{
			socket.shutdownInput();
			socket.shutdownOutput();
			socket.close();
		}
		catch(Exception e){
			e.printStackTrace();
		}
	}
	public void run(){
		try{
			String op=null;
			String pass=null;
			String user=null;
			boolean repeat=false;
			while((op=this.in.readLine())!=null){
				try{
					System.out.println("Worker-"+Thread.currentThread().getId()+" > Received operation from client: ");
					switch(op){
					case "register":
						System.out.println("REGISTER");
						do{
							user=this.in.readLine();
							pass=this.in.readLine();
							if(this.gameserver.playerRegister(user,pass,this.out)){
								this.gameserver.playerLogin(user,pass);
								this.player=this.gameserver.getPlayer(user);
								write("registered");
								repeat=false;
							}
							else{
								write("not registered");
								repeat=true;
							}
						}while(repeat);
						break;
					case "login":
						System.out.println("LOGIN");
						do{
							user=this.in.readLine();
							pass=this.in.readLine();
							if(this.gameserver.playerLogin(user,pass)){
								this.player=this.gameserver.getPlayer(user);
								write("login executed");
								repeat=false;
							}
							else{
								write("not login executed");
								repeat=true;
							}
						}while(repeat);
						break;
					case "play":
						System.out.println("PLAY");
						write("Searching for a game...");
						this.game=this.gameserver.getGame(this.player.getRank());
						write("Game found\nSearching for more players");
						this.game.makeTeams(this.player);
						write("You make part of team "+this.game.getTeam(this.player));
						write("Choose a Hero, you have 30 seconds");
						for(int i=0,k=0;i<6;i++)
							write((k+1)+"- "+this.game.getHeroName(k++)+"\t"+
								(k+1)+"- "+this.game.getHeroName(k++)+"\t"+
								(k+1)+"- "+this.game.getHeroName(k++)+"\t"+
								(k+1)+"- "+this.game.getHeroName(k++)+"\t"+
								(k+1)+"- "+this.game.getHeroName(k++)+"\t");
						Thread pick=new Thread(new PickServerWorker());
						pick.start();
						Thread.sleep(30000);
						pick.interrupt();
						if(this.game.getAbort()==this.game.getMax()){
							write(this.game.teamsTable());
							write("Simulating game...");
							this.game.result();
							boolean res=this.game.getResult(this.game.getTeam(this.player));
							if(res)
								write("* The team "+this.game.getTeam(this.player)+" won!");
							else
								write("* The team "+this.game.getTeam(this.player)+" lost!");
							this.player.updateHistoric(res);
							this.player.reRank(res);
							this.gameserver.removeGame(this.game.getId());
							write("Write 'ok' to proceed.");
						}
						else{
							write("Game canceled.");
							write("Write 'ok' to proceed.");
						}
						break;
					case "historic":
						System.out.println("HISTORIC");
						write(this.player.getHistory());
						write("Write 'ok' to proceed.");
						break;
					case "get rank":
						System.out.println("GET RANK");
						write("This is your rank: "+this.player.getRank()+" ");
						write("Write 'ok' to proceed.");
						break;
					case "logout":
						System.out.println("LOGOUT");
						write("kill listener");
						this.gameserver.playerLogout(user);
						break;
					case "quit":
						System.out.println("QUIT");
						write("kill listener");
						close();
						break;
					default:
						System.out.println("Worker-"+Thread.currentThread().getId()+" > Unknown operation "+op);
					}
				}catch(InvalidPlayer ji){
					System.out.println("Worker-"+Thread.currentThread().getId()+" > Invalid player ");
				}catch(PlayerDoesntBelong pdb){
					System.out.println("Worker-"+Thread.currentThread().getId()+" > Player has no team ");
				}catch(Exception e){
					System.out.println("ERROR1: "+e.getMessage());
					e.printStackTrace();
				}
			}
		}catch(IOException ioe){
			try{
				System.out.println("Worker-"+Thread.currentThread().getId()+" > Client disconnected. Connection is closed.");
				close();
			}catch(Exception e){
				System.out.println("ERROR2: "+e.getMessage());
				e.printStackTrace();
			}
		}
	}
	public class PickServerWorker implements Runnable{
		public PickServerWorker(){}
		public void run(){
			try{
				String message;
				int hero=-1;
				String tm=game.getTeam(player);
				while((message=in.readLine())!=null && !message.equals("kill pick") && !message.equals("ready")){
					if(message.equals("cancel") && hero!=-1){
						game.getHero(tm,hero).unlock();
						write("Choose other hero.");
						game.setAbort(-1);
						game.setReady(-1);
						hero=-1;
					}
					else if(message.equals("cancel") && hero==-1)
						write("Choose a hero first");
					else if(!message.equals("cancel") && hero!=-1)
						write("To pick another hero, write 'cancel' first.");
					else{
						hero=Integer.parseInt(message);
						if(hero<31 && hero>0 && !game.getHero(tm,hero).isLock()){
							game.getHero(tm,hero).lock();
							game.setAbort(1);
							player.setHero(game.getHero(tm,hero).getName());
							game.teammatePicks(tm,player.getUsername(),hero);
							write("Hero choosed. Write 'cancel' to choose other.");
							int i=game.setReady(1);
							if(i==game.getMax())
								game.getReady();
						}
						else if(hero<31 && hero>0 && game.getHero(tm,hero).isLock()){
							write("Hero allready choosed, try other one.");
							hero=-1;
						}
						else{
							write("Invalid choice, try again.");
							hero=-1;
						}
					}
				}
				if(message.equals("ready"))
					write("ALL PLAYERS LOCKED IN. GAME IS ABOUT TO START.");
			}catch(PlayerDoesntBelong pdb){
				System.out.println("Worker-"+Thread.currentThread().getId()+" > Player has no team ");
			}catch(IOException e){
				e.printStackTrace();
			}
		}
	}
}