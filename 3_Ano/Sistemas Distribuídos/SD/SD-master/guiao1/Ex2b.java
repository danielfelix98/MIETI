class myThread extends Thread
{
	private Integer i;
	private Integer n;
	private Integer c;

	public myThread(Integer i, Integer n, Integer c)
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
			c++;
			System.out.println("Thread -> "+n+" Número:"+c);
		}
	}
}

public class Ex2b
{
	public static void main(String[] args) throws InterruptedException
	{
		Integer i=1000;
		Integer n=0;
		Integer c=0;
		myThread[] mt = new myThread[10];
		for(;n<10;n++)
		{
			mt[n] = new myThread(i,n+1,c);
			mt[n].start();
		}
		for(n=0;n<10;n++)
			mt[n].join();
		System.out.println("O ultimo valor é " + c);
	}
}