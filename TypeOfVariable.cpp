#include <iostream>
using namespace std;
// 变量声明
extern short a,b,c;
extern float f;
short funInit(void);
int main (void)
{
    // 变量定义
    short a,b,c;
    float f;
    // 实际初始化
    c = funInit();
    a = 10;
    b = 20;
    c = a + b;
    cout << c << endl ;
    f = 70.0/3.0;
    cout << f << endl ;
    return 0;
}

short funInit(void){
    return 0;
}
