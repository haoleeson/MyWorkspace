#ifndef __KMP_H_
#define __KMP_H_

#include <iostream>
#include <string>
#include <vector>

class KMP {
private:
    /**
     * 初始化部分匹配表（根据模式串, 递推计算next数组）
     * @describe next[j] = k 代表 p[j] 之前的模式串子串p[0,j-1]中，有长度为 k 的相同前缀p[0,k-1]和后缀p[j-k,j-1]。
     * 若 p[k] == p[j]，说明 前缀p[0,k] 和 后缀p[j-k,j] 相同，即：next[j+1] = next[j] + 1 = k + 1
     * 若 p[k] != p[j], 若能不断的递归前缀索引 k' = next [k] (相当于模式串的自我匹配)，
     * 去寻找长度更短一点的相同前缀p[0,k'-1]和后缀p[j-k',j-1]，
     * 则 next[j+1] = next[k'] + 1 = k' + 1；若找不到这样的 k'，则 next[j+1] = 0
     * @param p 模式串
     * @param next 部分匹配表
     */
    void fillNextTab(std::string& p, std::vector<int>& next) {
        int len = p.length();
        // 计算模式串每个从0开始的子串的“前缀”，“后缀”共有元素长度
        int j = 0, k = -1;// k = next[0]
        while (j < len - 1) {
            // 若 p[k] == p[j]，说明 前缀p[0,k] 和 后缀p[j-k,j] 相同，即：next[j+1] = next[j] + 1 = k + 1
            // 若 p[k] != p[j], 若能不断的递归前缀索引 k' = next [k] (相当于模式串的自我匹配)，去寻找长度更短一点的相同前缀p[0,k'-1]和后缀p[j-k',j-1]，
            if (k == -1 || p[k] == p[j]) {
                next[++j] = ++k;// next[j+1] = next[j] + 1 = k + 1
            } else {
                k = next[k];
            }
        }
    }
public:
    /**
     * KMP比较
     * @param s 待查询串
     * @param p 模式串
     * @return -1 -- 不存在子串；other -- 存在子串，并返回子串的起始位置
     */
    int kmpFind(std::string& s, std::string& p) {
        int sLen = s.length(), pLen = p.length();
        if (pLen == 0 || pLen > sLen) {
            return -1;
        }
        // 计算模式串匹配值，部分匹配表
        std::vector<int> next(pLen, -1);
        fillNextTab(p, next);
        int sIndex = 0, pIndex = 0;
        while (sIndex < sLen && pIndex < pLen) {
            if (pIndex == -1 || s[sIndex] == p[pIndex]) {
                ++sIndex;
                ++pIndex;
            } else {
                pIndex = next[pIndex];
            }
        }
        // 若模式串已匹配完，则返回成功字符串的起始下标，否则返回匹配失败：-1
        return pIndex == pLen ? sIndex - pIndex : -1;
    }
};

/**
// 测试
int main(void) {
    KMP kmp;
    std::string strs[] = {
            "BBC ABCDAB ABCDABCDABDE",
            "abcabcd",
            "hello"   // -1, 0, 0, 0, 0, 1, 2
    };
    std::string ps[] = {
            "ABCDABD",
            "abcd",
            "ll"
    };
    for (int i = 0; i < 3; ++i) {
        std::cout << kmp.kmpFind(strs[i], ps[i]) << std::endl;
    }
    return 0;
}
*/

#endif //__KMP_H_
