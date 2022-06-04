#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
using namespace std;
#define NUM_THREADS 5
void *wait(void *t) {
    int i;
    long tid;
    tid = (long)t;
    sleep(1);
    cout << "Sleeping in thread " << endl;
    cout << "Thread with id : " << tid << "  ...exiting " << endl;
    pthread_exit(NULL);
}
int main (void) {
    int rc;
    int i;
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
    void *status;
    // 初始化并设置线程为可连接的（joinable）
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    for( i=0; i < NUM_THREADS; i++ ) {
        cout << "main() : creating thread, " << i << endl;
        rc = pthread_create(&threads[i], NULL, wait, (void *)&i );
        if (rc) {
            cout << "Error:unable to create thread," << rc << endl;
            exit(-1);
        }
    }
    // 删除属性，并等待其他线程
    pthread_attr_destroy(&attr);
    for( i=0; i < NUM_THREADS; i++ ) {
        rc = pthread_join(threads[i], &status);
        if (rc) {//创建失败
            cout << "Error:unable to join," << rc << endl;
            exit(-1);
        }
        cout << "Main: completed thread id :" << i ;
        cout << "  exiting with status :" << status << endl;
    }
    cout << "Main: program exiting." << endl;
    pthread_exit(NULL);
    return 0;
}
/*
g++ -Wno-write-strings ExmMulThread_JoinDetach.cpp -lpthread -o ExmMulThread_JoinDetach.o
./ExmMulThread_JoinDetach.o
运行结果：
main() : creating thread, 0
main() : creating thread, 1
main() : creating thread, 2
main() : creating thread, 3
main() : creating thread, 4
Sleeping in thread 
Thread with id : 4  ...exiting 
Sleeping in thread 
Thread with id : 3  ...exiting 
Sleeping in thread 
Thread with id : 2  ...exiting 
Sleeping in thread 
Thread with id : 1  ...exiting 
Sleeping in thread 
Thread with id : 0  ...exiting 
Main: completed thread id :0  exiting with status :0
Main: completed thread id :1  exiting with status :0
Main: completed thread id :2  exiting with status :0
Main: completed thread id :3  exiting with status :0
Main: completed thread id :4  exiting with status :0
Main: program exiting.
*/
