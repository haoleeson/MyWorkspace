/*
No239.sliding-window-maximum
*/

// method 1: single down queue
// time: O(n), space: O(k)
func maxSlidingWindow(nums []int, k int) []int {
	// single down queue
	idxQue := []int{}

	var push func(int)
	push = func(idx int) {
		// if tail elem <= nums[idx], remove tail elem
		for len(idxQue) > 0 && nums[idxQue[len(idxQue)-1]] <= nums[idx] {
			idxQue = idxQue[:len(idxQue)-1]
		}
		// push idx
		idxQue = append(idxQue, idx)
	}

	// push first k elem
	for i := 0; i < k; i++ {
		push(i)
	}

	n := len(nums)
	ret := make([]int, n-k+1)
	ret[0] = nums[idxQue[0]]
	retIdx := 1

	for i := k; i < n; i++ {
		push(i)
		// not in window, index <= i-k, pop
		for idxQue[0] <= i-k {
			idxQue = idxQue[1:]
		}
		ret[retIdx] = nums[idxQue[0]]
		retIdx++
	}

	return ret
}

// method 2: max heap
// time: O(nlogk), space: O(k)

// max index heap
var hpList []int

func maxSlidingWindow2(nums []int, k int) []int {
	hpList = nums

	// first k elem index window
	idxQue := &hp{make([]int, k)}
	for i := 0; i < k; i++ {
		idxQue.IntSlice[i] = i
	}
	heap.Init(idxQue)

	n := len(nums)
	ret := make([]int, n-k+1)
	ret[0] = nums[idxQue.IntSlice[0]]
	retIdx := 1

	for i := k; i < n; i++ {
		heap.Push(idxQue, i)
		// not in window, index <= i-k, pop
		for idxQue.IntSlice[0] <= i-k {
			heap.Pop(idxQue)
		}
		ret[retIdx] = nums[idxQue.IntSlice[0]]
		retIdx++
	}

	return ret
}

type hp struct {
	sort.IntSlice
}

func (h hp) Less(i, j int) bool {
	// max heap, >
	return hpList[h.IntSlice[i]] > hpList[h.IntSlice[j]]
}

func (h *hp) Push(v interface{}) {
	h.IntSlice = append(h.IntSlice, v.(int))
}

func (h *hp) Pop() interface{} {
	hList := h.IntSlice
	v := hList[len(hList)-1]
	h.IntSlice = hList[:len(hList)-1]
	return v
}