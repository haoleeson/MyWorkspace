#include <iostream>
#include <cstdlib>
#include <pthread.h>
using namespace std;
#define NUM_THREADS 5
struct thread_data {
    int  thread_id;
    char *message;
};
void *PrintHello(void *threadarg) {
    struct thread_data *my_data;
    my_data = (struct thread_data *) threadarg;
    cout << "Thread ID : " << my_data->thread_id ;
    cout << " Message : " << my_data->message << endl;
    pthread_exit(NULL);
}
int main (void) {
    pthread_t threads[NUM_THREADS];
    struct thread_data td[NUM_THREADS];
    int rc;
    int i;
    for( i=0; i < NUM_THREADS; i++ ) {
        cout <<"main() : creating thread, " << i << endl;
        td[i].thread_id = i;
        td[i].message = (char*)"This is message";
        rc = pthread_create(&threads[i], NULL,
        PrintHello, (void *)&td[i]);
        if (rc) {
            cout << "Error:unable to create thread," << rc << endl;
            exit(-1);
        }
    }
    pthread_exit(NULL);
}
/*
$ g++ -Wno-write-strings ExmMulThread3.cpp -lpthread -o ExmMulThread3.o
$ ./ExmMulThread3.o
运行结果：
main() : creating thread, 0
main() : creating thread, 1
Thread ID : 0 Message : This is message
main() : creating thread, Thread ID : 21
 Message : This is message
main() : creating thread, 3
Thread ID : 2 Message : This is message
main() : creating thread, 4
Thread ID : 3 Message : This is message
Thread ID : 4 Message : This is message

*/
