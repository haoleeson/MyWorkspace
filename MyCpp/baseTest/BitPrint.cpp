//
// Created by eisenhao on 2019-07-24.
//

#include "BitPrint.h"

/**
     * 打印一个 byte 变量的每一位
     * 默认每一字节从左至右 对应 高位至地位
     * eg. 0x80  --> [1000 0000]
     * */
void BitPrint::bitPrint_Byte(const byte val) {
    byte comp = 0x80;
    cout << " [";
    while (comp > 0) {
        if (comp == 0x08)
            cout << " ";
        if ((val & comp) == comp)
            cout << "1";
        else
            cout << "0";
        comp >>= 1;
    }
    cout << "]";
}

/**
     * 打印一个 char 变量的每一位
     * 默认每一字节从左至右 对应 高位至地位
     * eg. 0x80  --> [1000 0000]
     * */
void BitPrint::bitPrint_Char(const char val) {
    cout << endl << "char = " << val << endl << "Bits:";
    bitPrint_Byte((byte)val);
    cout << endl;
}

/**
     * 打印一个 int 变量的每一位
     * 默认每一字节从左至右 对应 高位至地位,
     * 默认从左至右为内存地址的增长方向
     * 小端字节序（正序）：高字节对应内存的高地址
     * 大端字节序（逆序）：高字节对应内存的低地址（网络传输统一用大端字节序）
     * eg. 0x00001234
     * 小端（正序） [0011 0100] [0001 0010] [0000 0000] [0000 0000]
     * 大端（逆序） [0000 0000] [0000 0000] [0001 0010] [0011 0100]
     * */
void BitPrint::bitPrint_Int(const int val) {
    byte* byteBuf = (byte *) &val;

    cout << endl << "int = " << val << endl << "Bits:";
    for (int i=0; i<IntLen; i++) {
        bitPrint_Byte(byteBuf[i]);
    }
    cout << endl;
}

/**
     * 打印一个 任意 变量的每一位
     * 默认每一字节从左至右 对应 高位至地位,
     * 默认从左至右为内存地址的增长方向
     * 小端字节序（正序）：高字节对应内存的高地址
     * 大端字节序（逆序）：高字节对应内存的低地址（网络传输统一用大端字节序）
     * eg. 0x00001234
     * 小端（正序） [0011 0100] [0001 0010] [0000 0000] [0000 0000]
     * 大端（逆序） [0000 0000] [0000 0000] [0001 0010] [0011 0100]
     * */
void BitPrint::bitPrint_Element(void *val, int len) {
    byte* byteBuf = new byte[len];//申请len长度的内存用于存放变量的所有字节

    memcpy(byteBuf, val, len);//深拷贝
    cout << "Bits:";
    for (int i=0; i<len; i++) {
        bitPrint_Byte(byteBuf[i]);
    }
    cout << endl;
    delete[] byteBuf;//释放byteBuf内存
}

/**
     * 判断运行此代码的系统是否为大端字节序
     * 小端字节序（正序）：高字节对应内存的高地址
     * 大端字节序（逆序）：高字节对应内存的低地址（网络传输统一用大端字节序）
     * @Return 是大端字节序（true）；是小端字节序（false）
     * */
bool BitPrint::isBigEndian() {
    int test = 0x01;
    byte* byteBuf = (byte *) &test;
    //取低地址的一个字节为Byte变量，若其值等于低字节0x01则为正序（小端）
    return (byteBuf[0] == 0x01) ? false : true;
}

/**
 * 测试字节对齐
 */
void BitPrint::testByteAlignment() {
    MSG1 msg1;
    cout <<
         "&msg1:\t\t\t\t" << (void*)&msg1 << " , " << (uint64_t)(void*)&msg1 - (uint64_t)(void*)&msg1 << endl <<
         "&msg1.ID:\t\t\t" << (void*)&msg1.ID << " , " << (uint64_t)(void*)&msg1.ID - (uint64_t)(void*)&msg1 << endl <<
         "&msg1.type:\t\t\t" << (void*)&msg1.type << " , " << (uint64_t)(void*)&msg1.type - (uint64_t)(void*)&msg1 << endl <<
         "&msg1.flag:\t\t\t" << (void*)&msg1.flag << " , " << (uint64_t)(void*)&msg1.flag - (uint64_t)(void*)&msg1 << endl <<
         "&msg1.uiHashValue:\t" << (void*)&msg1.uiHashValue << " , " << (uint64_t)(void*)&msg1.uiHashValue - (uint64_t)(void*)&msg1 << endl <<
         "&msg1.uiDataLen:\t" << (void*)&msg1.uiDataLen << " , " << (uint64_t)(void*)&msg1.uiDataLen - (uint64_t)(void*)&msg1 << endl <<
         "&msg1.contentData:\t" << (void*)msg1.contentData << " , " << (uint64_t)(void*)&msg1.contentData - (uint64_t)(void*)&msg1 << endl << endl;

    MSG0 msg0;
    cout <<
         "&msg0:\t\t\t\t" << (void*)&msg0 << " , " << (uint64_t)(void*)&msg0 - (uint64_t)(void*)&msg0 << endl <<
         "&msg0.ID:\t\t\t" << (void*)&msg0.ID << " , " << (uint64_t)(void*)&msg0.ID - (uint64_t)(void*)&msg0 << endl <<
         "&msg0.type:\t\t\t" << (void*)&msg0.type << " , " << (uint64_t)(void*)&msg0.type - (uint64_t)(void*)&msg0 << endl <<
         "&msg0.flag:\t\t\t" << (void*)&msg0.flag << " , " << (uint64_t)(void*)&msg0.flag - (uint64_t)(void*)&msg0 << endl <<
         "&msg0.uiHashValue:\t" << (void*)&msg0.uiHashValue << " , " << (uint64_t)(void*)&msg0.uiHashValue - (uint64_t)(void*)&msg0 << endl <<
         "&msg0.uiDataLen:\t" << (void*)&msg0.uiDataLen << " , " << (uint64_t)(void*)&msg0.uiDataLen - (uint64_t)(void*)&msg0 << endl <<
         "&msg0.ulStartTime:\t" << (void*)&msg0.ulStartTime << " , " << (uint64_t)(void*)&msg0.ulStartTime - (uint64_t)(void*)&msg0 << endl <<
         "&msg0.ulEndTime:\t" << (void*)&msg0.ulEndTime << " , " << (uint64_t)(void*)&msg0.ulEndTime - (uint64_t)(void*)&msg0 << endl <<
         "&msg0.contentData:\t" << (void*)msg0.contentData << " , " << (uint64_t)(void*)&msg0.contentData - (uint64_t)(void*)&msg0 << endl << endl;
}

/**
 * 测试字节操纵
 */
void BitPrint::testByteOperator() {
    cout << MSG0_HEAD_LEN << endl;
    cout << MSG1_HEAD_LEN << endl;

    MSG0 msg0;
    msg0.ulStartTime = 20181112ULL;
    msg0.ulEndTime = 561341235ULL;

    void* p = &msg0;

    MSG1* msg1Ptr = (MSG1*)p;

    cout  << "(msg1Ptr->contentData): " << (void *)(msg1Ptr->contentData) << ", " <<  *(unsigned long long int*)(msg1Ptr->contentData)  << " ULL" << endl;
    cout  << "(msg1Ptr->contentData + 8): " << (void *)(msg1Ptr->contentData + 8)<< ", " <<  *(unsigned long long int*)(msg1Ptr->contentData + 8) << " ULL" << endl;
}

/**
 * main.cpp 测试
 * */
//#include "BitPrint.h"
//
////学生成绩类
//class Student {
//public:
//    char id;
//    int score;
//    Student(char id, int score) {
//        this->id = id;
//        this->score = score;
//    }
//};
//
//int main(void) {
//    BitPrint* bitPrint = new BitPrint();
//
//    byte b = 0x55;
//    char ch = 'M';
//    int i = 0x01234567;
//    short s = 1234;
//    double d = 12.34;
//    Student* xiaoming = new Student('A', 88);
//
//
//    cout << "val = " << b << endl;
//    bitPrint->bitPrint_Byte(b);
//    cout << endl;
//
//    bitPrint->bitPrint_Char(ch);
//
//    bitPrint->bitPrint_Int(i);
//
//    cout << "short = " << s << endl;
//    bitPrint->bitPrint_Element(&s, sizeof(short));
//    cout << "double = " << d << endl;
//    bitPrint->bitPrint_Element(&d, sizeof(double));
//
//
//    cout << "class = {" << xiaoming->id << ", " << xiaoming->score << "}" << endl;
//    bitPrint->bitPrint_Element(xiaoming, sizeof(Student));
//
//    //判断运行此代码的系统是否为大端字节序
//    if (bitPrint->isBigEndian()) {
//        cout << endl << "Yes, this system is Big Endian System" << endl;
//    } else {
//        cout << endl << "No, this system is Small Endian System" << endl;
//    }
//
//    return 0;
//}

