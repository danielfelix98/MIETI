class Reader extends Thread{
	private RWlock rwlock;

	public Reader(RWlock rwlock){
	this.rwlock=rwlock;
	}

	public void run(){
		this.rwlock.readLock();
		try{
			sleep(1);
		}catch(InterruptedException ex){
			System.out.println(ex.getMessage());
		}
		this.rwlock.readUnlock();
	}
}