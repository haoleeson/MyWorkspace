#include "iostream"
#include "fstream"
using namespace std;

//向文件内部写入数据，并将数据读出
void file_wr(void) {
    char data[100];
    //向文件写入数据
    ofstream outfile;
    outfile.open("test.txt");
    cout << "Write to the file" << endl;
    cout << "Enter your name:" << endl;
    cin.getline(data, 100);
    outfile << data << endl;
    cout << "Enter your age:" << endl;
    cin >> data;
    cin.ignore();
    outfile << data << endl;
    outfile.close();
    //从文件读取数据
    ifstream infile;
    infile.open("test.txt");
    cout << "Read from the file" << endl;
    infile >> data;
    cout << data << endl;
    infile >> data;
    cout << data << endl;
    infile.close();
}

//将数据从一文件复制到另一文件中
void file_copy(void) {
    char data[100];
    ifstream infile;
    ofstream outfile;
    infile.open("test.txt");
    outfile.open("test_1.txt");
    cout << "copy from test.txt to test_1.txt" << endl;
//    while ( !infile.eof() ) {
//        infile >> data;
    while ( infile >> data ) {
        cout << data << endl;
        outfile << data << endl;
    }
    infile.close();
    outfile.close();
}

//测试上述读写文件，与文件数据复制
int _tmain(int argc, _TCHAR* argv[]) {
    file_wr();
    file_copy();
    return 0;
}
