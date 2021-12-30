class myThread extends Thread
{
	private Integer i;
	private Integer n;

	public myThread(Integer i, Integer n)
	{
		this.i=i;
		this.n=n;
	}

	public void run()
	{
		Integer x=1;
		for(;x<=this.i;x++)
			System.out.printf("Sou a Thread %d -> %d\n", this.n, x);
	}
}

public class Ex1
{
	public static void main(String[] args) throws InterruptedException
	{
		Integer i=1000;
		Integer n=0;
		myThread[] mt = new myThread[10];
		for(;n<10;n++)
		{
			mt[n] = new myThread(i,n+1);
			mt[n].start();
		}
		for(n=0;n<10;n++)
			mt[n].join();
	}
}