/*
design-an-ordered-stream
*/
type OrderedStream struct {
	l   []string
	ptr int
}

func Constructor(n int) OrderedStream {
	return OrderedStream{
		l:   make([]string, n+1),
		ptr: 1,
	}
}

func (this *OrderedStream) Insert(idKey int, value string) []string {
	this.l[idKey] = value
	i := this.ptr
	for this.ptr < len(this.l) && this.l[this.ptr] != "" {
		this.ptr++
	}
	return this.l[i:this.ptr]
}

/**
 * Your OrderedStream object will be instantiated and called as such:
 * obj := Constructor(n);
 * param_1 := obj.Insert(idKey,value);
 */