package main

import (
	"fmt"
	"strconv"
)

// ABC_Union is an interface that is implemented by valid types for the union for the ABC
type ABC_Union interface {
	Is_ABC_Union()
}

// ABC_Union_String is used when ABC is to be set to a string value.
type ABC_Union_String struct {
	String	string
}

// Is_ABC_Union ensures that ABC_Union_String implements the ABC_Union interface.
func (*ABC_Union_String) Is_ABC_Union() {}

// ABC_Union_Uint32 is used when ABC is to be set to a uint32 value.
type ABC_Union_Uint32 struct {
	Uint32	uint32
}

// Is_ABC_Union ensures that ABC_Union_Uint32 implements the ABC_Union interface.
func (*ABC_Union_Uint32) Is_ABC_Union() {}

// To_ABC_Union takes an input interface{} and attempts to convert it to a struct
// which implements the ABC_Union union. It returns an error if the interface{} supplied
// cannot be converted to a type within the union.
func To_ABC_Union(i interface{}) (ABC_Union, error) {
	switch v := i.(type) {
	case string:
		fmt.Println("Debug: type is string")
		a := &ABC_Union_String{v}
		fmt.Sprintln("(a): %p", a)
		fmt.Sprintln("Addr(a): %p", &a)
		return a, nil
	case uint32:
		fmt.Println("Debug: type is uint32")
		return &ABC_Union_Uint32{v}, nil
	default:
		return nil, fmt.Errorf("cannot convert %v to ABC_Union, unknown union type, got: %T, want any of [string, uint32]", i, i)
	}
}

// get the value of ABC_Union with its correct type
func obtainValue(v interface{}) {
	var s string
	switch x := v.(type) {
	case *ABC_Union_String:
		s = x.String
		fmt.Println("union type is string, value is : ", s)
	case *ABC_Union_Uint32:
		s = strconv.Itoa(int(x.Uint32))
		fmt.Println("union type is uint32, value is : ", s)
	default:
		fmt.Println("Unknown type")
	}
}

func main() {
	var abc1 ABC_Union
	var abc2 ABC_Union
	var err error

	str := "hello"
	abc1, err = To_ABC_Union(str)
	if err != nil {
		fmt.Println("abc1 failed.")
	}
	obtainValue(abc1)

	ui32 := uint32(123)
	abc2, err = To_ABC_Union(ui32)
	if err != nil {
		fmt.Println("abc2 failed.")
	}
	obtainValue(abc2)
}
