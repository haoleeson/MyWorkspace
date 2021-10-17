//
// Created by eisenhao on 2019-07-24.
//

#ifndef CPPTEST_BITPRINT_H
#define CPPTEST_BITPRINT_H

#include <iostream>
#include <iomanip>
#define byte unsigned char
#define IntLen 4 //默认int变量占4字节
using namespace std;
#pragma pack(1) // 编译使用1字节对齐，未设置则自动字节对齐
struct MSG0 {
    char ID[16];// 16
    unsigned short type;// 2
    char flag; // 1  -->   字节对齐（占2字节）
    unsigned int uiHashValue;// 4
    unsigned int uiDataLen;// 4  -->   字节对齐（占8字节）
    unsigned long long int ulStartTime;// 8
    unsigned long long int ulEndTime;// 8

    char contentData[1];
};
struct MSG1 {
    char ID[16];// 16
    unsigned short type;// 2
    char flag;// 1  -->   字节对齐（占2字节）
    unsigned int uiHashValue;// 4
    unsigned int uiDataLen;// 4

    char contentData[1];
};
#define MSG1_HEAD_LEN  (offsetof(MSG1,contentData))
#define MSG0_HEAD_LEN  (offsetof(MSG0,contentData))
/**
 * 打印字符的每一位
 */
class BitPrint {
public:
    /**
     * 打印一个 byte 变量的每一位
     * 默认每一字节从左至右 对应 高位至地位
     * eg. 0x80  --> [1000 0000]
     */
    void bitPrint_Byte(const byte val);

    /**
     * 打印一个 char 变量的每一位
     * 默认每一字节从左至右 对应 高位至地位
     * eg. 'M'  --> [0100 1101]
     */
    void bitPrint_Char(const char val);

    /**
     * 打印一个 int 变量的每一位
     * 默认每一字节从左至右 对应 高位至地位,
     * 默认从左至右为内存地址的增长方向
     * 小端字节序（正序）：高字节对应内存的高地址
     * 大端字节序（逆序）：高字节对应内存的低地址（网络传输统一用大端字节序）
     * eg. 0x00001234
     * 小端（正序） [0011 0100] [0001 0010] [0000 0000] [0000 0000]
     * 大端（逆序） [0000 0000] [0000 0000] [0001 0010] [0011 0100]
     */
    void bitPrint_Int(const int val);


    /**
     * 打印一个 任意 变量的每一位
     * 默认每一字节从左至右 对应 高位至地位,
     * 默认从左至右为内存地址的增长方向
     * 小端字节序（正序）：高字节对应内存的高地址
     * 大端字节序（逆序）：高字节对应内存的低地址（网络传输统一用大端字节序）
     * eg. 0x00001234
     * 小端（正序） [0011 0100] [0001 0010] [0000 0000] [0000 0000]
     * 大端（逆序） [0000 0000] [0000 0000] [0001 0010] [0011 0100]
     */
    void bitPrint_Element(void* val, int len);

    /**
    * 判断运行此代码的系统是否为大端字节序
    *
    * @Return 是大端字节序（true）；是小端字节序（false）
    */
    bool isBigEndian();

    /**
     * 测试字节对齐
     */
    void testByteAlignment();

    /**
     * 测试字节操纵
     */
    void testByteOperator();
};



#endif //CPPTEST_BITPRINT_H
