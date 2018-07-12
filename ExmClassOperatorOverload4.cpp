#include <iostream>
using namespace std;
class Distance {
    public:
        Distance(void);            //构造函数1 无参数
        Distance(int f, int i);    //构造函数2 有参数
        void displayDistance(void); //显示距离
        // 重载负运算符（ - ）
        Distance operator- () {
            feet = -feet;
            inches = -inches;
            return Distance(feet, inches);
        }
        // 重载小于运算符（ < ）
        bool operator <(const Distance& d) {
            if (feet < d.feet) {
                return true;
            }
            if (feet == d.feet && inches < d.inches) {
                return true;
            }
            return false;
        }
    private:
        int feet;             // 0 到无穷
        int inches;           // 0 到 12
};
// 构造函数1 无参数
Distance::Distance(void){
    feet = 0;
    inches = 0;
}
// 构造函数2 有参数
Distance::Distance(int f, int i){
    feet = f;
    inches = i;
}
// 显示距离的方法
void Distance::displayDistance(void) {
    cout << "F: " << feet << " I:" << inches <<endl;
}
int main(void) {
    Distance D1(11, 10), D2(5, 11);
    cout<<"Distance D1(11, 10), D2(5, 11)"<<endl;
    if ( D1 < D2 ) { //此"<"为重载运算符，比较D1与D2的feet
        cout << "compare feet, D1 is less than D2 " << endl;
    } else {
        cout << "compare feet, D2 is less than D1 " << endl;
    }
    return 0;
}
