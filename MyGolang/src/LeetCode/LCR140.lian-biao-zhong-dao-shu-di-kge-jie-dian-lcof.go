/*
LCR140.lian-biao-zhong-dao-shu-di-kge-jie-dian-lcof
*/

/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func trainingPlan(head *ListNode, cnt int) *ListNode {
	var ret *ListNode = nil
	var dfs func(*ListNode) int
	dfs = func(node *ListNode) int {
		if node == nil {
			return 0
		}
		thisIsLastK := dfs(node.Next) + 1
		if thisIsLastK == cnt {
			ret = node
		}
		return thisIsLastK
	}

	dfs(head)

	return ret
}
