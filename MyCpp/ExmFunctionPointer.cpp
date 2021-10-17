#include <iostream>
using namespace std;
int ShowOnce(string str) {
    cout << "No.1 " << str << endl;
    cout << endl;
    return 0;
}
int ShowTwice(string str) {
    for (int i=1; i<=2; i++) {
        cout << "No." << i << " " << str <<endl;
    }
    cout << endl;
}
int ShowThrice(string str) {
    for (int i=1; i<=3; i++) {
        cout << "No." << i << " " << str <<endl;
    }
    cout << endl;
}
int main(void) {
    int (*fun)(string);
    fun = ShowOnce;
    (*fun)("ShowOnce");

    fun = ShowTwice;
    (*fun)("ShowTwice");

    fun = ShowThrice;
    (*fun)("ShowThrice");
    return 0;
}
