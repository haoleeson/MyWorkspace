#include <iostream>
using namespace std;
// 基类
class Shape {
    public:
        void setWidth(double w) {
            width = w;
        }
        void setHeight(double h) {
            height = h;
        }
    protected:
        double width;
        double height;
};
// 派生类
class Rectangle: public Shape {
    public:
        static short GouZaoCount;
        static short XiGouCount;
        double getArea(void) { 
            return (width * height); 
        }
        Rectangle(double w, double h);//构造函数
        ~Rectangle();//析构函数
};
//成员函数定义
Rectangle::Rectangle(double w, double h) {
    GouZaoCount++ ;
    cout<<"调用构造"<<GouZaoCount<<" 开始"<<endl;
    this->setWidth(w);//this->width = w;
    this->setHeight(h);//this->height = h;
}
Rectangle::~Rectangle(void){
    XiGouCount++ ;
    cout<<"调用析构"<<XiGouCount<<" 开始"<<endl;
}
short Rectangle::GouZaoCount = 0;
short Rectangle::XiGouCount = 0;
int main(void) {
    Rectangle Rect(0,0);
    Rect.setWidth(5.3);
    Rect.setHeight(7.4);
    // 输出对象的面积
    cout << "Rectangle1 Total area: " << Rect.getArea()  << endl;
    
    Rectangle Rect2(6.3,5.8);
    // 输出对象的面积
    cout << "Rectangle2 Total area: " << Rect2.getArea()  << endl;
    return 0;
}
