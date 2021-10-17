#include <fstream> 
#include <string>
#include <iostream>
#include <streambuf> 
using namespace std;
//向文件写入字符串
int WriteFile(string filepath,const string& Init) {
    //定义文件输出流 
    ofstream outfile; 
    //根据参数路径创建要输出的文件 
    outfile.open(filepath, ios::out | ios::trunc);    
    if(!outfile){
        return 1;
    }
    outfile << Init << endl;
    outfile.close(); 
    return 0;
}
//从文件读取
string Read_Str(string filepath) {
    ifstream infile;
    infile.open(filepath);
    //打开失败，路径不正确
    if(!infile){
        cout << "Open File Fail!" << endl;
    }
    //读取文本内容到字符串
    string readStr((std::istreambuf_iterator<char>(infile)),  std::istreambuf_iterator<char>()); 
    return readStr;
}
int main(void) {
    //执行完成在mian.cpp同一目录下生产C.txt文件
    WriteFile("./C.txt","Hello , world!");
    cout << Read_Str("./C.txt") << endl;
    getchar();
    return 0;
}
