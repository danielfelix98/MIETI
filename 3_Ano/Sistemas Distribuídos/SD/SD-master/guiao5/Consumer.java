class Consumer extends Thread{
	private Warehouse wh;

	public Consumidor(Warehouse wh){
	this.wh = wh;
	}

	public void run(){
		this.wh.consume(new String[] {"item1","item2","item3"});
	}
}