/*

given an array with  10 random integer, 
at first calculate the prefix sum of the array and keep changing the 
elements accordingly, and after than calculate the prefix multiplication, all using mutex threads

*/


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

int array[SIZE];
pthread_mutex_t mutex;

void *calculate_prefix_sum(void *arg) {
    pthread_mutex_lock(&mutex);
    for (int i = 1; i < SIZE; i++) {
        array[i] += array[i - 1];
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *calculate_prefix_multiplication(void *arg) {
    pthread_mutex_lock(&mutex);
    for (int i = 1; i < SIZE; i++) {
        array[i] *= array[i - 1];
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t threads[2];

    // Initialize array with random numbers
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 10 + 1;
    }

    printf("Original array: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    pthread_mutex_init(&mutex, NULL);

    // Create thread for prefix sum
    pthread_create(&threads[0], NULL, calculate_prefix_sum, NULL);
    pthread_join(threads[0], NULL);

    printf("After prefix sum: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    // Create thread for prefix multiplication
    pthread_create(&threads[1], NULL, calculate_prefix_multiplication, NULL);
    pthread_join(threads[1], NULL);

    printf("After prefix multiplication: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    pthread_mutex_destroy(&mutex);

    return 0;
}