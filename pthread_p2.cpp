#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <windows.h>

#define n 10
#define thread_num 2


int arr[n] = {1,2,3,4,5,3,2,1,5,5};
int sum = 0;

using namespace std;

pthread_mutex_t mutex;

void* routine(void *arg){
    pthread_mutex_lock(&mutex);

    for(int i=0; i<n/thread_num; i++){
    int* ptr = (int *) arg;
    sum += *ptr;
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}


int main(){
    pthread_t th[thread_num]; ///2
    pthread_mutex_init(&mutex, NULL);
    
    for(int i=0; i<n; i++){
        int start = (n/thread_num)*i;
        int end = (n/thread_num)*(i+1);

        for(int j=start; j<end; j++){
            pthread_create(&th[i], NULL, routine, &arr);
        }

    }

    return 0;
}