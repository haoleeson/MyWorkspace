#include <iostream>
#include <malloc.h>
using namespace std;
class TEST {
    public:
        TEST(){
            num1 = 10;
            num2 = 20;
        }
        void Print(void){
            cout << "num1: "  << num1 << " " << "num2: " << num2 << endl;
        }
    private:
        int num1;
        int num2;
};
int main(void) {
    // 用malloc()函数在堆区分配一块内存空间，然后用强制类型转换将该块内存空间
    // 解释为是一个TEST类对象，这不会调用TEST的默认构造函数
    TEST *pObj1 = (TEST *)malloc(sizeof(TEST));
    pObj1->Print();
    // 用new在堆区创建一个TEST类的对象，这会调用TEST类的默认构造函数
    TEST *pObj2 = new TEST;
    pObj2->Print();
    return 0;
}
/*
运行结果：
-842150451 -842150451       |
10 20                       |
我们可以看到pObj1所指的对象中，字段num1与num2都是垃圾值
而pObj2所指的对象中，字段num1与num2显然是经过了构造后的值
*/
