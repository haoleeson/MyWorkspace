// No855.exam-room.go

type ExamRoom struct {
	s []int // array of seated seats Number
	n int   // total seats
}

func Constructor(n int) ExamRoom {
	return ExamRoom{
		s: []int{},
		n: n,
	}
}

func (this *ExamRoom) Seat() int {
	seatNo, idx := 0, 0

	if len(this.s) > 0 {
		dist := this.s[0]
		pre := -1

		// try choose max distance seat
		for i, v := range this.s {
			if pre != -1 {
				d := (v - pre) / 2
				if d > dist {
					dist = d
					seatNo = pre + d
					idx = i
				}
			}
			pre = v
		}

		// consider the last seat (if has the last seat, d is 0, not match)
		if this.n-1-this.s[len(this.s)-1] > dist {
			seatNo = this.n - 1
			idx = len(this.s)
		}
	}

	this.s = append(this.s, 0)

	// Insert seatNo
	copy(this.s[idx+1:], this.s[idx:])
	this.s[idx] = seatNo

	return seatNo
}

func (this *ExamRoom) Leave(p int) {
	// find p index, todo dichotomy
	idx := 0
	for i := 0; i < len(this.s); i++ {
		if this.s[i] == p {
			idx = i
			break
		}
	}

	// delete p
	this.s = append(this.s[:idx], this.s[idx+1:]...)
}

/**
 * Your ExamRoom object will be instantiated and called as such:
 * obj := Constructor(n);
 * param_1 := obj.seatedList();
 * obj.Leave(p);
 */