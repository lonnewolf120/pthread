#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <windows.h>
#include <bits/stdc++.h>

int unit = 50000;

pthread_mutex_t mutex;

typedef struct {
    int id;
    int units;
} ThreadArg;

void* workerfunc(void *arg){
    ThreadArg *data = (ThreadArg *) arg;
    pthread_mutex_lock(&mutex);
    if(data->units > unit){
        printf("Worker %d: Not enough units to process\n", data->id);
        pthread_mutex_unlock(&mutex);
        return NULL;
    }
    unit -= data->units;
    printf("Worker %d: Removed %d processed units\n", data->id, data->units);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* truckfunc(void *arg){
    ThreadArg *data = (ThreadArg *) arg;
    pthread_mutex_lock(&mutex);
    unit += data->units;
    printf("Truck %d: Delivered %d processed units\n", data->id, data->units);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(){
    int worker[5] = {1500, 2000, 3000, 500, 2500};
    int truck[2] = {10000, 8000};

    pthread_t th[7];
    ThreadArg args[7];
    pthread_mutex_init(&mutex, NULL);

    for(int i=0; i<5; i++){
        args[i].id = i;
        args[i].units = worker[i];
        if(pthread_create(&th[i], NULL, workerfunc, &args[i]) !=0){
            printf("Failed to create thread for Worker %d\n", i);
            perror("Error");
        }
    }
    for(int i=0; i<5; i++){
        pthread_join(th[i], NULL);
    }
    for(int i=0; i<2; i++){
        args[i+5].id = i;
        args[i+5].units = truck[i];
        if(pthread_create(&th[i+5], NULL, truckfunc, &args[i+5]) !=0){
            printf("Failed to create thread for Truck %d\n", i);
            perror("Error");
        }
    }
    
    for(int i=5; i<7; i++){
        pthread_join(th[i], NULL);
    }

    printf("Final stock: %d\n", unit);

    pthread_mutex_destroy(&mutex);

    return 0;
}