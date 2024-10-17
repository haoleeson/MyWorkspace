/*
No3200.maximum-height-of-a-triangle
*/

func calcHeight(j, o int) int {
    // 用  k * k 个 red 球排奇数列, 可排 k 层
    hJ := int(math.Sqrt(float64(j))) * 2 - 1
    // 用 j * (2 * j + 2) / 2 个 red 球排偶数列，可排 j 层
    hO := 2 * int((-1 + math.Sqrt(1 + 4 * float64(o))) / 2)

    return min(hJ, hO) + 1
}

func maxHeightOfTriangle(red int, blue int) int {
    res1 := calcHeight(red, blue)
    res2 := calcHeight(blue, red)

    return max(res1, res2)
}