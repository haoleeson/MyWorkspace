/*
No2264.largest-3-same-digit-number-in-string
*/

func largestGoodInteger(num string) string {
    n := len(num)
    betterNum := make([]byte, 3)

    for i:=0; i<n-2; i++ {
        if num[i+1] != num[i] || num[i+2] != num[i] {
            continue
        }
        // exist
        if betterNum[0] == 0 {
            betterNum[0] = num[i]
            betterNum[1] = num[i+1]
            betterNum[2] = num[i+2]
        } else if num[i] > betterNum[0] {
            betterNum[0] = num[i]
            betterNum[1] = num[i+1]
            betterNum[2] = num[i+2]
        }
    }

    if betterNum[0] == 0 {
        return ""
    }
    return string(betterNum)
}