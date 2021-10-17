#include <iostream>
#include <string>
using namespace std;

/*
char str[20]="0123456789";
int a=strlen(str); // a=10;
int b=sizeof(str); // 而 b=20;

char str[20]="0123456789";
int a=strlen(str);         // a=10; >>>> strlen 计算字符串的长度，以结束符 0x00 为字符串结束。
int b=sizeof(str);         // 而 b=20; >>>> sizeof 计算的则是分配的数组 str[20] 所占的内存空间的大小，不受里面存储的内容改变。  

char* ss = "0123456789";
sizeof(ss) 结果 4 ＝＝＝》ss 是指向字符串常量的字符指针，sizeof 获得的是一个指针的之所占的空间,应该是长整型的，所以是 4。
sizeof(*ss) 结果 1 ＝＝＝》*ss 是第一个字符 其实就是获得了字符串的第一位 '0' 所占的内存空间，是 char 类型的，占了 1 位
strlen(ss)= 10      ＝＝＝》 如果要获得这个字符串的长度，则一定要使用 strlen。strlen 用来求字符串的长度；而 sizeof 是用来求指定变量或者变量类型等所占内存大小。

*/

int main(void)
{
    //定义一个string类对象
    string http = "www.runoob.com";
   //打印字符串长度
   cout<<http.length()<<endl;
    //拼接
    http.append("/C++");
    cout<<http<<endl; //打印结果为：www.runoob.com/C++
    //删除
    int pos = http.find("/C++"); //查找"C++"在字符串中的位置
    cout<<pos<<endl;
    http.replace(pos, 4, "");   //从位置pos开始，之后的4个字符替换为空，即删除
    cout<<http<<endl;
    //找子串runoob
    int first = http.find_first_of("."); //从头开始寻找字符'.'的位置
    int last = http.find_last_of(".");   //从尾开始寻找字符'.'的位置
    cout<<http.substr(first+1, last-first-1)<<endl; //提取"runoob"子串并打印
    return 0;
}
