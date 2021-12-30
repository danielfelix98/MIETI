import java.util.ArrayList;
import java.util.Random;
import java.util.HashMap;
import java.io.BufferedWriter;
import java.io.IOException;

public class Game{
    private int id;
    private int rank;
    private int max;
    private int cur1;
    private int cur2;
    private int cur3;
    private double count1;
    private double count2;
    private ArrayList<Team> teams;
    private boolean winner;
    private int abort;
    private int ready;

    public Game(int id,int rank){
        this.id=id;
        this.max=4;
        this.cur1=0;
        this.cur2=0;
        this.cur3=0;
        this.count1=0.0;
        this.count2=0.0;
        this.rank=rank;
        this.teams=new ArrayList<Team>(2);
        this.teams.add(new Team());
        this.teams.add(new Team());
        this.abort=0;
        this.ready=0;
    }
    public int getId(){
        return this.id;
    }
    public int getRankGame(){
        return this.rank;
    }
    public synchronized Hero getHero(String eq,int h){
        if(eq.equals("BLACK"))
            return this.teams.get(0).getTheHero(h);
        else
            return this.teams.get(1).getTheHero(h);
    }
    public int getMax(){
        return this.max;
    }
    public int getCur1(){
        return this.cur1;
    }
    public synchronized int getAbort(){
        this.cur3++;
        while(this.cur3<this.max){
            try{
                this.wait();
            }catch(InterruptedException e){
                e.printStackTrace();
            }
        }
        this.notifyAll();
        return this.abort;
    }
    public void setAbort(int n){
        this.abort+=n;
    }
    public String getHeroName(int h){
        return this.teams.get(0).getTheHeroName(h);
    }
    public synchronized void makeTeams(Player pl){
        this.cur1++;
        if(this.count1<this.count2){
            this.count1++;
            this.teams.get(0).getTeam().add(pl);
            this.teams.get(0).setMedian((double)pl.getRank(),this.count1);
        }
        else if(this.count1>this.count2){
            this.count2++;
            this.teams.get(1).getTeam().add(pl);
            this.teams.get(1).setMedian((double)pl.getRank(),this.count2);
        }
        else if(this.teams.get(0).getMedian()<this.teams.get(1).getMedian() && pl.getRank()>this.teams.get(0).getMedian()){
            this.count1++;
            this.teams.get(0).getTeam().add(pl);
            this.teams.get(0).setMedian((double)pl.getRank(),this.count1);
        }
        else{
            this.count2++;
            this.teams.get(1).getTeam().add(pl);
            this.teams.get(1).setMedian((double)pl.getRank(),this.count2);
        }
        while(this.cur1<this.max){
            try{
                this.wait();
            }catch(InterruptedException e){
                e.printStackTrace();
            }
        }
        this.notifyAll();
    }
    public String teamsTable(){
        StringBuilder sb=new StringBuilder();
        sb.append("\n-- Team BLACK\n");
        sb.append(this.teams.get(0).teamContent());
        sb.append("-- Team WHITE\n");
        sb.append(this.teams.get(1).teamContent());
        return sb.toString();
    }
    public String getTeam(Player pl)throws PlayerDoesntBelong{
        if(this.teams.get(0).getTeam().contains(pl))
            return "BLACK";
        else if(this.teams.get(1).getTeam().contains(pl))
            return "WHITE";
        else
            throw new PlayerDoesntBelong(pl.getUsername());
    }
    public synchronized void result(){
        this.cur3++;
        while(this.cur3<this.max){
            try{
                this.wait();
            } catch(InterruptedException e){
                e.printStackTrace();
            }
        }
        Random genarator=new Random();
        int result=genarator.nextInt(1);
        if(result==1)
            this.winner=true;
        else
            this.winner=false;
        this.notifyAll();
    }
    public boolean getResult(String equipa){
        if(equipa.equals("BLACK")&&this.winner)
            return true;
        if(equipa.equals("BLACK")&&!this.winner)
            return false;
        if(equipa.equals("WHITE")&&!this.winner)
            return true;
        else
            return false;
    }
    public synchronized int setReady(int i){
        this.ready+=i;
        return this.ready;
    }
    public void getReady(){
        for(Team t : this.teams){
            for(Player j : t.getTeam()){
                try{
                    BufferedWriter bw=j.getBufOut();
                    bw.write("ready");
                    bw.newLine();
                    bw.flush();
                }catch(IOException e){
                    e.printStackTrace();
                }
            }
        }
    }
    public void teammatePicks(String team,String user,int hero){
        if(team.equals("BLACK")){
            for(Player j : this.teams.get(0).getTeam()){
                try{
                    BufferedWriter bw=j.getBufOut();
                    bw.write("-> "+user+" choosed "+getHeroName(hero-1)+"!");
                    bw.newLine();
                    bw.flush();
                }catch(IOException e){
                    e.printStackTrace();
                }
            }
        }
        else{
            for(Player j : this.teams.get(1).getTeam()){
                try{
                    BufferedWriter bw=j.getBufOut();
                    bw.write("-> "+user+" choosed "+getHeroName(hero-1)+"!");
                    bw.newLine();
                    bw.flush();
                }catch(IOException e){
                    e.printStackTrace();
                }
            }
        }
    }
}

class PlayerDoesntBelong extends Exception{
    public PlayerDoesntBelong(){}
    public PlayerDoesntBelong(String user){
        super("Player "+user+" doesn't belong to a team!");
    }
}
