 package main

import (
	"log"
	"reflect"
)

func checkStructFieldExist(fieldName string, structEmptyVal interface{}) bool {
	metaValue := reflect.ValueOf(structEmptyVal).Elem()
	field := metaValue.FieldByName(fieldName)
	if field == (reflect.Value{}) {
		log.Printf("Field %s not exist in struct", fieldName)
		return false
	}
	log.Printf("Field %s exist in struct", fieldName)
	return true
}

func main() {
	type test struct {
		A bool
		B bool
		C bool
	}

	v := new(test)
	checkStructFieldExist("A", v)
	checkStructFieldExist("C", v)
	checkStructFieldExist("M", v)
}
