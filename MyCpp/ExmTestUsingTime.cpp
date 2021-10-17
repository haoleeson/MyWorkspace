#include <iostream>
#include <time.h>
#include <math.h>
using namespace std;

#define MAXN 10  //多项式最大项数(9阶)
#define MAXK 1e7 //被测函数最大重复调用次数
clock_t start, stop;
double duration; //运行时间　变量
double Function1(int n, double a[], double x);
double Function2(int n, double a[], double x);

int main (void) {
    double a[MAXN];
    for (int i=0; i<MAXN; i++) { //赋值项系数
        a[i] = (double)i;
    }
    //计算Function1用时
    start = clock();//记录时钟此刻打点数
    for (int i=0; i<MAXK ;i++) { //重复调用多次函数
        Function1(MAXN-1, a, 1.1);
    }
    stop = clock();//记录始终此时打点数
    duration = ((double)(stop - start))/CLOCKS_PER_SEC/MAXK;//计算实际用时
    cout << "Ticks1 = " << (double)(stop - start) << endl;
    cout << "Using time = " << duration << " s" << endl;
    //计算Function2用时
    start = clock();//记录时钟此刻打点数
    for (int i=0; i<MAXK ;i++) { //重复调用多次函数
        Function2(MAXN-1, a, 1.1);
    }
    stop = clock();//记录始终此时打点数
    duration = ((double)(stop - start))/CLOCKS_PER_SEC/MAXK;//计算实际用时
    cout << "Ticks2 = " << (double)(stop - start) << endl;
    cout << "Using time = " << duration << " s" << endl;

    return 0;
}
double Function1(int n, double a[], double x) {
    double p = a[0];
    for (int i=1; i<=n; i++) {
        p += (a[i] * pow(x, i));
    }
    return p;
}
double Function2(int n, double a[], double x) {
    double p = a[n];
    for (int i=n; i>0; i--) {
        p = a[i-1] + x*p;
    }
    return p;
}
/*
运行结果：
Ticks1 = 5.01585e+06
Using time = 5.01585e-07 s
Ticks2 = 284705
Using time = 2.84705e-08 s
可以看到Function2的用时比Function1少了一个＂数量级＂
*/
