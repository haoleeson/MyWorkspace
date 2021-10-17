/*模板函数定义的一般形式如下所示：
template <class type> ret-type func-name(parameter list)
{
    // 函数的主体
}
*/
#include <iostream>
#include <string>
using namespace std;
template <typename T>
inline T const& Max (T const& a, T const& b) {
    return a < b ? b:a;
}
int main (void) {
    int i = 39;
    int j = 20;
    cout << "Max(i, j): " << Max(i, j) << endl;
    double f1 = 13.5;
    double f2 = 20.7;
    cout << "Max(f1, f2): " << Max(f1, f2) << endl;
    string s1 = "Hello";
    string s2 = "World";
    cout << "Max(s1, s2): " << Max(s1, s2) << endl;
    return 0;
}
/*
运行结果:
请按 ENTER 或其它命令继续
Max(i, j): 39
Max(f1, f2): 20.7
Max(s1, s2): World
*/
