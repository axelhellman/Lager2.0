import java.util.ArrayList;
import java.util.Random;

public class Simulation {
	public Store store;
	public int time;
	public int intensity;
	public int maxGroceries;
	public int thresholdForNewRegister;
	public int customersServed;
	public int maxWaitTime;
	public int averageWaitTime;
	public int totalTime;

	public Simulation(Store store, int time, int intensity, int maxGroceries, int thresholdForNewRegister) {
		this.store = store;
		this.time = time;
		this.intensity = intensity;
		this.maxGroceries = maxGroceries;
		this.thresholdForNewRegister = thresholdForNewRegister;
		this.customersServed = 0;
		this.maxWaitTime = 0;
		this.averageWaitTime = 0;
		this.totalTime = 0;
	}

	public void step() {
		store.step();
		this.time++;
		Random random = new Random();
		int u = random.nextInt(100);
		if (u < this.intensity) {
			Customer c = new Customer(this.time, random.nextInt(maxGroceries-1)+1);
			store.newCustomer(c);
		}
		if ((store.getAverageQueueLength()) > thresholdForNewRegister) {
			store.openNewRegister();
		}
		Queue q = this.store.getDoneCustomers();
		while(q.first() != null) {
		Customer v = q.dequeue();
		served();
		if ((this.time - v.bornTime) > (this.maxWaitTime)) {
			maxWait(this.time-v.bornTime);
		}
		this.totalTime = this.totalTime + (this.time - v.bornTime);
		this.averageWaitTime = (this.totalTime / customersServed);
	}

}

	public void served() {
		this.customersServed++;
	}

	public void maxWait(int toTest) {
		this.maxWaitTime = toTest;
	}

	public String toString() {
		String str = "";
		str = str + store.toString() + "\n";
		str = str + "Number of customers served: " + this.customersServed + "\n";
		str = str + "Maximum wait time: " + this.maxWaitTime + "\n";
		str = str + "Average wait time: " + this.averageWaitTime;
		return str;
	}

}

