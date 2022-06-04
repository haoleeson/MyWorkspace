#include <iostream>

using namespace std;

/***************************
 * 函数功能: 计算渡口中停了多少艘船
 * return: 渡口中停的艘船个数
 * @para ferry: 二维的渡口
 * @para m: 渡口的行数
 * @para n: 渡口的列数
***************************/

int countOfShips(char **ferry, int m, int n)
{
    /********** BEGIN **********/

    int shipCount = 0; //船计数
    bool isCameFlag[m][n] = {false}; //等规模是否遍历标志

    //遍历：从左向右，从上向下
    for (int Row=0; Row<m; Row++) //行
    {
        for (int Column=0; Column<n; Column++) //列
        {
            //若该点未被遍历
            if (!isCameFlag[Row][Column])
            {
                isCameFlag[Row][Column] = true;
                //若该点为'+'
                if ( *(*(ferry + Row) + Column) == '+' )
                {
                    //特例1：该'+'点为右下角一个孤立点
                    if (Row == m-1 && Column == n-1)
                    {
                        shipCount ++;
                    }
                    //特例：该'+'在右侧侧边上
                    else if (Row < m-1 && Column == n-1)
                    {
                        //垂直向下遍历
                        int chuiZhiPianYi = 1;
                        while ( Row+chuiZhiPianYi < m )
                        {
                            isCameFlag[Row + chuiZhiPianYi][Column] = true; //添加访问标志
                            if (*(*(ferry + Row + chuiZhiPianYi) + Column) != '+') break;
                            chuiZhiPianYi++;
                        }
                        shipCount++;
                    }
                    //特例：该'+'在底边上
                    else if (Row == m-1 && Column < n-1 )
                    {
                        //水平向右遍历
                        int shuiPingPianYi = 1;
                        while ( Column+shuiPingPianYi < n )
                        {
                            isCameFlag[Row][Column + shuiPingPianYi] = true; //添加访问标志
                            if (*(*(ferry + Row) + Column + shuiPingPianYi) != '+') break;
                            shuiPingPianYi++;
                        }
                        shipCount++;
                    }
                    //一般情况：该'+'在中间区域、右边、上边
                    else
                    {
                        //判断船体方向
                        //A1: 右、下均非'+'，船身为1
                        if ( *(*(ferry + Row) + Column+1) != '+' && *(*(ferry + Row+1) + Column) != '+' )
                        {
                            isCameFlag[Row][Column+1] = true;
                            isCameFlag[Row+1][Column] = true;
                            shipCount++;
                        }
                        //A2: 右边为'+', 下边非'+' ,水平方向
                        else if ( *(*(ferry + Row) + Column+1) == '+' && *(*(ferry + Row+1) + Column) != '+' )
                        {
                            //水平向右遍历
                            int shuiPingPianYi = 1;
                            while ( Column+shuiPingPianYi < n )
                            {
                                isCameFlag[Row][Column + shuiPingPianYi] = true; //添加访问标志
                                if (*(*(ferry + Row) + Column + shuiPingPianYi) != '+') break;
                                shuiPingPianYi++;
                            }
                            shipCount++;
                        }
                        //A3: 右边非'+', 下边为'+' ,垂直方向
                        else if ( *(*(ferry + Row) + Column+1) != '+' && *(*(ferry + Row+1) + Column) == '+' )
                        {
                            //垂直向下遍历
                            int chuiZhiPianYi = 1;
                            while ( Row+chuiZhiPianYi < m )
                            {
                                isCameFlag[Row + chuiZhiPianYi][Column] = true; //添加访问标志
                                if (*(*(ferry + Row + chuiZhiPianYi) + Column) != '+') break;
                                chuiZhiPianYi++;
                            }
                            shipCount++;
                        }
                        //A4: 其他非正常情况
                        else{}
                    }
                }
                //该点不为'+', eg:'o'，则跳过
                else
                {
                    continue;
                }
            }
            //该点已被遍历
            else
            {
                continue;
            }
        }
    }
    return shipCount;

    /********** END **********/
}
int main(void)
{
    cout << "hello" << endl;
    bool isCameFlag[5][5] = {false};
    if (!isCameFlag[3][2])
    {
        cout << " : " << isCameFlag[3][2] << endl;
    }
}
