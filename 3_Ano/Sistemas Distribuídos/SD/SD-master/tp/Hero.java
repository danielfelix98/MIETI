import java.util.concurrent.locks.ReentrantLock;

public class Hero{
	private String h;
	private ReentrantLock lockHero;

	public Hero(String h){
		this.h=h;
		this.lockHero=new ReentrantLock();
	}
	public String getName(){
		return this.h;
	}
	public void lock(){
		this.lockHero.lock();
	}
	public void unlock(){
		this.lockHero.unlock();
	}
	public boolean isLock(){
		return this.lockHero.isLocked();
	}
}