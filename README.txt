Name: Lauren Yeung
UID: 104456482

Name: Albert Wang
UID: 504457700 


QUESTIONS 1.1

Fails at 10 threads and 1000 iterations.
1. It takes this many threads and iterations to fail because a higher number of iterations and threads increase the chance of race conditions.
With a greater number of threads, more threads are modifying the global counter, especially for a greater number of iterations.

2. A signifigantly smaller number of iterations seldomly fails because it lowers the chance of collision. Smaller number of iterations also means that context switching is less likely to affect the global variable, as the changes may negate each other.


QUESTIONS 1.2

1. The average cost per operation drops with increasing iterations because the ratio of work done compared to thread operation. Economies of scale show that the time for creating a thread becomes a smaller ratio of the overall cost for operations for increasing iterations. 

2. The "correct" cost is the overall cost for operations subtracting the time taken for thread creation. 

3. --yield runs much slower because of context switching; threads have to wait as the CPU switches from one thread to another.

4. Using --yield, we can not get valid timings because we cannot tell how much time was spent switching between threads. We cannot isolate or time when that happens. 

busy waiting
waiting in loop 
uses processing power and thread takes CPU time checking lock availability

QUESTIONS 1.3

1. All options perform similarly for low numbers of threads because there are only so many threads to grab locks or make comparisons. With fewer threads, there is less waiting for each thread to do so.

2. The three protected operations slow down as the number of threads increases because more threads wait to grab the lock, or go through more comparisons. 

3. Spin locks are expensive for large number of threads as there is more contention for the spinlock; the threads do busy-waiting. Whenever a thread has its turn, it waits in a loop, taking CPU time to continuously check the lock.


QUESTION 2.1

Variation in time per operation vs number of iterations:

Correcting this effect:


QUESTION 2.2

Variation in time per protected operation vs number of threads


QUESTION 2.3

The change in performance of the synchronized methods is a function of the number of threads per list 

Threads per list is a more interesting number than threads


QUESTION 3.1

The mutex must be held when pthread_cond_wait is called

The mutex must be released when the waiting thread is blocked 

The mutex must be reacquired when the calling thread resumes

This must be done inside of pthread_cond_wait 
The caller cannot simply release the mutex before calling pthread_con_wait



