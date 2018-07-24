#include <iostream>
#include <thread>
std::thread::id main_thread_id = std::this_thread::get_id();
void hello(void) {
    std::cout << "Hello Concurrent World\n";
    if (main_thread_id == std::this_thread::get_id()) {
        std::cout << "This is the main thread.\n";
    } else {
        std::cout << "This is not the main thread.\n";
    }
}
void pause_thread(int n) {
    std::this_thread::sleep_for(std::chrono::seconds(n));
    std::cout << "pause of " << n << " seconds ended\n";
}
int main(void) {
    std::thread t(hello);
    std::cout << t.hardware_concurrency() << std::endl;//可以并发执行多少个(不准确)
    std::cout << "native_handle " << t.native_handle() << std::endl;//可以并发执行多少个(不准确)
    t.join();
    std::thread a(hello);
    a.detach();
    std::thread threads[5];                         // 默认构造线程
    std::cout << "Spawning 5 threads...\n";
    for (int i = 0; i < 5; ++i) {
        threads[i] = std::thread(pause_thread, i + 1);   // move-assign threads
    }
    std::cout << "Done spawning threads. Now waiting for them to join:\n";
    for (auto &thread : threads) {
        thread.join();
    }
    std::cout << "All threads joined!\n";
    return 0;
}
/*
g++ -std=c++11 ExmMulThread4.cpp -lpthread -o ExmMulThread4.o
./ExmMulThread4.o
运行结果：
Hello Concurrent World
This is not the main thread.
8
native_handle 140044929611520
Spawning 5 threads...
Hello Concurrent World
This is not the main thread.
Done spawning threads. Now waiting for them to join:
pause of 1 seconds ended
pause of 2 seconds ended
pause of 3 seconds ended
pause of 4 seconds ended
pause of 5 seconds ended
All threads joined!
*/
