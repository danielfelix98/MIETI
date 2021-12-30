class Main{
	public static void main(String[] args) {
		Warehouse wh = new Warehouse();
		wh.supply("item1", 0);
		wh.supply("item2", 0);
		wh.supply("item3", 0);
		Produtor p = new Produtor(wh);
		Consumidor c = new Consumidor(wh);
		Thread t1 = new Thread(p);
		Thread t2 = new Thread(c);
		t1.start();
		t2.start();
		try{
			t2.join();
			t1.join();
		}catch(InterruptedException e){
			System.out.println(e.getMessage());
		}
		System.out.println("Fim");
	}
}