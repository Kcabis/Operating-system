//Program to implement multithreaded process
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* threadFunction(void* arg) {
    int threadNum = *((int*) arg);
    printf("Hey I am thread %d!\n", threadNum);
    return NULL;
}

int main() {
    pthread_t threads[2];  
    int threadArgs[2];   

    for (int i = 0; i < 2; i++) {
        threadArgs[i] = i + 1;  
        if (pthread_create(&threads[i], NULL, threadFunction, &threadArgs[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    for (int i = 0; i < 2; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            return 1;
        }
    }

    printf("All threads have completed execution.\n");
    return 0;
}

