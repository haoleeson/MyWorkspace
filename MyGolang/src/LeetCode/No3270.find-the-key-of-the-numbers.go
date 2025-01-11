/*
No3270.find-the-key-of-the-numbers
*/

func splitNum(num int) []int {
    ret := make([]int, 4)
    ret[0] = num / 1000
    ret[1] = num / 100 % 10
    ret[2] = num / 10 % 10
    ret[3] = num % 10
    
    return ret
}

func smaller(a, b []int) []int {
    for i := 0; i<4; i++ {
        if b[i] < a[i] {
            a[i] = b[i]
        }
    }
    return a
}

func generateKey(num1 int, num2 int, num3 int) int {
    ret := splitNum(num1)
    ret = smaller(ret, splitNum(num2))
    ret = smaller(ret, splitNum(num3))
    
    return 1000*ret[0]+100*ret[1]+10*ret[2]+ret[3]
}