/*
No83.remove-duplicates-from-sorted-list
*/
/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func deleteDuplicates(head *ListNode) *ListNode {
	var cur, ptr *ListNode = head, head

	for cur != nil {
		ptr = cur.Next
		// skip duplicate nodes
		for ; ptr != nil && ptr.Val == cur.Val; ptr = ptr.Next {
		}
		// remove duplicate nodes
		cur.Next = ptr
		cur = ptr
	}
	return head
}