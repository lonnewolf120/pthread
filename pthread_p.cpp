#include <iostream>
#include <pthread.h>
#include <windows.h>

/*
one bank account with 300000 tk balance,
3 users 

*/


using namespace std;

pthread_mutex_t mutex; // Mutex to protect the account balance

int balance = 300000; //Critical section

void *withdrawMoney(void *arg){
    int* amount = (int*) arg;  //amount he'll withdraw

    pthread_mutex_lock(&mutex); // Lock the mutex before accessing the critical section

    if(balance >= (*amount)){
        balance -= (*amount);
        cout << "Withdrawn: " << *amount << endl;
    }else{
        cout << "Insufficient balance" << endl;
    }
    cout << "Current balance: " << balance << endl;

    pthread_mutex_unlock(&mutex); // Unlock the mutex after accessing the critical section  
    return NULL;
}

void* depositMoney(void *arg){
    int* amount = (int*) arg;  //amount he'll deposit

    pthread_mutex_lock(&mutex); // Lock the mutex before accessing the critical section

    balance += (*amount);
    cout << "Deposited: " << *(amount) << endl;
    cout << "Current balance: " << balance << endl;
    pthread_mutex_unlock(&mutex); // Unlock the mutex after accessing the critical section
    return NULL;
}


int main(){
    pthread_t withdraw[3], deposit;

    pthread_mutex_init(&mutex, NULL); // Initialize the mutex


    int withdraw_amounts[3] = {20, 2000, 60};
    int deposit_amount = 40000;

    for(int i = 0; i < 3; i++){
        if(pthread_create(&withdraw[i], NULL, withdrawMoney, &withdraw_amounts[i])!=0){
            perror("Failed to create withdrawal thread");
            return 1;
        }
    }
    if(pthread_create(&deposit, NULL, depositMoney, &deposit_amount)!=0){
        perror("Failed to create deposit thread");
        return 1;   
    }

    for(int i = 0; i < 3; i++){
        pthread_join(withdraw[i], NULL);
    }
    pthread_join(deposit, NULL);
    
    pthread_mutex_destroy(&mutex); // Destroy the mutex

    return 0;
}