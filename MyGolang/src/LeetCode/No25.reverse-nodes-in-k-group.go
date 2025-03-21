/*
No25.reverse-nodes-in-k-group
*/
/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func reverseKGroup(head *ListNode, k int) *ListNode {
	preHead := &ListNode{Next: head}
	prePtr, tailPtr := preHead, head
	var p *ListNode = nil

	for {
		// move tailPtr to the Kth node
		tailPtr = prePtr.Next
		th := 1
		for th < k && tailPtr != nil {
			tailPtr = tailPtr.Next
			th++
		}
		// if tail not enough, exit
		if th < k || tailPtr == nil {
			break
		}
		// reverse k node
		newTailPtr := prePtr.Next
		for i := 1; i < k; i++ {
			p = prePtr.Next
			prePtr.Next = p.Next
			p.Next = tailPtr.Next
			tailPtr.Next = p
		}
		prePtr = newTailPtr
	}
	return preHead.Next
}