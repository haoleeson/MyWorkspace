#include <iostream>
using namespace std;
void pointerArray();
void pointerArray4Char();
const int MAX = 3;
int main(void){
    // pointerArray();
    pointerArray4Char();
    return 0;
}
void pointerArray(){
    int var[MAX] = {20,30,40};
    int *ptr[MAX];
    for(int i = 0; i < MAX; i++){
        ptr[i] = &var[i];//赋值为整数的地址
    }
    for(int i = 0; i < MAX; i++){
        cout << "Value of var[" << i << "] = ";
        cout << *ptr[i] <<endl;
    }
}
/**
 * 用一个指向字符的指针数组来存储一个字符串列表
 * Value of names[0] = sun;
 */
void pointerArray4Char(){
    const char *names[MAX] = {
            "sun","bin","sunbin"
    };
    for(int i = 0;i < MAX;i++){
        cout <<"Value of names[" << i << "] = ";//输出字符串的值
        cout << names[i] << endl;
        cout <<"Value of *names[" << i << "] = ";//输出指针所指向字符串首地址的值
        cout << *names[i] << endl;
        cout <<"Value of *names[" << i << "]+1 = ";//输出ascii码值
        cout << *names[i]+1 << endl;
        cout <<"Value of *(names[" << i << "]+1) = ";//输出指针所指向字符串首地址上一位的值
        cout << *(names[i]+1) << endl;
        cout << endl;
    }
}
