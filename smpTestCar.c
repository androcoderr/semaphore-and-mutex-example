#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_SPACES 3  // Number of parking spaces
#define NUM_CARS 10   // Number of cars

sem_t parkingSpaces;

void* car(void* arg) {
    int car_id = *((int*)arg);
    int availableSpace;

    sem_getvalue(&parkingSpaces, &availableSpace);

    printf("Car %d is looking for a parking space. There are %d available space \n", car_id, availableSpace);
    sem_wait(&parkingSpaces);  // Try to enter the parking lot (decrement semaphore)
    
    // Car has found a parking space
    printf("Car %d has parked.\n", car_id);
    sleep(rand() % 10 + 1);  // Simulate the car being parked for some time
    
    // Car is leaving the parking space
    printf("Car %d is leaving the parking space.\n", car_id);
    sem_post(&parkingSpaces);  // Leave the parking lot (increment semaphore)
    
    return NULL;
}

int main() {
    pthread_t cars[NUM_CARS];
    int car_ids[NUM_CARS];

    // Initialize the semaphore with the number of parking spaces
    sem_init(&parkingSpaces, 0, NUM_SPACES);

    // Create threads for each car
    for (int i = 0; i < NUM_CARS; ++i) {
        car_ids[i] = i + 1;
        pthread_create(&cars[i], NULL, car, &car_ids[i]);
        sleep(rand() % 2);  // Stagger the arrival of cars
    }

    // Wait for all car threads to finish
    for (int i = 0; i < NUM_CARS; ++i) {
        pthread_join(cars[i], NULL);
    }

    // Destroy the semaphore
    sem_destroy(&parkingSpaces);

    return 0;
}
