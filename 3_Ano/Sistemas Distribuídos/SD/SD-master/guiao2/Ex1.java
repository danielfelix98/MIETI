class Counter 
{
	private int c;

	public Counter()
	{
		this.c = 0;
	}

	synchronized public void increment(int numThread)
	{
		c++;
		System.out.println("Thread -> "+numThread+" Número:"+c);
	}

	public int getX()
	{
		return c;
	}
}

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
		Integer x=1;
		for(;x<=this.i;x++)
			this.c.increment(this.n);
	}
}

public class Ex1
{
	public static void main(String[] args) throws InterruptedException
	{
		Integer n=0;
		myThread[] mt = new myThread[10];
		Counter contador = new Counter();
		for(;n<10;n++)
		{
			mt[n] = new myThread(100,n+1,contador);
			mt[n].start();
		}
		for(n=0;n<10;n++)
			mt[n].join();
		System.out.println("O ultimo valor é " + contador.getX());
	}
}