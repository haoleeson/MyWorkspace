type BioLinkNode struct {
	Key  int
	Val  int
	Pre  *BioLinkNode
	Next *BioLinkNode
}

type LRUCache struct {
	PreHead   *BioLinkNode
	PostTail  *BioLinkNode
	Size      int
	ExisteMap map[int]*BioLinkNode
}

func Constructor(capacity int) LRUCache {
	ptrPre := &BioLinkNode{}
	ptrTail := &BioLinkNode{}
	ptrPre.Next = ptrTail
	ptrTail.Pre = ptrPre
	return LRUCache{
		PreHead:   ptrPre,
		PostTail:  ptrTail,
		Size:      capacity,
		ExisteMap: make(map[int]*BioLinkNode),
	}
}

func (this *LRUCache) Get(key int) int {
	if ptr, existed := this.ExisteMap[key]; existed {
		// move ptr to header next, PreHead ... ptr ...
		// pick ptr out
		ptr.Pre.Next = ptr.Next
		ptr.Next.Pre = ptr.Pre
		// insert ptr behind preHead
		ptr.Next = this.PreHead.Next
		ptr.Pre = this.PreHead
		this.PreHead.Next.Pre = ptr
		this.PreHead.Next = ptr
		return ptr.Val
	}
	return -1
}

func (this *LRUCache) Put(key int, value int) {
	if ptr, existed := this.ExisteMap[key]; existed {
		// existed, update value
		ptr.Val = value
		// move ptr to header next, PreHead ... ptr ...
		// pick ptr out
		ptr.Pre.Next = ptr.Next
		ptr.Next.Pre = ptr.Pre
		// put ptr behind preHead
		ptr.Next = this.PreHead.Next
		ptr.Pre = this.PreHead
		this.PreHead.Next.Pre = ptr
		this.PreHead.Next = ptr
	} else {
		// not existed, insert behind preHead
		node := &BioLinkNode{Key: key, Val: value, Pre: this.PreHead, Next: this.PreHead.Next}
		this.PreHead.Next.Pre = node
		this.PreHead.Next = node
		if len(this.ExisteMap) == this.Size {
			// drop last node
			dropPtr := this.PostTail.Pre
			dropPtr.Pre.Next = this.PostTail
			this.PostTail.Pre = dropPtr.Pre
			dropPtr.Pre = nil
			dropPtr.Next = nil
			delete(this.ExisteMap, dropPtr.Key)
		}
		this.ExisteMap[key] = node
	}
}

/**
 * Your LRUCache object will be instantiated and called as such:
 * obj := Constructor(capacity);
 * param_1 := obj.Get(key);
 * obj.Put(key,value);
 */
