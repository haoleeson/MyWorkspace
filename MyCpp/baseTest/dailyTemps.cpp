#include <iostream>

using namespace std;

/***************************
 * 函数功能: 根据一个时间段内的气温列表，来重新生成一个数组
 * return: 计算结果
 * @para array: 一段时间内的气温列表
 * @para size: 数组array的大小
***************************/
int* dailyTemps(int temps[], int size)
{
    int *result = new int[size];
    /********** BEGIN **********/

    for (int i=0; i<size-1; i++)
    {
        bool isExit = false;
        for (int j=i+1; j<size; j++)
        {
            if (temps[j] > temps[i])
            {
                *(result + i) = j - i;
                isExit = true;
                break;
            }
        }
        //no higher day
        if(!isExit)
        {
            *(result + i) = 0;
        }
    }
    *(result + size -1) = 0;

    /********** END **********/
    return result;
}

int main(void)
{
    int temps[8] = {34,35,33,25,44,19,18,17};
    int *re;
    re = dailyTemps(temps, 8);
    for (int i=0; i<8; i++)
    {
        cout << *(re + i) << " ";
    }
}

