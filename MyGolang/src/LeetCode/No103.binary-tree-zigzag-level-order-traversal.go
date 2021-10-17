/**
No103. 二叉树的锯齿形层序遍历
给定一个二叉树，返回其节点值的锯齿形层序遍历。（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。

例如：
给定二叉树 [3, 9, 20, null, null, 15, 7],
    3
   / \
  9  20
    /  \
   15   7
返回锯齿形层序遍历如下：
[
  [3],
  [20,9],
  [15,7]
]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/binary-tree-zigzag-level-order-traversal
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */
package LeetCode

func zigzagLevelOrder(root *TreeNode) (ans [][]int) {
    if root == nil {
        return
    }
    // 当前层及下一层非空节点数
    thisCount := 1
    thisLevel := make([]*TreeNode, 1)
    thisLevel[0] = root
    ans = append(ans, []int{root.Val})
    // 是否逆序遍历
    isBackwardTraversal := true

    for true {
        nextCount := 0
        nextLevel := make([]*TreeNode, thisCount * 2)
        var tmpTraversal []int

        for i := thisCount - 1; i >= 0; i-- {
            // 逆序遍历(先右后左)
            if isBackwardTraversal {
                // 若右子节点存在
                if thisLevel[i].Right != nil {
                    nextLevel[nextCount] = thisLevel[i].Right
                    nextCount++
                    tmpTraversal = append(tmpTraversal, thisLevel[i].Right.Val)
                }
                // 若左子节点存在
                if thisLevel[i].Left != nil {
                    nextLevel[nextCount] = thisLevel[i].Left
                    nextCount++
                    tmpTraversal = append(tmpTraversal, thisLevel[i].Left.Val)
                }
            } else {
                // 正序遍历(先左后右)
                // 若左子节点存在
                if thisLevel[i].Left != nil {
                    nextLevel[nextCount] = thisLevel[i].Left
                    nextCount++
                    tmpTraversal = append(tmpTraversal, thisLevel[i].Left.Val)
                }
                // 若右子节点存在
                if thisLevel[i].Right != nil {
                    nextLevel[nextCount] = thisLevel[i].Right
                    nextCount++
                    tmpTraversal = append(tmpTraversal, thisLevel[i].Right.Val)
                }
            }
        }

        if nextCount == 0 {
            break
        }
        // 添加当前层遍历结果到ans
        ans = append(ans, tmpTraversal)
        // 遍历方向取反
        isBackwardTraversal = !isBackwardTraversal
        // 准备遍历下一层
        thisCount = nextCount
        thisLevel = nextLevel
    }
    return
}
