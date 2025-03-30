/*
No88.merge-sorted-array
*/

func merge(nums1 []int, m int, nums2 []int, n int) {
	idx1, idx2, i := m-1, n-1, m+n-1

	for idx1 >= 0 && idx2 >= 0 {
		if nums2[idx2] > nums1[idx1] {
			nums1[i] = nums2[idx2]
			idx2--
			i--
		} else {
			nums1[i] = nums1[idx1]
			idx1--
			i--
		}
	}

	for idx2 >= 0 {
		nums1[i] = nums2[idx2]
		idx2--
		i--
	}
}
