/*
No234.palindrome-linked-list
*/
/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func isPalindrome(head *ListNode) bool {
	if head.Next == nil {
		return true
	}

	frontNode := head
	var reserveCheck func(*ListNode) bool
	reserveCheck = func(node *ListNode) bool {
		if node == nil {
			return true
		}
		if !reserveCheck(node.Next) {
			return false
		}
		if node.Val != frontNode.Val {
			return false
		}
		frontNode = frontNode.Next
		return true
	}

	return reserveCheck(head)
}
