/*
华为笔试题：C++平安果 D P 算法
题目：平安果
题目介绍：给出一个m*n的格子，每个格子里有一定数量的平安果，现在要求从左上角顶点（1,1）出发，每次走一格并拿走那一格的所有平安果，且只能向下或向右前进，最终到达右下角顶点（m，n），要求求出能拿走的平安果的最大数值。
输入：第一行有两个数值m，n，然后是m行n列数值。
输出：一个数值代表平安果的最大数量。
例：
输入：
4 4
1 2 4 8
10 14 3 9
17 6 7 20
12 5 21 23
输出：
89
*/

/*
分析：这是一种比较典型的dp算法（动态规划）的题目，每一格获取的平安果最大数值都与上格或左格有关（即交叠问题），且无后效性。这题也证明了动态规划可以解决贪心算法所解决不了的问题，若用贪心算法，不一定能得出总体最优解。

状态方程：dp[ i ][ j ]=max{ dp[ i-1 ][ j ] , dp[ i ][ j-1 ]}+A[ i ][ j ]
*/
     
#include <iostream>
#include <vector>
using namespace std;

#define Bigger( A, B ) ( ((A) > (B)) ? (A) : (B) )

int Peace_fruit( vector< vector<int> >&A, int Row, int Column );//华为笔试题：C++平安果DP算法

int main (void) {
    int Row, Column, Maxsum = 0, inputFlag = 0;
    cout << "华为笔试题：C++平安果 D P 算法" << endl;
    while(1) {
        cout << "请选择输入:'0'或'1'选择方式:" << endl << "'0'.测试默认数组A[4][4]" << endl << "'1'.手动输入数组大小Row、Column、及数组各元素" << endl << " :" ;
        cin >> inputFlag;
        if ( inputFlag == 0 ) {
            int B[4][4]={
                {1, 2, 4, 8},
                {10, 14, 3, 9},
                {17, 6, 7, 20},
                {12, 5, 21, 23},
            };
            Row = 4;
            Column = 4;
            cout << "'0'.测试默认数组A[4][4]" << endl;
            cout << "Row=" << Row << ", Column=" << Column << endl;
            cout << "测试数组A[" << Row << "]["<< Column <<"]为:" << endl;
            vector< vector<int> > A( Row, vector<int>(Column) );//创建一个Row * Column的int型二维向量
            for ( int i=0; i<Row; i++ ) {
                for ( int j=0; j<Column; j++ ) {
                    A[i][j] = B[i][j];
                    cout << A[i][j] << " ";
                    if ( j%Column == Column-1 ) {
                        cout << endl ;
                    }
                }
            }
            Maxsum = Peace_fruit( A, Row, Column );
            cout << Maxsum;
            A.clear();//移除容器内所有数据
            break;
        } else if ( inputFlag == 1 ) {
            cout << "'1'.手动输入数组大小行Row、列Column" << endl << " :" ;
            cin >> Row;
            cin >> Column;
            cout << "Row=" << Row << ", Column=" << Column << endl;
            cout << "请手动输入数组A[" << Row << "]["<< Column <<"]的个元素:" << endl;
            vector< vector<int> > A( Row, vector<int>(Column) );//创建一个Row * Column的int型二维向量
            for ( int i=0; i<Row; i++ ) {
                for ( int j=0; j<Column; j++ ) {
                    cin >> A[i][j];
                }
            }
            cout << "测试数组A[" << Row << "]["<< Column <<"]为:" << endl;
            for ( int i=0; i<Row; i++ ) {
                for ( int j=0; j<Column; j++ ) {
                    cout << A[i][j] << " ";
                    if ( j%Column == Column-1 ) {
                        cout << endl ;
                    }
                }
            }
            Maxsum = Peace_fruit( A, Row, Column );
            cout << Maxsum;
            A.clear();//移除容器内所有数据
            break;
        } else {
            cout << endl << "Error:　请正确输入'0'或'1'" << endl;
        }
    }

    return 0;
}
//华为笔试题：C++平安果DP算法
int Peace_fruit( vector< vector<int> >&A, int Row, int Column ) {
    int Maxsum = 0;
    vector< vector<int> > dp(A);//将容器A赋值给容器dp
//    vector< vector<int> > dp( Row, vector<int>(Column) );//创建一个Row * Column的int型二维向量
    //特殊(左边界)：求第一列直下各元素点的路径和
    for ( int i=1; i<Row; i++ ) {
        dp[i][0] += dp[i-1][0];
    }
    //特殊(右边界)：计算第一行直右各元素点的路径和
    for ( int j=1; j<Column; j++ ) {
        dp[0][j] += dp[0][j-1];
    }
    //判断dp[i][j]：的上方元素、左方元素谁大，并选择较大值与自身累加
    for ( int i=1; i<Row; i++ ) {
        for ( int j=1; j<Column; j++ ) {
            dp[i][j] += Bigger( dp[i-1][j], dp[i][j-1] );
        }
    }
    Maxsum = dp[Row-1][Column-1];
    //打印dp
    cout << "广度优先搜索，过程数组(dp数组)dp[" << Row << "]["<< Column <<"]为:" << endl;
    for ( int i=0; i<Row; i++ ) {
        for ( int j=0; j<Column; j++ ) {
            cout << dp[i][j] << " ";
            if ( j%Column == Column-1 ) {
                cout << endl ;
            }
        }
    }
    dp.clear();
    return Maxsum;
}

