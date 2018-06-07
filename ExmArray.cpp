#include <iostream>
#include <iomanip>
using namespace std;

int main(void)
{
    int n[10]={0};
    //初始化数组
    for(int i=0;i<10;i++)
    {
        n[i] = i + 13; 
    }
    cout<<"Element"<<setw(10)<<"Value"<<endl;
    for(int i=0;i<10;i++)
    {
        cout<<setw(4)<<i<<setw(11)<<n[i]<<endl;
    }
    return 0;
}
