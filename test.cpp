#include<iostream>
using namespace std;
int main(void)
{
    int i,j;
    for(i=1;i<10;i++)
    {
        for(j=0;j<i;j++)
        {
            cout<<"*";
        }
        cout<<endl;  
    }
    //cout<<endl;
    cout<<"end!"<<endl;
    return 0;
}