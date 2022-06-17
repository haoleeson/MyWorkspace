package main

import "fmt"

func print_map(m map[byte]int) {
	for key, val := range m {
		fmt.Println("key: ", key, ", val: ", val)
	}
}

func checkInclusion(t, s string) bool {
	len_s, len_t := len(s), len(t)
	need := map[byte]int{}
	window := map[byte]int{}
	for _, ch := range t {
		need[byte(ch)]++
	}

	left, right, valid := 0, 0, 0
	len_need := len(need)

	for right < len_s {
		c := (byte)(s[right])
		right++
		if _, ok := need[c]; ok {
			window[c]++
			if window[c] == need[c] {
				valid++
			}
		}

		for valid == len_need {
			if right-left == len_t {
				return true
			}
			d := (byte)(s[left])
			left++
			if _, ok := need[d]; ok {
				if window[d] == need[d] {
					valid--
				}
				window[d]--
			}
		}
	}

	return false
}

func main() {
	fmt.Println("ans: ", checkInclusion("ab", "eidbaooo"))
	fmt.Println("ans: ", checkInclusion("ab", "eidboaoo"))
}
