/*
No24.swap-nodes-in-pairs
*/

/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func swapPairs(head *ListNode) *ListNode {
	if head == nil {
		return head
	}
	preHead := &ListNode{Next: head}
	var preCur, cur, curNext *ListNode = preHead, head, head.Next

	for cur != nil && curNext != nil {
		// swap node
		cur.Next = curNext.Next
		curNext.Next = cur
		preCur.Next = curNext

		// iterator next
		preCur = cur
		cur = cur.Next
		if cur == nil {
			break
		}
		curNext = cur.Next
	}
	return preHead.Next
}