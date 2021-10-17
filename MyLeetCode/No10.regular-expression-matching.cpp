#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * No10. 正则表达式匹配（动态规划）
 * 给你一个字符串s和一个字符规律p，请你来实现一个支持 '.'和'*'的正则表达式匹配。
'.' 匹配任意单个字符
'*' 匹配零个或多个前面的那一个元素
所谓匹配，是要涵盖整个字符串s的，而不是部分字符串。

说明:
s可能为空，且只包含从a-z的小写字母。
p可能为空，且只包含从a-z的小写字母，以及字符.和*。

示例 1:
输入:
s = "aa"
p = "a"
输出: false
解释: "a" 无法匹配 "aa" 整个字符串。

示例 2:
输入:
s = "aa"
p = "a*"
输出: true
解释:因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次。

示例3:
输入:
s = "ab"
p = ".*"
输出: true
解释:".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。

示例 4:
输入:
s = "aab"
p = "c*a*b"
输出: true
解释:因为 '*' 表示零个或多个，这里 'c' 为 0 个, 'a' 被重复一次。因此可以匹配字符串 "aab"。

示例 5:
输入:
s = "mississippi"
p = "mis*is*p*."
输出: false

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/regular-expression-matching
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 力扣官解：动态规划
 * 题目中的匹配是一个「逐步匹配」的过程：我们每次从字符串 p 中取出一个字符或者「字符 + 星号」的组合，并在 s 中进行匹配。对于 p 中一个字符而言，它只能在 s 中匹配一个字符，匹配的方法具有唯一性；而对于 p 中字符 + 星号的组合而言，它可以在 s 中匹配任意自然数个字符，并不具有唯一性。因此我们可以考虑使用动态规划，对匹配的方案进行枚举。

我们用 f[i][j] 表示 s 的前 i 个字符与 p 中的前 j 个字符是否能够匹配。在进行状态转移时，我们考虑 p 的第 j 个字符的匹配情况：

1. 如果 p 的第 j 个字符是一个小写字母，那么我们必须在 s 中匹配一个相同的小写字母，即
也就是说，如果 s 的第 i 个字符与 p 的第 j 个字符不相同，那么无法进行匹配；否则我们可以匹配两个字符串的最后一个字符，完整的匹配结果取决于两个字符串前面的部分。

2. 如果 p 的第 j 个字符是 *，那么就表示我们可以对 p 的第 j-1j−1 个字符匹配任意自然数次。在匹配 00 次的情况下，我们有
也就是我们「浪费」了一个字符 + 星号的组合，没有匹配任何 s 中的字符。

在匹配 1,2,3,⋯ 次的情况下，类似地我们有
如果我们通过这种方法进行转移，那么我们就需要枚举这个组合到底匹配了 s 中的几个字符，会增导致时间复杂度增加，并且代码编写起来十分麻烦。我们不妨换个角度考虑这个问题：字母 + 星号的组合在匹配的过程中，本质上只会有两种情况：
a1. 匹配 s 末尾的一个字符，将该字符扔掉，而该组合还可以继续进行匹配；
a2. 不匹配字符，将该组合扔掉，不再进行匹配。

如果按照这个角度进行思考，我们可以写出很精巧的状态转移方程：
s[i] == p[j-1], f[i][j] = f[i-1][j] or f[i][j-2]
s[i] != p[j-1], f[i][j] = f[i][j-2]

3. 在任意情况下，只要 p[j] 是 .，那么 p[j] 一定成功匹配 s 中的任意一个小写字母。

最终状态转移方程：
当 p[j] != '*'，且s[i] matches p[j]，f[i][j] = f[i-1][j-1]
当 p[j] != '*'，且s[i] !matches p[j]，false
当p[j] == '*'，且s[i] matches p[j-1]，f[i][j] = f[i-1][j] or f[i][j] = f[i][j-2] // 即s*匹配 or 忽略 s*
当p[j] == '*'，且s[i] !matches p[j-1]，f[i][j] = f[i][j-2]


动态规划的边界条件为 f[0][0]=true，即两个空字符串是可以匹配的。最终的答案即为 f[m][n]，其中 mm 和 nn 分别是字符串 s 和 p 的长度。
 */
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size();
        int n = p.size();

        /** 创建临时函数以方便重复调用(在C++11标准的语法中，auto被定义为自动推断变量的类型)
         * [](){}; 是在定义一个函数
         * []中括号里可以用&修饰，具体什么作用可以查查资料，我也不太清楚，在大部分情况下&符号不加也没关系，但有时编译器无法隐式捕获；
         * ()小括号中是形参列表；
         * {}括号中是函数体，
         * 因为是定义函数,大括号后面记得加 ; 分号
         */
        auto matches = [&](int i, int j) {
            // i j 表示第几个字符，从1开始，关系为：字符串内下标加1
            if (i == 0) {
                return false;
            }
            // 若p的第j个字符为. 且s不为空，则一定可以匹配
            if (p[j - 1] == '.') {
                return true;
            }
            return s[i - 1] == p[j - 1];
        };

        vector<vector<int>> f(m + 1, vector<int>(n + 1));
        f[0][0] = true;
        // s为空时也是可以参与匹配的，故i从0开始
//        当 p[j] != '*'，且s[i] matches p[j]，f[i][j] = f[i-1][j-1]
//        当 p[j] != '*'，且s[i] !matches p[j]，false
//        当p[j] == '*'，且s[i] matches p[j-1]，f[i][j] = f[i-1][j] or f[i][j] = f[i][j-2] // 即s*匹配 or 忽略 s*
//        当p[j] == '*'，且s[i] !matches p[j-1]，f[i][j] = f[i][j-2]
        for (int i = 0; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p[j - 1] == '*') {
                    f[i][j] |= f[i][j - 2];
                    if (matches(i, j - 1)) {
                        f[i][j] |= f[i - 1][j];
                    }
                }
                else {
                    if (matches(i, j)) {
                        f[i][j] |= f[i - 1][j - 1];
                    }
                }
            }
        }
        return f[m][n];
    }
};

/**
 * 暴力倒推，情况及其复杂（无法处理）
 */
class Solution0 {
public:
    bool isMatch(string s, string p) {
        int lenS = s.length(), lenP = p.length(), iteratorS = lenS - 1, iteratorP = lenP - 1;
        char ch = 0;

        // 倒序判断
        while (iteratorP >= 0) {
            ch = p[iteratorP];

            switch (ch) {
                // 1. 为 .* 或 [a-z]*
                case '*':
                    ch = p[--iteratorP];
                    // 1.1 为 .*
                    if (ch == '.') {
                        // .* 直接匹配所有 s 剩下部分
                        if (iteratorP == 0) {
                            return true;
                        }
                        // 判断 p 余下部分是否为 s 剩下部分的起始子串

                    } else {
                        // 1.2 为 [a-z]*
                        int countS = 0;
                        int countP = 0;
                        while (iteratorS >= 0 && s[iteratorS] == ch) {
                            --iteratorS;
                            ++countS;
                        }
                        while (iteratorP >= 0 && p[iteratorP] == ch) {
                            ++countP;
                            --iteratorP;
                        }
                        // 特殊情况：sss   sssss*
                        if (countP > countS + 1) {
                            return false;
                        }
                    }
                    break;
                    // 2. 为 .
                case '.':
                    if (iteratorS < 0) {
                        return false;
                    }
                    --iteratorS;
                    --iteratorP;
                    break;
                    // 3. 其他字符[a-z]
                default:
                    if (iteratorS < 0 || s[iteratorS] != p[iteratorP]) {
                        return false;
                    }
                    --iteratorS;
                    --iteratorP;
                    break;
            }
        }
        return iteratorS >= 0 ? false : true;
    }
};

int main() {
    Solution solution;
    string s = "aaa";
    string p = "ab*a*c*a";

    cout << solution.isMatch(s, p) << endl;
    return 0;
}
