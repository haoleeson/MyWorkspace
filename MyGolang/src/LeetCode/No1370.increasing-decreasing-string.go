/**
No1370. 上升下降字符串
给你一个字符串 s ，请你根据下面的算法重新构造字符串：
1. （升序）从 s 中选出最小的字符，将它接在结果字符串的后面。
2. 从 s 剩余字符中选出最小的字符，且该字符比上一个添加的字符大，将它接在结果字符串后面。
3. 重复步骤2，直到你没法从 s 中选择字符。

4. （降序）从 s 中选出最大的字符，将它接在结果字符串的后面。
5. 从 s 剩余字符中选出最大的字符，且该字符比上一个添加的字符小，将它接在结果字符串后面。
6. 重复步骤 5 ，直到你没法从 s 中选择字符。

6. 重复步骤 1 到 6 ，直到 s 中所有字符都已经被选过。
在任何一步中，如果最小或者最大字符不止一个 ，你可以选择其中任意一个，并将其添加到结果字符串。

请你返回将 s 中字符重新排序后的 结果字符串 。


示例 1：
输入：s = "aaaabbbbcccc"
输出："abccbaabccba"
解释：第一轮的步骤 1，2，3 后，结果字符串为 result = "abc"
第一轮的步骤 4，5，6 后，结果字符串为 result = "abccba"
第一轮结束，现在s = "aabbcc" ，我们再次回到步骤 1
第二轮的步骤 1，2，3 后，结果字符串为 result = "abccbaabc"
第二轮的步骤 4，5，6 后，结果字符串为 result = "abccbaabccba"

示例 2：
输入：s = "rat"
输出："art"
解释：单词 "rat" 在上述算法重排序以后变成 "art"

示例 3：
输入：s = "leetcode"
输出："cdelotee"

示例 4：
输入：s = "ggggggg"
输出："ggggggg"

示例 5：
输入：s = "spo"
输出："ops"

提示：
1 <= s.length <= 500
s 只包含小写英文字母。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/increasing-decreasing-string
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */
package LeetCode

func sortString(s string) string {
    lenS := len(s)
    cnt := [26]int{0}
    for _, ch := range s {
        cnt[int32(ch - 'a')]++
    }
    ans := make([]byte, 0, lenS)
    for len(ans) < lenS {
        // 升序
        for ch := byte('a'); ch <= byte('z'); ch++ {
            if cnt[int32(ch - 'a')] > 0 {
                ans = append(ans, ch)
                cnt[int32(ch - 'a')]--
            }
        }
        // 降序
        for ch := byte('z'); ch >= byte('a'); ch-- {
            if cnt[int32(ch - 'a')] > 0 {
                ans = append(ans, ch)
                cnt[int32(ch - 'a')]--
            }
        }
    }
    return string(ans)
}
