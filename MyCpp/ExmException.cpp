#include <iostream>
using namespace std;
double division(int a, int b) {
    if ( b == 0 ) { //当被除数b 为0时抛出一个异常 "Division by zero condition!"
        throw "Division by zero condition!";
    }
    return (a/b);
}
int main (void) {
    int x = 50;
    int y = 0;
    double z = 0;
    try {
        z = division(x, y);
        cout << z << endl;
    } catch (const char* msg) { //捕获信息异常。若是捕获任意异常catch(...){  }
        cerr << msg << endl;
    }
    return 0;
}
