/*
No82.remove-duplicates-from-sorted-list-ii
*/
/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func deleteDuplicates(head *ListNode) *ListNode {
	preHead := &ListNode{Next: head}
	lastP := preHead
	p := head
	var nextDiffP *ListNode = nil

	for p != nil && p.Next != nil {
		if p.Val == p.Next.Val {
			// find Next Diff Node
			nextDiffP = p.Next
			for nextDiffP != nil && p.Val == nextDiffP.Val {
				nextDiffP = nextDiffP.Next
			}
			// delete those node
			lastP.Next = nextDiffP
			p = nextDiffP
		} else {
			lastP = p
			p = p.Next
		}
	}

	return preHead.Next
}