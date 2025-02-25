/*
No2502.design-memory-allocator
*/
type Allocator struct {
	n   int
	mem []int
}

func Constructor(n int) Allocator {
	return Allocator{
		n:   n,
		mem: make([]int, n),
	}
}

func (this *Allocator) Allocate(size int, mID int) int {
	count := 0
	for i := 0; i < this.n; i++ {
		if this.mem[i] != 0 {
			count = 0
		} else {
			count++
			if count == size {
				for j := i - size + 1; j <= i; j++ {
					this.mem[j] = mID
				}
				return i - size + 1
			}
		}
	}
	return -1
}

func (this *Allocator) FreeMemory(mID int) int {
	count := 0

	for i := 0; i < this.n; i++ {
		if this.mem[i] == mID {
			this.mem[i] = 0
			count++
		}
	}

	return count
}
