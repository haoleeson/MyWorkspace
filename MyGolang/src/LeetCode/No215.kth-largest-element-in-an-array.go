/*
No215.kth-largest-element-in-an-array
*/

// 桶排序，pass
// Time: O(n), Mem: O(maxNum - minNum + 1)
func findKthLargest(nums []int, k int) int {
	minVal, maxVal := nums[0], nums[0]
	for _, num := range nums {
		minVal = min(minVal, num)
		maxVal = max(maxVal, num)
	}

	// bucket count
	bucketCnt := make([]int, maxVal-minVal+1)
	for _, num := range nums {
		bucketCnt[num-minVal]++
	}

	// get the k th max num
	maxNumIdx := maxVal - minVal
	for k > 0 {
		for bucketCnt[maxNumIdx] == 0 {
			maxNumIdx--
		}
		bucketCnt[maxNumIdx]--
		k--
	}

	return maxNumIdx + minVal
}

// 滑动记录前k个最大值，超时
func findKthLargest1(nums []int, k int) int {
	n := len(nums)
	que := make([]int, k)
	que[0] = nums[0]
	sizeQue := 1

	for i := 1; i < n; i++ {
		// if sizeQue < k, add num
		if sizeQue < k {
			// find que[bigIdx] bigger than num
			bigIdx := 0
			for bigIdx < sizeQue && que[bigIdx] < nums[i] {
				bigIdx++
			}
			// move que[bigIdx:sizeQue] to que[bigIdx+1:sizeQue+1]
			for j := sizeQue; j > bigIdx; j-- {
				que[j] = que[j-1]
			}
			// insert nums[i] into que[bigIdx]
			que[bigIdx] = nums[i]
			sizeQue++
		} else {
			if nums[i] <= que[0] {
				continue
			}
			// else, add num and remove the smallest
			// find que[bigIdx] bigger than num
			bigIdx := 0
			for bigIdx < k && que[bigIdx] < nums[i] {
				bigIdx++
			}
			// move que[1:bigIdx-1] to que[0:bigIdx-2]
			for j := 0; j < bigIdx-1; j++ {
				que[j] = que[j+1]
			}
			// modify que[bigIdx-1] to nums[i]
			que[bigIdx-1] = nums[i]
		}
	}

	return que[0]
}

// 基于快排的选择方法
func findKthLargest2(nums []int, k int) int {
	n := len(nums)
	return quickselect(nums, 0, n-1, n-k)
}

func quickselect(nums []int, l, r, k int) int {
	if l == r {
		return nums[k]
	}
	partition := nums[l]
	i := l - 1
	j := r + 1
	for i < j {
		for i++; nums[i] < partition; i++ {
		}
		for j--; nums[j] > partition; j-- {
		}
		if i < j {
			nums[i], nums[j] = nums[j], nums[i]
		}
	}
	if k <= j {
		return quickselect(nums, l, j, k)
	} else {
		return quickselect(nums, j+1, r, k)
	}
}

// 堆排序
func findKthLargest3(nums []int, k int) int {
	heapSize := len(nums)
	buildMaxHeap(nums, heapSize)
	for i := len(nums) - 1; i >= len(nums)-k+1; i-- {
		nums[0], nums[i] = nums[i], nums[0]
		heapSize--
		maxHeapify(nums, 0, heapSize)
	}
	return nums[0]
}

func buildMaxHeap(a []int, heapSize int) {
	for i := heapSize/2 - 1; i >= 0; i-- {
		maxHeapify(a, i, heapSize)
	}
}

func maxHeapify(a []int, i, heapSize int) {
	l, r, largest := i*2+1, i*2+2, i
	if l < heapSize && a[l] > a[largest] {
		largest = l
	}
	if r < heapSize && a[r] > a[largest] {
		largest = r
	}
	if largest != i {
		a[i], a[largest] = a[largest], a[i]
		maxHeapify(a, largest, heapSize)
	}
}
