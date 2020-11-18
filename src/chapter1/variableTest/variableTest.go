/**
 * Go 变量测试
 */
package main // 定义本.go文件所在的包是main
import (
    "fmt"
    "unsafe"
) // 引入基本包fmt

// 主函数
func main() {
    // 布尔类型
    var b1 bool = false
    fmt.Println("b1 =", b1, ", Sizeof(b1) =", unsafe.Sizeof(b1))

    // 整数类型（默认为: int）
    var a1 int = 2                        // 一般声明变量：var 变量名 数据类型 = 初值
    var a2 int                            // 一般声明变量（无初值）：var 变量名 数据类型; (编译器根据初值类型默认初值，0)
    a3 := a1 + a2                         // 简短声明变量：变量名 := 初值; (编译器根据初值类型自动定义变量类型)
    var a4 byte = 97                      // 字节类型，等价于 uint8，可用于存储并处理 ASCII 码
    var a5 rune = 22909                   // 等价于 int32，可用于存储并处理 Unicode 码  '好'(22909)

    var ui1 uint8 = 255                   // 2^8 - 1
    var ui2 uint16 = 65535                // 2^16 - 1
    var ui3 uint32 = 4294967295           // 2^32 - 1
    var ui4 uint64 = 18446744073709551615 // 2^64 - 1
    var i1 int8 = -128                    // -2^7, 2^7 - 1
    var i2 int16 = -32768                 // -2^15, 2^15 - 1
    var i3 int32 = -2147483648            // -2^31, 2^31 - 1
    var i4 int64 = -9223372036854775808   // -2^63, 2^63 - 1
    fmt.Println("a1 =", a1)
    fmt.Println("a2 =", a2)
    fmt.Println("a3 =", a3)
    fmt.Printf("a4 = %c\n", a4)
    fmt.Printf("a5 = %c\n", a5)
    fmt.Println("ui1 =", ui1)
    fmt.Println("ui2 =", ui2)
    fmt.Println("ui3 =", ui3)
    fmt.Println("ui4 =", ui4)
    fmt.Println("i1 =", i1)
    fmt.Println("i2 =", i2)
    fmt.Println("i3 =", i3)
    fmt.Println("i4 =", i4)

    // 浮点类型(默认为: float64)
    const pi float32 = 3.1415926535   // const 修饰常量(4字节浮点数赋值时，尾部可能丢失。eg.'6535')
    var f1 float32 = pi + float32(a3) // 强制转换类型(放大): 变量类型()
    var f2 float64 = float64(pi)      // 强制转换类型(放大，可能造成脏数据): 变量类型()
    a6 := int(f1)                     // 强制转换类型(缩小，可能造成部分数据细节丢失): 变量类型()
    fmt.Println("pi =", pi)
    fmt.Println("f1 =", f1)
    fmt.Println("f2 = float64(", pi, ") =", f2)
    fmt.Println("a6 = int(", f1, ") =", a6)

    // 指针
    var ptr1 *int = &a1
    fmt.Println("ptr1 =", ptr1, "*ptr1 = a1 =", *ptr1)
    ptr2 := &a2
    fmt.Println("ptr2 =", ptr2, "*ptr2 = a2 =", *ptr2)
    ptr2 = (*int)(unsafe.Pointer(&f1)) // 使用unsafe.Pointer进行类型的转换 int -> float32
    fmt.Println("ptr2 =", ptr2, "*ptr2 = f1 =", *ptr2)
    // 指针数组
    var ptrArr [3]*int
    ptrArr[0] = &a1
    ptrArr[1] = (*int)(unsafe.Pointer(&f1))
    ptrArr[2] = (*int)(unsafe.Pointer(&b1))
    fmt.Println("ptrArr[0] =", *ptrArr[0], "ptrArr[1] =", *(*float32)(unsafe.Pointer(ptrArr[1])), "ptrArr[2] =", *(*bool)(unsafe.Pointer(ptrArr[2])))

    // 数组
    arr := [5]int{0, 1, 2, 3, 4}
    p0 := unsafe.Pointer(&arr[0])
    p3 := unsafe.Pointer(uintptr(p0) + 2 * unsafe.Sizeof(arr[0]))
    *(*int)(p3) = 9
    fmt.Println("p3 =", *(*int)(p3))
    arr2D := [3][4]int{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}
    fmt.Println("arr2D[2][3] =", arr2D[2][3])

    // 其他数字类型
    var c1 byte = 'A'                               // 传统 ASCII 编码的字符，用byte代替，，类型等价于 uint8
    var r1 rune = '好'                              // 代表UTF-8字符，当需要处理中文、日文或者其他复合字符时可用rune，类型等价于 int32
    var ptr3 uintptr = uintptr(unsafe.Pointer(&b1)) // 指针，uintptr值可以进行算术运算
    fmt.Println("c1 =", c1)
    fmt.Println("r1 =", r1)
    fmt.Println("ptr3 =", ptr3, "*ptr3 = b1 =", *(*bool)(unsafe.Pointer(ptr3)))

    // 字符串类型（使用utf-8编码，变长编码(1~4)，字符串不可改值）
    var str1 string = "hello world!"
    // len()返回字符串的字符占用的字节数，而非字符个数
    fmt.Printf("str1 = %q, len = %d, Sizeof(str1) =%d\n", str1, len(str1), unsafe.Sizeof(str1))
    c2 := str1[2]
    fmt.Println("c2 =", c2)
    // str[2] = 'a'                                 // error, 字符串不能改某字节的值
    // ptr4 := unsafe.Pointer(&str1[2])             // error, 获取字符串某字节地址属于非法行为
    var str2 string = "世界你好"                     // utf-8不是固定字长编码（1~4字节），中文汉字在utf-8中一般是占3个字节
    fmt.Println("str2 =", str2, ", len =", len(str2), ", Sizeof(str2) =", unsafe.Sizeof(str2))
    var str3 string = "Go爱好者"
    fmt.Println("str3 =", str3)
    // rune类型逐个解析string每个字符(变长编码utf8)
    fmt.Printf("  => by runes(char): %q\n", []rune(str3))
    // 查看rune解读字符串的每一位utf8的值（变长）
    fmt.Printf("  => by runes(hex): %x\n", []rune(str3))
    // 查看byte解读字符串的utf8变长编码字符
    fmt.Printf("  => by byte(hex) :[% x]\n", []byte(str3))

    // 结构体
    type Student struct {
        name string
        id uint64
        sex bool
        age uint8
    }
    student1 := Student{"xiaoming", 123456, true, 15}
    fmt.Println(student1)
    fmt.Println(student1.name)
    // 结构体指针
    var studentPtr *Student
    studentPtr = &student1
    studentPtr.age += 1                             // 结构体成员小写（private）是相对于包的，因此这里指针可以访问到值
    fmt.Println("studentPtr.age =", studentPtr.age, "; student1.age =", student1.age)
}
