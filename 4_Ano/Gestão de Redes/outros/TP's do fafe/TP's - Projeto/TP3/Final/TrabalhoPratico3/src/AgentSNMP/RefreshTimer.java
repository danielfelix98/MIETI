package AgentSNMP;

import java.io.IOException;
import java.util.Timer;
import java.util.TimerTask;

public class RefreshTimer {
    private Timer timer;

    public void startTimer(int delay, long interval) throws IOException {
        this.timer = new Timer();
        SNMPAgent agent = new SNMPAgent("0.0.0.0/6666");
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                agent.refresh();
            }
        }, delay, interval);
    }

    public void cancelTimer() {
        this.timer.cancel();
    }
}
