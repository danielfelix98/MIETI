import java.util.ArrayList;

public class Team{
  private ArrayList<Hero> heroes;
  private ArrayList<Player> team;
  private double median;

  public Team(){
    this.heroes=new ArrayList<Hero>(30);
    this.heroes.add(new Hero("Casillas"));
    this.heroes.add(new Hero("José Sá"));
    this.heroes.add(new Hero("Fabiano"));
    this.heroes.add(new Hero("Alves"));
    this.heroes.add(new Hero("Costa"));
    this.heroes.add(new Hero("Felipe"));
    this.heroes.add(new Hero("Marcano"));
    this.heroes.add(new Hero("Reyes"));
    this.heroes.add(new Hero("Telles"));
    this.heroes.add(new Hero("Layun"));
    this.heroes.add(new Hero("Ricardo"));
    this.heroes.add(new Hero("Maxi"));
    this.heroes.add(new Hero("Danilo"));
    this.heroes.add(new Hero("Herrera"));
    this.heroes.add(new Hero("Andre"));
    this.heroes.add(new Hero("Sergio"));
    this.heroes.add(new Hero("Oliver"));
    this.heroes.add(new Hero("Otavio"));
    this.heroes.add(new Hero("Brahimi"));
    this.heroes.add(new Hero("Corona"));
    this.heroes.add(new Hero("Hernani"));
    this.heroes.add(new Hero("Marega"));
    this.heroes.add(new Hero("Aboubakar"));
    this.heroes.add(new Hero("Soares"));
    this.heroes.add(new Hero("Conceicao"));
    this.heroes.add(new Hero("Pintinho"));
    this.heroes.add(new Hero("Emplastro"));
    this.heroes.add(new Hero("Quaresma"));
    this.heroes.add(new Hero("Baia"));
    this.heroes.add(new Hero("Ronaldo"));
    this.team=new ArrayList<Player>(5);
    this.median=0.0;
   }
   public Hero getTheHero(int h){
   	  return this.heroes.get(h-1);
   }
   public ArrayList<Player> getTeam(){
   		return this.team;
   }
   public String getTheHeroName(int h){
      return this.heroes.get(h).getName();
   }
   public double getMedian(){
      return this.median;
   }
   public void setMedian(double rank,double count){
      this.median=((this.median*(count-1))+rank)/count;
   }
   public String teamContent(){
      StringBuilder sb=new StringBuilder();
      for(Player p:this.team)
        sb.append("* "+p.getUsername()+" -> "+p.getHeroChoosed()+"\n");
      return sb.toString();
   }
   public boolean belongs(String user){
      for(Player p:team){
        if(p.getUsername().equals(user)) return true;
      }
      return false;
   }
}