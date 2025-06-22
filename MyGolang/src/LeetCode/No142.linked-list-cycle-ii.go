/*
No142.linked-list-cycle-ii
*/
/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func detectCycle(head *ListNode) *ListNode {
	slow, fast := head, head
	for fast != nil {
		slow = slow.Next
		if fast.Next == nil {
			// none cycle
			return nil
		}
		fast = fast.Next.Next

		// first meet
		if fast == slow {
			p := head

			// wait p meet slow
			for p != slow {
				p = p.Next
				slow = slow.Next
			}
			return p
		}
	}
	return nil
}