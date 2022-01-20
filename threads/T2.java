import java.util.*;

public class T2 extends Thread {
	int pauseTime;
    	String name;

    	public T2(int x, String n){
        	pauseTime = x;
        	name = n;
    	}

    	public void run(){
        	while (true) {
	 		try {
	   			System.out.println(name+": " +new Date(System.currentTimeMillis()));
	   			Thread.sleep(pauseTime);
	 		}
			catch(Exception e) {
	   			System.out.println(e);
	 		}
		}
    	}

	public static void main(String [] args) {
		T2 tp1 = new T2(1000, "Fast");
        	T2 tp2 = new T2(3000, "Slow");
        	tp1.start();
        	tp2.start();
       		System.out.println("DONE");
	}
}
