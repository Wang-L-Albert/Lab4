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

long long counter;
int opt_yield;

void add(long long *pointer, long long value) {
       long long sum = *pointer + value;
       if(opt_yield){
	 pthread_yield();
       }
       *pointer = sum;
}

void *executeAdd(void* iterations){
  int numIter = *((int*) iterations);
  for (int a = 0; a < numIter; a++){
    add(&counter, 1);
    //printf("Counter Add: %lld \n", counter);
  }
  for (int b = 0; b < numIter; b++){
    add(&counter, -1);		
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
        {0,0,0,0}
    };
    //initialize default values
    numThreads = 1;
    numIterations = 1;
    counter = 0;
    opt_yield = 0;
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
		printf("NumThreads: %i \n",numThreads);
		break;
	      case ITERATIONS:
	        numIterations = atoi(optarg);
		printf("NumIterations: %i \n",numIterations);
		break;
	      case YIELD:
		opt_yield = 1;
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
    printf("Total number of operations performed: %d ns \n", numOperations);
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
