#include <iostream>
#include <time.h>
#include <math.h>
using namespace std;

#define MAXN 10   //多项式最大项数(9阶)
#define Fun_x 1.1 //多项式x的值
#define MAXK 1e3  //被测函数最大重复调用次数
double a[MAXN];   //多项式系数
double Function1(void);
double Function2(void);
void showFunctionUsingTime(double (*fun)(void));

int main (void) {
    for (int i=0; i<MAXN; i++) { //赋值项系数
        a[i] = (double)i;
    }
    //计算Function1用时
    showFunctionUsingTime(Function1);
    //计算Function2用时
    showFunctionUsingTime(Function2);
    return 0;
}
double Function1(void) {
    double p = a[0];
    for (int i=1; i<=(MAXN-1); i++) {
        p += (a[i] * pow(Fun_x, i));
    }
    return p;
}
double Function2(void) {
    double p = a[MAXN-1];
    for (int i=(MAXN-1); i>0; i--) {
        p = a[i-1] + Fun_x * p;
    }
    return p;
}
void showFunctionUsingTime(double (*fun)(void)) {
    clock_t start, stop;
    double duration; //运行时间　变量
    //计算Function1用时
    start = clock();//记录时钟此刻打点数
    for (int i=0; i<MAXK ;i++) { //重复调用多次函数
        (*fun)();
    }
    stop = clock();//记录始终此时打点数
    duration = ((double)(stop - start))/CLOCKS_PER_SEC/MAXK;//计算实际用时
    cout << "Ticks = " << (double)(stop - start) << endl;
    cout << "Using time = " << duration << " s" << endl;
}
/*
运行结果：
Ticks1 = 5.01585e+06
Using time = 5.01585e-07 s
Ticks2 = 284705
Using time = 2.84705e-08 s
可以看到Function2的用时比Function1少了一个＂数量级＂
*/

