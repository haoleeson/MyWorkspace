/*
No61.rotate-list
*/
/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func rotateRight(head *ListNode, k int) *ListNode {
	if head == nil {
		return head
	}

	// get link length
	var lenL int = 0
	for p := head; p != nil; p = p.Next {
		lenL++
	}

	k = k % lenL
	// no need rotate
	if k == 0 {
		return head
	}

	var lastEndNode, newEndNode *ListNode = nil, nil

	var iteratorLink func(*ListNode) int
	iteratorLink = func(node *ListNode) int {
		if node == nil {
			return 0
		}
		lastIdx := iteratorLink(node.Next) + 1

		if lastIdx == 1 {
			lastEndNode = node
		} else if lastIdx == k+1 {
			newEndNode = node
		}

		return lastIdx
	}

	iteratorLink(head)

	// rotete
	preHeader := &ListNode{Next: head}
	lastEndNode.Next = preHeader.Next
	preHeader.Next = newEndNode.Next
	newEndNode.Next = nil

	return preHeader.Next
}