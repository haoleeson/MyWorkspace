#include <iostream>
using namespace std;
class Distance {
    public:
        Distance(void);         //构造函数1 不带参数
        Distance(int f, int i); //构造函数2 带参数
        // 显示距离的方法
        void displayDistance(void);
        // 重载负运算符（ - ）
        Distance operator- (void) {
            feet = -feet;
            inches = -inches;
            return Distance(feet, inches);
        }
    private:
        int feet;             // 0 到无穷
        int inches;           // 0 到 12
};
// 构造函数1 不带参数
Distance::Distance(void) {
    feet = 0;
    inches = 0;
}
// 构造函数2 带参数
Distance::Distance(int f, int i) {
    feet = f;
    inches = i;
}
// 显示距离的方法
void Distance::displayDistance(void) {
    cout << "F: " << feet << " I:" << inches <<endl;
}
int main(void) {
    Distance D1(11, 10), D2(-5, 11);
    D1.displayDistance();    // 距离 D1
    D2.displayDistance();    // 距离 D2
    cout<<"取相反数后："<<endl;
    -D1;                     // 取相反数
    D1.displayDistance();    // 距离 D1
    -D2;                     // 取相反数
    D2.displayDistance();    // 距离 D2
    return 0;
}
