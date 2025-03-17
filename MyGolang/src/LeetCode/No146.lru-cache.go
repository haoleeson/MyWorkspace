// No146.lru-cache
type DoubleLinkListNode struct {
	Key      int
	Val      int
	PreNode  *DoubleLinkListNode
	NextNode *DoubleLinkListNode
}

type LRUCache struct {
	maxCap   int
	size     int
	m        map[int]*DoubleLinkListNode
	headNode *DoubleLinkListNode
	tailNode *DoubleLinkListNode
}

func Constructor(capacity int) LRUCache {
	headNode := &DoubleLinkListNode{}
	tailNode := &DoubleLinkListNode{}
	headNode.NextNode = tailNode
	tailNode.PreNode = headNode
	return LRUCache{
		maxCap:   capacity,
		size:     0,
		m:        make(map[int]*DoubleLinkListNode, capacity),
		headNode: headNode,
		tailNode: tailNode,
	}
}

func (this *LRUCache) Get(key int) int {
	node, existed := this.m[key]
	if !existed {
		return -1
	}

	// pick out node
	node.NextNode.PreNode = node.PreNode
	node.PreNode.NextNode = node.NextNode
	// insert behand head
	this.headNode.NextNode.PreNode = node
	node.NextNode = this.headNode.NextNode
	node.PreNode = this.headNode
	this.headNode.NextNode = node
	return node.Val
}

func (this *LRUCache) Put(key int, value int) {
	node, existed := this.m[key]
	if !existed {
		node = &DoubleLinkListNode{
			Key:      key,
			Val:      value,
			PreNode:  nil,
			NextNode: nil,
		}
		if this.size == this.maxCap {
			// remove last node
			delete(this.m, this.tailNode.PreNode.Key)
			this.tailNode.PreNode.PreNode.NextNode = this.tailNode
			this.tailNode.PreNode = this.tailNode.PreNode.PreNode
		} else {
			this.size++
		}
		this.m[key] = node
	} else {
		node.Val = value
		// pick out node
		node.NextNode.PreNode = node.PreNode
		node.PreNode.NextNode = node.NextNode
	}
	// insert behand head
	this.headNode.NextNode.PreNode = node
	node.NextNode = this.headNode.NextNode
	node.PreNode = this.headNode
	this.headNode.NextNode = node
}

/**
 * Your LRUCache object will be instantiated and called as such:
 * obj := Constructor(capacity);
 * param_1 := obj.Get(key);
 * obj.Put(key,value);
 */