class Producer extends Thread{
	private Warehouse wh;

	public Producer(Warehouse wh){
	this.wh=wh;
	}

	public void run(){
		this.wh.supply("item1",1);
		try{
			sleep(3);
		}catch(InterruptedException ex){
			System.out.println(ex.getMessage());
		}
		this.wh.supply("item2", 1);
		try{
			sleep(3);
		}catch(InterruptedException ex){
			System.out.println(ex.getMessage());
		}
		this.wh.supply("item3", 1);
	}
}