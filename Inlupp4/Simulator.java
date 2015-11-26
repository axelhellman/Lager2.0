public class Simulator{

    public static void main(String[] args) throws InterruptedException{
        int steps = 100;
        Store c = new Store(Integer.parseInt(args[0]));
        int time = Integer.parseInt(args[1]);
        int intensity = Integer.parseInt(args[2]);
        int maxGroceries = Integer.parseInt(args[3]);
        int thresholdForNewRegister = Integer.parseInt(args[4]);
        Simulation s = new Simulation(c, time, intensity, maxGroceries, thresholdForNewRegister);
        System.out.print("\033[2J\033[;H");
        for(int i = 0; i < steps; i++){
            String os = System.getProperty("os.name");
            s.step();
            System.out.println(s);
            Thread.sleep(500);
        }
        System.out.println("");
        System.out.println("Simulation finished!");
    }
}