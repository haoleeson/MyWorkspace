/*
No151.reverse-words-in-a-string
*/

func reverseWords(s string) string {
	lenS := len(s)
	ans := ""
	isFirstWord := true
	var wordEndIdx, wordStartIdx int = lenS - 1, 0

	var appendWordToAns func(string)
	appendWordToAns = func(word string) {
		if isFirstWord {
			ans += word
			isFirstWord = false
		} else {
			ans += " " + word
		}
	}

	for wordEndIdx >= 0 {
		// ignore space
		for ; wordEndIdx >= 0 && s[wordEndIdx] == ' '; wordEndIdx-- {
		}
		if wordEndIdx < 0 {
			break
		}

		// find word length
		wordStartIdx = wordEndIdx
		for ; wordStartIdx >= 0 && s[wordStartIdx] != ' '; wordStartIdx-- {
		}

		// add word
		if wordEndIdx == lenS-1 {
			appendWordToAns(string(s[wordStartIdx+1:]))
		} else {
			appendWordToAns(string(s[wordStartIdx+1 : wordEndIdx+1]))
		}

		wordEndIdx = wordStartIdx - 1
	}

	return ans
}
