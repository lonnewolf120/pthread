#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LIMIT 50

pthread_mutex_t mutex;
int current_number = 2;

bool is_prime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

void *find_primes(void *arg) {
    int thread_id = *(int *)arg;

    while (true) {
        pthread_mutex_lock(&mutex);
        int num = current_number;
        current_number++;
        pthread_mutex_unlock(&mutex);

        if (num > LIMIT) break;

        if (is_prime(num)) {
            printf("Thread %d: %d is a prime number\n", thread_id, num);
        }
    }
    return NULL;
}

int main() {
    pthread_t threads[2];
    int ids[2] = {1, 2};

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, find_primes, &ids[i]);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}