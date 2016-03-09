#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

#define noarg 0
#define hasarg 1
#define noflag 0

#define THREADS 'a'
#define ITERATIONS 'b'

static long long counter;
void add(long long *pointer, long long value) {
       long long sum = *pointer + value;
       *pointer = sum;
}

int main(int argc, char* argv[]){
    int numErrors;
    numErrors = 0;
    struct timespec startTime;
    struct timespec endTime;

    struct option optionList[]= {
        {"threads=", hasarg, noflag, THREADS},
        {"iterations=", hasarg, noflag, ITERATIONS},
        {0,0,0,0}
    };
    int numThreads;
    int numIterations;
    //initialize default values
    numThreads = 1;
    numIterations = 1;
    counter = 0;
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
            if (optionValue == '?'){//occurs when we find an option without the appropriate argument
    			fprintf(stderr, "%s is missing an argument\n", optionList[optionIndex].name);
    			numErrors++;
    			continue;
    		}
            if(optionValue == THREADS){
                numThreads = atoi(optarg);
            } else if (optionValue == ITERATIONS){
                numIterations = atoi(optarg);
            }
        }
    }
    pid_t child;
    //we now have proper number of threads and interations, time to fork
    for (int b = 0; b < numThreads; b++){

        child = fork();
        if(child == -1){
            numErrors++;
        }
        if(child == 0){
            for (int c = 0; c < numIterations; c++){
                add(&counter, 1);
            }
            for (int d = 0; d < numIterations; d++){
                add(&counter, -1);
            }
            exit(0);
        }
    }
    //wait for all children
    int childStatus;
    while(child = waitpid(-1, &childStatus,0)){
        if (child == ECHILD){
            break;
        }
    }
    //get time
    clock_gettime(CLOCK_MONOTONIC,&endTime);
    //if count is not 0, report error
    if (count != 0 ){
        fprintf(stderr, "Error: Final Count = %lld \n", count);
    }
    int numOperations;
    numOperations = 2*numThreads*numIterations;
    printf("Total number of operations performed: %d \n", numOperations);
    //calculate run time
    float startRunTime = (float) (startTime.tv_sec*1e9) + (float)(startTime.tv_nsec);
	float endRunTime = (float) (endTime.tv_sec*1e9) + (float)(endTime.tv_nsec);
	float totalRunTime = endRunTime - startRunTime;
    printf("Elapsed Time: %f \n", totalRunTime);
    printf("Average Operation Time: %f \n", totalRunTime/numOperations);
    exit(exitNum);
}
