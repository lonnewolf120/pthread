#include <iostream>
#include <pthread.h>
#include <windows.h>

/*
one bank account with 300000 tk balance,
3 users 

*/


using namespace std;

pthread_mutex_t lock; // Mutex to protect the account balance

int account_balance = 300000; // Initial account balance

// Thread function for withdrawing money
void* withdraw(void *args) {
    int *withdraw_amount = (int*)args;
    pthread_mutex_lock(&lock); /// Lock the mutex before accessing the critical section

    if (account_balance >= *withdraw_amount) {
        account_balance -= *withdraw_amount;
        cout << "Withdrew " << *withdraw_amount << ", current balance: " << account_balance << endl;
    } else {
        cout << "Insufficient funds for withdrawal of " << *withdraw_amount << endl;
    }

    pthread_mutex_unlock(&lock); /// Unlock the mutex after accessing the critical section
    return NULL;
}

// Thread function for crediting money
void* credit(void *args) {
    int *credit_amount = (int*)args;
    pthread_mutex_lock(&lock); /// Lock the mutex before accessing the critical section

    account_balance += *credit_amount;
    cout << "Credited " << *credit_amount << ", current balance: " << account_balance << endl;

    pthread_mutex_unlock(&lock); /// Unlock the mutex after accessing the critical section
    return NULL;
}

int main() {
    pthread_t th[4]; // Array of thread identifiers
    pthread_mutex_init(&lock, NULL); /// Initialize the mutex

    int withdraw_amounts[3] = {20, 2000, 60};
    int credit_amount = 40000;

    // Create threads for withdrawals
    for (int i = 0; i < 3; i++) {
        if (pthread_create(&th[i], NULL, withdraw, &withdraw_amounts[i]) != 0) {
            perror("Failed to create withdrawal thread");
            return 1;
        }
    }

    // Create thread for credit
    if (pthread_create(&th[3], NULL, credit, &credit_amount) != 0) {
        perror("Failed to create credit thread");
        return 1;
    }

    // Wait for all threads to finish
    for (int i = 0; i < 4; i++) {
        pthread_join(th[i], NULL);
    }

    pthread_mutex_destroy(&lock); /// Destroy the mutex

    cout << "Final account balance: " << account_balance << endl;
    return 0;
}
