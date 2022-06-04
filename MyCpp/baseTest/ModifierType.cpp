#include <iostream>
using namespace std;
 
/* 
 * 这个程序演示了有符号整数和无符号整数之间的差别
*/
int main()
{
   short int i;           // 有符号短整数
   short unsigned int j;  // 无符号短整数
 
   j = 50000;
 
   i = j;
   cout << i << " " << j;
 
   return 0;
}

/*
 *笔记
const	const 类型的对象在程序执行期间不能被修改改变。
volatile	修饰符 volatile 告诉编译器，变量的值可能以程序未明确指定的方式被改变。
restrict	由 restrict 修饰的指针是唯一一种访问它所指向的对象的方式。只有 C99 增加了新的类型限定符 restrict。 
 */
