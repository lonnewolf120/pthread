#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <windows.h>

#define n 10
#define thread_num 2


int arr[n] = {1,2,3,4,5,3,2,1,5,5};

pthread_mutex_t mutex;

void* routine(void* arg) {
    
    int *index = (int *)arg;
    pthread_mutex_lock(&mutex);
    ///Cast the argument to an integer pointer
    int sum = 0;
    for (int j = 0; j < (n/thread_num); j++) {
        sum += arr[*index + j];
    }
    printf("Local sum: %d\n", sum);
    *(int *)arg = sum;
    pthread_mutex_unlock(&mutex);
    ///assigns the value of sum to the memory location pointed to by arg
    return arg; ///Return the pointer to the sum
}

int main() {

    pthread_t th[thread_num]; ///2
    pthread_mutex_init(&mutex, NULL);
    int i;

    for (i = 0; i < thread_num; i++) {
        int* a = (int *) malloc(sizeof(int));
        *a = (n/thread_num)*i;// initial a=(10/2)*0 = 0 then a=(10/2)*1 = 5
        if (pthread_create(&th[i], NULL, routine, a) != 0) {
            ///a is a pointer to an int. When u pass a, you are passing the addr of the int,
            ///which allows the thread funct to access and modify the orgn int val stored at that addr.
            perror("Failed to create thread");
        }
    }
    int globalSum = 0;
    for (i = 0; i < thread_num; i++) {
        int* r;
        if (pthread_join(th[i], (void**) &r) != 0) {
            perror("Failed to join thread");
            /// takes the address of r, you are passing a pointer to r.
            ///r will point to the memory location returned by the thread's return statement
        }
        globalSum += *r;
        free(r);
    }
    printf("Global sum: %d\n", globalSum);
    pthread_mutex_destroy(&mutex);
    return 0;
}
