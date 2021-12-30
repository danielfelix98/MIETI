import java.util.*;
import java.util.concurrent.locks.*;

class NotEnoughFunds extends Exception{
	public NotEnoughFunds(){
		super(); 
	}
}

class InvalidAccount extends Exception{
	public InvalidAccount(){
		super(); 
	}
}

class Conta 
{
	private float saldo;
	private ReentrantLock lock;

	public Conta(float s){
		this.saldo=s;
	}

	public ReentrantLock getLock(){
		return lock;
	}

	public void creditar (float montante){
		this.saldo+=montante;
	}

	public void debitar (float montante){
		this.saldo-=montante;
	}

	public float consultar (){
		return saldo;
	}
}

class Banco implements Bank{
	private int numContas;
	private Map<Integer,Conta> contas;
	private ReentrantLock lock;

	public Banco(){
		numContas=0;
		contas=new TreeMap<>();
	}

	public int createAccount(float initialBalance){
		lock.lock();
		try{
			Conta nova=new Conta(initialBalance);
			numContas++;
			contas.put(new Integer(numContas),nova);
		}
		finally{
			lock.unlock();
		}
		return numContas;
	}

	public float closeAccount(int id) throws InvalidAccount{
		float saldo=contas.get(id).consultar();
		lock.lock();
		try{
			Conta apagar=contas.get(id);
			if(apagar==null)
				throw new InvalidAccount();
			contas.remove(id);
		}
		finally{
			lock.unlock();
		}
		return saldo;
	}

	public void transfer(int from, int to, float amount) throws InvalidAccount, NotEnoughFunds{
		lock.lock();
		try{
			Conta origem=contas.get(from);
			Conta destino=contas.get(to);
			if (origem==null||destino==null)
				throw new InvalidAccount();
			if (origem.consultar()<amount)
				throw new NotEnoughFunds();
			origem.getLock().lock();
			origem.debitar(amount);
			origem.getLock().unlock();
			destino.getLock().lock();
			destino.creditar(amount);
			destino.getLock().unlock();
		}
		finally{
			lock.unlock();
		}
	}

	public float totalBalance(int accounts[]){
		float total=0;
		lock.lock();
		try{
			for(int i=0;i<accounts.length;i++)
				total+=contas.get(accounts[i]).consultar();
		}
		finally{
			lock.unlock();
		}
		return total;
	}

	public static void main(String[] args){
	}
}