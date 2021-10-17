/**
No222. 完全二叉树的节点个数 (位操作 + 二分法)
给出一个完全二叉树，求出该树的节点个数。

说明：
完全二叉树的定义如下：在完全二叉树中，除了最底层节点可能没填满外，其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最左边
的若干位置。若最底层为第 h 层，则该层包含 1 ~ 2^h 个节点。

示例:
输入:
    1
   / \
  2   3
 / \  /
4  5 6
输出: 6

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/count-complete-tree-nodes
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */
package LeetCode

/**
 * 判断 path 路径的节点是否存在
 * @param root 根节点
 * @param height 完全二叉树的高度
 * @param theKNode 待探究是否存在的第 K 个节点
 * @return 第 K 个节点是否存在
 */
func isTheKNodeExist(root *TreeNode, height int, theKNode int) bool {
    // 从次高位开始从高位->低位遍历 theKNode 的每一位
    var bits int = 1 << (height - 1)
    node := root
    for node != nil && bits > 0 {
        // theKNode 的次高位 -> 低位 包含了从根节点到第K个节点的路径信息
        // 0 表示移动到左子节点，1 表示移动到右子节点
        if (theKNode & bits) == 0 {
            node = node.Left
        } else {
            node = node.Right
        }
        bits >>= 1
    }
    return node != nil
}

/**
 * 统计完全二叉树的节点个数
 * @param root 完全二叉树的根节点
 * @return 完全二叉树的节点个数
 */
func countNodes(root *TreeNode) int {
    if root == nil {
        return 0
    }
    // 求二叉树高度（一直遍历左节点）
    var height int = 0
    for node := root; node.Left != nil; node = node.Left {
        height++
    }
    // 完全二叉树节点数范围：[2^h, 2^(h+1) - 1]
    // theKNode 的次高位 -> 低位 包含了从根节点到第K个节点的路径信息
    // 0 表示移动到左子节点，1 表示移动到右子节点
    var left int = 1 << height          // 2^h
    var right = (1 << (height + 1)) - 1 // 2^(h+1) - 1
    var mid int
    // 二分法判断中间节点是否存在
    for left < right {
        mid = (right - left + 1) / 2 + left
        // 若第K个节点存在
        if isTheKNodeExist(root, height, mid) {
            left = mid // 保守，未+1
        } else {
            right = mid - 1
        }
    }
    return left
}
