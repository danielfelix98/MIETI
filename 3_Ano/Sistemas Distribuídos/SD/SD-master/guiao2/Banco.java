class Conta
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
	public float consulta(int n)
	{
		synchronized(this.contas[n-1])
		{
			return this.contas[n-1].getSaldo();
		}
	}

	public void credito (int n, float c)
	{
		synchronized(this.contas[n-1])
		{
			contas[n-1].cSaldo(c);
		}
	}

	public void debito (int n, float d)
	{
		synchronized(this.contas[n-1])
		{
			contas[n-1].dSaldo(d);
		}
	}

	public void transferencia(int nrConta1, int nrConta2, float valor)
	{
		if(nrConta1 > nrConta2)
		{
			synchronized(contas[nrConta1])
			{
				synchronized(contas[nrConta2])
				{
					credito(nrConta1, valor);
					debito(nrConta2, valor);
				}
			}
		}
		else
		{
			synchronized(contas[nrConta2])
			{
				synchronized(contas[nrConta1])
				{
					credito(nrConta1, valor);
					debito(nrConta2, valor);
				}
			}
		}
	}

	public static void main(String[] args) throws InterruptedException
	{
		Banco b = new Banco(10);
		System.out.println("Saldo -> "+b.consulta(1));
		System.out.println("Saldo -> "+b.consulta(2));
	}
}