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
#include "SortedList.h"

#define noarg 0
#define hasarg 1
#define optionalarg 2
#define noflag 0
#define maxKeyLength 10

#define THREADS 'a'
#define ITERATIONS 'b'
#define YIELD 'c'
#define SYNC 'd'

static long long counter;
//static int opt_yield;
static int mutexFlag;
static int spinFlag;
static int atomicFlag;
static pthread_mutex_t mutex;
static int spinLock;
static int atomicLock;
static int yieldInsert;
static int yieldDelete;
static int yieldSearches;
int opt_yield;

struct argsStruct{
    int start;
    int end;
};

SortedListElement_t* elementArray;
SortedList_t* head;
/**
 * SortedList_insert ... insert an element into a sorted list
 *
 *	The specified element will be inserted in to
 *	the specified list, which will be kept sorted
 *	in ascending order based on associated keys
 *
 * @param SortedList_t *list ... header for the list
 * @param SortedListElement_t *element ... element to be added to the list
 *
 * Note: if (opt_yield & INSERT_YIELD)
 *		call pthread_yield in middle of critical section
 */
void SortedList_insert(SortedList_t *list, SortedListElement_t *element){
    printf("Running regular. \n");
    printf("Inserting element with key: %s \n", element->key);
    const char* keyToBeAdded;
    keyToBeAdded = element->key;
    //int i = strcmp(keyToBeAdded, list->key);
    //if (i != NULL){
    //    printf("After strcmp. I = %d \n", i);
//    }
    //traverse through linked list until we find the first element
    //with a key > ours.
    SortedListElement_t * iterator;
    //start iterator at first element
    iterator = list;
    printf("Before while loop. \n");
    while(iterator->next != NULL){//loop until iterator points to the last element
        //if keyToBeAdded < iterator->key, then we've found the element we want to insert before
        printf("Inside while loop. \n");
        if (iterator->key != NULL){
            printf("Inside if. \n");
            if(strcmp(keyToBeAdded, iterator->key) < 0){
            //insert the element
                printf("Found a bigger word. \n");
                iterator->prev->next = element;
                element->prev = iterator->prev;
                if(opt_yield & INSERT_YIELD){
                    pthread_yield();
                }
                iterator->prev = element;
                element->next = iterator;
                return;
            }
        }
        iterator = iterator -> next;
    }
    //iterator now points to last element in list

    printf("Outside of loop. \n");
    if (iterator->key != NULL){
        printf("inside outside nullcheck. \n");
        if(strcmp(keyToBeAdded, iterator->key) < 0){
            //insert the element
            printf("Found a bigger word outside of loop. \n");
            iterator->prev->next = element;
            element->prev = iterator->prev;
            if(opt_yield & INSERT_YIELD){
                pthread_yield();
            }
            iterator->prev = element;
            element->next = iterator;

            return;
        }
    }
        printf("Adding element to the end. \n");
        //if we're here, the element we want to add is the greatest, tack it to the end
        iterator->next = element;
        if(opt_yield & INSERT_YIELD){
            pthread_yield();
        }
        element->prev = iterator;

<<<<<<< HEAD
}
void mutexSortedList_insert(SortedList_t *list, SortedListElement_t *element){
printf("Running mutex. \n");
    printf("Inserting element with key: %s \n", element->key);
=======
   // printf("Inserting element with key: %s \n", element->key);
>>>>>>> origin/master
    const char* keyToBeAdded;
    keyToBeAdded = element->key;
    //int i = strcmp(keyToBeAdded, list->key);
    //if (i != NULL){
    //    printf("After strcmp. I = %d \n", i);
//    }
    //traverse through linked list until we find the first element
    //with a key > ours.
    SortedListElement_t * iterator;
    //start iterator at first element
    iterator = list;
<<<<<<< HEAD
    printf("Before while loop. \n");
    pthread_mutex_lock(&mutex);
=======
  //  printf("Before while loop. \n");
>>>>>>> origin/master
    while(iterator->next != NULL){//loop until iterator points to the last element
        //if keyToBeAdded < iterator->key, then we've found the element we want to insert before
   //     printf("Inside while loop. \n");
        if (iterator->key != NULL){
     //       printf("Inside if. \n");
            if(strcmp(keyToBeAdded, iterator->key) < 0){
            //insert the element
<<<<<<< HEAD
                printf("Found a bigger word. \n");

=======
       //         printf("Found a bigger word. \n");
>>>>>>> origin/master
                iterator->prev->next = element;
                element->prev = iterator->prev;
                if(opt_yield & INSERT_YIELD){
                    pthread_yield();
                }
                iterator->prev = element;
                element->next = iterator;

                pthread_mutex_unlock(&mutex);
                return;
            }
        }
        iterator = iterator -> next;
    }
    pthread_mutex_unlock(&mutex);
    //iterator now points to last element in list

<<<<<<< HEAD
    printf("Outside of loop. \n");
    pthread_mutex_lock(&mutex);
=======
   // printf("Outside of loop. \n");
>>>>>>> origin/master
    if (iterator->key != NULL){
      //  printf("inside outside nullcheck. \n");
        if(strcmp(keyToBeAdded, iterator->key) < 0){
            //insert the element
<<<<<<< HEAD
            printf("Found a bigger word outside of loop. \n");

=======
        //    printf("Found a bigger word outside of loop. \n");
>>>>>>> origin/master
            iterator->prev->next = element;
            element->prev = iterator->prev;
            if(opt_yield & INSERT_YIELD){
                pthread_yield();
            }
            iterator->prev = element;
            element->next = iterator;
            pthread_mutex_unlock(&mutex);
            return;
        }
    }
    pthread_mutex_unlock(&mutex);
        printf("Adding element to the end. \n");
        //if we're here, the element we want to add is the greatest, tack it to the end
        pthread_mutex_lock(&mutex);
        iterator->next = element;
        if(opt_yield & INSERT_YIELD){
            pthread_yield();
        }
        element->prev = iterator;
        pthread_mutex_unlock(&mutex);

}
void spinSortedList_insert(SortedList_t *list, SortedListElement_t *element){
printf("Running spin. \n");
    printf("Inserting element with key: %s \n", element->key);
    const char* keyToBeAdded;
    keyToBeAdded = element->key;
    //int i = strcmp(keyToBeAdded, list->key);
    //if (i != NULL){
    //    printf("After strcmp. I = %d \n", i);
//    }
    //traverse through linked list until we find the first element
    //with a key > ours.
    SortedListElement_t * iterator;
    //start iterator at first element
    iterator = list;
    printf("Before while loop. \n");
    while(__sync_lock_test_and_set(&spinLock, 1)){
        continue;
    }
    while(iterator->next != NULL){//loop until iterator points to the last element
        //if keyToBeAdded < iterator->key, then we've found the element we want to insert before
        printf("Inside while loop. \n");
        if (iterator->key != NULL){
            printf("Inside if. \n");
            if(strcmp(keyToBeAdded, iterator->key) < 0){
            //insert the element
                printf("Found a bigger word. \n");

                iterator->prev->next = element;
                element->prev = iterator->prev;
                if(opt_yield & INSERT_YIELD){
                    pthread_yield();
                }
                iterator->prev = element;
                element->next = iterator;
                __sync_lock_release(&spinLock);
                return;
            }
        }
        iterator = iterator -> next;
    }
    __sync_lock_release(&spinLock);
    //iterator now points to last element in list
    while(__sync_lock_test_and_set(&spinLock, 1)){
        continue;
    }
    printf("Outside of loop. \n");
    if (iterator->key != NULL){
        printf("inside outside nullcheck. \n");
        if(strcmp(keyToBeAdded, iterator->key) < 0){
            //insert the element
            printf("Found a bigger word outside of loop. \n");

            iterator->prev->next = element;
            element->prev = iterator->prev;
            if(opt_yield & INSERT_YIELD){
                pthread_yield();
            }
            iterator->prev = element;
            element->next = iterator;
            __sync_lock_release(&spinLock);
            return;
        }
    }
    //    printf("Adding element to the end. \n");
        //if we're here, the element we want to add is the greatest, tack it to the end
        iterator->next = element;
        if(opt_yield & INSERT_YIELD){
            pthread_yield();
        }
        element->prev = iterator;
        __sync_lock_release(&spinLock);

}

/**
 * SortedList_delete ... remove an element from a sorted list
 *
 *	The specified element will be removed from whatever
 *	list it is currently in.
 *
 *	Before doing the deletion, we check to make sure that
 *	next->prev and prev->next both point to this node
 *
 * @param SortedListElement_t *element ... element to be removed
 *
 * @return 0: element deleted successfully, 1: corrtuped prev/next pointers
 *
 * Note: if (opt_yield & DELETE_YIELD)
 *		call pthread_yield in middle of critical section
 */
int SortedList_delete( SortedListElement_t *element){
<<<<<<< HEAD
    printf("Running regular. \n");
    printf("Deleting element with key: %s \n", element->key);
=======
 //   printf("Deleting element with key: %s \n", element->key);
>>>>>>> origin/master
    const char* keyToBeDeleted;
    keyToBeDeleted = element->key;
    SortedListElement_t * iterator;
    //start iterator at head
    iterator = head;
    while(iterator->next != NULL){//loop until iterator points to the last element
        //if we found the key we want to delete
        if(iterator->key == keyToBeDeleted){
            //check that prev->next and next->prev point to elements
            int prevCheck = (iterator->prev->next == element);
            int nextCheck = (iterator->next->prev == element);
            if (prevCheck && nextCheck){
                //delete from list
                iterator->next->prev = iterator->prev;
                iterator->prev->next = iterator->next;
                if(opt_yield & DELETE_YIELD){
                    pthread_yield();
                }
                iterator->prev = NULL;
                iterator->next = NULL;
                return 0;
            } else{
                return 1;
            }
        } else{
            iterator = iterator -> next;
        }
    }
    //if we're here, iterator points to last element, we still haven't found a matching
    if(iterator->key == keyToBeDeleted){
        if (iterator->prev->next == element){
            iterator->prev->next = NULL;
            if(opt_yield & DELETE_YIELD){
                pthread_yield();
            }
            iterator->prev = NULL;
            iterator->next = NULL;
            return 0;
        }
    }
    return 1;
}
int mutexSortedList_delete( SortedListElement_t *element){
    printf("Running mutex. \n");
    printf("Deleting element with key: %s \n", element->key);
    const char* keyToBeDeleted;
    keyToBeDeleted = element->key;
    SortedListElement_t * iterator;
    //start iterator at head
    iterator = head;
    pthread_mutex_lock(&mutex);
    while(iterator->next != NULL){//loop until iterator points to the last element
        //if we found the key we want to delete
        if(iterator->key == keyToBeDeleted){
            //check that prev->next and next->prev point to elements
            int prevCheck = (iterator->prev->next == element);
            int nextCheck = (iterator->next->prev == element);
            if (prevCheck && nextCheck){
                //delete from list
                iterator->next->prev = iterator->prev;
                iterator->prev->next = iterator->next;
                if(opt_yield & DELETE_YIELD){
                    pthread_yield();
                }
                iterator->prev = NULL;
                iterator->next = NULL;
                pthread_mutex_unlock(&mutex);
                return 0;
            } else{
                return 1;
            }
        } else{
            iterator = iterator -> next;
        }
    }
    //if we're here, iterator points to last element, we still haven't found a matching
    if(iterator->key == keyToBeDeleted){
        if (iterator->prev->next == element){

            iterator->prev->next = NULL;
            if(opt_yield & DELETE_YIELD){
                pthread_yield();
            }
            iterator->prev = NULL;
            iterator->next = NULL;
            pthread_mutex_unlock(&mutex);
            return 0;
        }
    }

    pthread_mutex_unlock(&mutex);
    return 1;
}
int spinSortedList_delete( SortedListElement_t *element){
    printf("Running spin. \n");
    printf("Deleting element with key: %s \n", element->key);
    const char* keyToBeDeleted;
    keyToBeDeleted = element->key;
    SortedListElement_t * iterator;
    //start iterator at head
    iterator = head;

    while(__sync_lock_test_and_set(&spinLock, 1)){
        continue;
    }
    while(iterator->next != NULL){//loop until iterator points to the last element
        //if we found the key we want to delete
        if(iterator->key == keyToBeDeleted){
            //check that prev->next and next->prev point to elements
            int prevCheck = (iterator->prev->next == element);
            int nextCheck = (iterator->next->prev == element);
            if (prevCheck && nextCheck){
                //delete from list
                iterator->next->prev = iterator->prev;
                iterator->prev->next = iterator->next;
                if(opt_yield & DELETE_YIELD){
                    pthread_yield();
                }
                iterator->prev = NULL;
                iterator->next = NULL;
                __sync_lock_release(&spinLock);
                return 0;
            } else{

                __sync_lock_release(&spinLock);
                return 1;
            }
        } else{
            iterator = iterator -> next;
        }
    }
    //if we're here, iterator points to last element, we still haven't found a matching
    if(iterator->key == keyToBeDeleted){
        if (iterator->prev->next == element){
            iterator->prev->next = NULL;
            if(opt_yield & DELETE_YIELD){
                pthread_yield();
            }
            iterator->prev = NULL;
            iterator->next = NULL;
            __sync_lock_release(&spinLock);
            return 0;
        }
    }

    __sync_lock_release(&spinLock);
    return 1;
}

/**
 * SortedList_lookup ... search sorted list for a key
 *
 *	The specified list will be searched for an
 *	element with the specified key.
 *
 * @param SortedList_t *list ... header for the list
 * @param const char * key ... the desired key
 *
 * @return pointer to matching element, or NULL if none is found
 *
 * Note: if (opt_yield & SEARCH_YIELD)
 *		call pthread_yield in middle of critical section
 */
SortedListElement_t *SortedList_lookup(SortedList_t *list, const char *key){
<<<<<<< HEAD
    printf("Running regular. \n");
    printf("Looking up element with key: %s \n", key);
=======
//    printf("Looking up element with key: %s \n", key);
>>>>>>> origin/master
    const char* keyToFind;
    keyToFind = key;
    SortedListElement_t * iterator;
    //start iterator at first element
    iterator = list;
    while(iterator->next != NULL){//loop until iterator points to the last element
        //if we found the key we want to delete
        if(iterator->key == keyToFind){
            break;
        } else{
            if(opt_yield & SEARCH_YIELD){
                pthread_yield();
            }
            iterator = iterator -> next;
        }
    }
    //the check for once we're at the last element
    if (iterator->key != keyToFind){
        return NULL;
    }
    return iterator;
}
SortedListElement_t *mutexSortedList_lookup(SortedList_t *list, const char *key){
    printf("Running mutex. \n");
    printf("Looking up element with key: %s \n", key);
    const char* keyToFind;
    keyToFind = key;
    SortedListElement_t * iterator;
    //start iterator at first element
    iterator = list;

        pthread_mutex_lock(&mutex);
    while(iterator->next != NULL){//loop until iterator points to the last element
        //if we found the key we want to delete
        if(iterator->key == keyToFind){
            break;
        } else{
            if(opt_yield & SEARCH_YIELD){
                pthread_yield();
            }
            iterator = iterator -> next;
            pthread_mutex_unlock(&mutex);
        }
    }
    //the check for once we're at the last element
    if (iterator->key != keyToFind){

        pthread_mutex_unlock(&mutex);
        return NULL;
    }

    pthread_mutex_unlock(&mutex);
    return iterator;
}
SortedListElement_t *spinSortedList_lookup(SortedList_t *list, const char *key){
    printf("Running spin. \n");
    printf("Looking up element with key: %s \n", key);
    const char* keyToFind;
    keyToFind = key;
    SortedListElement_t * iterator;
    //start iterator at first element
    iterator = list;

        while(__sync_lock_test_and_set(&spinLock, 1)){
            continue;
        }
    while(iterator->next != NULL){//loop until iterator points to the last element
        //if we found the key we want to delete
        if(iterator->key == keyToFind){
            break;
        } else{
            if(opt_yield & SEARCH_YIELD){
                pthread_yield();
            }
            iterator = iterator -> next;
            __sync_lock_release(&spinLock);
        }
    }
    //the check for once we're at the last element
    if (iterator->key != keyToFind){

        __sync_lock_release(&spinLock);
        return NULL;
    }

    __sync_lock_release(&spinLock);
    return iterator;
}
/**
 * SortedList_length ... count elements in a sorted list
 *	While enumeratign list, it checks all prev/next pointers
 *
 * @param SortedList_t *list ... header for the list
 *
 * @return int number of elements in list (excluding head)
 *	   -1 if the list is corrupted
 *
 * Note: if (opt_yield & SEARCH_YIELD)
 *		call pthread_yield in middle of critical section
 */
int SortedList_length(SortedList_t *list){
<<<<<<< HEAD
    printf("Running regular. \n");
    printf("Getting length of list. \n");
=======
 //   printf("Getting length of list. \n");
>>>>>>> origin/master
    int count;
    count = 0;
    SortedListElement_t * iterator;
    //start iterator at first element
    iterator = list->next;
  //  printf("Outside loop. \n");
    while(iterator != NULL){
        //move to next one
     //   printf("Inside loop. \n");
        //SortedListElement_t * nextElement;
        if(opt_yield & SEARCH_YIELD){
            pthread_yield();
        }
       // printf("Spot 1. \n");
        //nextElement = iterator->next;
        //check pointers?
       // printf("Spot 2. \n");
        //if next is not null, next->prev should be ourselves
        if (iterator->next != NULL){
            if (iterator->next->prev != iterator){
                return -1;
            }
        }
        if (iterator->prev != NULL){
            if (iterator->prev->next != iterator){
                return -1;
            }
        }
      //  printf("spot 3. \n");
        iterator = iterator->next;
        count++;
    }
    return count;
}
int mutexSortedList_length(SortedList_t *list){
    printf("Running mutex. \n");
    printf("Getting length of list. \n");
    int count;
    count = 0;
    SortedListElement_t * iterator;
    //start iterator at first element
    iterator = list->next;
    printf("Outside loop. \n");

    pthread_mutex_lock(&mutex);
    while(iterator != NULL){
        //move to next one
        printf("Inside loop. \n");
        //SortedListElement_t * nextElement;
        if(opt_yield & SEARCH_YIELD){
            pthread_yield();
        }
        printf("Spot 1. \n");
        //nextElement = iterator->next;
        //check pointers?
        printf("Spot 2. \n");
        //if next is not null, next->prev should be ourselves
        if (iterator->next != NULL){
            if (iterator->next->prev != iterator){

                pthread_mutex_unlock(&mutex);
                return -1;
            }
        }
        if (iterator->prev != NULL){
            if (iterator->prev->next != iterator){

                pthread_mutex_unlock(&mutex);
                return -1;
            }
        }
        printf("spot 3. \n");
        iterator = iterator->next;
        pthread_mutex_unlock(&mutex);
        count++;
    }

    pthread_mutex_unlock(&mutex);
    return count;
}
int spinSortedList_length(SortedList_t *list){
    printf("Running spin. \n");
    printf("Getting length of list. \n");
    int count;
    count = 0;
    SortedListElement_t * iterator;
    //start iterator at first element
    iterator = list->next;
    printf("Outside loop. \n");

    while(__sync_lock_test_and_set(&spinLock, 1)){
        continue;
    while(iterator != NULL){
        //move to next one
        printf("Inside loop. \n");
        //SortedListElement_t * nextElement;
        }
        if(opt_yield & SEARCH_YIELD){
            pthread_yield();
        }
        printf("Spot 1. \n");
        //nextElement = iterator->next;
        //check pointers?
        printf("Spot 2. \n");
        //if next is not null, next->prev should be ourselves
        if (iterator->next != NULL){
            if (iterator->next->prev != iterator){

                __sync_lock_release(&spinLock);
                return -1;
            }
        }
        if (iterator->prev != NULL){
            if (iterator->prev->next != iterator){

                __sync_lock_release(&spinLock);
                return -1;
            }
        }
        printf("spot 3. \n");
        iterator = iterator->next;
        __sync_lock_release(&spinLock);
        count++;
    }
    return count;
}
/**
 * variable to enable diagnositc calls to pthread_yield
 */

void* ListOperations(void* arguments){
    struct argsStruct* args = (struct argsStruct*) arguments;
    int start;
    int end;
    start = args->start;
    end = args->end;
    //free(args);
//    printf("ListOperation start: %d \n", start);
        //printf("ListOperation a: %d \n", a);
  //      printf("ListOperation end: %d \n", end);
    for (int a = start; a < end; a++){
<<<<<<< HEAD
        printf("ListOperation start: %d \n", start);
            printf("ListOperation a: %d \n", a);
            printf("ListOperation end: %d \n", end);
        if(spinFlag){
            spinSortedList_insert(head, &elementArray[a]);
        } else if (mutexFlag){
            mutexSortedList_insert(head, &elementArray[a]);
        } else{
            SortedList_insert(head, &elementArray[a]);
        }
=======
    //    printf("ListOperation start: %d \n", start);
      //      printf("ListOperation a: %d \n", a);
        //    printf("ListOperation end: %d \n", end);

        SortedList_insert(head, &elementArray[a]);
>>>>>>> origin/master
    }

    //printf("Element 1 : %s \n", head->key);
    //printf("Element 2 : %s \n", head->next->key);
    //printf("Element 3 : %s \n", head->next->next->key);
    int length;
    if(spinFlag){
        length = spinSortedList_length(head);
    } else if (mutexFlag){
        length = mutexSortedList_length(head);
    } else{
        length = SortedList_length(head);
    }
    printf("Length: %d \n", length);
    SortedListElement_t * elementToDelete;
    for (int b = start; b < end; b++){
        if(spinFlag){
            elementToDelete = spinSortedList_lookup(head, elementArray[b].key);
        } else if (mutexFlag){
            elementToDelete = mutexSortedList_lookup(head, elementArray[b].key);
        } else{
            elementToDelete = SortedList_lookup(head, elementArray[b].key);
        }
        if(spinFlag){
            spinSortedList_delete(elementToDelete);
        } else if (mutexFlag){
            mutexSortedList_delete(elementToDelete);
        } else{
            SortedList_delete(elementToDelete);
        }
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
    mutexFlag = 1;
    spinFlag = 0;
    atomicFlag = 0;
    spinLock = 0;
    yieldInsert = 0;
    yieldDelete = 0;
    yieldSearches = 0;
    //initialize linkedlist
    head = malloc(sizeof(SortedListElement_t));
    if (head == NULL){
    //    printf("Failed to initialize linked list. \n");
        numErrors++;
        exit(numErrors);
    }

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
                        if (*optarg == 'i'){
                            opt_yield | INSERT_YIELD;
                            printf("Set insert. \n");
                            //yieldInsert = 1;
                        } else if (*optarg == 'd'){
                            opt_yield | DELETE_YIELD;
                            printf("Set delete. \n");
                            //yieldDelete = 1;
                        } else if (*optarg == 's'){
                            opt_yield | SEARCH_YIELD;
                            printf("Set searches. \n");
                            //yieldSearches = 1;
                        } else if (strcmp(argv[optind], "is")){
                            opt_yield | INSERT_YIELD |SEARCH_YIELD;
                            printf("Set insert searches. \n");
                            //yieldSearches = 1;
                        } else if (strcmp(argv[optind], "id")){
                            opt_yield | INSERT_YIELD |DELETE_YIELD;
                            printf("Set insert delete. \n");
                            //yieldSearches = 1;
                        }else {
                            printf("Could not set yield. \n");
                        }
		                break;
                    case SYNC:
                        printf("Inside sync switch. \n");
                        if (*optarg == 'm'){
                            printf("Set mutex. \n");
                            mutexFlag = 1;
                        } else if (*optarg == 's'){
                            printf("Set spin. \n");
                            spinFlag = 1;
                        } else {
                            printf("Could not set sync. \n");
                        }
                        break;
                }
            }
	    }
	}

    //initialize the elements
    int numElements = numThreads*numIterations;
    printf("Number of elements in array: %d \n", numElements);
    elementArray = malloc((sizeof(SortedListElement_t))*numElements);
    if (elementArray == NULL){
        printf("Could not initialize element array. \n");
        numErrors++;
        exit(numErrors);
    }
    for (int d = 0; d < numElements; d++){

        //printf("First: Char 0 is: %s \n", elementArray[0].key);
        elementArray[d].next = NULL;
        elementArray[d].prev = NULL;

        //printf("Second: Char 0 is: %s \n", elementArray[0].key);
        //generate length of key

        int keyLength;
        keyLength = rand() % maxKeyLength;
        //generate each char of the keyLength
        //printf("Third:Char 0 is: %s \n", elementArray[0].key);
        char* newChar = malloc(sizeof(char)*(keyLength+1));
        //printf("Fourth:Char 0 is: %s \n", elementArray[0].key);
        for (int e = 0; e < keyLength; e++){

        //    printf("4.5:Char 0 is: %s \n", elementArray[0].key);
            newChar[e] = rand() % 255;
        }

        //printf("Fifth:Char 0 is: %s \n", elementArray[0].key);
        //printf("Char %s being added to array. \n", newChar);
        newChar[keyLength] = '\0';

        elementArray[d].key = newChar;
        //free(newChar);
        //printf("Char 0 is: %s \n", elementArray[0].key);
    }
 //   printf("Chars inside array: %s %s",elementArray[0].key, elementArray[1].key );
    //
    pthread_t tids[numThreads];
    int tid;
    //we now have proper number of threads and interations, time to fork

    int numThreadsPassed;
    numThreadsPassed = 0;

//    printf("Num Iterations: %d \n", numIterations);
    for (int b = 0; b < numThreads; b++){
        struct argsStruct* args = malloc(sizeof(struct argsStruct));
        if (args == NULL){
            printf("Could not allocate memory for arguments. \n");
            numErrors++;
            exit(numErrors);
        }
        args->start = numThreadsPassed;
  //      printf("Start passed: %d \n", args->start);
        args->end = numThreadsPassed + numIterations;
    //    printf("End passed: %d \n", args->end);
        tid = pthread_create(&tids[b], NULL, ListOperations, (void*)args);
        if (tid == -1){
            numErrors++;
	        printf("Failed to create a thread. \n");
	        exit(numErrors);
        }
        numThreadsPassed = numThreadsPassed + numIterations;
    }
    for (int c = 0; c < numThreads; c++){
        printf("Waiting on threads. \n");
        pthread_join(tids[c], NULL);
        printf("Finished waiting on thread, \n");
    }
    //get time
    clock_gettime(CLOCK_MONOTONIC,&endTime);
    //if count is not 0, report error
  //  printf("Finished waiting. \n");
    if (SortedList_length(head) != 0 ){
        fprintf(stderr, "Error: Final List Count = %d \n", SortedList_length(head));
    }
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
