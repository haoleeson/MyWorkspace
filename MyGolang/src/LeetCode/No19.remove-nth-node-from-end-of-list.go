/*
No19.remove-nth-node-from-end-of-list
*/
/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func removeNthFromEnd(head *ListNode, n int) *ListNode {
	preHead := &ListNode{Next: head}

	var d func(*ListNode) int
	d = func(node *ListNode) int {
		if node == nil {
			return 0
		}

		tmpRet := d(node.Next)

		if tmpRet == n {
			node.Next = node.Next.Next
		}

		return tmpRet + 1
	}

	nodeCnt := d(head)
	if nodeCnt == n {
		// delete head
		preHead.Next = head.Next
	}

	return preHead.Next
}