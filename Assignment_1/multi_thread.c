
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>



int SharedVariable = 0;

pthread_mutex_t mutexsum;
pthread_barrier_t barr;


void SimpleThread(int which){
    
    int num, val;
   
    for(num = 0; num < 20; num++){
        
        if(random() > RAND_MAX / 2)
        usleep(500);
        val = SharedVariable;
        printf("**** thread %d sees value %d\n", which, val);
        // Create mutex lock so that only one thread can access the variable at one time
        pthread_mutex_lock (&mutexsum);
        SharedVariable = val + 1;
        pthread_mutex_unlock (&mutexsum); 
    }

    #ifdef PTHREAD_SYNC
    // Barrier_wait so that threads wait for other threads to finish
    int rc = pthread_barrier_wait(&barr);
    if(rc != 0 && rc != PTHREAD_BARRIER_SERIAL_THREAD)
    {
        printf("Could not wait on barrier\n");
        exit(-1);
    }
    #endif

    val = SharedVariable;    
    printf("Thread %d sees final value %d\n", which, val);
   
    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    pthread_attr_t attr;  
    void *status;
    // Validate user input
    if(argc <= 1 || atoi(argv[1]) <= 0)
    {
        printf("Argument must be a positive non-zero integer\n");
        exit(-1);
    }
    int NUM_THREADS = atoi(argv[1]);
    // Threads list
    pthread_t threads[NUM_THREADS];
   
    int rc;
    long t;
    // Initialize the mutex
    pthread_mutex_init(&mutexsum, NULL);
    // Initialize the attribute
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    // Initialize the barrier
    if(pthread_barrier_init(&barr, NULL, NUM_THREADS))
    {
        printf("Could not create a barrier\n");
        return -1;
    }

    for(t=0; t<NUM_THREADS; t++){
        // Create threads
       rc = pthread_create(&threads[t], &attr, SimpleThread, (void *) t);
       if (rc){
          printf("ERROR; return code from pthread_create() is %d\n", rc);
          exit(-1);
       }
    }
    // Destroy attributes after we are done
    pthread_attr_destroy(&attr);
    // Join threads to end program
    for(int i=0; i<NUM_THREADS; i++)
       {
       pthread_join(threads[i], &status);
       }


    // Exit threads and destroy mutex
    pthread_exit(NULL);
    pthread_mutex_destroy(&mutexsum);
    pthread_exit(NULL);
    return 0;
}