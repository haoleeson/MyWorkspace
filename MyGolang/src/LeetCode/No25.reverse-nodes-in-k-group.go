/*
No25.reverse-nodes-in-k-group
*/
/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func reverseKGroup(head *ListNode, k int) *ListNode {
	preHead := &ListNode{Next: head}
	prePtr, tailPtr := preHead, head
	var p *ListNode = nil

	for {
		// move tailPtr to the Kth node
		tailPtr = prePtr.Next
		th := 1
		for th < k && tailPtr != nil {
			tailPtr = tailPtr.Next
			th++
		}
		// if tail not enough, exit
		if th < k || tailPtr == nil {
			break
		}
		// reverse k node
		newTailPtr := prePtr.Next
		for i := 1; i < k; i++ {
			p = prePtr.Next
			prePtr.Next = p.Next
			p.Next = tailPtr.Next
			tailPtr.Next = p
		}
		prePtr = newTailPtr
	}
	return preHead.Next
}

// 2025-11-26
func reverseKGroup2(head *ListNode, k int) *ListNode {
	if k < 2 {
		return head
	}
	preHead := &ListNode{Next: head}

	// lastEnd -> ... curEnd -> cur -> ...
	lastEnd := preHead
	curEnd := head
	cur := curEnd.Next
	subCnt := 2
	for cur != nil {
		curEnd.Next = cur.Next
		cur.Next = lastEnd.Next
		lastEnd.Next = cur

		if subCnt == k {
			lastEnd = curEnd
			// check next nodes cnt >= k
			nextCnt := 0
			for p := lastEnd.Next; p != nil && nextCnt < k; p = p.Next {
				nextCnt++
			}
			if nextCnt < k {
				break
			}
			curEnd = lastEnd.Next
			cur = curEnd.Next
			subCnt = 2
			continue
		}

		cur = curEnd.Next
		subCnt++
	}

	return preHead.Next
}