/**
 * Encoding：utf-8
 * Programming language：c++
 * Coder：EisenHao
 * */
#include <iostream>
#include <vector>
#include <iomanip>

#define showWidth 3 //宏定义显示间距

using namespace std;

//求绝对值
int abs(int num){
    if(num < 0)
        return -num;
    return num;
}

//显示结果
void showResult(vector<int>& x){
    cout << endl << "The answer of "<< x.size() << " queens problem is: ";
    for(int i=0; i<x.size(); i++){
        cout << setw(showWidth) << x[i];
    }
    cout << endl << "============= Draw =============" << endl;
    cout << " ";
    for(int i=0; i<x.size(); i++){
        cout << setw(showWidth) << i;
    }
    cout << endl;
    for(int i=0; i<x.size(); i++){
        cout << i;
        for(int j=0; j<x.size(); j++){
            if(j == x[i]){
                cout << setw(showWidth) << "Q";
            }else{
                cout << setw(showWidth) << "-";
            }
        }
        cout << endl;
    }
}

void showPartResul(vector<int>& x, int k){
    cout << endl;
    for(int i=0; i<k; i++){
        cout << setw(showWidth) << x[i];
    }
    cout << endl;
}


//判断N皇后问题第k行之前行 与 第k行 是否存在冲突
bool PLACE(int k, vector<int>& x){
    for(int i=0; i<k; i++){
        if(x[i]==x[k] || abs(x[i]-x[k])==abs(i-k)){
            return false;//有冲突
        }
    }
    return true;//无冲突
}

//用回溯算法求解8皇后问题
void NQueensByBackTracking(int n){
    int k=0;//k:表示行数，从第0行开始
    vector<int> x(n, -1);//创建int x[n]容器，x[k]用于存储第k行皇后放置的列数
    while (k>=0){
        x[k]++;//第k行皇后放置位置右移，初次正好到0； 回溯时在上一次失败尝试下右移
        //试探右移找到不冲突的列
        while(x[k]<n && !PLACE(k, x)){
            x[k]++;//列右移
        }
        //【判断】上一步退出while的原因（是否找到不冲突的列）
        //一、若已找到不冲突的列
        if (x[k] < n){
            //【判断】：是否所有行均找到结果
            //1.所有行结果均已找到：输出结果
            if(k == n-1){
                showResult(x);//显示n皇后结果
                return;
            }
            //2.k行后面行还没找到结果
            else{
                k++;//行数后移
                x[k] = -1;//初始值
            }
        }
        //二、（未找到不冲突的列）当前行k的所有结果均冲突时，回溯，行数k-1
        else{
            k--;
        }
    }
    if(k<0){
        cout << n << " queens problem has no answer" << endl;
    }
}

int main(int argc, const char * argv[]) {
    //用回溯算法求解8皇后问题
    NQueensByBackTracking(8);
    return 0;
}
