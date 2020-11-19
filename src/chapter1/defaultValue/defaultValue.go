/**
 * Go 默认值测试
 * 总结：
 * bool默认值false；
 * 整形默认值为“零值”；
 * 数组与map的默认值为空的数组与map
 * 默认值为 nil的类型有：指针、chan、func、error
 */
package main
import "fmt"

func main()  {
    var b1 bool
    fmt.Println("bool:", b1)

    var ui1 uint8
    fmt.Println("uint8:", ui1)
    var ui2 uint16
    fmt.Println("uint16:", ui2)
    var ui3 uint32
    fmt.Println("uint32:", ui3)
    var ui4 uint64
    fmt.Println("uint64:", ui4)
    var i0 int
    fmt.Println("int:", i0)
    var i1 int8
    fmt.Println("int8:", i1)
    var i2 int16
    fmt.Println("int16:", i2)
    var i3 int32
    fmt.Println("int32:", i3)
    var i4 int64
    fmt.Println("int64:", i4)

    var b2 byte
    fmt.Println("byte:", b2)

    var r1 rune
    fmt.Println("rune:", r1)

    var f1 float32
    fmt.Println("float32:", f1)
    var f2 float64
    fmt.Println("float64:", f2)

    var str1 string
    fmt.Println("string:", str1)

    var uip1 uintptr
    fmt.Println("uintptr:", uip1)

    var ptr *int
    fmt.Println("*int:", ptr)

    var arr []int
    fmt.Println("[]int:", arr)

    var map1 map[string] int
    fmt.Println("map[]:", map1)

    var c1 chan int
    fmt.Println("chan:", c1)

    var func1 func(string) int
    fmt.Println("func:", func1)

    var e1 error
    fmt.Println("error:", e1)
}
