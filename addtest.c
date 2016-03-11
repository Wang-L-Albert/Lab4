#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <pthread.h>


#define noarg 0
#define hasarg 1
#define optionalarg 2
#define noflag 0


#define THREADS 'a'
#define ITERATIONS 'b'
#define YIELD 'c'
#define SYNC 'd'

static long long counter;
static int opt_yield;
static int mutexFlag;
static int spinFlag;
static int atomicFlag;
static pthread_mutex_t mutex;
static int spinLock;
static int atomicLock;

void add(long long *pointer, long long value) {
    long long sum = *pointer + value;
    if(opt_yield){
        pthread_yield();
    }
    *pointer = sum;
}

void mutexAdd(long long *pointer, long long value){
    pthread_mutex_lock(&mutex);
    long long sum = *pointer + value;
    *pointer = sum;
    pthread_mutex_unlock(&mutex);
}

void spinAdd(long long *pointer, long long value){
    //spins until spinLock was 0 when it was run, meanint it was freed
    while(__sync_lock_test_and_set(&spinLock, 1)){
        continue;
    }
    long long sum = *pointer + value;
    *pointer = sum;
    __sync_lock_release(&spinLock);
}

void atomicAdd(long long *pointer, long long value){
    while (__sync_val_compare_and_swap(&atomicLock,0,1)){
        continue;
    }
    long long sum = *pointer + value;
    *pointer = sum;
    __sync_val_compare_and_swap(&atomicLock, 1, 0);
}

void chooseAdd(int addVal){
    if(mutexFlag){
        //printf("Using mutex. \n");
        mutexAdd(&counter, addVal);
    } else if (spinFlag){
        //printf("Using spin. \n");
        spinAdd(&counter, addVal);
    } else if (atomicFlag){
        //printf("Using atomic. \n");
        atomicAdd(&counter, addVal);
    } else{
        //printf("Using regular. \n");
        add(&counter, addVal);
    }
}

void *executeAdd(void* iterations){
  int numIter = *((int*) iterations);
  for (int a = 0; a < numIter; a++){
      chooseAdd(1);
  }
  for (int b = 0; b < numIter; b++){
      chooseAdd(-1);
    //printf("Counter Subtract: %lld \n", counter);
  }
  pthread_exit(NULL);
}

int main(int argc, char* argv[]){
    int numErrors;
    numErrors = 0;
    struct timespec startTime;
    struct timespec endTime;

    int numThreads;
    int numIterations;
    struct option optionList[]= {
        {"threads", optionalarg, noflag, THREADS},
        {"iterations", optionalarg, noflag, ITERATIONS},
	{"yield", optionalarg, noflag, YIELD},
    {"sync", optionalarg, noflag, SYNC},
        {0,0,0,0}
    };
    //initialize default values
    numThreads = 1;
    numIterations = 1;
    counter = 0;
    opt_yield = 0;
    mutexFlag = 0;
    spinFlag = 0;
    atomicFlag = 0;
    spinLock = 0;
    pthread_mutex_init(&mutex, NULL);
    //get starting time values
    clock_gettime(CLOCK_MONOTONIC, &startTime);
    //see if there's any passed in values for threads and iter
    if(argc != 1){
        int optionValue;
        int optionIndex;
        for (int a = 1; a < argc; a++){
            //option_ind is the option's index in argv[].
    		//global var optarg now points to option_ind+1, and optind to the index of the next index after optarg (first non-option
    		//in argv[] if no more options).
            optionValue = getopt_long(argc,argv, "", optionList, &optionIndex);
	    if(optarg != NULL){
            switch(optionValue) {
            case '?'://occurs when we find an option without the appropriate argument
                fprintf(stderr, "%s is missing an argument\n", optionList[optionIndex].name);
                numErrors++;
                break;
            case THREADS:
                numThreads = atoi(optarg);
                break;
		        printf("NumThreads: %i \n",numThreads);
            case ITERATIONS:
                numIterations = atoi(optarg);
		        printf("NumIterations: %i \n",numIterations);
		        break;
            case YIELD:
		        opt_yield = 1;
		        break;
            case SYNC:
                printf("Inside sync switch. \n");
                if (*optarg == 'm'){
                        printf("Set mutex. \n");
                        mutexFlag = 1;
                } else if (*optarg == 's'){
                        printf("Set spin. \n");
                        spinFlag = 1;
                } else if (*optarg == 'c'){
                        printf("Set atomic. \n");
                        atomicFlag = 1;
                } else {
                    printf("Could not set sync. \n");
                }
                break;
	      }
	    }
	}
    }
    pthread_t tids[numThreads];
    int tid;
    //we now have proper number of threads and interations, time to fork
    for (int b = 0; b < numThreads; b++){
      tid = pthread_create(&tids[b], NULL, executeAdd, (void*)&numIterations);
      if (tid == -1){
	numErrors++;
	printf("Failed to create a thread. \n");
	exit(numErrors);
      }
    }
    for (int c = 0; c < numThreads; c++){
      pthread_join(tids[c], NULL);
    }
    //get time
    clock_gettime(CLOCK_MONOTONIC,&endTime);
    //if count is not 0, report error
    if (counter != 0 ){
        fprintf(stderr, "Error: Final Count = %lld \n", counter);
    }
    printf("Final Count: %lld \n",counter);
    int numOperations;
    numOperations = 2 * numThreads * numIterations;
    printf("Total number of operations performed: %d \n", numOperations);
    //calculate run time
    //printf("Starting Time: %f s \n", (float)startTime.tv_sec);
    //printf("Starting Time: %f ns \n", (float)startTime.tv_nsec);

    //printf("End Time: %f s \n", (float)endTime.tv_sec);
    //printf("End Time: %f ns \n", (float)endTime.tv_nsec);
    long long startRunTime = (long long) (startTime.tv_sec*1e9) + (long long)(startTime.tv_nsec);
	long long endRunTime = (long long) (endTime.tv_sec*1e9) + (long long)(endTime.tv_nsec);
	long long totalRunTime = endRunTime - startRunTime;
    printf("Elapsed Time: %lld ns \n", totalRunTime);
    printf("Average Operation Time: %lld ns \n", totalRunTime/numOperations);
    exit(numErrors);
}
