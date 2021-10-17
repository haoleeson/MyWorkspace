/**
No767. 重构字符串 （奇偶下标）
给定一个字符串S，检查是否能重新排布其中的字母，使得两相邻的字符不同。
若可行，输出任意可行的结果。若不可行，返回空字符串。

示例1:
输入: S = "aab"
输出: "aba"

示例 2:
输入: S = "aaab"
输出: ""
注意:

S 只包含小写字母并且长度在[1, 500]区间内。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/reorganize-string
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */
package LeetCode

func reorganizeString(S string) string {
    size := len(S)
    if size < 2 {
        return S
    }

    // 统计字符个数
    cnt := [int('z') + 1]int{}
    for _, ch := range S {
        cnt[ch]++
    }
    maxCnt := 0
    maxCntCh := 'a'
    for ch := 'a'; ch <= 'z'; ch++ {
        if cnt[ch] > maxCnt {
            maxCnt = cnt[ch]
            maxCntCh = ch
        }
    }
    // 若有某字符超过一半，无法重构
    if maxCnt > (size + 1) / 2 {
        return ""
    }
    // 可以重构
    ans := make([]byte, size)
    jiIndex, ouIndex := 1, 0
    // 特殊情况: size为奇数，且最大字母数恰好为 (n + 1) / 2, 该最多个数字母只能放偶数下标
    if (size & 0x01) == 0x01 && (size + 1) / 2 == maxCnt {
        for ouIndex < size {
            ans[ouIndex] = byte(maxCntCh)
            ouIndex += 2
        }
        cnt[maxCntCh] = 0
    }

    for ch := 'a'; ch <='z'; ch++ {
        // 优先放奇下标
        for cnt[ch] > 0 && jiIndex < size {
            ans[jiIndex] = byte(ch)
            cnt[ch]--
            jiIndex += 2
        }
        // 奇数下标装满后, 再装偶数下标
        for cnt[ch] > 0 {
            ans[ouIndex] = byte(ch)
            cnt[ch]--
            ouIndex += 2
        }
    }
    return string(ans)
}
