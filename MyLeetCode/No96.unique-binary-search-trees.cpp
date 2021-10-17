#include <iostream>
#include <vector>
using namespace std;
/**
 * No96. 不同的二叉搜索树
 * 给定一个整数 n，求以1 ...n为节点组成的二叉搜索树有多少种？

示例:
输入: 3
输出: 5
解释:
给定 n = 3, 一共有 5 种不同结构的二叉搜索树:

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
*/

/**
 * 解题思路：动态规划
 * 给定一个有序序列 1⋯n，为了构建出一棵二叉搜索树，我们可以遍历每个数字 i，
 * 将该数字作为树根，将 1⋯(i−1) 序列作为左子树，
 * 将 (i+1)⋯n 序列作为右子树。接着我们可以按照同样的方式递归构建左子树和右子树。
 * 在上述构建的过程中，由于根的值不同，因此我们能保证每棵二叉搜索树是唯一的。
 *                      左子树的个数     右子树的个数
 * numTrees(n) = sum(numTrees(i - 1) * numTrees(n - i)) ，其中 i 取值为: 1~n
 * 可见，numTrees(n) 依赖于：numTrees(0)，numTrees(1),...,numTrees(n-1)

 */
class Solution {
public:
    int numTrees(int n) {
        if (n < 0) {
            return 0;
        }
        vector<int> G(n + 1, 0);
        G[0] = 1;
        G[1] = 1;

        for (int subN = 2; subN <= n; ++subN) {
            // numTrees(n) = sum(numTrees(i - 1) * numTrees(n - i))
            for (int rootIndex = 1; rootIndex <= subN; ++rootIndex) {
                G[subN] += G[rootIndex - 1] * G[subN - rootIndex];
            }
        }
        return G[n];
    }
};

int main() {
    Solution solution;
    cout << solution.numTrees(3) << endl;
    return 0;
}
