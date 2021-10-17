/**
 * Encoding：utf-8
 * Programming language：c++
 * Coder：EisenHao
 * */
#include <iostream>
#include <vector>
using namespace std;

//宏定义
#define length 5 //矩阵元素个数
#define numOfMatrix length-1 //矩阵个数 = length - 1

//全局变量
//定义规模为：矩阵链的个数^2 的二维数组,并赋初值无穷大WuQiongDa
vector<vector<int>> m(numOfMatrix); //numOfMatrix 矩阵个数 = length - 1

/**
 * 计算第i到j段的最小计算次数
 * 返回值<int>：第i到j段的最小运算次数
* */
#define WuQiongDa 69999999
int LookUp_Chain(int p[], int i, int j)
{
    //备忘录：若已计算，则返回已计算值
    if (m[i-1][j-1] != WuQiongDa){
        return m[i-1][j-1];
    }
    //若没计算
    //a.过小只有两个矩阵
    if(j == i+1){
        return p[i-1] * p[i] * p[j];
    }
    //b.有可分性
    else {
        //计算从 k 处划分(k取值：i到j-1)，后的两边的值 + 两边相乘的值
        for (int k=i; k<=j-1; k++) {
            //中间值q
            int q = LookUp_Chain(p, i, k) + LookUp_Chain(p, k+1, j)
                    + p[i-1] * p[k] * p[j];
            //记录从k处划分的m[i][j]最小值
            if(q < m[i-1][j-1]){
                cout << "k = " <<  k << endl;
                m[i-1][j-1] = q;
            }
        }
        return m[i-1][j-1];
    }
}


/* *
 * 备忘录，矩阵链最小计算次数
 * 传入参数：矩阵链容器，存储顺序的矩阵相乘下标
 * 如：<3, 5, 2, 1, 10> 即为：(3, 5) x (5, 2) x (2, 1) x (1, 10)
 * */
int Memory_Matrix_Chain(int p[])
{
    int result = 0;
    for(int i=0; i<numOfMatrix; i++)
    {
        for(int j=0; j<numOfMatrix; j++)
        {
            if(i == j){
                m[i].push_back(0);
            }else{
                m[i].push_back(WuQiongDa);
            }
        }
    }
    result = LookUp_Chain(p, 1, numOfMatrix);//下标
    return result;
}

int main(void)
{
    int a[5] = {3, 5, 2, 1, 10};//答：55, 计算次序为：2，1，3
    int b[5] = {2, 7, 3, 6, 10};//答：198， 计算次序为：1，2，3
    int c[6] = {10, 3, 15, 12, 7, 2};//答：654038
    int d[6] = {7, 2, 4, 15, 20, 5};
    int result = Memory_Matrix_Chain(a);
    cout << "Min Calc times = " << result << endl;
    return 0;
}

