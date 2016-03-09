#include <unistd.h>
#include <stdio.h>

#include <string.h>
#include <getopt.h>
#include <stdlib.h>

#define noarg 0
#define hasarg 1
#define noflag 0

#define THREADS 'a'
#define ITERATIONS 'b'


void add(long long *pointer, long long value) {
       long long sum = *pointer + value;
       *pointer = sum;
}

int main(int argc, char* argv[]){
    struct option optionList[]= {
        {"threads=", hasarg, noflag, THREADS},
        {"iterations=", hasarg, noflag, ITERATIONS},
        {0,0,0,0},
    }
    int numThreads;
    int numIterations;
}
