/**
 * Go 循环语句
 * for循环形式如下：
 * for init; condition; post { }
 * 其中：init 和 post 参数是可选的，我们可以直接省略它，类似 While 语句。
 * 循环控制语句包括：break、continue、goto。继承自C语言，与其一致：
 * break，经常用于中断当前 for 循环或跳出 switch 语句
 * continue，跳过当前循环的剩余语句，然后继续进行下一轮循环
 * goto，将控制转移到被标记的语句
 */
package main
import "fmt"

/**
 * 判断一个数是否是素数
 * @param num 待判断数
 * @return true -- 是素数；false -- 非素数
 */
func isPrime(num int) bool {
    if num <= 1 {
        return false
    }
    for i := 2; i * i <= num; i++ {
        if num % i == 0 {
            return false
        }
    }
    return true
}

/**
 * 打印小于 100 的所有素数
 */
func printPrimeNumberSmallThan100() {
    fmt.Println("打印小于 100 的所有素数:")
    for num := 2; num < 100; num++ {
        if isPrime(num) {
            fmt.Printf("%d ", num)
        }
    }
}

/**
 * 打印九九乘法表
 * @description 循环嵌套
 */
func printMultiplicationTable() {
    fmt.Printf("\n打印九九乘法表:\n")
    var j int
    for i := 1; i < 10; i++ {
        j = i
        for {
            fmt.Printf("%dx%d=%d", i, j, i * j)
            j++
            if j == 10 {
                break
            }
            fmt.Printf("\t")
        }
        fmt.Printf("\n")
    }
}


func main() {
    // 打印小于 100 的所有素数
    printPrimeNumberSmallThan100()
    // 100以内所有素数的和
    primeNums := [25]int{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97}
    sum := 0
    for i := range primeNums {
        sum += i
    }
    fmt.Printf("\n100以内所有素数的和为：%d", sum)
    // 打印九九乘法表
    printMultiplicationTable()
}