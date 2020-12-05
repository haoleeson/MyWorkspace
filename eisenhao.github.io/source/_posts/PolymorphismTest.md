layout: post
title: C++中的四种多态
date: 2018/10/14 19:30:44
updated: 2018/10/16 23:06:45
comments: true
tags:
- C++
categories:
- 技术

---
<img src="https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/PolymorphismTest.jpg" class="full-image" />
# 程序中多态存在的意义:
* 使程序中的数学运算符合常规的数学运算规则,使程序提供更强的表达能力;
* 使得对不同类型的数据有同样的操作语义(程序的重用);
* 重用标识的资源,提高程序的可读性和可理解性。
<!-- more -->
# 程序中多态的种类:
在程序中多态分为：通用的多态(universal)及特定的多态。其中通用多态包含：参数多态(parametric)和包含多态(inclusion)，特点是对数据类型不加限制;允许对不同类型的值执行相同的代码。特定的多态包含：过载多态(overloading)和强制多态(coercion)，特点是只对有限数量的类型有效、对不同类型的值可能要执行不同的代码。
## 参数多态(Parametric polymorphism)
概念:采用参数化模板,通过给出不同的类型实参,使得一个程序结构有多种类型。例如：Ada中的generic(类属)、C++中的template(模板)，二者均支持数据类型和函数的参数多态。从C++的template 结构可以看出:对实参所取的类型不加限制;不同的实参执行的是相同的代码。所以参数多态是一种通用多态。模板的特点有:在一个抽象结构中允许以参数形式来表示可变部分--包括：类型、函数、常数;在编译时(静态)才进行实例化，结果是一个具体的结构(类型、函数等)。对比:类型的实例化(类型→变量)可以静态进行,也可以动态进行,但结果都是一个值。

如以下代码，在.h文件中定义模板类shape时，将类中的变量类型暂时用"T"代替

```c++
/**参数多态**/
template<class T>
//基类：图形
class shape
{
    protected:
        T bottomLength; //底边长
        T height; //高
};
```
然后在.cpp文件中实例化该shape类时再指定变量的类型。如以下代码实例化该shape时分别指定类中的成员变量bottomLength、height的类型为int、double
```c++
/**参数多态**/
shape<int> shape1();
shape<double > shape2();
```
## 包含多态(inclusion polymorphism)
概念：同样的操作可用于一个(基)类型及其派生类型。
```c++
template<class T>
//基类：图形
class shape
{
    public:
        //求图形面积
        virtual T getArea()
        {
            return (bottomLength * height);
        }
    protected:
        T bottomLength; //底边长
        T height; //高
};

template<class T>
//派生：平行四边形类
class Parallelogram : public shape<T>
{
    public:
        /**包含多态，可直接调用基类的getArea()方法**/
};

template<class T>
//派生：矩形类
class Rectangle : public shape<T>
{
    public:
        /**包含多态，可直接调用基类的getArea()方法**/
};
```
## 重置
类比与之相似的“重置”。如C++中在基类定义的virsual方法，在派生类中再进行不同实现。如以下代码，在.h文件中从基类shape派生了两个子类：Triangle和Rectangle，两个子类中对父类的同一方法getArea()进行了两种不同的再实现，此为C++中的另一种形式的多态（重置）
```c++
template<class T>
//基类：图形
class shape
{
    public:
        //求图形面积
        virtual T getArea()
        {
            return (bottomLength * height);
        }
    protected:
        T bottomLength; //底边长
        T height; //高
};
template<class T>
//派生：三角形类
class Triangle : public shape<T>
{
    public:
        /**包含多态**/
        T getArea()
        {
            return (this->bottomLength * this->height / 2);
        }
};

template<class T>
//派生：矩形类
class Rectangle : public shape<T>
{
    public:
        /**包含多态**/
        T getArea()
        {
            return (this->bottomLength * this->height);
        }
};
```
## 过载多态(overloading polymorphism)
概念:同一个表示操作的名字(如操作符、函数名)在不同的上下文中有不同的类型。(相同抽象,不同细节)。程序设计语言中基本类型的多数操作符都是过载多态的。如：一个过载多态的操作符或函数名,它通常对应多个不同的实现。
如以下代码在定义shape类中，有两个shape()构造函数，仅形参不同
```c++
template<class T>
//基类：图形
class shape
{
    protected:
        T bottomLength; //底边长
        T height; //高
    public:
        /**过载多态：不带参数**/
        shape()
        {
            bottomLength = 0;
            height = 0;
        }
        /**过载多态：带2个参数**/
        shape(T value1, T value2)
        {
            bottomLength = value1;
            height = value2;
        }
};
```
## 强制多态(coercion)
概念:通过语义操作,把操作数的类型强行加以变换,以符合操作符或函数的要求。程序设计语言中基本类型的大多数操作符,在发生不同类型的数据进行混合运算时,编译程序一般都会进行强制类型转换(强制多态)。这种强制转换通常是隐式的,但程序员也可以显式地进行强制多态的操作(Casting)。
```c++
/**强制多态**/
    int a=3, b=2;
    double c;
    c = a + b; //隐式强制多态 将int类型的a,b转换为double
```
# 尝试构建一个同时包含四种多态的范例
构造了一个基于C++的包含参数多态、包含多态、过载多态和强制多态的范例, 其中参数多态用模板展现。
## .h文件完整代码如下：
```c++ 文件名: PolymorphismTest.h
#ifndef POLYMORPHISMTEST_H_
#define POLYMORPHISMTEST_H_

/**参数多态**/
template<class T>
//基类：图形
class shape
{
    protected:
        T bottomLength; //底边长
        T height; //高
    public:
        /**过载多态：不带参数**/
        shape()
        {
            bottomLength = 0;
            height = 0;
        }
        /**过载多态：带1个参数**/
        shape(T value)
        {
            bottomLength = value;
            height = value;
        }
        /**过载多态：带2个参数**/
        shape(T value1, T value2)
        {
            bottomLength = value1;
            height = value2;
        }
        //求图形面积
        virtual T getArea()
        {
            return (bottomLength * height);
        }
};

/**参数多态**/
template<class T>
//派生：三角形类
class Triangle : public shape<T>
{
    public:
        /**重置**/
        T getArea()
        {
            return (this->bottomLength * this->height / 2);
        }
        Triangle(T value1, T value2)
        {
            this->bottomLength = value1;
            this->height = value2;
        }
};

template<class T>
//派生：平行四边形类
class Parallelogram : public shape<T>
{
    public:
        /**包含多态，可直接调用基类的getArea()方法**/
        Parallelogram(T value1, T value2)
        {
        	this->bottomLength = value1;
            this->height = value2;
        }
};

/**参数多态**/
template<class T>
//派生：矩形类
class Rectangle : public shape<T>
{
    public:
        /**重置**/
        T getArea()
        {
            return (this->bottomLength * this->height);
        }
        Rectangle(T value1, T value2)
        {
            this->bottomLength = value1;
            this->height = value2;
        }
};

#endif

```

## .cpp文件完整代码如下：

```c++ 文件名: PolymorphismTest.cpp
#include <iostream>
#include "PolymorphismTest.h"

using namespace std;

int main(void)
{

    /**参数多态**/
    shape<int> shape1();
    shape<double > shape2();

    /**过载多态**/
    shape<double> shape3();
    shape<double> shape4(3.2, 5.7);

    /**包含多态**/
    shape<double> shape5(4, 5);
    Parallelogram<double> parallelogram(4, 5);
    shape5.getArea();
    parallelogram.getArea();
    
    /**重置**/
    int a, b;
    Rectangle<int> rectangle1(4, 4);
    Triangle<int> triangle1(4, 4);
    a = rectangle1.getArea();
    b = triangle1.getArea();

    /**强制多态**/
    double c;
    c = a + b; //隐式强制多态 将int类型a,b转换为double
    cout << c << endl;

    return 0;
}

```
