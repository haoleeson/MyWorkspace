#include<iostream>
using namespace std;
class A {
    public:
        A(void);
        A(int n);
        A operator+(const A & obj);
        A operator+(const int b);
        friend A operator+(const int b, A obj); 
        void display(void); 
    private:
        int a;
};
//成員函數定義
A::A(void) {
    a = 0;
}
A::A(int n) { //构造函数
    a = n;
}
A A::operator +(const A& obj) { //重载+号用于 对象相加
    return this->a + obj.a;
}
A A::operator+(const int b) { //重载+号用于  对象与数相加
    return A(a + b);
}
A operator+(const int b,  A obj) {
    return obj + b;//友元函数调用第二个重载+的成员函数  相当于 obj.operator+(b); 
}
void A::display(void) {
    cout<<a<<endl;
}
    int main(void) {
    A a1(1);
    A a2(2);
    A a3,a4,a5;
    cout<<"A a1(1)  ,a1=";
    a1.display();
    cout<<"A a2(2)  ,a2=";
    a2.display();
    int m = 1;
    a3 = a1 + a2;//可以交换顺序，相当月a3=a1.operator+(a2); 
    cout<<"a3 = a1 + a2  ,a3=";
    a3.display();
    a4 = a1 + m;//因为加了个友元函数所以也可以交换顺序了。
    cout<<"a4 = a1 + 1  ,a4=";
    a4.display();
    a5 = m + a1;
    cout<<"a5 = 1 + a1  ,a5=";
    a5.display();
}
