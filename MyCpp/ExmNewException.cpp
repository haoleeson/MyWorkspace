#include <iostream>
#include <exception>
using namespace std;
//继承exception结构体，自定义异常
struct MyException : public exception {
    const char * what () const throw () {
        return "C++ Exception";
    }
};
int main(void) {
    try {
        throw MyException(); //抛出自定义异常
    } catch (MyException& e) {
        std::cout << "MyException caught" << std::endl;
        std::cout << e.what() << std::endl;
    } catch (std::exception& e) {
        //其他的错误
    }
}
