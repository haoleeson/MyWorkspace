layout: post
title: 验证变量在内存中的存储
date: 2019/07/24 21:44:44
updated: 2019/07/25 00:31:45
comments: true
tags:

- C++
categories:
- 技术

---
<img src="https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/bitPrint.jpg" class="full-image" />

众所周知，程序中的变量存放于计算机内存中，程序对这些变量执行特定的赋值和计算等操作以实现某种功能。你是否好奇变量是如何被存储和表示于内存之中呢？不同类型的变量所占字节大小不同、相同类型的变量在不同操作系统内所占字节大小也可能不同。而对于超过1字节的变量，根据不同的操作系统，还涉及字节序、字节对齐、大端or小端等其他问题。接下来让我们探究一下变量在内存中的表示与存放吧！

关键词: 比特打印、字节序、字节对齐
<!-- more -->

# 1. 背景
一般初学一门编程语言时，最开始了解的就是这门语言支持的基本变量类型、其大小（占多少字节），可表示的数值范围。如在C/C++语言中，char类型的变量占一个字节(一个字节含8bit，为减少内存管理负担，一字节通常也是操作系统内存的最小单位，但应用时每一bit可被赋予不同的语义）。char变量有8bit，除去最高位为符号位用于表示数的正负外，剩余的低7位可以表示到(0 ~ 2^7 - 1，即0～127)，加上符号位即 + - (0～127)，又由于"-0"(0x80)与我们常用的数学方式不符，而被译为-128，故在C/C++程序语言中，一个char类型的变量，仅占用一个字节，却被可以表示 -128 ~ 127 的数值范围。
# 2. 代码探究
## 2.1. 打印每一比特原理概述
运用C/C++中提供的位操作符和与操作原理“a & 1 = a” 和 “a & 0 = 0”获得每一位的01值。依次从最高位开始提取，若位1则打印“1”，若为0则打印“0”，然后提取次高位的01值并打印，直至提取打印到最低位。至此一个字节的每一比特的值都以打印出来。下面是代码演示：

## 2.2. 编码实验
### 2.2.1. 打印 byte 变量的每一比特
```c++
/**
     * 打印一个 byte 变量的每一位
     * 默认每一字节从左至右 对应 高位至地位
     * eg. 0x80  --> [1000 0000]
     * */
void BitPrint::bitPrint_Byte(const byte val) {
    byte comp = 0x80;//相当于标尺，当前取最高位
    cout << " [";
    while (comp > 0) {
        if (comp == 0x08)
            cout << " ";
        if ((val & comp) == comp)
            cout << "1";
        else
            cout << "0";
        comp >>= 1;//逻辑右移，依次取每一位
    }
    cout << "]";
}
```
当在调用该函数并传入参数0x55时，其执行结果为:
```c++
[0101 0101]
```
**分析**：
由于传入参数0x55其高低字节都为5，二进制中表示为0101，而我们可以看到其在内存中存储结果其高低字节分别为[0101 0101]，与分析相符。

### 2.2.2. 打印 char 变量的每一比特
```c++
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
```
当在调用该函数并传入参数'M'时，其执行结果为:
```c++
char = M
Bits: [0100 1101]
```

**分析**：
char类型与byte类型十分相似，都占用一个字节，但其最高位拥有特殊语义，最高位为0表示正数，最高位为1表示负数。当传入参数为'M'，查询ASCII（美国信息交换标准代码）表可知'M'的为表中第77个字符，用0x4D表示。其中高字节4二进制表示为0100，低字节D二进制表示为1101，且最高位（最左位）为0表示正数，结果与分析一致。

### 2.2.3. 打印 int 变量的每一比特
```c++
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
```
当在调用该函数并传入参数19088743时，其执行结果为:
```c++
int = 19088743
Bits: [0110 0111] [0100 0101] [0010 0011] [0000 0001]
```
**分析**：

int变量类型占用四个字节，其最高位拥有特殊语义，最高位为0表示正数，最高位为1表示负数。int变量占四个字节，所以就会引发这样一个问题————“字节在电脑中存放时的序列与输入（输出）时的序列是先到的在前还是后到的在前？”针对此问题，产生两种不同的字节序，即规定多字节变量在内存中连续存放时的顺序是低地址对应高字节or低地址对应低字节。产生了两种字节序：
* 小端字节序（正序）：高字节对应内存的高地址
* 大端字节序（逆序）：高字节对应内存的低地址（网络传输统一用大端字节序）
由于不同的系统采用的字节序不同，正好也可验证下自己的操作系统采用哪种字节序。
当传入参数为19088743，其十六进制表示为0x01234567。而分析其执行结果，低地址存放为[0110 0111]，十六进制为0x67，对应int值的低字节；而高地址存放为[0000 0001]，十六进制为0x01，对应int值的高字节。故可得知博主操作系统字节序为小端字节序（正序）。

## 2.3. 扩展延伸
### 2.3.1. 打印 任意 变量的每一比特
```c++
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
    delete byteBuf;//释放byteBuf内存
}
```
当在调用该函数并传入参数为一个自定义类（或结构体）时，其执行结果为:
```c++
//传入参数：学生成绩类的首地址
//学生成绩类
class Student {
public:
    char id;
    int score;
    Student(char id, int score) {
        this->id = id;
        this->score = score;
    }
};
//主函数内运行
Student* xiaoming = new Student('A', 88);
cout << "class = {" << xiaoming->id << ", " << xiaoming->score << "}" << endl;
bitPrint->bitPrint_Element(xiaoming, sizeof(Student));

//运行结果为：
class = {A, 88}
Bits: [0100 0001] [0000 0000] [0000 0000] [0000 0000] [0101 1000] [0000 0000] [0000 0000] [0000 0000]
```
**分析**：
从学生成绩类的定义可以看出，此类含有两个属性：char类型的学生编号id 和 int类型的学生成绩score，按理说这个类实例化后分配的内存应该是（1+4）为5个字节，但结果确是8个字节，这是为了方便快速地寻址，编译器会采用字节对齐，将下一个变量地址放置在系统能快速读取的位置（如：32位系统，放在偶地址的变量能够1个读周期取到值，而放在奇地址的变量却需要2个读周期才能取到值，故会存在字节对齐）。所以在第一个char变量后跳过了3个字节，将第二个int变量首地址设置为第5个字节。故此Student类在内存中的存放为：0x41、连续3个0x00对齐字节，4个字节的int变量[0101 1000] [0000 0000] [0000 0000] [0000 0000]，合计8个字节。

### 2.3.2. 判断运行此代码的系统是否为大端字节序
```c++
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
//主函数内运行
//判断运行此代码的系统是否为大端字节序
if (bitPrint->isBigEndian()) {
    cout << endl << "Yes, this system is Big Endian System" << endl;
} else {
    cout << endl << "No, this system is Small Endian System" << endl;
}

//运行结果为：
No, this system is Small Endian System
```
**分析**：

通过判断特定的int变量在内存中存放的次序即可判断当前系统采用的字节序。实际操作为取特定值为0x01的int变量的低地址的一个字节为Byte变量，若其值等于低字节0x01则为正序（小端），反之则为大端字节序。

# 3. 字节对齐
前面分析到为了方便快速地寻址，编译器会采用字节对齐，将下一个变量地址放置在系统能快速读取的位置（如：32位系统，放在偶地址的变量能够1个读周期取到值，而放在奇地址的变量却需要2个读周期才能取到值，故会存在字节对齐）。
即对待结构体内的每一位元素就像对待sizeof为n的数组一样，从结构体首地址开始依次向后为每个成员寻找第一个满足“addr % N == 0”的地址，如果不够则在前一个成员变量后补空字节使之满足条件。上面的N为对齐参数(N = min(sizeof(第i个成员类型),n))，n，可以设置，在c++中缺省值为8。
下面一起来验证一下吧！
## 3.1. 先自定义一个包含多类型变量的结构体
```c++
struct MSG1 {
    char ID[16];// 16
    unsigned short type;// 2
    char flag;// 1  -->   字节对齐（其后闲置1字节，共占2字节）
    unsigned int uiHashValue;// 4
    unsigned int uiDataLen;// 4

    char contentData[1];
};
struct MSG0 {
    char ID[16];// 16
    unsigned short type;// 2
    char flag; // 1  -->   字节对齐（其后闲置1字节）
    unsigned int uiHashValue;// 4
    unsigned int uiDataLen;// 4  -->   字节对齐（其后闲置4字节，共占8字节）
    unsigned long long int ulStartTime;// 8
    unsigned long long int ulEndTime;// 8

    char contentData[1];
};
```
定义一个该结构体变量并打印出各成员变量的地址如下
```c++
int main() {
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
    return 0;
}
//运行结果为：
&msg1:				0x7ffeed56a8d8 , 0
&msg1.ID:			0x7ffeed56a8d8 , 0
&msg1.type:			0x7ffeed56a8e8 , 16
&msg1.flag:			0x7ffeed56a8ea , 18
&msg1.uiHashValue:	0x7ffeed56a8ec , 20
&msg1.uiDataLen:	0x7ffeed56a8f0 , 24
&msg1.contentData:	0x7ffeed56a8f4 , 28

&msg0:				0x7ffeecdd38c0 , 0
&msg0.ID:			0x7ffeecdd38c0 , 0
&msg0.type:			0x7ffeecdd38d0 , 16
&msg0.flag:			0x7ffeecdd38d2 , 18
&msg0.uiHashValue:	0x7ffeecdd38d4 , 20
&msg0.uiDataLen:	0x7ffeecdd38d8 , 24
&msg0.ulStartTime:	0x7ffeecdd38e0 , 32
&msg0.ulEndTime:	0x7ffeecdd38e8 , 40
&msg0.contentData:	0x7ffeecdd38f0 , 48
```
**分析**：

通过结构体MSG1定义的变量，其成员变量的地址于首地址的偏差可以看出，第三个成员变量flag虽为char类型，只占1字节，但编译器为了访问后续自变量更方便（放在偶地址，若为奇地址需要2个读周期才能取到值），所以编译器将下一个变量uiHashValue的首地址向后挪动一位到偏移地址为20处（偶地址的变量能够1个读周期取到值），相当于第三个成员变量占用2各字节（后一字节闲置）
* 第一个成员地址为0，已对齐。
* 第二个成员，由于上一个成员大小为16所以当前准地址为：16，N = min(sizeof(unsigned short),8)等于2，满足“addr % N == 0”，已对齐
* 第三个成员，由于上一个成员大小为2所以当前准地址为：18，N = min(sizeof(char),8)等于1，满足“addr % N == 0”，已对齐
* 第四个成员，由于上一个成员大小为1所以当前准地址为：19，N = min(sizeof(unsigned int),8)等于4，不满足“addr % N == 0”，19%4余1，故在前一个变量后补1个字节，使当前地址20满足“addr % N == 0”
* 第五个成员，由于上一个成员大小为4所以当前准地址为：24，N = min(sizeof(unsigned int),8)等于4，满足“addr % N == 0”，已对齐
* 第六个成员，由于上一个成员大小为4所以当前准地址为：28，N = min(sizeof(char),8)等于1，满足“addr % N == 0”，已对齐

同理对结构体MSG0的实际变量定义的变量，齐成员变量的地址于首地址的偏差可看出除了同样在第三个成员变量flag后跳过了1个字节，将下一个变量uiHashValue的首地址向后挪动一位到偏移地址为20处外，还在第5个变量uiDataLen后插入4字节闲置字节{8+8},{2+(1+1)+4},{(4+4)},{8},{8}。
* 第一个成员地址为0，已对齐。
* 第二个成员，由于上一个成员大小为16所以当前准地址为：16，N = min(sizeof(unsigned short),8)等于2，满足“addr % N == 0”，已对齐
* 第三个成员，由于上一个成员大小为2所以当前准地址为：18，N = min(sizeof(char),8)等于1，满足“addr % N == 0”，已对齐
* 第四个成员，由于上一个成员大小为1所以当前准地址为：19，N = min(sizeof(unsigned int),8)等于4，不满足“addr % N == 0”，19%4余1，故在前一个成员后补1个字节，使当前地址20满足“addr % N == 0”
* 第五个成员，由于上一个成员大小为4所以当前准地址为：24，N = min(sizeof(unsigned int),8)等于4，满足“addr % N == 0”，已对齐
* 第六个成员，由于上一个成员大小为4所以当前准地址为：28，N = min(sizeof(unsigned long long int),8)等于8，不满足“addr % N == 0”，28%8余4，故在前一字成员后补4个字节，使当前地址为32满足“addr % N == 0”
* 第七个成员，由于上一个成员大小为8所以当前准地址为：40，N = min(sizeof(unsigned int),8)等于8，满足“addr % N == 0”，已对齐
* 第八个成员，由于上一个成员大小为8所以当前准地址为：48，N = min(sizeof(char),8)等于1，满足“addr % N == 0”，已对齐

## 3.2. 禁止编译器自动字节对齐
我们可以在定义结构体上方加一句配置，设置对齐参数为1字节从而实现关闭编译器自动对齐的目的（可能带来性能损失或其他错误）。
```c++
#pragma pack(1) // 编译使用1字节对齐，未设置则自动字节对齐
struct MSG1 {
    ...
}
struct MSG0 {
    ...
}
```
打印出各成员变量的地址如下：
```c++
&msg1:				0x7ffee5ce28d8 , 0
&msg1.ID:			0x7ffee5ce28d8 , 0
&msg1.type:			0x7ffee5ce28e8 , 16
&msg1.flag:			0x7ffee5ce28ea , 18
&msg1.uiHashValue:	0x7ffee5ce28eb , 19
&msg1.uiDataLen:	0x7ffee5ce28ef , 23
&msg1.contentData:	0x7ffee5ce28f3 , 27

&msg0:				0x7ffee5ce28a8 , 0
&msg0.ID:			0x7ffee5ce28a8 , 0
&msg0.type:			0x7ffee5ce28b8 , 16
&msg0.flag:			0x7ffee5ce28ba , 18
&msg0.uiHashValue:	0x7ffee5ce28bb , 19
&msg0.uiDataLen:	0x7ffee5ce28bf , 23
&msg0.ulStartTime:	0x7ffee5ce28c3 , 27
&msg0.ulEndTime:	0x7ffee5ce28cb , 35
&msg0.contentData:	0x7ffee5ce28d3 , 43
```
可以看出设置字节对齐参数为1字节后，相当于关闭了字节对齐

# 4. 按字节访问
所有对结构体成员的指针访问，都可以理解为用特定的类型去解读一个地址。下方为示例：
```c++
#define MSG1_HEAD_LEN  (offsetof(MSG1,contentData))
#define MSG0_HEAD_LEN  (offsetof(MSG0,contentData))

int main() {
    cout << MSG0_HEAD_LEN << endl;
    cout << MSG1_HEAD_LEN << endl;

    MSG0 msg0;
    msg0.ulStartTime = 20181112ULL;
    msg0.ulEndTime = 561341235ULL;

    void* p = &msg0;

    MSG1* msg1Ptr = (MSG1*)p;

    cout  << "(msg1Ptr->contentData): " << (void *)(msg1Ptr->contentData) << ", " <<  *(unsigned long long int*)(msg1Ptr->contentData)  << " ULL" << endl;
    cout  << "(msg1Ptr->contentData + 8): " << (void *)(msg1Ptr->contentData + 8)<< ", " <<  *(unsigned long long int*)(msg1Ptr->contentData + 8) << " ULL" << endl;

    return 0;
}
```
运行结果：
```c++
43
27
(msg1Ptr->contentData): 0x7ffeeb5118e3, 20181112 ULL
(msg1Ptr->contentData + 8): 0x7ffeeb5118eb, 561341235 ULL
```
**分析**：

代码主要是有结构体MSG0定义了一个变量并未其相对于MSG1多出的两个变量赋值，然后实现用MSG1类型的指针访问MSG0中多出的变量（默认没有指针），来例证c++的访问变量的机制为“以特定的类型去解读一个地址”，无论其是否真的被定义成那样（前提条件：该地址是被定义过的且可访问的地址，否则会被认为内存越界）。


附录：完整代码详见个人git仓库：[BitPrint.cpp](https://github.com/EisenHao/Cpp_Learning/blob/master/BitPrint.cpp),[BitPrint.h](https://github.com/EisenHao/Cpp_Learning/blob/master/BitPrint.h)

# 5. 参考文档

- [结构体内存分配分析](https://wenku.baidu.com/view/ec9cba000740be1e650e9aa5.html)
