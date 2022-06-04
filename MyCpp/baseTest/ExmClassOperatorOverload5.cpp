#include <iostream>
using namespace std;
class Distance {
    public:
        //构造函数
        Distance(void);
        Distance(int f, int i);
        // 显示距离的方法
        void displayDistance(void);
        //重载运算符"="
        void operator= (const Distance &D ) { 
            feet = D.feet;
            inches = D.inches;
        }
    private:
        int feet;             // 0 到无穷
        int inches;           // 0 到 12
};
// 所需的构造函数
Distance::Distance(void) {
    feet = 0;
    inches = 0;
}
Distance::Distance(int f, int i) {
    feet = f;
    inches = i;
}
// 显示距离的方法
void Distance::displayDistance(void) {
    cout << "F: " << feet <<  " I:" <<  inches << endl;
}
int main(void) {
    Distance D1(11, 10), D2(5, 11);
    cout << "First Distance : "; 
    D1.displayDistance();
    cout << "Second Distance :"; 
    D2.displayDistance();
    // 使用赋值运算符
    D1 = D2;
    cout<<"D1 = D2"<<endl;
    cout << "First Distance :"; 
    D1.displayDistance();
    return 0;
}
