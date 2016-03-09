Name: Lauren Yeung
UID: 104456482

Name: Albert Wang
UID: 504457700 


QUESTIONS 1.1

1. It takes this many threads and iterations

2. A signifigantly smaller number of iterations seldomly fails


QUESTIONS 1.2

1. The average cost per operation drops with increasing iterations

2. The "correct" cost 

3. --yield runs much slower

4. Using --yield, we can _____ get valid timings


QUESTIONS 1.3

1. All options perform similarly for low numbers of threads because not as much parallelization can happen. Therefore, all operations take around the same amount of time.

2. The three protected operations slow down as the number of threads increases

3. Spin locks are expensive for large number of threads


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



