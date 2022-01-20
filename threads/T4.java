
public class T4 extends Thread {

	public static void main(String [] args) {
		SharedCell sc = new SharedCell();
        	Producer p = new Producer(sc);
        	Consumer c = new Consumer(sc);

        	Thread t1 = new Thread(p);
        	Thread t2 = new Thread(c);
        	t1.start();
        	t2.start();
	}
}

class SharedCell{
	private int shared = -1;
    	public synchronized void set(int i) { 
      		System.out.println("Producer producing: " + i);
      		shared = i;
    	}

    	public synchronized int get() {
      		System.out.println("Consumer consuming: " +shared);
      		return shared;
    	}
}

class Producer implements Runnable{
	private SharedCell shared;

    	public Producer(SharedCell sc) { shared = sc; }

    	public void run() {
        	int sum=0;
        	for(int count=0; count < 10; count++){
            		try {
 				Thread.sleep((int)(Math.random()*3000));
			}
            		catch(InterruptedException e) {
				System.err.println(e.toString());
            		}
            		shared.set(count);
            		sum += count;
        	}
        	System.out.println("Producer, produced: " +sum);
    	}
}

class Consumer implements Runnable {
    private SharedCell shared;

    public Consumer (SharedCell sc) { shared = sc; }

    public void run() {
	int val, sum=0;
        do {
		try {
 			Thread.sleep((int)(Math.random()*3000));
	    	}
            	catch(InterruptedException e) {
			System.err.println(e.toString());
            	}
            	val = shared.get();
            	sum += val;
        } while(val != 9);
        System.err.println("Consumer, consumed: "+ sum);
    }
}

