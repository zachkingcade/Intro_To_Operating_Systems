#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//global varibles
int GARRAY[4000];
int TOTAL = 0;

//prototypes
void *addToGlobalVaribles(void* tid);


int main(){
    //varibles
    pthread_t threads[4];

    //fill the global array with numbers
    for (int i = 0; i < 4000; i++){
        GARRAY[i] = i + 1;
    }

    //create our 4 threads
    for (int i = 0; i < 4; i++){
        int status = pthread_create(&threads[i], NULL, addToGlobalVaribles, (void*)i+1);

        if(status != 0){
            printf("Error, threads not created properly, exiting\n");
            exit(-1);
        }
    }

		// join/wait on all threads to complete before finishing
		for(int i = 0; i < 4; i++){
			pthread_join(threads[i], NULL);
		}

		printf("Our result is: %d\n", TOTAL); 
    exit(0);
}

void* addToGlobalVaribles(void* tid){
	int threadID = (int)tid;
	  // loop vals with different values of thread id
    for (int i = (threadID - 1)*1000; i <= (threadID*1000)-1; i++){
      TOTAL += GARRAY[i];
			printf("Thread #%d: adding %d\n", threadID, GARRAY[i]);
    }
		pthread_exit(NULL);
}