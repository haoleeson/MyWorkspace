/*逻辑与 &&
&& 会先判断左边的值是否为真。
如果为假，那么整个表达式毫无疑问也为假。
如果为真，那就还需要判断右值，才能知道整个式子的值。
这个时候判断左值的过程就起了一个if的作用，可以利用这个过程判断左边表达式是否为真。
下面代码：
不用任何循环语句，不用if，来实现1+2+3+...+10的值*/
#include <iostream>
using namespace std;
int add(int c)
{
    int a=0;
    c&&(a=add(c-1));//递归循环，直到传入c的值为0则结束循环
    cout<<c+a<<endl;
    return c+a;
}
int main(void)
{ 
    add(10);
    return 0;
}
