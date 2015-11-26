public class CustomerTest {

    public static void main(String args[]) {
        // Nedan foljer ett forslag pa hur man kan testa sin kundklass:
        Customer c = new Customer(0, 3);
        c.serve();
        c.serve();
        c.serve();
        if(c.isDone()) {
             System.out.println("The customer is done, just as expected!");
         } else {
            System.out.println("The customer is not done, but should be...");
         }
         Customer b = new Customer(30, 6);
         Customer v = new Customer(20, 7);
         Customer h = new Customer(15, 9);
         Queue q = new Queue();
         q.enqueue(b);
         q.enqueue(v);
         q.enqueue(h);
         q.dequeue();
         q.print();
         if ((q.first().bornTime == 20) && (q.first().groceries == 7)) {
            System.out.println("The first customer is correct.");
         }
         if ((q.last().bornTime == 15) && (q.last().groceries == 9)) {
            System.out.println("The last customer is correct.");
         }
    }

}