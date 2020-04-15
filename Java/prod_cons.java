public class prod_cons
{
  public static void main(String [] args) throws InterruptedException
  {
     Buffer buf = new Buffer(10);
     Producer p1 = new Producer(buf);
     Producer p2 = new Producer(buf);
     Producer p3 = new Producer(buf);
     Consumer c1 = new Consumer(buf);
     Consumer c2 = new Consumer(buf);
     Consumer c3 = new Consumer(buf);

     p1.start();
     p2.start();
     p3.start();
     c1.start();
     c2.start();
     c3.start();

     p1.join();
     p2.join();
     p3.join();
     c1.join();
     c2.join();
     c3.join();
  }
}

interface IBuffer{
   void Put(int v);
   int Get();
}

class Buffer implements IBuffer {
   private int [] buffer;
   private int count = 0, in = 0, out = 0;

   Buffer(int size)
   {
      buffer = new int[size];
   }
 
   public synchronized void Put(int c) {
    while(count == buffer.length) 
                 {
                      try { wait(); }
                      catch (InterruptedException e) { } 
                      finally { } 
                 } 
                 System.out.println("Producing -->" + c );
                 buffer[in] = c; 
                 in = (in + 1) % buffer.length; 
                 count++; 
                 notify(); 
   }
    
   public synchronized int Get() {
    while (count == 0) 
                 {
                      try { wait(); }
                      catch (InterruptedException e) { } 
                      finally { } 
                 } 
                 int c = buffer[out]; 
                 out = (out + 1) % buffer.length;
                 count--;
                 System.out.println("Consuming -->" + c ); 
                 notify(); 
                 return c;
   }
}
     

class Producer extends Thread {
   private Buffer buffer;
     
   Producer(Buffer b) { buffer = b; }
   public void run() {
     for(int i = 100; i < 200; i++) {
        buffer.Put((int)(i)); }
   }
}    

class Consumer extends Thread {
   private Buffer buffer;
   
   Consumer(Buffer b) { buffer = b; }
   public void run() {
     for(int i = 0; i < 100; i++) {
        buffer.Get(); }
   }
} 