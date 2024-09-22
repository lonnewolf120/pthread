#include<bits/stdc++.h>
#include<pthread.h>
#include<windows.h>

using namespace std;

void * routine(void *args){
    int *a = (int *) args;
    cout<<"Hello from threads"<<endl;
    Sleep(3000);
    cout<<"Ending thread"<<endl;
}
///Each thread prints "Hello from threads", sleeps for 3 seconds, and then prints "Ending thread".
int main(){
    pthread_t th[1000];
    int i;
    for (i=0; i<1000; i++){
    if(pthread_create(&th[i], NULL, routine, NULL) !=0){
            perror("Failed to create thread");
        }
    }
    cout<<"Thread "<<i<<" has started"<<endl;

}
