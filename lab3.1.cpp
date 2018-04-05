#include <iostream>
using namespace std;

//temputer change

float Convert(float);
int main(void)
{
    float TempFer;
    float TempCel;

    cout << "请输入华氏温度：";
    cin >> TempFer;
    TempCel = Convert(TempFer);
    cout << "\n转换为摄氏温度是：";
    cout << TempCel << endl;
    return 0;
}

float Convert(float TempFer)
{
    float TempCel;
    TempCel = ((TempFer - 32) * 5) / 9;
    return TempCel;
}
