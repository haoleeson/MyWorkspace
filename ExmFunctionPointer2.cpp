#include <iostream>
#include <iomanip>
using namespace std;
double Add(double num1, double num2) {//加
    return (num1 + num2);
}
double Subtract(double num1, double num2) {//减
    return (num1 - num2);
}
double Multiply(double num1, double num2) {//乘
    return (num1 * num2);
}
double Divide(double num1, double num2) {//除
    return (num1 / num2);
}
int main(void) {
    double (*fun)(double, double);
    cout << "Test (*fun)(5,3) :" << endl <<endl;
    fun = Add;
    cout << setw(10) << "Add: " << (*fun)(5,3) << endl;
    fun = Subtract;
    cout << setw(10) << "Subtract: " << (*fun)(5,3) << endl;
    fun = Multiply;
    cout << setw(10) << "Multiply: " << (*fun)(5,3) << endl;
    fun = Divide;
    cout << setw(10) << "Divide: " << (*fun)(5,3) << endl;
    return 0;
}
