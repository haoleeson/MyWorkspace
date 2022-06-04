package main

import (
	"encoding/base64"
	"fmt"
	"strings"
)

const (
	PREFIX = "Basic "
)

func parseBasic64(auth string) (username, password string, ok bool) {
	// Case insensitive prefix match. See Issue 22736.
	if len(auth) < len(PREFIX) || !strings.HasPrefix(auth, PREFIX) {
		fmt.Println("prefix is not 'Basic ', exit")
		return
	}
	c, err := base64.StdEncoding.DecodeString(auth[len(PREFIX):])
	if err != nil {
		fmt.Println("An error occur when base64.StdEncoding.DecodeString(): ", err)
		return
	}
	cs := string(c)
	fmt.Println("cs: ", cs)
	s := strings.IndexByte(cs, ':')
	if s < 0 {
		return
	}
	return cs[:s], cs[s+1:], true
}


func main() {
	auth_str := "foo:bar:admin"
	// base64 编码 (Zm9vOmJhcjphZG1pbg==)
	auth_str_base64 := base64.StdEncoding.EncodeToString([]byte(auth_str))
	// base64 解码
	de_auth_str_base64, _ := base64.StdEncoding.DecodeString(auth_str_base64)
	fmt.Println("auth_str: ", auth_str)
	fmt.Println("auth_str_base64: ", auth_str_base64)
	fmt.Println("de_auth_str_base64: ", string(de_auth_str_base64))

	usr, pwd, ok := parseBasic64(PREFIX + auth_str_base64)

	fmt.Println("usr: ", usr)
	fmt.Println("pwd: ", pwd)
	fmt.Println("ok: ", ok)
}
