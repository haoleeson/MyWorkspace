#include <iostream>
#include <iomanip>
using namespace std;
int main(void)
{
    cout << setw(10) << setiosflags(ios::left) <<setfill('*') << 10 << endl;
    cout << setw(10) << setiosflags(ios::right) <<setfill('*') << 10 << endl;
    cout << setw(10) << setfill('*') << 10 << endl;
    //使用以下这种形式来调用显得更加整齐并简洁 
    int a=10,b=20;
    cout.setf(ios::right,ios::adjustfield);cout.fill('0');cout << setw(5) << a <<endl;cout << setw(5) << b << endl;
}

//输出结果
//10********
//********10
//********10
//00010
//00020
//
//real	0m0.002s
//user	0m0.002s
//sys	0m0.000s
