/*
No1472.design-browser-history
*/
type BrowserHistory struct {
	urls  []string
	index int
}

func Constructor(homepage string) BrowserHistory {
	return BrowserHistory{
		urls:  []string{homepage},
		index: 0,
	}
}

func (this *BrowserHistory) Visit(url string) {
	if len(this.urls)-1 > this.index {
		this.urls = this.urls[:this.index+1]
	}
	this.urls = append(this.urls, url)
	this.index++
}

func (this *BrowserHistory) Back(steps int) string {
	if steps > this.index {
		this.index = 0
	} else {
		this.index -= steps
	}
	return this.urls[this.index]
}

func (this *BrowserHistory) Forward(steps int) string {
	if this.index+steps > len(this.urls)-1 {
		this.index = len(this.urls) - 1
	} else {
		this.index += steps
	}
	return this.urls[this.index]
}
