layout: post
title: 函数指针 & 指针函数
date: 2018/10/09 11:30:30
updated: 2018/10/10 22:55:45
comments: true
tags:
- C++
categories:
- 技术

---
<img src="../../../../uploads/pointerFunction.jpg" class="full-image" />

# 1. 指针函数

```c++
int* fun(char ch);//指针函数
```
指针函数，即返回值为指针地址的函数。实质仍为函数，与普通函数的差异仅在于返回值比较特殊，为一个指针地址（当然需要告知编译器一个特定的类型处理数据类型）。
<!-- more -->
## 1.1. 指针函数实例1： 返回值为基本类型
函数实现：大小写互转。将传入字符串内所有小写字母转换为大写字母，所有大写字母转换为小写字母
```c++
#include <iostream>
using namespace std;

char* Cover (char* const Ptr ) {
    char* p = Ptr;
    char ch = *p ;
    while( ch != '\0' ) {
        if( ch >= 'a' && ch <= 'z' ) {
            *p -= 32;
        } else if ( ch >= 'A' && ch <= 'Z' ) {
            *p += 32;
        } else {}
        ch = *(++p);
    }
    return Ptr;
}

int main(void) {
    char str[15] = {"Hello World!"};
    cout << "Previous: " << str << endl;
    cout << "Aftet: " << Cover(str) << endl;
    return 0;
}
```

## 1.2. 指针函数实例2：返回值为结构体

函数实现：获取并返回注册信息结构体。获取用户信息并返回包含用户名、用户密码的结构体。

```c++
#include <iostream>
#include <string>
using namespace std;

struct UserMessage {
    string userName;
    string userPassword;
};

void showUser ( struct UserMessage* user ) {
    if ( user == NULL ) {
        cout << "Error: register failed!" << endl;
    } else {
        cout << "Success: register success:)" << endl;
        cout << "User: " << user->userName << endl << "Psw: " << user->userPassword << endl;
    }
}

struct UserMessage* Register ( void ) {
    string str0, str1, str2;
    cout << endl << "Please input UserName:";
    cin >> str0;
    cout << endl << "Please input Password:";
    cin >> str1;
    cout << endl << "Please input Password again:";
    cin >> str2;
    if ( str1.compare(str2) == 0 ) {
        //(string)(user->userName) = str0; //Doesn't work
        //(string)(user->userPassword) = str1; //Doesn't work
        struct UserMessage* user = new UserMessage;
        *user = { str0, str1 };
        return user;
    }
    return NULL;
}

int main(void) {
    struct UserMessage* Test = Register();
    showUser(Test);
    return 0;
}
```

<img src="../../../../uploads/functionPointer.jpg" class="full-image" />
# 2. 函数指针
```c++
int (*fun)(char ch);//函数指针
```
函数指针，即指针地址指向一个函数入口地址的指针。实质任为指针。我们可以通过改变这个指针的不同地址调用同型的不同函数。

## 2.1. 函数指针实例1： 通过一个指针调用同型的不同函数

代码实现：通过改变一个指针地址的赋值，以调用同型的不同函数

```c++
#include <iostream>
using namespace std;

int ShowOnce (string str) {
    cout << "No.1 " << str << endl;
    cout << endl;
    return 0;
}
int ShowTwice (string str) {
    for (int i=1; i<=2; i++) {
        cout << "No." << i << " " << str <<endl;
    }
    cout << endl;
}
int ShowThrice (string str) {
    for (int i=1; i<=3; i++) {
        cout << "No." << i << " " << str <<endl;
    }
    cout << endl;
}

int main (void) {
    int (*fun)(string);//函数指针定义
    fun = ShowOnce;
    (*fun)("ShowOnce");//通过函数指针调用 函数1

    fun = ShowTwice;
    (*fun)("ShowTwice");//通过函数指针调用 函数2

    fun = ShowThrice;
    (*fun)("ShowThrice");//通过函数指针调用 函数3
    return 0;
}
```

## 2.2. 函数指针实例2： 通过一个指针调用同型的不同函数2

代码实现：通过改变一个指针地址的赋值，以调用同型的不同函数，与实例1区别在多个形参，需特别注意函数指针形参类型必须与调用的函数形参类型一致

```c++
#include <iostream>
#include <iomanip>
using namespace std;
double Add (double num1, double num2) {//加
    return (num1 + num2);
}
double Subtract (double num1, double num2) {//减
    return (num1 - num2);
}
double Multiply (double num1, double num2) {//乘
    return (num1 * num2);
}
double Divide (double num1, double num2) {//除
    return (num1 / num2);
}

int main (void) {
    double (*fun)(double, double);//函数指针定义
    cout << "Test (*fun)(5,3) :" << endl <<endl;
    fun = Add;
    cout << setw(10) << "Add: " << (*fun)(5,3) << endl;
    fun = Subtract;
    cout << setw(10) << "Subtract: " << (*fun)(5,3) << endl;
    fun = Multiply;
    cout << setw(10) << "Multiply: " << (*fun)(5,3) << endl;
    fun = Divide;
    cout << setw(10) << "Divide: " << (*fun)(5,3) << endl;
    return 0;
}
```

## 2.3. 函数指针高级应用：通过函数指针测试不同函数的运行时间（函数指针作为形参）

代码实现：通过形参传入一个函数指针，可在函数体内调用该函数指针形参指向的函数，以测试不同函数的运行时间

```c++
#include <iostream>
#include <time.h>
#include <math.h>
using namespace std;

#define MAXN 10   //多项式最大项数(9阶)
#define Fun_x 1.1 //多项式x的值
#define MAXK 1e3  //被测函数最大重复调用次数
double a[MAXN];   //多项式系数
double Function1(void);
double Function2(void);
void showFunctionUsingTime (double (*fun)(void)); // *******函数指针作为形参 *******

int main (void) {
    for (int i=0; i<MAXN; i++) { //赋值项系数
        a[i] = (double)i;
    }
    //计算Function1用时
    showFunctionUsingTime(Function1);
    //计算Function2用时
    showFunctionUsingTime(Function2);
    return 0;
}
double Function1 (void) {
    double p = a[0];
    for (int i=1; i<=(MAXN-1); i++) {
        p += (a[i] * pow(Fun_x, i));
    }
    return p;
}
double Function2 (void) {
    double p = a[MAXN-1];
    for (int i=(MAXN-1); i>0; i--) {
        p = a[i-1] + Fun_x * p;
    }
    return p;
}
void showFunctionUsingTime (double (*fun)(void)) {
    clock_t start, stop;
    double duration; //运行时间　变量
    //计算Function1用时
    start = clock();//记录时钟此刻打点数
    for (int i=0; i<MAXK ;i++) { //重复调用多次函数
        (*fun)();
    }
    stop = clock();//记录始终此时打点数
    duration = ((double)(stop - start))/CLOCKS_PER_SEC/MAXK;//计算实际用时
    cout << "Ticks = " << (double)(stop - start) << endl;
    cout << "Using time = " << duration << " s" << endl;
}
```
