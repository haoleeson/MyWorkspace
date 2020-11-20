/**
 * Go 条件语句
 * 总结：
 * 不需使用括号将条件包含起来
 * 条件执行块的大括号{}必须存在，即使只有一行语句
 * 左括号必须在if或else的同一行
 * 在if之后，条件语句之前，可以添加变量初始化语句，使用';'进行分隔
 * 在有返回值的函数中，最终的return不能在条件语句中

 */
package main
import "fmt"

/**
 * 返回成绩的级别
 * @description 有效输入范围: [0, 100]
 * @param score 待判断分数
 * @return 0 -- 异常输入; A -- [90, 100]; B -- [80, 89]; C -- [70, 79]; D -- [60, 69]; E -- [0, 59];
 */
func grade(score uint8) byte {
    if score > 100 {
        return 0
    } else if score > 89 {
        return 'A'
    } else if score > 79 {
        return 'B'
    } else if score > 69 {
        return 'C'
    } else if score > 59 {
        return 'D'
    } else {
        return 'E'
    }
    return 0
}

/**
 * 是否是偶数
 * @param num 待判断数字
 * @return false -- 不是偶数； true -- 是偶数
 */
func isEven(num int) bool {
    // 在if之后，条件语句之前，可以添加变量初始化语句，使用';'进行分隔
    if val := num & 0x01; val == 0x00 {
        return true
    }
    return false
}

/**
 * 根据成绩级别颁发小星星
 * @description 有效输入范围: {A, B, C, D, E}
 * @param grade 分数级别
 * @return "ERROR INPUT" -- 异常输入; "****" -- A; "***" -- B; "**" -- C; "*" -- D; "" -- E;
 */
func awardStars(grade byte) string {
    var str string
    switch grade {
        case 'A':
            str = "****"
        case 'B':
            str = "***"
        case 'C':
            str = "**"
        case 'D':
            str = "*"
        case 'E':
            str = ""
        default:
            str = "ERROR INPUT"
    }
    return str
}

/**
 * 根据成绩级别颁发奖学金
 * @description 有效输入范围: {A, B, C, D, E}，达到A--100；达到B--50；达到C--20；达到D--10；达到E--0；奖励可累计
 * @param grade 分数级别
 * @return 获得的奖学金数额
 */
func awardMoney(grade byte) uint8 {
    var money uint8 = 0
    switch grade {
        case 'A':
            money += 100
            fallthrough // 不判断直接执行下一case的执行代码
        case 'B':
            money += 50
            fallthrough // 不判断直接执行下一case的执行代码
        case 'C':
            money += 20
            fallthrough // 不判断直接执行下一case的执行代码
        case 'D':
            money += 10
            fallthrough // 不判断直接执行下一case的执行代码
        case 'E':
        default:
    }
    return money
}

func communicationTest() {
    var c1, c2, c3 chan int
    var i1, i2 int
    select {
        case i1 = <-c1:
            fmt.Printf("received ", i1, " from c1\n")
        case c2 <- i2:
            fmt.Printf("sent ", i2, " to c2\n")
        case i3, ok := (<-c3):  // same as: i3, ok := <-c3
            if ok {
                fmt.Printf("received ", i3, " from c3\n")
            } else {
                fmt.Printf("c3 is closed\n")
            }
        default:
            fmt.Printf("no communication\n")
    }
}

func main() {
    var score uint8
    fmt.Println("输入一个分数:")
    fmt.Scan(&score)
    fmt.Printf("分数(%d)对应成绩等级为：%c\n", score, grade(score))
    fmt.Printf("分数(%d)是否是偶数：%t\n", score, isEven(int(score)))
    fmt.Printf("分数(%d)获得的小星星为：\"%s\"\n", score, awardStars(grade(score)))
    fmt.Printf("分数(%d)获得的奖学金为：%d\n", score, awardMoney(grade(score)))
    communicationTest()
}
