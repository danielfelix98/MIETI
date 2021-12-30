import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Condition;

class Item{
	ReentrantLock l;
	Condition isEmpty;
	int quantity;

	Item(){
		l=new ReentrantLock();
		isEmpty=l.newCondition();
		quantity=0;
	}

	void supply(int quantity){
		this.l.lock();
		this.quantity+=quantity;
		this.isEmpty.signalAll();
		this.l.unlock();
	}

	void consume(){
		this.l.lock();
		while(this.quantity==0){
			try{
				this.isEmpty.await();
			} catch(InterruptedException ex){
				System.out.println(ex.getMessage());
			}
		}
		this.quantity--;
		this.l.unlock();
	}
}