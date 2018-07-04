#include <iostream>
using namespace std;
class Line{
    public:
        void setLength( double len );
        double getLength( void );
        Line(double len);  // 这是构造函数
    private:
        double length;
};
// 成员函数定义，包括构造函数
Line::Line( double len){
    length = len;
    cout << "Object is being created, length = " << len << endl;
}
/*Line::Line( double len): length(len) //等价于上面的构造函数
{
    cout << "Object is being created, length = " << len << endl;
}*/
void Line::setLength( double len ){
    length = len;
}
double Line::getLength( void ){
    return length;
}
// 程序的主函数
int main(void){
    Line line(10.0);
    cout << "Length of line : " << line.getLength() <<endl;
    // 再次设置长度
    line.setLength(6.0); 
    cout << "Length of line : " << line.getLength() <<endl;
    return 0;
}
