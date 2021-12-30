class Writer extends Thread{
	private RWlock rwlock;

	public Writer(RWlock rwlock){
	this.rwlock=rwlock;
	}

	public void run(){
		this.rwlock.writeLock();
		try{
			sleep(1);
		}catch(InterruptedException ex){
			System.out.println(ex.getMessage());
		}
		this.rwlock.writeUnlock();
	}
}