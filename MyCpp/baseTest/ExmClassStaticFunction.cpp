/*
静态成员函数与普通成员函数的区别：
静态成员函数没有 this 指针，只能访问静态成员（包括静态成员变量和静态成员函数）。
普通成员函数有 this 指针，可以访问类中的任意成员；而静态成员函数没有 this 指针。
 */
#include <iostream>
using namespace std;
class Box {
    public:
        static int objectCount;
        // 构造函数定义
        Box(double l=2.0, double b=2.0, double h=2.0) {
         cout <<"Constructor called." << endl;
         length = l;
         breadth = b;
         height = h;
         // 每次创建对象时增加 1
         objectCount++;
        }
        double Volume(void) {
            return length * breadth * height;
        }
        static int getCount(void) {
            return objectCount;
        }
    private:
        double length;     // 长度
        double breadth;    // 宽度
        double height;     // 高度
};
// 初始化类 Box 的静态成员
int Box::objectCount = 0;
int main(void) {
    // 在创建对象之前输出对象的总数
    cout << "Inital Stage Count: " << Box::getCount() << endl;
    Box Box1(3.3, 1.2, 1.5);    // 声明 box1
    Box Box2(8.5, 6.0, 2.0);    // 声明 box2
    // 在创建对象之后输出对象的总数
    cout << "Final Stage Count: " << Box::getCount() << endl;
    return 0;
}
