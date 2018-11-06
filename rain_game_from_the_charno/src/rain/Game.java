package rain;

public class Game implements Runnable{
    public static int WIDTH = 640;
    public static int HEIGHT = WIDTH / 16 * 9;
    public static int SCALE = 3;

    private Thread thread;

    public synchronized void Start(){
        thread = new Thread(this, "Display");
        thread.start();
    }

    public synchronized void Stop(){
        try {
            this.thread.join();
        } catch(InterruptedException e){
            e.printStackTrace();
        }
    }
}
