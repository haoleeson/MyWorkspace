/*&& 会先判断左边的值是否为真。

如果为假，那么整个表达式毫无疑问也为假。

如果为真，那就还需要判断右值，才能知道整个式子的值。

这个时候判断右值的过程就起了一个if的作用，可以利用这个过程判断右边表达式是否为真。

下面代码：

不用任何循环语句，不用if，来实现1+2+3+...+10的值

*/

#include <iostream>
using namespace std;

int add(int num)
{
    int sum=0;
    num&&(sum=add(num-1));//递归循环，直到传入c的值为0则结束循环
    return num+sum;
}
int main(void)
{
    int a = -5;
    unsigned int b = 1;
    cout<<"int(-5)   > unsigned int(1)   = "<<(a>b)<<endl;   //输出1，非常有趣的结果 原因是int型的i转换为unsigned int型
    short c = -5;
    unsigned short d = 1;
    cout<<"short(-5) > unsigned short(1) = "<<(c>d)<<endl;  //输出0 比较时short和unsigned short都提升为int型  
    cout<<"1+2+...+10="<<add(10)<<endl;
    return 0;
}


/*
 *
逻辑或 ||

其实与上面的逻辑与 && 大同小异。

都是先判断左边是否为真，再来考虑右边。

因为逻辑与 || 只需要左边为真，那么整个表达式就有值，就不会再去算右边的值了。

所以我们加个 ! 让 c 值为假时，!c 才为真，这样的话逻辑与 || 还需要判断右边的表达式才能计算出整个表达式的值。

(!c)||(a=add(c-1));
这样就达到了和用逻辑与&&时一样的目的。

代码：

不用任何循环语句，不用if，来实现1+2+3+...+10的值


#include <iostream>
using namespace std;

int add(int c)
{
    int a=0;
    (!c)||(a=add(c-1));//递归循环，直到传入c的值为0，(!c)就为真，结束循环
    cout<<c+a<<endl;
    return c+a;
}
int main(void)
{ 
    add(10);
    return 0;
}


*/
