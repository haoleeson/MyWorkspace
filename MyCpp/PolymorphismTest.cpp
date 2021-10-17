#include <iostream>
#include "PolymorphismTest.h"

using namespace std;

int main(void)
{

    /**参数多态**/
    shape<int> shape1();
    shape<double > shape2();

    /**过载多态**/
    shape<double> shape3();
    shape<double> shape4(3.2, 5.7);

    /**包含多态**/
    shape<double> shape5(4, 5);
    Parallelogram<double> parallelogram(4, 5);
    shape5.getArea();
    parallelogram.getArea();

    /**重置**/
    int a, b;
    Rectangle<int> rectangle1(4, 4);
    Triangle<int> triangle1(4, 4);
    a = rectangle1.getArea();
    b = triangle1.getArea();

    /**强制多态**/
    double c;
    c = a + b; //隐式强制多态 将int类型a,b转换为double
    cout << c << endl;

    return 0;
}

