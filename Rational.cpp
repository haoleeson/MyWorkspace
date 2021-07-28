//OOT第2次作业-EisenHao
#include "Rational.h" //有理数类定义

int main(void)
{
    Rational num1(1, 3), num2(3, 1), num3(2, 6);
    Rational result;
    //求和
    result = num1 + num2;
    printf("%s + %s = %s\n", num1.value(), num2.value(), result.value());
    //求积
    result = num1 * num2;
    printf("%s * %s = %s\n", num1.value(), num2.value(), result.value());
    //判等num1， num2
    printf("%s is%s equal to %s\n", num1.value(), (num1 == num2)?"":" not", num2.value());
    //判等num1， num3
    printf("%s is%s equal to %s\n", num1.value(), (num1 == num3)?"":" not", num3.value());
    return 0;
}
