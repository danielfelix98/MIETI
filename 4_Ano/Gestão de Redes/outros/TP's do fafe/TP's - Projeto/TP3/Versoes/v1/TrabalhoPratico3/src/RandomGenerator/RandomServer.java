package RandomGenerator;

import java.util.Random;

public class RandomServer {
    public int main() {
        Random randomGenerator = new Random();
        int randomInt = randomGenerator.nextInt(10000000);
        return randomInt;
    }
}
