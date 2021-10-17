/*
raise() 函数
您可以使用函数 raise() 生成信号，该函数带有一个整数信号编号作为参数，语法如下：
int raise (signal sig);
在这里，sig 是要发送的信号的编号，这些信号包括：SIGINT、SIGABRT、SIGFPE、SIGILL、SIGSEGV、SIGTERM、SIGHUP。以下是我们使用 raise() 函数内部生成信号的实例：
*/
#include <iostream>
#include <csignal>
#include <unistd.h>
using namespace std;
void signalHandler( int signum ) {
    cout << "Interrupt signal (" << signum << ") received.\n";
    // 清理并关闭
    // 终止程序
    exit(signum);
}
int main (void) {
    int i = 0;
    // 注册信号 SIGINT 和信号处理程序
    signal(SIGINT, signalHandler);
    while (++i) {
        cout << "Going to sleep...." << endl;
        if( i == 3 ){
            raise( SIGINT);
        }
        sleep(1);
    }
    return 0;
}
/*
当上面的代码被编译和执行时，它会产生下列结果，并会自动退出：
Going to sleep....
Going to sleep....
Going to sleep....
Interrupt signal (2) received.
*/
