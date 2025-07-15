/*
No2.add-two-numbers
*/

/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func addTwoNumbers(l1 *ListNode, l2 *ListNode) *ListNode {
	p1, p2 := l1, l2
	preHead := &ListNode{}
	pRet := preHead

	var tmpSum, jinFlag int = 0, 0

	var addNumAction func(int)
	addNumAction = func(num int) {
		tmpSum = num
		if tmpSum > 9 {
			tmpSum -= 10
			jinFlag = 1
		} else {
			// clear jin flag
			jinFlag = 0
		}
		pRet.Next = &ListNode{Val: tmpSum}
		pRet = pRet.Next
	}

	for p1 != nil && p2 != nil {
		addNumAction(p1.Val + p2.Val + jinFlag)
		p1 = p1.Next
		p2 = p2.Next
	}

	for p1 != nil {
		addNumAction(p1.Val + jinFlag)
		p1 = p1.Next
	}

	for p2 != nil {
		addNumAction(p2.Val + jinFlag)
		p2 = p2.Next
	}

	if jinFlag > 0 {
		pRet.Next = &ListNode{Val: 1}
		pRet = pRet.Next
	}

	return preHead.Next
}
