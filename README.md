# STARVE-FREE-READERS-AND-WRITERS-PROBLEM
# Problem Description
The readers and writers problem is a  synchronization problem where reading an dwriting done at the same location. Readers tries to read and riter tries to write in the same memory location or common resource.In First Readers-Writer problem Writer starve and Second Readers and writer problem Reader strave .Write Pseudo code for starve free  solutions using semaphores.
# Proposed solution (INTUITION)
Here I allocate the shared resources to Reader or Writer based on First Come First Serve basis.If the resources are already been allocated to some one then we block the process .To maintain the order of the process in the waiting list we maintain a `Queue(FIFO-QUEUE)` .We have the constraint of mutual exclusion is that writer and reader cannot share the common resources simultaneously so as th handle this I used “cs_mutex” semaphore.
### **During reading:**
When a resource is in the reader access we can allow other immediate reader to read the file simultaneously .I maintained the count `(“read_count”)` .I used a semaphore `“readcount_mutex”` to allow a single reader to update the value of read_count for not to go in race condition(or to maintain mutual exclusion) . 
I used another semaphore `“execute”`  which a process in queue to execute in an order .The fist reader while entering takes the access of the shared resources for all . 
### **During Writing:**
Here we are not allowed two or more writer to write in the same memory location because they are updating something In the shared resources, we handle this by using semaphore at write place.

# Semaphores
1. semphore **"execute"** is for the process to execute in the order of arrival and i used this semaphore to signal other process to start after its execution.
2. semaphore  **""cs_mutex""** is used to maintain mutual exlusion between reader-writers and writer-writer.
3. semphore **"readcount_mutex"** is used for updation od read_count to not to go for a race condition.
```

//Intialise the read_count
long long int read_count=0;
// Initialising semaphores
semaphore execute=1;//semaphore which holds a process untill it get it's execution turn from the FIFO Queue
semaphore cs_mutex=1;//semaphore which hepls us to get mutual exclusion between writer and readers(cs can operate ony one function either read ot write at a time)
semaphore readcount_mutex=1;//sempahore to update the read_count value one at a time


struct Semaphore{
    long long sema= 1;                // semophore for entering into critical section
    Queue* fifo = new Queue();     // FIFO queue to obtain first in first serve basis

    void wait(int process_pid){
                            // process_pid denotes a process id
             sema--;
        if(sema < 0){
            fifo->push(process_pid);
            block(process_pid);         // If critical section is busy we add the current invoking process to  fifi queue  
        }// size of FIFO Queue defines the number of waiting process in the queue
    }
        void signal(){
        sema++;
        if(sema<=0){
            int process_pid = fifo->pop();
            wake(process_pid);    // to wakeup the process at the starting of the queue with pid
        }
    }
}
``` 

# Pseudo code for Reader 
```
Readers(){
    .
    ..
    ...
    
    wait(execute);                   // This sempahore waits in this step till it turn get for execution from the FIFO QUEUE(pop(process));
    wait(readcount_mutex);read_count++;//This semaphore lock the access of read_count to update the read value one at a time 
    if(read_count==1) wait(cs_mutex);  // This is to take the shared resources by the first reader from  the consequtive readers 
    signal(readcount_mutex);         // Here we release the  read_count  access to future updation
    signal(execute);               // we signal the next process in queue for their execution turn it may be areader or the writer
    
       ....
       
       //reading performed here
       
       ....
       
       wait(readcount_mutex);       //This semaphore lock the access of read_count to update the read value one at a time 
       read_count--;
       if(read_count==0)  signal(cs_mutex);   // Here  after all the execution of consequtive readers we release the acccess of (CS) or shared resources to tyhe writer in their turn 
       signal(readcount_mutex);     // Here we release the  read_count  access to future updation
     ...
     ..
     .
       } 
  ```     
# Pseudocode for Writer
```
Writer(){
    
    .
    ..
    ...
       
    wait(execute);                   // This sempahore waits in this step till it turn get for execution from the FIFO QUEUE(pop(process));
    wait(cs_mutex);                //Here writer locks the access of shared resources for readers and other writers too. 
     
     .....
     
    // writing by writer is performed
     
     .....
     
     signal(cs_mutex);           //Here we release the shared resources by the writers for the next process
     signal(execute);           //we are giving signal for the next process from the FIFO QUEUE to be exceuted next
    
    ...
    ..
    .
} ```


