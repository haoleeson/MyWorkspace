package main // 定义本test.go文件所在的包是main
import "fmt" // 引入基本包fmt

// 主函数
func main() {
	var a1 int = 2
	var a2 = 3
	a3 := 4
	num := a1 + a2 + a3
	var flag bool = false
	if (!flag) {
		fmt.Println("false")
	} else {
		fmt.Println("true")
	}
	var f1 float32 = 3.14
	var bb byte = 'A'
	var str string = "hello world!"

	fmt.Println(f1)
	fmt.Println(bb)
	fmt.Println(num)
	fmt.Println(str)
}
