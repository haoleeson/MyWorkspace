/*
No92.reverse-linked-list-ii
*/

/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */

// 2025-12-09 recoding
func reverseBetween(head *ListNode, left int, right int) *ListNode {
    preHead := &ListNode{Next: head}
    idx := 0
    var pNode, subPreHeadNode, subEndNode *ListNode = preHead, nil, nil

    for idx <= right {
        if idx == left - 1 {
            subPreHeadNode = pNode
            subEndNode = pNode.Next
        } else if idx > left {
            subEndNode.Next = pNode.Next
            pNode.Next = subPreHeadNode.Next
            subPreHeadNode.Next = pNode
            pNode = subEndNode
        }

        pNode = pNode.Next
        idx++
    }
    return preHead.Next
}

func reverseBetween(head *ListNode, left int, right int) *ListNode {
	preHead := &ListNode{Next: head}
	order := 0

	// find the left-1 order node as pre node
	pre := preHead
	for order < left-1 {
		pre = pre.Next
		order++
	}

	// left node
	var pLeftNode, p *ListNode = pre.Next, nil
	order++

	// resorve until right
	for order < right {
		p = pLeftNode.Next
		pLeftNode.Next = p.Next
		p.Next = pre.Next
		pre.Next = p
		order++
	}

	return preHead.Next
}