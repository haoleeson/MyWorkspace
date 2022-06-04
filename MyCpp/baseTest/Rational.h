//OOT第2次作业-EisenHao
#ifndef RATIONAL_H_
#define RATIONAL_H_
#include <stdio.h> //printf(), sprintf()函数

//有理数类
class Rational
{
    private:
        int Numerator;//分子
        int Denominator;//分母
        char* showBuff = NULL;//用于存储value()函数中 new 的首地址，方便析构时删除value()函数可能申请的char空间
    public:
        Rational();//构造函数1（过载多态）
        Rational(int a, int b);//构造函数2（过载多态）
        ~Rational();//析构函数，删除value()函数可能申请的char空间
        char* value();//返回表示当前有理数的字符串首char地址
        //重载操作符 =
        Rational& operator=(const Rational& num);
        //重载操作符 +
        Rational operator+(const Rational& num);
        //重载操作符 *
        Rational operator*(const Rational& num);
        //重载操作符 ==
        bool operator==(const Rational& num);
};

//构造函数1（过载多态）
Rational::Rational()
{
    //无参数时默认赋值为 0/1
    Numerator = 0; //分子
    Denominator = 1; //分母
}
//构造函数2（过载多态）
Rational::Rational(int a, int b)
{
    Numerator = a; //分子
    Denominator = b; //分母
}
//析构函数，删除value()函数可能申请的char空间
Rational::~Rational()
{
    if(showBuff != NULL) //若调用过value() --> 删除申请空间
    {
        delete []showBuff;//删除value()函数申请的char空间
        showBuff = NULL;//指针赋NULL
    }
}
//返回表示当前有理数的字符串首char地址
char* Rational::value()
{
    //非首次调用value() --> 先删除上一次申请的空间
    if(showBuff != NULL)
    {
        delete []showBuff;//删除上一次调用value()函数申请的char空间，因为值可能变化
        showBuff = NULL;//指针赋NULL
    }
    showBuff = new char[10]();//申请字符串空间，在析构函数中释放
    sprintf(showBuff, "%d/%d", Numerator, Denominator);
    return showBuff;
}
//重载操作符 =
Rational& Rational::operator=(const Rational& num)
{
    this->Numerator = num.Numerator;
    this->Denominator = num.Denominator;
    return *this;
}
//重载操作符 +
Rational Rational::operator+ (const Rational& num)
{
    Rational sum;//和
    sum.Numerator = this->Numerator * num.Denominator + num.Numerator * this->Denominator;//分子交叉相乘后求和
    sum.Denominator = this->Denominator * num.Denominator;//分母相乘
    return sum;
}
//重载操作符 *
Rational Rational::operator* (const Rational& num)
{
    Rational product;//积
    product.Numerator = this->Numerator * num.Numerator;//分子相乘
    product.Denominator = this->Denominator * num.Denominator;//分母相乘
    return product;
}
//重载操作符 ==
bool Rational::operator== (const Rational& num)
{
    float a = (float)this->Numerator / (float)this->Denominator;
    float b = (float)num.Numerator / num.Denominator;
    if (a == b) //是否相等
    {
        return true;
    }
    return false;
}

#endif
