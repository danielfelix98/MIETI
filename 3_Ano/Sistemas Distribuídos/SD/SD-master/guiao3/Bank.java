interface Bank
{
	int createAccount(float initialBalance);
	float closeAccount(int id) throws InvalidAccount;
	void transfer(int from, int to, float amount) throws InvalidAccount, NotEnoughFunds;
	float totalBalance(int accounts[]);
}