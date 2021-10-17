#include <iostream>
#include<stdio.h>
#include<time.h>
#define random(x)(rand()%x)  //宏定义中顶一个random（int number）函数：
using namespace std;
int main(void)
{
    srand((int)time(0));//部署随机种子
    for (int i = 0; i < 10; i++){
        cout << random(100) << endl;
        //输出0-100的随机数
    };
    return 0;
}
