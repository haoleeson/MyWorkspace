/*
多继承
多继承即一个子类可以有多个父类，它继承了多个父类的特性。
C++ 类可以从多个类继承成员，语法如下：
class <派生类名>:<继承方式1><基类名1>,<继承方式2><基类名2>,…
{
<派生类类体>
}; 
 */
#include <iostream>
using namespace std;
// 基类 Shape
class Shape {
    public:
        void setWidth(int w) {
            width = w;
        }
        void setHeight(int h) {
            height = h;
        }
    protected:
        int width;
        int height;
};
// 基类 PaintCost
class PaintCost {
    public:
        int getCost(int area) {
            return area * 70;//每平方 造价
        }
};
// 派生类
class Rectangle: public Shape, public PaintCost {
    public:
        int getArea(void);
        Rectangle(int w, int h);
        ~Rectangle();
};
int Rectangle::getArea(void) { 
    return (width * height); 
}
Rectangle::Rectangle(int w, int h) {
    this->width = w;
    this->height = h;
}
Rectangle::~Rectangle(){}
int main(void) {
    Rectangle Rect(5,7);
    Rect.setWidth(50);
    // 输出对象的面积
    cout << "Total area: " << Rect.getArea() << endl;
    // 输出总花费
    cout << "Total paint cost: $" << Rect.getCost( Rect.getArea() ) << endl;
    return 0;
}
