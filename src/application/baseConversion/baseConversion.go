/**
 * 进制转换
 */
package main

import "fmt"

/*
 * 二进制转换为十进制
 * @param str 二进制字符串
 * @return int 十进制
 */
func ConvBase2To10(str string) int {
    var num int = 0
    for _, ch := range str {
        num *= 2
        // 有效字符
        if  ch >= '0' && ch <= '1' {
            num += int(ch) - '0'
        } else {
            return -1
        }
    }
    return num
}

/*
 * 16进制转换为十进制
 * @param str 十六进制字符串
 * @return int 十进制
 */
func ConvBase16To10(str string) int {
    var num int = 0
    for _, ch := range str {
        num *= 16
        // 有效字符
        if  ch >= '0' && ch <= '9' {
            num += int(ch) - '0'
        } else if ch >= 'A' && ch <= 'F' {
            num += int(ch) - 'A' + 10
        } else if ch >= 'a' && ch <= 'f' {
            num += int(ch) - 'a' + 10
        } else {
            return -1
        }
    }
    return num
}

/*
 * 任意进制转换为十进制
 * @param str 任意进制字符串
 * @param base 几进制: 进制有效范围：[2, 36]
 * @return int 十进制
 */
func ConvAnyBaseTo10(str string, base int) int {
    if base < 2 || base > 36 {
        return -1
    }
    var num int = 0
    for _, ch := range str {
        num *= base
        // 有效字符
        if  ch >= '0' && ch <= '9' {
            num += int(ch) - '0'
        } else if ch >= 'A' && ch <= 'A' + rune(base) - 11 {
            num += int(ch) - 'A' + 10
        } else if ch >= 'a' && ch <= 'a' + rune(base) - 11 {
            num += int(ch) - 'a' + 10
        } else {
            return -1
        }
    }
    return num
}

/**
 * 除法
 * @param dividend 被除数
 * @param divisor 除数
 * @return int 商
 * @return int 余数
 */
func div (dividend int, divisor int) (int, int) {
    quotient := dividend / divisor // 商
    remainder := dividend % divisor // 余数
    return quotient, remainder
}

/*
 * 十进制转换为二进制
 * @param num 十进制数
 * @return str 二进制字符串
 */
func ConvBase10To2(num int) string {
    var ans []byte
    var reminder int
    for num > 0 {
        num, reminder = div(num, 2)
        ans = append(ans, '0' + byte(reminder))
    }
    // 翻转 ans
    len := len(ans)
    for i := 0; i * 2 < len; i++ {
        ans[i] ^= ans[len - 1 - i]
        ans[len - 1 - i] ^= ans[i]
        ans[i] ^= ans[len - 1 - i]
    }
    return string(ans)
}

/*
 * 十进制转换为任意进制
 * @param num 十进制数
 * @param targetBase 目标进制: 进制有效范围：[2, 36]
 * @return str 目标进制字符串
 */
func ConvBase10ToAny(num int, targetBase int) string {
    if targetBase < 2 || targetBase > 36 {
        return ""
    }
    var ans []byte
    var reminder int
    for num > 0 {
        num, reminder = div(num, targetBase)
        if reminder < 10 {
            ans = append(ans, '0' + byte(reminder))
        } else {
            ans = append(ans, 'A' + byte(reminder - 10))
        }
    }
    // 翻转 ans
    len := len(ans)
    for i := 0; i * 2 < len - 1; i++ {
        ans[i] ^= ans[len - 1 - i]
        ans[len - 1 - i] ^= ans[i]
        ans[i] ^= ans[len - 1 - i]
    }
    return string(ans)
}

func main() {
    fmt.Println(ConvBase10ToAny(14, 16)) // E
    fmt.Println(ConvBase10To2(14)) // 1110
    fmt.Println(ConvBase2To10("1011"))        // 11
    fmt.Println(ConvBase16To10("78CD4"))      // 494804
    fmt.Println(ConvAnyBaseTo10("1011", 2))   // 11
    fmt.Println(ConvAnyBaseTo10("78CD4", 16)) // 494804
    fmt.Println(ConvAnyBaseTo10("700", 8))    // 448
}