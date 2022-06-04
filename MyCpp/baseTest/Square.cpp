#include <iostream>

using namespace std;

/***************************
 * 函数功能: 计算裁剪的相同大小的正方形
 * return: void
 * @para m: 长方形的长
 * @para n: 长方形的宽
 * @para j: 存放输出正方形边长最大值
 * @para k: 存放输出正方形个数
***************************/
void Square(int m, int n, int &j, int &k)
{
	/********** BEGIN **********/

    int smaller = (m < n) ? m : n;
    while((m%smaller != 0) || (n%smaller) != 0)
    {
        smaller--;
    }
    j = smaller;
    k = m * n / j / j;
    
	/********** END **********/
}
int main(void)
{
    int j=0,  k=0;
    Square(4, 2, j, k);
    cout << j << " " << k;
}
