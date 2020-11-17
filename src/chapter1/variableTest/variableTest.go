/**
 * 变量测试
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
    fmt.Println("b1 =", b1)

    // 整数类型
    var a1 int = 2                        // 一般声明变量：var 变量名 数据类型 = 初值
    var a2 int                            // 一般声明变量（无初值）：var 变量名 数据类型; (编译器根据初值类型默认初值，0)
    a3 := a1 + a2                         // 简短声明变量：变量名 := 初值; (编译器根据初值类型自动定义变量类型)
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
    fmt.Println("ui1 =", ui1)
    fmt.Println("ui2 =", ui2)
    fmt.Println("ui3 =", ui3)
    fmt.Println("ui4 =", ui4)
    fmt.Println("i1 =", i1)
    fmt.Println("i2 =", i2)
    fmt.Println("i3 =", i3)
    fmt.Println("i4 =", i4)

    // 浮点类型
    const pi float32 = 3.14159        // const 修饰常量
    var f1 float32 = pi + float32(a3) // 强制转换类型(放大): 变量类型()
    var f2 float64 = float64(pi)      // 强制转换类型(放大，可能造成脏数据): 变量类型()
    a5 := int(f1)                     // 强制转换类型(缩小，可能造成部分数据细节丢失): 变量类型()
    fmt.Println("pi =", pi)
    fmt.Println("f1 =", f1)
    fmt.Println("f2 = float64(", pi, ") =", f2)
    fmt.Println("a5 = int(", f1, ") =", a5)

    // 指针
    var ptr1 *int = &a1
    fmt.Println("ptr1 =", ptr1, "*ptr1 = a1 =", *ptr1)
    ptr2 := &a2
    fmt.Println("ptr2 =", ptr2, "*ptr2 = a2 =", *ptr2)
    ptr2 = (*int)(unsafe.Pointer(&f1)) // 使用unsafe.Pointer进行类型的转换 int -> float32
    fmt.Println("ptr2 =", ptr2, "*ptr2 = f1 =", *ptr2)

    // 数组
    arr := [5]int{0, 1, 2, 3, 4}
    p0 := unsafe.Pointer(&arr[0])
    p3 := unsafe.Pointer(uintptr(p0) + 2 * unsafe.Sizeof(arr[0]))
    *(*int)(p3) = 9
    fmt.Println("p3 =", *(*int)(p3))

    // 其他数字类型
    var c1 byte = 'A'                               // 传统 ASCII 编码的字符，用byte代替，，类型等价于 uint8
    var r1 rune = '好'                               // 代表UTF-8字符，当需要处理中文、日文或者其他复合字符时可用rune，类型等价于 int32
    var ptr3 uintptr = uintptr(unsafe.Pointer(&b1)) // 指针，uintptr值可以进行算术运算
    fmt.Println("c1 =", c1)
    fmt.Println("r1 =", r1)
    fmt.Println("ptr3 =", ptr3, "*ptr3 = b1 =", *(*bool)(unsafe.Pointer(ptr3)))

    // 字符串类型
    var str1 string = "hello world!"
    fmt.Println("str1 =", str1, "len =", len(str1))
}
