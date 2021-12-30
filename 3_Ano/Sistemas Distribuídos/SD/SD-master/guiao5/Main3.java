class Main3{
	public static void main(String[] args){
		RWlock rwlock = new RWlock();
		Thread rds[] = new Thread[15];
		Thread wts[] = new Thread[15];
		for(int i=0;i<15;i++){
			rds[i]=new Thread(new Reader(rwlock));
			wts[i]=new Thread(new Writer(rwlock));
		}
		for(i=0;i<15;i++){
			rds[i].start();
			wts[i].start();
		}
		try{
			for(i=0;i<15;i++){
				rds[i].join();
				wts[i].join();
			}
		}catch(InterruptedException e){
			System.out.println(e.getMessage());
		}
		System.out.println("Fim");
	}
}