/*
No232.implement-queue-using-stacks
*/
type MyQueue struct {
	inStack  []int
	outStack []int
}

func Constructor() MyQueue {
	return MyQueue{}
}

func (this *MyQueue) Push(x int) {
	this.inStack = append(this.inStack, x)
}

// move in stack to out stack
func (this *MyQueue) moveIn2Out() {
	for len(this.inStack) > 0 {
		this.outStack = append(this.outStack, this.inStack[len(this.inStack)-1])
		this.inStack = this.inStack[:len(this.inStack)-1]
	}
}

func (this *MyQueue) Pop() int {
	// if outStack is empty, move num from inStack
	if len(this.outStack) == 0 {
		this.moveIn2Out()
	}

	v := this.outStack[len(this.outStack)-1]
	this.outStack = this.outStack[:len(this.outStack)-1]

	return v
}

func (this *MyQueue) Peek() int {
	// if outStack is empty, move num from inStack
	if len(this.outStack) == 0 {
		this.moveIn2Out()
	}

	return this.outStack[len(this.outStack)-1]
}

func (this *MyQueue) Empty() bool {
	return len(this.inStack) == 0 && len(this.outStack) == 0
}

/**
 * Your MyQueue object will be instantiated and called as such:
 * obj := Constructor();
 * obj.Push(x);
 * param_2 := obj.Pop();
 * param_3 := obj.Peek();
 * param_4 := obj.Empty();
 */