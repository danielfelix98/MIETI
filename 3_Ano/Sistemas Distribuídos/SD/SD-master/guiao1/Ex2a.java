class myThread extends Thread
{
	private Integer i;
	private Integer n;
	private Counter c;

	public myThread(Integer i, Integer n, Counter c)
	{
		this.i=i;
		this.n=n;
		this.c=c;
	}

	public void run()
	{
		Integer x=0;
		for(;x<this.i;x++)
		{
			this.c.increment(this.n);
		}
	}
}

class Counter 
{
	private int c;

	public Counter()
	{
		this.c = 0;
	}

	public void increment(int numThread)
	{
		c++;
		System.out.println("Thread -> "+numThread+" Número:"+c);
	}

	public int getX()
	{
		return c;
	}

}

public class Ex2a
{
	public static void main(String[] args) throws InterruptedException
	{
		Integer i=100;
		Integer n=0;
		myThread[] mt = new myThread[10];
		Counter contador = new Counter();
		for(;n<10;n++)
		{
			mt[n] = new myThread(i,n+1,contador);
			mt[n].start();
		}
		for(n=0;n<10;n++)
			mt[n].join();
		System.out.println("O ultimo valor é " + contador.getX());
	}
}