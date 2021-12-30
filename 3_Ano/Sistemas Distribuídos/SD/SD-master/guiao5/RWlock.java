import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Condition;

class RWlock{

	private ReentrantLock l;
	private Condition cread;
	private Condition cwrite;
	private int readers;
	private int writers;

	public RWlock(){
		l=new ReentrantLock();
		cread=l.newCondition();
		readers=0;
		cwrite=l.newCondition();
		writers=0;
	}

	public void readLock(){
		this.l.lock();
		while(this.writers==1||this.readers>5)
		{
			try{
				cr.await();
			}
			catch(InterruptedException ex){
				System.out.println(ex.getMessage());
			}
		}
		this.readers++;
		this.l.unlock();
	}

	public void readUnlock(){
		this.l.lock();
		this.readers--;
		this.cw.signalAll();
		this.l.unlock();
	}

	public void writeLock(){
		this.l.lock();
		while(this.readers>0)
		{
			try{
				wr.await();
			}
			catch(InterruptedException ex){
				System.out.println(ex.getMessage());
			}
		}
		this.writers++;
		this.l.unlock();
	}

	public void writeUnlock(){
		this.l.lock();
		this.writers--;
		this.cr.signalAll();
		this.cw.signalAll();
		this.l.unlock();
	}
}