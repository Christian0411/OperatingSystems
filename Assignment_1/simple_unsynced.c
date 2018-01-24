
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


int SharedVariable = 0;

void SimpleThread(int which){
    int num, val;

    for(num = 0; num < 20; num++){
        #ifdef PTHREAD_SYNC
        
        #endif
        if(random() > RAND_MAX / 2)
        usleep(500);

        val = SharedVariable;
        printf("**** thread %d sees value %d\n", which, val);
        SharedVariable = val + 1;
    }
    val = SharedVariable;
    printf("Thread %d sees final value %d\n", which, val);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
     
   if(argc <= 1 || atoi(argv[1]) <= 0)
   {
       printf("Argument must be a positive non-zero integer\n");
       exit(-1);
   }
    int NUM_THREADS = atoi(argv[1]);
    pthread_t threads[NUM_THREADS];
   
    int rc;
    long t;

    for(t=0; t<NUM_THREADS; t++){
       rc = pthread_create(&threads[t], NULL, SimpleThread, (void *) t);
       if (rc){
          printf("ERROR; return code from pthread_create() is %d\n", rc);
          exit(-1);
       }
    }

    /* Last thing that main() should do */
    pthread_exit(NULL);
    return 0;
}