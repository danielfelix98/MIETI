import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Condition;

class BoundedBuffer{

	private int array[]=null;
	private int n,p=0,t=0;
	private ReentrantLock l = new ReentrantLock();
	private Condition full = l.newCondition();
	private Condition empty = l.newCondition();

	public BoundedBuffer(int n){
		this.n=n;
		array=new int[n];
	}

	public int get() throws InterruptedException{
		this.l.lock();
		try{
			while(t==0)
				this.empty.await();
			int r=array[p];
			t--;
			p=(p+1)%n;
			this.full.signalAll();
			return r;
		}
		finally{
			this.l.unlock();
		}
	}

	public void put(int v) throws InterruptedException{
		this.l.lock();
		try{
			while(t==n)
				this.full.await();
			array[(p+t)%n]=v;
			t++;
			this.empty.signalAll();
		}
		finally{
			this.l.unlock();
		}
	}

	public static void main(String[] args){
	}
}