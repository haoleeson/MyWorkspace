#include <iostream>
using namespace std;
class Box {
    public:
        static short Con_count,Des_count;
        Box() {
            Con_count++;
            cout <<"第"<<Con_count<< "次调用构造函数！" <<endl; 
        }
        ~Box() {
            Des_count++;
            cout <<"第"<<Des_count<< "次调用析构函数！" <<endl; 
        }
};
short Box::Con_count = 0;
short Box::Des_count = 0;
int main(void) {
    Box* myBoxArray = new Box[4];
    delete [] myBoxArray; // 删除数组
    return 0;
}
