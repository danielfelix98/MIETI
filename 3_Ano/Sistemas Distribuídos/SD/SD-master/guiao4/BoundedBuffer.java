class BoundedBuffer{

	int array[]=null;
	int n,p=0,t=0;

	public BoundedBuffer(int n){
		array=new int[n];
		this.n=n;
	}

	public int get() throws InterruptedException {
		while(t==0)
			wait();
		int r=array[p];
		t--;
		p=(p+1)%n;
		notifyAll();
		//vff diz que o notifyAll dá uma sobrecarga no sistema, 
		//por isso usar notifyAll quando necessario!
		//neste exercicio usa-se notifyAll.
		return r;
	}

	public void put(int v) throws InterruptedException {
		while(t==n)
			wait();
		array[(p+t)%n]=v;
		t++;
		notifyAll();
	}

	public static void main(String[] args){
	}
}