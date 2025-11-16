/*
No328.odd-even-linked-list
*/

/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func oddEvenList(head *ListNode) *ListNode {
	// case n == 0,1,2, return head
	if head == nil || head.Next == nil || head.Next.Next == nil {
		return head
	}

	// jiEndPtr -> ... -> ouEndPtr -> p -> ...
	jiEndPtr, ouEndPtr, p := head, head.Next, head.Next.Next
	jiFlag := true

	for p != nil {
		if jiFlag {
			// move p to jiEndPtr Next
			ouEndPtr.Next = p.Next
			p.Next = jiEndPtr.Next
			jiEndPtr.Next = p
			jiEndPtr = p
		} else {
			// move p to ouEndPtr Next
			ouEndPtr = p
		}

		p = ouEndPtr.Next
		jiFlag = !jiFlag
	}
	return head
}
