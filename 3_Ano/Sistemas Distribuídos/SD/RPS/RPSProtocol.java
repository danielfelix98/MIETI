package RPS;

public final class RPSProtocol
{
	public static final int PORT=50516;

	public static final String MSG_SEP = ":";
	public static final int START = 0; //server Response - game start
	public static final int BET = 1; //client Request - bet Rock,Scissor or Paper
	public static final int RESULT= 2; //server Response - result of game
	public static final int END = 3; //server Response - end of game

	public static final int TIE = 0;
	public static final int WIN=1;
	public static final int LOSE=2;

	public static final int SCISSOR=1;
	public static final int PAPER=2;
	public static final int ROCK=3;
}
