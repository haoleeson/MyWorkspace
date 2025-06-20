/*
No160.intersection-of-two-linked-lists
*/
/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func getIntersectionNode(headA, headB *ListNode) *ListNode {
	recMap := make(map[*ListNode]struct{})

	// add headA
	var p *ListNode = headA
	for p != nil {
		recMap[p] = struct{}{}
		p = p.Next
	}

	// iterator headB
	p = headB
	for p != nil {
		if _, existed := recMap[p]; existed {
			return p
		}
		p = p.Next
	}

	return nil
}