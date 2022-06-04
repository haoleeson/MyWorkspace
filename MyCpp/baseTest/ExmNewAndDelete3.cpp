#include <iostream>
using namespace std;
int main(void) {
    // p[2][3][4]
    int i,j,k;
    int ***p;
    //分配内存，第一维
    p = new int **[2];
    for(i=0; i<2; i++) {
        //分配内存，第二维
        p[i] = new int *[3];
        for(j=0; j<3; j++) {
            //分配内存，第三维
            p[i][j] = new int[4];
        }
    }
    //赋值并输出 p[i][j][k] 三维数据
    for(i=0; i<2; i++) {
        cout<<"第一维["<<i<<"]数据"<<endl;
        for(j=0; j<3; j++) {
            for(k=0; k<4; k++) {
                p[i][j][k] = i+j+k;
                cout<<p[i][j][k]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
    // 释放内存，第三维
    for(i=0; i<2; i++) {
        for(j=0; j<3; j++) {
            delete [] p[i][j];
        }
    }
    // 释放内存，第二维
    for(i=0; i<2; i++) {
        delete [] p[i];
    }
    // 释放内存，第一维
    delete [] p;
    return 0;
}
