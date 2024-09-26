/*
No2535.difference-between-element-sum-and-digit-sum-of-an-array
*/

func differenceOfSum(nums []int) int {
    var sum, numberSum int = 0, 0

    for _, num := range nums {
        sum += num
        for tmpNum := num; tmpNum > 0; tmpNum /= 10 {
            numberSum += tmpNum % 10
        }
    }

    if numberSum > sum {
        return numberSum - sum
    }
    return sum - numberSum
}