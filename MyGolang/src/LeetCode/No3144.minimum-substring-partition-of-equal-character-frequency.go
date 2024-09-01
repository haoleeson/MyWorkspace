/*
No3144. 分割字符频率相等的最少子字符串

给你一个字符串 s ，你需要将它分割成一个或者更多的 平衡 子字符串。比方说，s == "ababcc" 那么 ("abab", "c", "c") ，("ab", "abc", "c") 和 ("ababcc") 都是合法分割，但是 ("a", "bab", "cc") ，("aba", "bc", "c") 和 ("ab", "abcc") 不是，不平衡的子字符串用粗体表示。

请你返回 s 最少 能分割成多少个平衡子字符串。

注意：一个 平衡 字符串指的是字符串中所有字符出现的次数都相同。

 

示例 1：

输入：s = "fabccddg"

输出：3

解释：

我们可以将 s 分割成 3 个子字符串：("fab, "ccdd", "g") 或者 ("fabc", "cd", "dg") 。

示例 2：

输入：s = "abababaccddb"

输出：2

解释：

我们可以将 s 分割成 2 个子字符串：("abab", "abaccddb") 。

 

提示：

1 <= s.length <= 1000
s 只包含小写英文字母。
*/

package LeetCode


type CharCnt struct {
	Cnt []int
	MaxNum int
}

func NewCharCnt(b byte) *CharCnt {
	c := &CharCnt{
		Cnt: make([]int, 26),
		MaxNum: 0,
	}
	c.Cnt[b-'a'] = 1
	c.MaxNum = 1
	return c
}

func (c *CharCnt)AddOne(b byte) {
	c.Cnt[b-'a'] += 1
	if c.Cnt[b-'a'] > c.MaxNum {
		c.MaxNum = c.Cnt[b-'a']
	}
}

func (c *CharCnt)CheckBalance() bool {
	for _, i := range(c.Cnt) {
		if i != 0 && i != c.MaxNum {
			return false
		}
	}
	return true
}

func minimumSubstringsInPartition(s string) int {
	n := len(s)
	b := []byte(s)
	dp := make([]int, n)
	dp[0] = 1

	// dp(i) = for(j=i-1...0) + min(dp[j] if isBalanceString(s[j:i]))
	for i := 1; i < n; i++ {
		tmpMin := dp[i-1] + 1
		c := NewCharCnt(b[i])
		for j:=i-1; j >= 0; j-- {
			c.AddOne(b[j])
			if c.CheckBalance() {
				if j == 0 {
					tmpMin = 1
				} else if dp[j-1] + 1 < tmpMin {
					tmpMin = dp[j-1] + 1
				}
			}
		}
		dp[i] = tmpMin
	}

	return dp[n-1]
}
