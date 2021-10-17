#include <iostream>
using namespace std;
int main(void) {
    //p[4][8]
    int **p;
    int i,j;
    //分配内存，第一维
    p = new int *[4];
    for(i=0; i<4; i++) {
        //分配内存，第二维
        p[i] = new int [8];
    }
    //二维数组赋值
    for(i=0; i<4; i++) {
        for(j=0; j<8; j++) {
            p[i][j] = j*i;
        }
    }
    //打印数据
    for(i=0; i<4; i++) {
        for(j=0; j<8; j++) {
            if (j==0) {
                cout<<endl;
            }
            cout<<p[i][j]<<"\t";
        }
    }
    //释放内存，第二维
    for(i=0; i<4; i++) {
        delete [] p[i];
    }
    //释放内存，第一维
    delete [] p;
    return 0;
}
