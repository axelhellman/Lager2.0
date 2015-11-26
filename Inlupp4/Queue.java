public class Queue {
	private Node first;
	private Node last; 
	private int length;


	/** Constructs a queue
	* @param first Node
	* @param last Node
	 */
	public Queue(Node first, Node last) {
		this.first = first;
		this.last = last;
	}

	/**Constructs an empty queue
	*/
	public Queue() {
		this.first = null;
		this.last = null;
		this.length = 0;
	}

	private class Node {
		private Customer element = null;
		private Node next = null;

		/** Constructs a Node
		* @param Customer element, the Customer object stored in the Node
		* @param Node next, the next Node in the Queue
		*/
		public Node(Customer element, Node next) {
			this.element = element;
			this.next = next;
		}

		/** Returns the customer from a Node.
		* @return Customer object at the specified node
		*/
		public Customer getCustomer() {
			return this.element;
		}
	}
	/** Appends a Node containing a customer to the Queue.
	* @param The customer to append.
	*/
	public void enqueue(final Customer element) {
		Node newNode = new Node(element, null);
		this.length++;
		if (first == null) {
			this.last = this.first = newNode;
		}
			else {
				this.last.next = newNode;
				this.last = newNode;
			}
	}

	/** Polls a node from the Queue.
	* @return The Customer at the deleted Node.
	*/
	public Customer dequeue() {
		if (first == null || last == null) {
			return null;
		}
		Customer done = first.getCustomer();
		if (this.length == 1) {
			this.first = null;
			this.last = null;
			this.length = 0;
			return done;
		}
		this.first = first.next;
		this.length--;
		return done;
	}

	/** Returns the length of the Queue.
	* @return the length of the queue.
	*/
	public int length() {
		return this.length;
	}

	/** Returns the Customer at the first Node in the Queue. Null if Queue is empty.
	* @return customer at the first node.
	*/
	public Customer first() {
		if (this.first == null) {
			return null;
		}
		return this.first.getCustomer();
	}

	/** Returns the last customer in the last Node of the Queue. Null if Queue is empty.
	* @return customer at the last node.
	*/
	public Customer last() {
		if (this.last == null) {
			return null;
		}
		return this.last.getCustomer();
	}

	/** Prints the first and last customer in the queue to the console.
	*/
	public void print() {
		System.out.println("First: " + this.first().groceries + " " + this.first().bornTime);
		System.out.println("Last: " + this.last().groceries + " " + this.last().bornTime + " " + this.length());
	}
}