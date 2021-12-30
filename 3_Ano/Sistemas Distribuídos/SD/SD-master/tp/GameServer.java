import java.util.Map;
import java.util.HashMap;
import java.io.BufferedWriter;

public class GameServer{
	private HashMap<String,Player> players;
	private HashMap<Integer,Game> games;
	private int countGames;

	public GameServer(){
		this.players=new HashMap<String,Player>();
		this.games=new HashMap<Integer,Game>();
		this.countGames=0;
	}
	public synchronized boolean playerRegister(String user,String pass,BufferedWriter out){
		if(!this.players.containsKey(user)||this.players.isEmpty()){
			Player pl=new Player(user,pass,out);
			this.players.put(user,pl);
			return true;
		}
		else
			return false;
	}
	public synchronized boolean playerLogin(String user,String pass){
		if(this.players.containsKey(user)&&this.players.get(user).getPass().equals(pass)&&!this.players.get(user).isLock()){
			this.players.get(user).lock();
			return true;
		}
		else
			return false;
	}
	public synchronized void playerLogout(String user)throws InvalidPlayer{
		if(!this.players.containsKey(user))
			throw new InvalidPlayer(user);
		this.players.get(user).unlock();
	}
	public synchronized Game getGame(int rank){
		if(!this.games.isEmpty())
			for(Map.Entry<Integer,Game> p:this.games.entrySet())
				if(p.getValue().getCur1()<p.getValue().getMax()&&(p.getValue().getRankGame()==rank||p.getValue().getRankGame()==(rank+1)))
					return p.getValue();
		Game gm=new Game(this.countGames,rank);
		this.games.put(this.countGames,gm);
		this.countGames++;
		return gm;
	}
	public synchronized void removeGame(int id){
		this.games.remove(id);
	}
	public synchronized Player getPlayer(String user)throws InvalidPlayer{
		if(!this.players.containsKey(user))
			throw new InvalidPlayer(user);
		return this.players.get(user);
	}
}

class InvalidPlayer extends Exception{
	public InvalidPlayer(){}
	public InvalidPlayer(String user){
		super("Player "+user+" doesn't exist!");
	}
}