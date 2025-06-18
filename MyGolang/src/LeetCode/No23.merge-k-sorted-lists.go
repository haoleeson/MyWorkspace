/*
No23.merge-k-sorted-lists
*/
/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */

func mergeKLists(lists []*ListNode) *ListNode {
	// add all list head into MinHeap
	m := MinHeap{}
	for _, head := range lists {
		if head != nil {
			m = append(m, head)
		}
	}
	heap.Init(&m)

	preHead := &ListNode{}
	ptr := preHead

	for len(m) > 0 {
		// pop node from MinHeap
		node := heap.Pop(&m).(*ListNode)
		// push next of this list
		if node.Next != nil {
			heap.Push(&m, node.Next)
		}

		ptr.Next = node
		ptr = ptr.Next
	}
	return preHead.Next
}

type MinHeap []*ListNode

func (m MinHeap) Len() int {
	return len(m)
}

func (m MinHeap) Less(i, j int) bool {
	return m[i].Val < m[j].Val
}

func (m MinHeap) Swap(i, j int) {
	m[i], m[j] = m[j], m[i]
}

func (m *MinHeap) Push(x interface{}) {
	*m = append(*m, x.(*ListNode))
}

func (m *MinHeap) Pop() interface{} {
	old := *m
	n := len(old)
	iterm := old[n-1]
	old[n-1] = nil // 避免内存泄露
	*m = old[0 : n-1]
	return iterm
}
