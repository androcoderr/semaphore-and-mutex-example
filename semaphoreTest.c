#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore;

void* thread_function(void* arg) {
    sem_wait(&semaphore);
    // Critical section
    printf("Thread %d is in the critical section.\n", *((int*)arg));
    sem_post(&semaphore);
    return NULL;
}

int main() {
    pthread_t threads[5];
    int thread_args[5];

    sem_init(&semaphore, 0, 1);  // Initialize semaphore

    for (int i = 0; i < 5; ++i) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_args[i]);
    }

    for (int i = 0; i < 5; ++i) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&semaphore);  // Destroy semaphore
    return 0;
}
