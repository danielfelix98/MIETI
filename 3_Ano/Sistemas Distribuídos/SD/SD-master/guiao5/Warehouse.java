import java.util.HashMap;

class Warehouse{
	private HashMap<String,Item> stock;

	public Warehouse(){
		this.stock=new HashMap<String,Item>();
	}

	public void supply(String item, int quantity){
		if(!this.stock.containsKey(item)){
			Item i=new Item();
			this.stock.put(item,i);
		}
		this.stock.get(item).supply(quantity);
	}

	public void consume(String[] items){
		for(String i:items)
			if(this.stock.containsKey(item))
				this.stock.get(item).consume();
	}
}