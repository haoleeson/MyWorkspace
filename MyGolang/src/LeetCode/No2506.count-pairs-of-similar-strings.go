/*
No2506.count-pairs-of-similar-strings
*/
func stringToBitMap(s string) int {
	var bits int = 0

	for i := 0; i < len(s); i++ {
		bits |= 1 << (s[i] - 'a')
	}

	return bits
}

func Cn2(num int) int {
	if num < 2 {
		return 0
	}
	return num * (num - 1) / 2
}

func similarPairs(words []string) int {
	m := make(map[int]int)
	for _, w := range words {
		k := stringToBitMap(w)
		m[k]++
	}

	ret := 0
	for _, v := range m {
		ret += Cn2(v)
	}
	return ret
}