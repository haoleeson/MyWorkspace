#include <iostream>
using namespace std;
class Adder{
    public:
        void addNum(int number);// 对外的接口
        int getTotal(void);// 对外的接口
        Adder(int i = 0): total(i){}// 构造函数
    private:
        int total;// 对外隐藏的数据
};
// 对外的接口
void Adder::addNum(int number) {
    total += number;
}
// 对外的接口
int Adder::getTotal(void) {
    return total;
};
int main(void) {
    Adder a;
    a.addNum(10);
    a.addNum(20);
    a.addNum(30);
    cout << "Total " << a.getTotal() <<endl;
    return 0;
}
