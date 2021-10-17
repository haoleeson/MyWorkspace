#include <iostream>
using namespace std;
int func(int &x){//函数func将引用当作形参
    x=3;
    return 0;
} 
int main (void){
    int a=1;//声明整型变量
    func(a);////给函数func传参
    cout<<"a的值为: "<<a<<endl;//输出a的值，结果为“a的值为3”
    return 0;
}
