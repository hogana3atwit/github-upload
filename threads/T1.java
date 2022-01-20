//
// class Thread and interface Runnable
//
public class T1 {

	public static void main(String [] args){
		Thread ta = new A();
		Thread tb = new Thread(new B());

		ta.start();
		tb.start();

		/////////////////////////////////////////////////////

		SHARED shared = new SHARED();

		Thread tc1 = new Thread(new C(shared, true));
		Thread tc2 = new Thread(new C(shared, false));

		tc1.start();
		tc2.start();

		try {
			tc1.join();
			tc2.join();
		}
		catch (InterruptedException e ) {}

		System.out.println("FINAL RESULT: " + shared.VAR);

		System.out.println("DONE");
	}
}

class SHARED {
	public int VAR = 0;
}

class A extends Thread {
	public void run() {
		System.out.println("CLASS A");
	}
}

class B implements Runnable {
	public void run() {
		System.out.println("CLASS B");
	}
}

class C implements Runnable {
	private SHARED shared = null;
	private boolean inc = true;

    	public synchronized void increment() {
        	shared.VAR++;
    	}

    	public synchronized void decrement() {
        	shared.VAR--;
    	}

    	public int value() {
        	return shared.VAR;
    	}

	public C(SHARED shared, boolean inc) {
		this.shared = shared;
		this.inc = inc;
	}

	private int LIMIT = 10;		// CHANGE THIS TO 10000 and you'll see this doesn't work WHY?????????

	public void run() {
		if( inc ) {
			for(int i = 0; i < LIMIT; i++)
				increment();
		}
		else {
			for(int i = 0; i < LIMIT; i++)
				decrement();
		}
	}
}
