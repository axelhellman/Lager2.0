
/** 
 * Register, represents a register in the store 
 */

public class Register {
	public boolean open;
	public Queue queue;
	/**
	 * Cunstructor, creates a new Register. Sets status to open and creates a new queue 
	 * @param status Tells if the register is open
	 * @param queue Contructs a new register with a queue
	 */
	public Register(boolean status, Queue queue) {
		this.open = status;
		this.queue = queue;
	}
	/**
	 * Opens a register with a new queue
	 */
	public Register() {
		this.open = false;
		this.queue = new Queue();
	}
	/** Opens the register.
	*/
	public void open() {
		this.open = true;
	}
	/**	Closes a register
	*/
	public void close() {
		this.open = false;
	}
	/**
	 *  Checks if the register is open or not
	 * @return true if open, false if closed.
	 */
	public boolean isOpen() {
		if(open) {
			return true;
		}
		else {
			return false;
		}
	}
	
	
	/** Time goes one step. 
	 * The first customer gets a ware scanned. 
	 * Nothing happens if the register is closed or have no customers.
	*/
	public void step() {
		if (this.queue.first() != null) {
			this.queue.first().serve();
		}
	}
	
	/** Checkes if a queue has Costumers
	 * 
	 * @return {@code true} if it has Costumers or false if not.
	 */
	public boolean hasCustomers() {
		if (this.queue.length() > 0) {
			return true;
		}
		else {
			return false;
		}
	}
	/**
	 * Checkes if the current Costumer is done or not (i.e. all groceries are scanned)
	 * @return The first Costumer when done.
	 */
	public boolean currentCustomerIsDone() {
		if (this.queue.length() < 1) {
			return false;
		}
		if (this.queue.first() == null) {
			return false;
		}
		boolean ret = this.queue.first().isDone();
		return ret; 
	}
	/**
	 * Adds a costumer to a register queue
	 * @param c is a costumer c
	 */
	public void addToQueue(Customer c) {
		queue.enqueue(c);
	}
	/**
	 * Removes the first Costumer from the queue
	 * @return The first Costumer in the queue
	 */
	public Customer removeCurrentCustomer() {
		return queue.dequeue();
	}
	/**
	 * Gets the length of the queue
	 * @return the length of the queue
	 */
	public int getQueueLength() {
		return queue.length();
	}
	/**
	 * Gets a queue
	 * @return returning the queue
	 */
	public Queue getQueue() {
		return this.queue;
	}
	/**
	 * Converts a register to a string
	 * @return Returns the register as the string 
	 */
	public String toString() {
		String str = "";
		if (isOpen()) {
			str = str + "  ";
		}
		else {
			str = str + "x ";
		}
		if (queue.first() != null) {
			str = str + "[" + queue.first().groceries + "]";
		}
		else {
			str = str + "[ ]";
		}
		for (int i = 1; i < queue.length(); i++) {
			str = str + "@";
		}
		str = str + " - " + queue.first();
		return str;
	}
}