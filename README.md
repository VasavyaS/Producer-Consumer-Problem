# Producer-Consumer-Problem

Title: Producer-Consumer with Threads

Description:

The producer-consumer problem is a classical synchronization problem in computer science, which involves a producer that produces items and adds them to a shared buffer or queue, and one or more consumers that consume items from the buffer or queue. To solve this problem, synchronization mechanisms are needed to ensure that the producer and consumers do not access the shared buffer simultaneously, and to coordinate the transfer of items between the producer and consumers.
Some common synchronization mechanisms used to solve the producer-consumer problem include:

-->Mutexes
-->Semaphores
-->Condition Variables

In our program we follow the below steps to solve the above stated problem:

1. We define a circular buffer of fixed size, with a read index and a write index initialized to 0.

2. We define a synchronization primitive, a semaphore, to control access to the buffer.

3. The producer thread generates integers and writes them to successive buffer cells, starting at the write index. It then increments the write index (modulo the buffer size) to point to the next available cell. If the buffer is full (i.e., the write index is equal to the read index), the producer thread blocks until a consumer thread reads from the buffer and frees up space.

4. Each consumer thread reads from the buffer starting at the read index and increments the read index (modulo the buffer size) to point to the next unread cell. If the buffer is empty (i.e., the read index is equal to the write index), the consumer thread blocks until a producer thread writes to the buffer and makes data available.
We make use of sleep() to allow different consumers to empty the buffer.

5. When a thread acquires the synchronization primitive, it can access the buffer. When it's done accessing the buffer, it releases the synchronization primitive.

6. To ensure that the consumers print the integers in the order they were generated, we use a shared counter variable that is incremented by the producer each time it generates a new integer. The consumer threads read the counter value along with the integer from the buffer, and print them out in the order of the counter value. 

Process to run:

To run, download ProcuderConsumer.c file. In the Ubuntu terminal, run the below command from the folder where the file is located to compile the program:

gcc ProcuderConsumer.c 

On compiling you would notice an a.out file is generated. Now run the below command to get the output:

./a.out <num_consumer> <user_limit>
Enter the buffer size: <buffer_size>


