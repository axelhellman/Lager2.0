/** 
 * This class represent a costumer in the store
 */
public class Customer {
	/** The time this customer entered the store**/
	public int bornTime;
	/**The number of groceries the customer has **/
	public int groceries;
	/**
	 * Creates a new Customer
	 * @param bornTime The time the customer entered the store.
	 * @param groceries Number of groceries the customer has.
	 */
	public Customer(int bornTime, int groceries) {
		this.bornTime = bornTime;
		this.groceries = groceries;
	}
	/**
	 * Serve the customer. Decrease the number of groceries with 1.
	 */
	public void serve() {
		this.groceries--;
	}
	/**
	 * Checks if the a customer is done, which means that all the groceries
	 * are scanned in the register and after that ready to leave the store (if the 
	 * groceries are 0) 
	 */
	public Boolean isDone() {
		if (this.groceries > 0) {
			return false;
		}
		else {
			return true;
		}
	}

// ekvivalens
public boolean equals(Object c) { 
if (c instanceof Customer) {
    Customer customer = (Customer) c;
    return (this.bornTime == customer.bornTime && this.groceries == customer.groceries);
}
else return false;
}
}