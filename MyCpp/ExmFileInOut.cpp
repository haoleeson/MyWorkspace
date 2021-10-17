#include <fstream>
#include <iostream>
/*
关于 cin.ignore() ，完整版本是 cin.ignore(int n, char a), 从输入流 (cin) 中提取字符，提取的字符被忽略 (ignore)，不被使用。每抛弃一个字符，它都要计数和比较字符：如果计数值达到 n 或者被抛弃的字符是 a，则 cin.ignore()函数执行终止；否则，它继续等待。它的一个常用功能就是用来清除以回车结束的输入缓冲区的内容，消除上一次输入对下一次输入的影响。比如可以这么用：cin.ignore(1024,'\n')，通常把第一个参数设置得足够大，这样实际上总是只有第二个参数 \n 起作用，所以这一句就是把回车(包括回车)之前的所以字符从输入缓冲(流)中清除出去。
*/

using namespace std;
int main (void) {
    char data[100];
    // 以写模式打开文件
    ofstream outfile;
    outfile.open("afile.dat");
    cout <<endl<< "****Writing to the file****"<<endl;
    cout << "Enter your name: "; 
    cin.getline(data, 100);
    // 向文件写入用户输入的数据
    outfile << data << endl;
    cout << "Enter your age: "; 
    cin >> data;
    cin.ignore();//处理回车
    // 再次向文件写入用户输入的数据
    outfile << data << endl;
    // 关闭打开的文件
    outfile.close();

    // 以读模式打开文件
    ifstream infile; 
    infile.open("afile.dat"); 
    cout <<endl<< "****Reading from the file****"<<endl; 
    infile >> data; //读取文件中第一行数据 
    // 在屏幕上写入数据
    cout << data << endl;
    // 再次从文件读取数据，并显示它
    infile >> data; //读取文件中第二行数据 
    cout << data << endl; 
    // 关闭打开的文件
    infile.close();
    return 0;
}
