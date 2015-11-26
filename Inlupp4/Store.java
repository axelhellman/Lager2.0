import java.util.List;
import java.util.ArrayList;

public class Store {
	private Register registers[];

	/** Creates a store object.
	* @param number of registers in the store.
	*/
	public Store(int registeramount) {
		registers = new Register[registeramount];
		int i = 0;
		for (i = 0; i < registers.length; i++) {
			registers[i] = new Register();
		}
		registers[0].open();
	}
	
	/** Returns the amount of open registers in the store.
	* @param amount of open registers.
	*/
	public int amountOpen() {
		int amount = 0;
		for (int i = 0; i < registers.length; i++) {
			if (registers[i].isOpen()){
				amount++;
			}

		}
		return amount;
	}


	/** Returns the average queue length of the registers in the store.
	* @return average queue length.
	*/
	public int getAverageQueueLength() {
		int i = 0;
		int totalLength = 0;
		for (i = 0; i < registers.length; i++) {
			totalLength += registers[i].getQueueLength();
		}
		return (totalLength / amountOpen());
	}

	/** Appends a customer to the shortest open queue in the store.
	* @param Customer to enqueue.
	*/
	public void enQueueShortestQueue(Customer c) {
		int i = 0;
		Queue currentShortest = null;
		for (i = 0; i < registers.length; i++) {
			if (currentShortest == null) {
				currentShortest = registers[i].getQueue();
			}
			else if ((registers[i].isOpen()) && (registers[i].getQueueLength() < currentShortest.length())) {
				currentShortest = registers[i].getQueue();
		}
			else {

			}
		}
		currentShortest.enqueue(c);
	}

	/** Appends a customer to the shortest open queue in the store.
	* @param Customer to enqueue.
	*/
	public void newCustomer(Customer c) {
		enQueueShortestQueue(c);
	}

	public void step() {
		int i = 0;
		for (i = 0; i < registers.length; i++) {
				registers[i].step();
			}
		


	}

	/** Opens a new register if there are any closed registers in the store.
	*/
	public void openNewRegister() {
		int i = 0;
		for (i = 0; i < registers.length; i++) {
			if (!registers[i].open) {
				registers[i].open();
				return;
		}
	}
	return;
}

	/** Returns a Queue of all the done customers in the current state of the store.
	* @return Queue containing all the done customers.
	*/
	public Queue getDoneCustomers() {
		int i = 0;
		Queue q = new Queue();
		for (i = 0; i < registers.length; i++) {
			if (registers[i].hasCustomers() && (registers[i].currentCustomerIsDone())) {
					Customer done = registers[i].removeCurrentCustomer();
					q.enqueue(done);
			}
		}
	return q;
	}

	/** Prints status for all the registers in the store.
	* @return string describing the status of the registers.
	*/
	public String toString() {
	String str = "";	
	for (int i = 0; i < registers.length; i++) {
		str = str + registers[i].toString() + "\n";
		}
		return str;
	}

}

