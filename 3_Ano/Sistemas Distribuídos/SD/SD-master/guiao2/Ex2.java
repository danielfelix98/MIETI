// cada thread tem os seus prorpios registos

class Conta extends Thread
{
	public float saldo;

	public Conta()
	{
		saldo=0;
	}

	public float getSaldo()
	{
		return this.saldo;
	}

	public void cSaldo(float c)
	{
		this.saldo+=c;
	}

	public void dSaldo(float d)
	{
		this.saldo-=d;
	}
}

class Banco
{
	private Conta[] contas;

	public Banco(int n)
	{
		int i;
		for(i=0;i<n;i++)
			contas[i] = new Conta();
	}

	//sem o synchronized, o programa não funciona bem com várias transações ao mesmo tempo
	public synchronized float consulta(int n)
	{
		return this.contas[n-1].getSaldo();
	}

	public synchronized void credito (int n, float c)
	{
		contas[n-1].cSaldo(c);
	}

	public synchronized void debito (int n, float d)
	{
		contas[n-1].dSaldo(d);
	}

	// não precisa porque o credito e o debito ja são synch e em alguns sistemas dá dead lock
	// mas mais a frente vai ser synch
	//
	// tive a ver depois, e não faz muito sentido não ser, se houver dois creditos na conta 1
	// pode depois não haver saldo para fazer o debito para a conta 2
	public synchronized void transferencia(int nrConta1, int nrConta2, float valor)
	{
		credito(nrConta1, valor);
		debito(nrConta2, valor);
	}
}

class Ex2
{
	public static void main(String[] args) throws InterruptedException
	{
		Banco b = new Banco(10);
	}
}