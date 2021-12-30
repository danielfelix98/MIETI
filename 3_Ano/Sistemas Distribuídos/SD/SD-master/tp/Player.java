import java.util.concurrent.locks.ReentrantLock;
import java.util.ArrayList;
import java.io.BufferedWriter;

public class Player{
	private String username;
	private String password;
	private int rank;
	private ArrayList<String> history;
	private ReentrantLock lockPlayer;
	private String hero;
	private BufferedWriter out;

	public Player(String user,String pass,BufferedWriter out){
		this.username=user;
		this.password=pass;
		this.rank=0;
		this.history=new ArrayList<String>(10);
		this.lockPlayer=new ReentrantLock();
		this.hero=null;
		this.out=out;
	}
	public void reRank(boolean win){
		if(win && this.rank<9)
			this.rank++;
		else if(!win && this.rank>0)
			this.rank--;
	}
	public void updateHistoric(boolean win){
		if(win && this.history.size()<10)
			this.history.add(0,"W");
		else if(win && this.history.size()>9){
			this.history.remove(9);
			this.history.add(0,"W");
		}
		else if(!win && this.history.size()<10)
			this.history.add(0,"L");
		else{
			this.history.remove(9);
			this.history.add(0,"L");
		}
	}
	public String getUsername(){
		return this.username;
	}
	public String getPass(){
		return this.password;
	}
	public int getRank(){
		return this.rank;
	}
	public String getHistory(){
        StringBuilder sb=new StringBuilder("-> "+this.username+"\n");
        for(int i=1;i<11;i++)
        	sb.append(i+" ");
        sb.append("\n");
        if(this.history.isEmpty())
        	return sb.toString();
        for(String res:this.history)
        	sb.append(res+" ");
        sb.append("\n");
        return sb.toString();
	}
	public String getHeroChoosed(){
		return this.hero;
	}
	public BufferedWriter getBufOut(){
		return this.out;
	}
	public void setHero(String name){
		this.hero=name;
	}
	public void lock(){
		this.lockPlayer.lock();
	}
	public void unlock(){
		this.lockPlayer.unlock();
	}
	public boolean isLock(){
		return this.lockPlayer.isLocked();
	}
}