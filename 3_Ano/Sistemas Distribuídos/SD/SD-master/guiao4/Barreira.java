class Barreira extends Thread{
	private Integer n;
	private Integer espera;

	public Barreira(Integer n){
		this.n=n;
		this.espera=0;
	}

	public void esperar() throws InterruptedException{
		while(espera<n)
			wait();
		espera--;
		notifyAll();
	}

	public void run()
	{
		try{
			esperar();
		}
		catch (InterruptedException e) 
        {
            System.out.println("Erro!");
        }
	}
}