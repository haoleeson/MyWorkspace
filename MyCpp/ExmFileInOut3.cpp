#include<iostream>
#include<string>
#include<fstream>
using namespace std;
int main(void) {
    fstream iofile;
    iofile.open("D:\\t.txt", ios::out | ios::in | ios::trunc);
    string bookname;
    string bookwriter;
    cout << "input the bookname:" << endl;
    getline(cin, bookname);
    iofile << bookname << endl;
    cout << "input the bookwriter:" << endl;
    getline(cin, bookwriter);
    iofile << bookwriter << endl;
    iofile.close();
    cout << "read the input file:" << endl;
    iofile.open("D:\\t.txt");
    while (getline(iofile, bookname)) {
        cout << bookname << endl;
    }
    system("pause");
    return 0;
}
