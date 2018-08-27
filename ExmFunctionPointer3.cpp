#include<iostream>
using namespace std;
//函数指针
float *find(float (*p)[4], int m);//查询序号为m的学生的四门课程的成绩

int main(void) {
    int i, m;
    float score[][4] = {{50,51,52,55}, {70,70,40,80}, {77,99,88,67}};//定义成绩数组，第一维可以为变量
    float *pf = NULL;//定义一个指针时一定要初始化
    cout << "请输入您想查询的学生的序号:(0~2)";
    cin >> m;
    pf = find(score, m); //返回为一维数组指针，指向一个学生成绩
    for (i=0; i<4; i++) {
        cout << *(pf+i) << " ";
    }
    cout<<endl;
    return 0;
}

float *find(float (*p)[4], int m) {
    float *pf = NULL;
    pf = *(p+m);//p是指向二维数组的指针，加*取一维数组的指针
    return pf;
}
