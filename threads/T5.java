
//
// Try replacing the wait with sleep.
// What is the difference between the wait() and the sleep() ?
//
//

public class T5 extends Thread {
	
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
	private boolean consumerHasConsumed = true;

    	public synchronized void set(int i) { 
		while( consumerHasConsumed == false ) {
			try {
				wait();
			}
			catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
      		System.out.println("Producer producing: " + i);
      		shared = i;
		consumerHasConsumed = false;
		notify();
    	}

    	public synchronized int get() {
		while( consumerHasConsumed  ) {
			try {
				wait();
			}
			catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
      		System.out.println("Consumer consuming: " +shared);
		consumerHasConsumed = true;
		notify();
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

