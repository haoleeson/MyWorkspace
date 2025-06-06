/*
No141.linked-list-cycle
*/

/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func hasCycle(head *ListNode) bool {
	slowP, fastP := head, head

	for slowP != nil && fastP != nil && fastP.Next != nil {
		slowP = slowP.Next
		fastP = fastP.Next.Next
		if slowP == fastP {
			return true
		}
	}
	return false
}