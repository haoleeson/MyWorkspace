#include <iostream>
using namespace std;
class CExample 
{
private:
    int a;
public:
    //构造函数
    CExample(int b)
    { 
        a = b;
        cout<<"creat: "<<a<<endl;
    }
    //拷贝构造
    CExample(const CExample& C)
    {
        a = C.a;
        cout<<"copy"<<endl;
    }
    //析构函数
    ~CExample()
    {
        cout<< "delete: "<<a<<endl;
    }
    void Show ()
    {
        cout<<a<<endl;
    }
};
//全局函数，传入的是对象
void g_Fun(CExample C)
{
    cout<<"test"<<endl;
}
int main(void)
{
    CExample test(1);
    //传入对象
    g_Fun(test);
    return 0;
}
//调用g_Fun()时，会产生以下几个重要步骤：
//(1).test对象传入形参时，会先会产生一个临时变量，就叫 C 吧。
//(2).然后调用拷贝构造函数把test的值给C。 整个这两个步骤有点像：CExample C(test);
//(3).等g_Fun()执行完后, 析构掉 C 对象。
