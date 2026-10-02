#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{

    // TODO: wait, obtain mutex, wait, release mutex as described by thread_data structure
    // hint: use a cast like the one below to obtain thread arguments from your parameter
    //struct thread_data* thread_func_args = (struct thread_data *) thread_param;
    struct thread_data *tdPtr = (struct thread_data*) thread_param;
    int wait_to_obtain_ms = tdPtr->waitToObtainMs;
    int wait_to_release_ms = tdPtr->waitToReleaseMs;
    pthread_mutex_t *mutex = tdPtr->mutex;
    
    printf("sleep1\n");
    usleep(wait_to_obtain_ms);
    printf("lock\n");
    pthread_mutex_lock(mutex);
    printf("sleep2\n");
    usleep(wait_to_release_ms);
    printf("unlock\n");
    pthread_mutex_unlock(mutex);
    tdPtr->thread_complete_success = true;
    


    return (void*) thread_param;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{

    struct thread_data *tdptr = malloc(sizeof(struct thread_data));
    tdptr->mutex = mutex;
    tdptr->thread_complete_success = false;
    tdptr->waitToObtainMs = wait_to_obtain_ms;
    tdptr->waitToReleaseMs = wait_to_release_ms;

    int rc = pthread_create(thread,NULL,threadfunc,tdptr);

    // check if thread is successful
    if (rc != 0){
        free(tdptr);
        return false;
    }
    return true;

    /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.
     *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */
}

