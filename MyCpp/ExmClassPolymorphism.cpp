#include <iostream>
using namespace std;

class Shape {
    public:
        Shape(double a = 0.0, int b=0.0){
            width = a;
            height = b;
        }
        //纯虚函数纯虚函数声明如下： virtual void funtion1()=0; 纯虚函数一定没有定义，纯虚函数用来规范派生类的行为，即接口。
        virtual double area() = 0;//'=0'告诉编译器，area没有主体，这个函数是纯虚函数
    protected:
        double width, height = 0;
};
class Rectangle: public Shape {
    public:
        Rectangle( double a = 0.0, int b = 0.0 ):Shape(a, b){}
        double area(void){
            double area = 0.0;
            area = width * height ; 
            cout<<"Rectangle class area is: "<<area<<endl;
            return area;
        }
};
class Triangle: public Shape {
    public:
        Triangle( double a = 0, double b = 0 ):Shape(a, b){}
        double area(void){
            double area = 0.0;
            area = width * height / 2; 
            cout<<"Triangle class area is: "<<area<<endl;
            return area;
        }
};
//程序主函数
int main(void){
    Shape *shape;
    Rectangle rec(5.0,5.0);
    Triangle tri(5.0,5.0);
    cout<<"Rectangle rec(5.0,5.0);"<<endl<<"Triangle tri(5.0,5.0);"<<endl;
    shape = &rec;
    shape->area();
    shape = &tri;
    shape->area();
    return 0;
}

    
