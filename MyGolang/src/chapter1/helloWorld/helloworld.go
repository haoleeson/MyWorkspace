package main

import (
	"bufio"
	"bytes"
	"encoding/json"
	"errors"
	"fmt"
	"io"
	"io/ioutil"
	"math"
	"net/http"
	"os"
	"reflect"
	"regexp"
	"strconv"
	"strings"
	"time"

	"gopkg.in/yaml.v2"
)

func stringLowercaseTest(name string) string {
	if len(name) > 0 {
		name = strings.ToLower(name)
		println("lowercase string: ", name)
	}
	return name
}

func parsePlatformFromFile(filePath string) string {
	filePath = strings.TrimSpace(filePath)
	if filePath == "" {
		return ""
	}
	file, err := os.Open(filePath)
	if err != nil {
		fmt.Println("failed to open file due to %+v", err)
	}
	defer file.Close()

	fileScanner := bufio.NewScanner(file)
	for fileScanner.Scan() {
		line := fileScanner.Text()
		if !strings.HasPrefix(line, "onie_platform") {
			continue
		}
		res := strings.SplitN(line, "=", 2)
		if len(res) != 2 {
			continue
		}
		return strings.TrimSpace(res[1])
	}
	return ""
}

func generateInnerPortList(pipeList []uint32) []uint32 {
	var portList []uint32
	for _, innerPipe := range pipeList {
		var pt uint32
		for pt = 0; pt <= 60; pt += 4 {
			innerDP := innerPipe<<7 + pt
			portList = append(portList, innerDP)
		}
	}
	return portList
}

// func genHpaInnerPortList(pipeList []uint32) []uint32 {
// 	var portList []uint32
// 	var pipe1InnerPortList = []uint32{0, 1, 3}

// 	for _, innerPipe := range pipeList {
// 		var pt uint32
// 		for pt = 0; pt <= 60; pt += 4 {
// 			innerDP := innerPipe<<7 + pt
// 			portList = append(portList, innerDP)
// 		}
// 	}
// 	return portList
// }

//  **************** test functions ****************

func test_parse_platform() {
	// filePath := "/Users/haoleeson/work/HPA/hpa1_conf/host_machine_65x.conf"
	// filePath := "/Users/haoleeson/work/HPA/hpa1_conf/host_machine_xlt.conf"
	filePath := "/Users/haoleeson/work/HPA/hpa1_conf/host_machine_hpa.conf"
	strPlatform := parsePlatformFromFile(filePath)
	fmt.Printf("strPlatform: '%v'\n", strPlatform)
}

func test_gen_port_list() {
	var pipeList []uint32
	var portList []uint32
	// pipeList := make(list[uint32])
	i := 1
	if i == 1 {
		pipeList = []uint32{0, 1, 3}
	} else {
		pipeList = []uint32{2, 4, 6}
	}
	fmt.Printf("pipeList: '%v'\n", pipeList)

	portList = generateInnerPortList(pipeList)
	fmt.Printf("portList: '%v'\n", portList)
}

type BGPClientType uint

const (
	BGPClientTypeUNKNOWN BGPClientType = iota
	BGPClientTypeGOBGP
	BGPClientTypeFRR
)

func (r *BGPClientType) UnmarshalYAML(unmarshal func(interface{}) error) error {
	var types string
	unmarshal(&types)
	switch types {
	case "gobgp":
		*r = BGPClientTypeGOBGP
	case "frr":
		*r = BGPClientTypeFRR
	}
	return nil
}

func testUnmarshal() {
	var a BGPClientType = BGPClientTypeUNKNOWN
	fmt.Printf("a val: %v\n", a)
	gen_unmarshal_fun := func(s string) func(v interface{}) error {
		return func(v interface{}) error {
			switch x := v.(type) {
			case *string:
				*x = s
			default:
				return fmt.Errorf("Unsupported type")
			}
			return nil
		}
	}
	// unmarshal_gobgp_fun := func(v interface{}) error {
	// 	switch x := v.(type) {
	// 	case *string:
	// 		*x = "gobgp"
	// 	default:
	// 		return fmt.Errorf("Unsupported type")
	// 	}
	// 	return nil
	// }
	// unmarshal_frr_fun := func(v interface{}) error {
	// 	switch x := v.(type) {
	// 	case *string:
	// 		*x = "frr"
	// 	default:
	// 		return fmt.Errorf("Unsupported type")
	// 	}
	// 	return nil
	// }
	a.UnmarshalYAML(gen_unmarshal_fun("gobgp"))
	fmt.Printf("Type of UnmarshalYAMLed a: %T\n", reflect.TypeOf(a))
	fmt.Printf("a val: %v\n", a)
	a.UnmarshalYAML(gen_unmarshal_fun("frr"))
	fmt.Printf("Type of UnmarshalYAMLed a: %T\n", reflect.TypeOf(a))
	fmt.Printf("a val: %v\n", a)
}

type WorkType uint

const (
	WorkTypeUNKNOWN WorkType = iota
	WorkTypeFULL
	WorkTypeINC
)

type TRCWorkPriority uint

const (
	TRCWORKPRIORITYLOW TRCWorkPriority = iota
	TRCWORKPRIORITYHIGH
	TRCWORKPRIORITYNUM
)

type RetryPolicy struct {
	MaxAttemptTimes uint
	RetryWork       *WorkSpec
}

type WorkSpec struct {
	Type       WorkType
	WorkListID uint64
	WorkID     uint64
	Workfunc   func() error
	//Timeout  time.Duration
	Retrypl *RetryPolicy
	Pri     TRCWorkPriority
}

func (r WorkSpec) Copy() WorkSpec {
	var ws WorkSpec = r

	if r.Retrypl != nil {
		var rpl RetryPolicy = *r.Retrypl
		if r.Retrypl.RetryWork != nil {
			var rws WorkSpec = r.Retrypl.RetryWork.Copy()
			rpl.RetryWork = &rws
		}
		ws.Retrypl = &rpl
	} else {
		ws.Retrypl = &RetryPolicy{
			MaxAttemptTimes: 1,
		}
	}
	return ws
}

func testWorkSpecCopy() {
	a := WorkSpec{Retrypl: &RetryPolicy{MaxAttemptTimes: 0}}
	b := a.Copy()
	fmt.Printf("a: %+v\n", a)
	fmt.Printf("b: %+v\n", b)
	// fmt.Printf("c: %+v\n", c)
	fmt.Printf("a.Retrypl: %+v\n", a.Retrypl)
	fmt.Printf("b.Retrypl: %+v\n", b.Retrypl)
	// fmt.Printf("c.Retrypl: %+v\n", c.Retrypl)
}

func print_speed(v interface{}) {
	var ret float64 = 0
	val, ok := v.(float64)
	if ok {
		ret = val
	} else {
		val, ok := v.(string)
		if ok {
			motor0Speed0, err := strconv.ParseFloat(val, 64)
			if err == nil {
				ret = motor0Speed0
			}
		}
	}
	fmt.Printf("speed: %v\n", ret)
}

type ExecutorErr struct {
	causeerr error
}

func (r ExecutorErr) Error() string {
	return fmt.Sprintf("exector error: %v", r.causeerr)
}

type ControlerAPIErr struct {
	causeerr error
}

func (r ControlerAPIErr) Error() string {
	return "Controler API return err: " + r.causeerr.Error()
}

type (
	NeighborConfig struct {
		Asn       string `json:"asn"`
		Keepalive string `json:"keepalive"`
		LocalAddr string `json:"local_addr"`
		Name      string `json:"name"`
		NhopSelf  string `json:"nhopself"`
		RrClient  string `json:"rrclient"`
	}
	SonicConfig struct {
		BgpNeighbor map[string]*NeighborConfig `json:"BGP_NEIGHBOR"`
	}
)

func loadConfig(v interface{}, filename string) error {
	data, e := ioutil.ReadFile(filename)
	if e != nil {
		fmt.Println("no such file")
		return fmt.Errorf("load file error: %s", e.Error())
	}
	e = json.Unmarshal(data, v)
	if e != nil {
		fmt.Println("not valid json")
		return fmt.Errorf("load file error: %s", e.Error())
	}
	return nil
}

func calcLocalIP(peerIP string) string {
	if strings.Contains(peerIP, ".") {
		a := "121"
		if aa, e := strconv.ParseInt(a, 10, 64); e == nil {
			fmt.Printf("%s 10base strconv val = %d\n", a, aa)
			a2 := aa ^ 1
			fmt.Printf("%s peer val = %d\n", a, a2)
		}
	} else if strings.Contains(peerIP, ":") {
		b := "ecab"
		if bb, e := strconv.ParseInt(b, 16, 64); e == nil {
			fmt.Printf("%s 16base strconv val = %d\n", b, bb)
			b2 := bb ^ 1
			fmt.Printf("%s peer val = %x\n", b, b2)
		}
	}

	return ""
}

type Peer struct {
	a string
}

type Path struct {
	SourceAsn uint32
	SourceId  string
}

type Destination struct {
	Prefix string
	Paths  []*Path
}

func tblToAPIDest() []*Destination {
	ret := []*Destination{}
	pathnum := 0
	limit := 10

	for i := 0; i < 8; i++ {
		d := Destination{
			Prefix: "iii",
			Paths:  make([]*Path, 0, limit),
		}
		for j := 0; j < 5; j++ {
			p := &Path{
				SourceAsn: 1,
				SourceId:  "jjj",
			}
			d.Paths = append(d.Paths, p)
			pathnum += 1
		}

		if len(d.Paths) > 0 {
			ret = append(ret, &d)
		}

	}

	return ret
}

func test_release() {
	destarrarr := [][]*Destination{}
	for i := 0; i < 3; i++ {
		destarr := tblToAPIDest()
		destarrarr = append(destarrarr, destarr)
	}

	fmt.Println("create down")

	relFunc := func(destarrarr [][]*Destination) {
		for i := 0; i < len(destarrarr); i++ {
			destarr := destarrarr[i]
			for j := 0; j < len(destarr); j++ {
				d := destarr[j]
				for k := 0; k < len(d.Paths); k++ {
					d.Paths[k] = nil
				}
				d.Paths = nil
				destarr[j] = nil
			}
			destarrarr[i] = nil
		}
		destarrarr = nil
	}

	relFunc(destarrarr)

	fmt.Println("release down")

}

func test_variable_len_params(p1 string, bCalc ...bool) {
	bNeedCalc := false
	if len(bCalc) != 0 && bCalc[0] {
		bNeedCalc = true
	}
	fmt.Println("param1:", p1, ", param2: ", bNeedCalc)
}

func print_time() {
	fmt.Println("Format time.DateTime: ", time.Now().Format(time.DateTime))
	fmt.Println("Format time.RFC3339: ", time.Now().Format(time.RFC3339))
	// Format time.RFC3339Nano:  2024-07-08T10:25:34.565211+08:00
	fmt.Println("Format time.RFC3339Nano: ", time.Now().Format(time.RFC3339Nano))
	// Format time.StampMilli:  Jul  8 10:25:34.565
	fmt.Println("Format time.StampMilli: ", time.Now().Format(time.StampMilli))
}

func calcMinMaxAvgOfFileInputNums(filePath string) {
	var err error = nil
	var sum, tmpNum, avg float64 = 0.0, 0.0, 0.0
	var cnt int = 0
	var min float64 = math.MaxFloat64
	var max float64 = 0

	file, err := os.Open(filePath)
	if err != nil {
		fmt.Printf("failed to open file due to %s", err.Error())
		return
	}
	defer file.Close()

	fileScanner := bufio.NewScanner(file)
	for fileScanner.Scan() {
		line := fileScanner.Text()
		line = strings.Trim(line, " ")

		if strings.HasSuffix(line, "ms") {
			if tmpNum, err = strconv.ParseFloat(line[:len(line)-2], 64); err == nil {
				tmpNum = tmpNum * 1000
				sum += tmpNum
				cnt++
				if tmpNum < min {
					min = tmpNum
				}
				if tmpNum > max {
					max = tmpNum
				}
			}
		} else if strings.HasSuffix(line, "µs") {
			if tmpNum, err = strconv.ParseFloat(line[:len(line)-3], 64); err == nil {
				sum += tmpNum
				cnt++
				if tmpNum < min {
					min = tmpNum
				}
				if tmpNum > max {
					max = tmpNum
				}
			}
		} else {
			fmt.Printf("can not parse line: %s, ignore it\n", line)
		}
	}

	// output
	printCost := func(name string, val float64) {
		if val > 1000 {
			fmt.Printf("%s: %.3fms\n", name, val/1000)
		} else {
			fmt.Printf("%s: %.3fµs\n", name, val)
		}
	}

	fmt.Printf("cnt: %d\n", cnt)
	printCost("min", min)
	printCost("max", max)
	avg = sum / float64(cnt)
	printCost("avg", avg)
}

type RespRoutesInfo struct {
	Vni       uint32   `json:"vni"`
	Protocol  string   `json:"protocol"`
	IPNet     string   `json:"ipNet"`
	NextHop   []string `json:"nexthop"`
	IpVersion string   `json:"ipVersion"`
}

// type GetRoutesResp struct {
// 	ErrCode   string           `json:"errCode"`
// 	ErrMsg    string           `json:"errMsg"`
// 	Success   bool             `json:"success"`
// 	Data      []RespRoutesInfo `json:"data"`
// 	RequestID string           `json:"requestID"`
// }

type HpaRoutesInfo struct {
	Prefix                   string `json:"prefix"`
	Protocol                 string `json:"protocol"`
	VrfId                    uint64 `json:"vrfId"`
	VrfName                  string `json:"vrfName"`
	Selected                 bool   `json:"selected"`
	DestSelected             bool   `json:"destSelected"`
	Distance                 uint64 `json:"distance"`
	Metric                   uint64 `json:"metric"`
	Installed                bool   `json:"installed"`
	Table                    uint64 `json:"table"`
	InternalStatus           uint64 `json:"internalStatus"`
	InternalFlags            uint64 `json:"internalFlags"`
	InternalNextHopNum       uint64 `json:"internalNextHopNum"`
	InternalNextHopActiveNum uint64 `json:"internalNextHopActiveNum"`
	Uptime                   string `json:"uptime"`
	Nexthops                 []struct {
		Flags          uint64 `json:"flags"`
		Fib            bool   `json:"fib"`
		IP             string `json:"ip"`
		Afi            string `json:"afi"`
		InterfaceIndex uint64 `json:"interfaceIndex"`
		InterfaceName  string `json:"interfaceName"`
		Active         bool   `json:"active"`
		Weight         uint64 `json:"weight"`
	} `json:"nexthops"`
}

const (
	VTYSH_PROTOCOL_TYPE_BGP      = "bgp"
	VTYSH_PROTOCOL_TYPE_STATIC   = "static"
	VTYSH_VRF_NAME_DEFAULT       = "default"
	VTYSH_VRF_NAME_PREFIX        = "Vrf"
	VTYSH_AFI4                   = "ipv4"
	VTYSH_AFI6                   = "ipv6"
	VTYSH_CMD                    = "vtysh"
	VTYSH_EXECUTE_ARGUMENT       = "-c"
	VTYSH_EXECUTE_HELP           = "-h"
	VTYSH_SHOW_ALL_V4_ROUTES_CMD = "show ip route json"
	VTYSH_SHOW_ALL_V6_ROUTES_CMD = "show ipv6 route json"
	RESP_ROUTE_TYPE_BGP          = "BGP"
	RESP_ROUTE_TYPE_STATIC       = "STATIC"
	RESP_IP_V4_VERSION           = "IPv4"
	RESP_IP_V6_VERSION           = "IPv6"
	IPV4_SEPARATOR               = "."
	ROUTE_PREFIX_REGEXP          = "(default|[0-9a-f:/.]{2,})"
	ATTR_FIELD_SCOPE_LINK        = "scope link"
	ATTR_FIELD_PROTO_KERNEL      = "proto kernel"
	ATTR_KEY_PROTO               = "proto"
	ATTR_KEY_NEXTHOP             = "nexthop"
	ATTR_KEY_VIA                 = "via"
	ATTR_FIELD_STATIC            = "static"
	DEFAULT_ROUTE_PREFIX         = "default"
	V4_DEFAULT_ROUTE_PREFIX      = "0.0.0.0"
	V6_DEFAULT_ROUTE_PREFIX      = "::"
)

func parseRoutesInfo(m map[string][]HpaRoutesInfo) []RespRoutesInfo {
	res := make([]RespRoutesInfo, 0)

	for _, listHpaRoutesInfo := range m {
		for _, hpaRoutesInfo := range listHpaRoutesInfo {
			respRoutesInfo := RespRoutesInfo{}

			// vni
			if strings.HasPrefix(hpaRoutesInfo.VrfName, VTYSH_VRF_NAME_PREFIX) {
				if vniUint64, err := strconv.ParseUint(hpaRoutesInfo.VrfName[len(VTYSH_VRF_NAME_PREFIX):], 10, 32); err != nil {
					respRoutesInfo.Vni = uint32(vniUint64)
				}
			}
			// protocol
			switch hpaRoutesInfo.Protocol {
			case VTYSH_PROTOCOL_TYPE_BGP:
				respRoutesInfo.Protocol = RESP_ROUTE_TYPE_BGP
			case VTYSH_PROTOCOL_TYPE_STATIC:
				respRoutesInfo.Protocol = RESP_ROUTE_TYPE_STATIC
			default:
				fmt.Printf("unsupport protocol %s, skip", hpaRoutesInfo.Protocol)
				continue
			}
			// ipNet
			respRoutesInfo.IPNet = hpaRoutesInfo.Prefix
			// NextHop
			if len(hpaRoutesInfo.Nexthops) > 0 {
				respRoutesInfo.NextHop = make([]string, 0)
				// ipVersion
				switch hpaRoutesInfo.Nexthops[0].Afi {
				case VTYSH_AFI4:
					respRoutesInfo.IpVersion = RESP_IP_V4_VERSION
				case VTYSH_AFI6:
					respRoutesInfo.IpVersion = RESP_IP_V6_VERSION
				default:
					fmt.Printf("parse ip version failed, unsupport afi %s, skip", hpaRoutesInfo.Nexthops[0].Afi)
					continue
				}

				for _, nh := range hpaRoutesInfo.Nexthops {
					respRoutesInfo.NextHop = append(respRoutesInfo.NextHop, nh.IP)
				}
			}

			res = append(res, respRoutesInfo)
		}
	}

	return res
}

func testJsonUnmarshal() {
	var res *GetRoutesResp = &GetRoutesResp{}
	res.Data = make([]RespRoutesInfo, 0)

	var v4Out []byte = []byte("{\"0.0.0.0/0\":[{\"prefix\":\"0.0.0.0/0\",\"protocol\":\"bgp\",\"vrfId\":0,\"vrfName\":\"default\",\"selected\":true,\"destSelected\":true,\"distance\":20,\"metric\":0,\"installed\":true,\"table\":254,\"internalStatus\":16,\"internalFlags\":8,\"internalNextHopNum\":16,\"internalNextHopActiveNum\":16,\"uptime\":\"15w4d22h\",\"nexthops\":[{\"flags\":3,\"fib\":true,\"ip\":\"100.98.35.60\",\"afi\":\"ipv4\",\"interfaceIndex\":14,\"interfaceName\":\"ethernet1\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"100.98.35.62\",\"afi\":\"ipv4\",\"interfaceIndex\":15,\"interfaceName\":\"ethernet2\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"100.98.35.64\",\"afi\":\"ipv4\",\"interfaceIndex\":16,\"interfaceName\":\"ethernet3\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"100.98.35.66\",\"afi\":\"ipv4\",\"interfaceIndex\":17,\"interfaceName\":\"ethernet4\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"100.98.35.68\",\"afi\":\"ipv4\",\"interfaceIndex\":18,\"interfaceName\":\"ethernet5\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"100.98.35.70\",\"afi\":\"ipv4\",\"interfaceIndex\":19,\"interfaceName\":\"ethernet6\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"100.98.35.72\",\"afi\":\"ipv4\",\"interfaceIndex\":20,\"interfaceName\":\"ethernet7\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"100.98.35.74\",\"afi\":\"ipv4\",\"interfaceIndex\":21,\"interfaceName\":\"ethernet8\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"100.98.35.76\",\"afi\":\"ipv4\",\"interfaceIndex\":22,\"interfaceName\":\"ethernet9\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"100.98.35.78\",\"afi\":\"ipv4\",\"interfaceIndex\":23,\"interfaceName\":\"ethernet10\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"100.98.35.80\",\"afi\":\"ipv4\",\"interfaceIndex\":24,\"interfaceName\":\"ethernet11\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"100.98.35.82\",\"afi\":\"ipv4\",\"interfaceIndex\":25,\"interfaceName\":\"ethernet12\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"100.98.35.84\",\"afi\":\"ipv4\",\"interfaceIndex\":26,\"interfaceName\":\"ethernet13\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"100.98.35.86\",\"afi\":\"ipv4\",\"interfaceIndex\":27,\"interfaceName\":\"ethernet14\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"100.98.35.88\",\"afi\":\"ipv4\",\"interfaceIndex\":28,\"interfaceName\":\"ethernet15\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"100.98.35.90\",\"afi\":\"ipv4\",\"interfaceIndex\":29,\"interfaceName\":\"ethernet16\",\"active\":true,\"weight\":1}]}],\"10.0.0.0/8\":[{\"prefix\":\"10.0.0.0/8\",\"protocol\":\"bgp\",\"vrfId\":0,\"vrfName\":\"default\",\"selected\":true,\"destSelected\":true,\"distance\":20,\"metric\":0,\"installed\":true,\"table\":254,\"internalStatus\":16,\"internalFlags\":8,\"internalNextHopNum\":16,\"internalNextHopActiveNum\":16,\"uptime\":\"15w4d22h\",\"nexthops\":[{\"flags\":3,\"fib\":true,\"ip\":\"100.98.35.60\",\"afi\":\"ipv4\",\"interfaceIndex\":14,\"interfaceName\":\"ethernet1\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"100.98.35.62\",\"afi\":\"ipv4\",\"interfaceIndex\":15,\"interfaceName\":\"ethernet2\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"100.98.35.64\",\"afi\":\"ipv4\",\"interfaceIndex\":16,\"interfaceName\":\"ethernet3\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"100.98.35.66\",\"afi\":\"ipv4\",\"interfaceIndex\":17,\"interfaceName\":\"ethernet4\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"100.98.35.68\",\"afi\":\"ipv4\",\"interfaceIndex\":18,\"interfaceName\":\"ethernet5\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"100.98.35.70\",\"afi\":\"ipv4\",\"interfaceIndex\":19,\"interfaceName\":\"ethernet6\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"100.98.35.72\",\"afi\":\"ipv4\",\"interfaceIndex\":20,\"interfaceName\":\"ethernet7\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"100.98.35.74\",\"afi\":\"ipv4\",\"interfaceIndex\":21,\"interfaceName\":\"ethernet8\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"100.98.35.76\",\"afi\":\"ipv4\",\"interfaceIndex\":22,\"interfaceName\":\"ethernet9\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"100.98.35.78\",\"afi\":\"ipv4\",\"interfaceIndex\":23,\"interfaceName\":\"ethernet10\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"100.98.35.80\",\"afi\":\"ipv4\",\"interfaceIndex\":24,\"interfaceName\":\"ethernet11\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"100.98.35.82\",\"afi\":\"ipv4\",\"interfaceIndex\":25,\"interfaceName\":\"ethernet12\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"100.98.35.84\",\"afi\":\"ipv4\",\"interfaceIndex\":26,\"interfaceName\":\"ethernet13\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"100.98.35.86\",\"afi\":\"ipv4\",\"interfaceIndex\":27,\"interfaceName\":\"ethernet14\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"100.98.35.88\",\"afi\":\"ipv4\",\"interfaceIndex\":28,\"interfaceName\":\"ethernet15\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"100.98.35.90\",\"afi\":\"ipv4\",\"interfaceIndex\":29,\"interfaceName\":\"ethernet16\",\"active\":true,\"weight\":1}]}]}")
	v4Map := make(map[string][]HpaRoutesInfo)
	if err := json.Unmarshal(v4Out, &v4Map); err != nil {
		fmt.Printf("unmarshal v4 routes from output of vtysh failed")
	}

	v4RespRoutes := parseRoutesInfo(v4Map)
	if len(v4RespRoutes) > 0 {
		res.Data = v4RespRoutes
		res.Success = true
	}

	var v6Out []byte = []byte("{\"fdbd::/16\":[{\"prefix\":\"fdbd::/16\",\"protocol\":\"bgp\",\"vrfId\":0,\"vrfName\":\"default\",\"selected\":true,\"destSelected\":true,\"distance\":20,\"metric\":0,\"installed\":true,\"table\":254,\"internalStatus\":16,\"internalFlags\":8,\"internalNextHopNum\":16,\"internalNextHopActiveNum\":16,\"uptime\":\"15w5d02h\",\"nexthops\":[{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:233c\",\"afi\":\"ipv6\",\"interfaceIndex\":14,\"interfaceName\":\"ethernet1\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:233e\",\"afi\":\"ipv6\",\"interfaceIndex\":15,\"interfaceName\":\"ethernet2\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:2340\",\"afi\":\"ipv6\",\"interfaceIndex\":16,\"interfaceName\":\"ethernet3\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:2342\",\"afi\":\"ipv6\",\"interfaceIndex\":17,\"interfaceName\":\"ethernet4\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:2344\",\"afi\":\"ipv6\",\"interfaceIndex\":18,\"interfaceName\":\"ethernet5\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:2346\",\"afi\":\"ipv6\",\"interfaceIndex\":19,\"interfaceName\":\"ethernet6\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:2348\",\"afi\":\"ipv6\",\"interfaceIndex\":20,\"interfaceName\":\"ethernet7\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:234a\",\"afi\":\"ipv6\",\"interfaceIndex\":21,\"interfaceName\":\"ethernet8\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:234c\",\"afi\":\"ipv6\",\"interfaceIndex\":22,\"interfaceName\":\"ethernet9\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:234e\",\"afi\":\"ipv6\",\"interfaceIndex\":23,\"interfaceName\":\"ethernet10\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:2350\",\"afi\":\"ipv6\",\"interfaceIndex\":24,\"interfaceName\":\"ethernet11\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:2352\",\"afi\":\"ipv6\",\"interfaceIndex\":25,\"interfaceName\":\"ethernet12\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:2354\",\"afi\":\"ipv6\",\"interfaceIndex\":26,\"interfaceName\":\"ethernet13\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:2356\",\"afi\":\"ipv6\",\"interfaceIndex\":27,\"interfaceName\":\"ethernet14\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:2358\",\"afi\":\"ipv6\",\"interfaceIndex\":28,\"interfaceName\":\"ethernet15\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:235a\",\"afi\":\"ipv6\",\"interfaceIndex\":29,\"interfaceName\":\"ethernet16\",\"active\":true,\"weight\":1}]}],\"fdbd:dc00:46::6462:233c/127\":[{\"prefix\":\"fdbd:dc00:46::6462:233c/127\",\"protocol\":\"connected\",\"vrfId\":0,\"vrfName\":\"default\",\"selected\":true,\"destSelected\":true,\"distance\":0,\"metric\":0,\"installed\":true,\"table\":254,\"internalStatus\":16,\"internalFlags\":8,\"internalNextHopNum\":1,\"internalNextHopActiveNum\":1,\"uptime\":\"15w5d02h\",\"nexthops\":[{\"flags\":3,\"fib\":true,\"directlyConnected\":true,\"interfaceIndex\":14,\"interfaceName\":\"ethernet1\",\"active\":true}]}],\"fdbd:dc00:46::6462:233e/127\":[{\"prefix\":\"fdbd:dc00:46::6462:233e/127\",\"protocol\":\"connected\",\"vrfId\":0,\"vrfName\":\"default\",\"selected\":true,\"destSelected\":true,\"distance\":0,\"metric\":0,\"installed\":true,\"table\":254,\"internalStatus\":16,\"internalFlags\":8,\"internalNextHopNum\":1,\"internalNextHopActiveNum\":1,\"uptime\":\"15w5d02h\",\"nexthops\":[{\"flags\":3,\"fib\":true,\"directlyConnected\":true,\"interfaceIndex\":15,\"interfaceName\":\"ethernet2\",\"active\":true}]}],\"fdbd:dc00:46::6462:2340/127\":[{\"prefix\":\"fdbd:dc00:46::6462:2340/127\",\"protocol\":\"connected\",\"vrfId\":0,\"vrfName\":\"default\",\"selected\":true,\"destSelected\":true,\"distance\":0,\"metric\":0,\"installed\":true,\"table\":254,\"internalStatus\":16,\"internalFlags\":8,\"internalNextHopNum\":1,\"internalNextHopActiveNum\":1,\"uptime\":\"15w5d02h\",\"nexthops\":[{\"flags\":3,\"fib\":true,\"directlyConnected\":true,\"interfaceIndex\":16,\"interfaceName\":\"ethernet3\",\"active\":true}]}],\"fdbd:dc00:46::6462:2342/127\":[{\"prefix\":\"fdbd:dc00:46::6462:2342/127\",\"protocol\":\"connected\",\"vrfId\":0,\"vrfName\":\"default\",\"selected\":true,\"destSelected\":true,\"distance\":0,\"metric\":0,\"installed\":true,\"table\":254,\"internalStatus\":16,\"internalFlags\":8,\"internalNextHopNum\":1,\"internalNextHopActiveNum\":1,\"uptime\":\"15w5d02h\",\"nexthops\":[{\"flags\":3,\"fib\":true,\"directlyConnected\":true,\"interfaceIndex\":17,\"interfaceName\":\"ethernet4\",\"active\":true}]}],\"fdbd:dc00:46::6462:2344/127\":[{\"prefix\":\"fdbd:dc00:46::6462:2344/127\",\"protocol\":\"connected\",\"vrfId\":0,\"vrfName\":\"default\",\"selected\":true,\"destSelected\":true,\"distance\":0,\"metric\":0,\"installed\":true,\"table\":254,\"internalStatus\":16,\"internalFlags\":8,\"internalNextHopNum\":1,\"internalNextHopActiveNum\":1,\"uptime\":\"15w5d02h\",\"nexthops\":[{\"flags\":3,\"fib\":true,\"directlyConnected\":true,\"interfaceIndex\":18,\"interfaceName\":\"ethernet5\",\"active\":true}]}],\"fdbd:dc00:46::6462:2346/127\":[{\"prefix\":\"fdbd:dc00:46::6462:2346/127\",\"protocol\":\"connected\",\"vrfId\":0,\"vrfName\":\"default\",\"selected\":true,\"destSelected\":true,\"distance\":0,\"metric\":0,\"installed\":true,\"table\":254,\"internalStatus\":16,\"internalFlags\":8,\"internalNextHopNum\":1,\"internalNextHopActiveNum\":1,\"uptime\":\"15w5d02h\",\"nexthops\":[{\"flags\":3,\"fib\":true,\"directlyConnected\":true,\"interfaceIndex\":19,\"interfaceName\":\"ethernet6\",\"active\":true}]}],\"fdbd:dc00:46::6462:2348/127\":[{\"prefix\":\"fdbd:dc00:46::6462:2348/127\",\"protocol\":\"connected\",\"vrfId\":0,\"vrfName\":\"default\",\"selected\":true,\"destSelected\":true,\"distance\":0,\"metric\":0,\"installed\":true,\"table\":254,\"internalStatus\":16,\"internalFlags\":8,\"internalNextHopNum\":1,\"internalNextHopActiveNum\":1,\"uptime\":\"15w5d02h\",\"nexthops\":[{\"flags\":3,\"fib\":true,\"directlyConnected\":true,\"interfaceIndex\":20,\"interfaceName\":\"ethernet7\",\"active\":true}]}],\"fdbd:dc00:46::6462:234a/127\":[{\"prefix\":\"fdbd:dc00:46::6462:234a/127\",\"protocol\":\"connected\",\"vrfId\":0,\"vrfName\":\"default\",\"selected\":true,\"destSelected\":true,\"distance\":0,\"metric\":0,\"installed\":true,\"table\":254,\"internalStatus\":16,\"internalFlags\":8,\"internalNextHopNum\":1,\"internalNextHopActiveNum\":1,\"uptime\":\"15w5d02h\",\"nexthops\":[{\"flags\":3,\"fib\":true,\"directlyConnected\":true,\"interfaceIndex\":21,\"interfaceName\":\"ethernet8\",\"active\":true}]}],\"fdbd:dc00:46::6462:234c/127\":[{\"prefix\":\"fdbd:dc00:46::6462:234c/127\",\"protocol\":\"connected\",\"vrfId\":0,\"vrfName\":\"default\",\"selected\":true,\"destSelected\":true,\"distance\":0,\"metric\":0,\"installed\":true,\"table\":254,\"internalStatus\":16,\"internalFlags\":8,\"internalNextHopNum\":1,\"internalNextHopActiveNum\":1,\"uptime\":\"15w5d02h\",\"nexthops\":[{\"flags\":3,\"fib\":true,\"directlyConnected\":true,\"interfaceIndex\":22,\"interfaceName\":\"ethernet9\",\"active\":true}]}],\"fdbd:dc00:46::6462:234e/127\":[{\"prefix\":\"fdbd:dc00:46::6462:234e/127\",\"protocol\":\"connected\",\"vrfId\":0,\"vrfName\":\"default\",\"selected\":true,\"destSelected\":true,\"distance\":0,\"metric\":0,\"installed\":true,\"table\":254,\"internalStatus\":16,\"internalFlags\":8,\"internalNextHopNum\":1,\"internalNextHopActiveNum\":1,\"uptime\":\"15w5d02h\",\"nexthops\":[{\"flags\":3,\"fib\":true,\"directlyConnected\":true,\"interfaceIndex\":23,\"interfaceName\":\"ethernet10\",\"active\":true}]}],\"fdbd:dc00:46::6462:2350/127\":[{\"prefix\":\"fdbd:dc00:46::6462:2350/127\",\"protocol\":\"connected\",\"vrfId\":0,\"vrfName\":\"default\",\"selected\":true,\"destSelected\":true,\"distance\":0,\"metric\":0,\"installed\":true,\"table\":254,\"internalStatus\":16,\"internalFlags\":8,\"internalNextHopNum\":1,\"internalNextHopActiveNum\":1,\"uptime\":\"15w5d02h\",\"nexthops\":[{\"flags\":3,\"fib\":true,\"directlyConnected\":true,\"interfaceIndex\":24,\"interfaceName\":\"ethernet11\",\"active\":true}]}],\"fdbd:dc00:46::6462:2352/127\":[{\"prefix\":\"fdbd:dc00:46::6462:2352/127\",\"protocol\":\"connected\",\"vrfId\":0,\"vrfName\":\"default\",\"selected\":true,\"destSelected\":true,\"distance\":0,\"metric\":0,\"installed\":true,\"table\":254,\"internalStatus\":16,\"internalFlags\":8,\"internalNextHopNum\":1,\"internalNextHopActiveNum\":1,\"uptime\":\"15w5d02h\",\"nexthops\":[{\"flags\":3,\"fib\":true,\"directlyConnected\":true,\"interfaceIndex\":25,\"interfaceName\":\"ethernet12\",\"active\":true}]}],\"fdbd:dc00:46::6462:2354/127\":[{\"prefix\":\"fdbd:dc00:46::6462:2354/127\",\"protocol\":\"connected\",\"vrfId\":0,\"vrfName\":\"default\",\"selected\":true,\"destSelected\":true,\"distance\":0,\"metric\":0,\"installed\":true,\"table\":254,\"internalStatus\":16,\"internalFlags\":8,\"internalNextHopNum\":1,\"internalNextHopActiveNum\":1,\"uptime\":\"15w5d02h\",\"nexthops\":[{\"flags\":3,\"fib\":true,\"directlyConnected\":true,\"interfaceIndex\":26,\"interfaceName\":\"ethernet13\",\"active\":true}]}],\"fdbd:dc00:46::6462:2356/127\":[{\"prefix\":\"fdbd:dc00:46::6462:2356/127\",\"protocol\":\"connected\",\"vrfId\":0,\"vrfName\":\"default\",\"selected\":true,\"destSelected\":true,\"distance\":0,\"metric\":0,\"installed\":true,\"table\":254,\"internalStatus\":16,\"internalFlags\":8,\"internalNextHopNum\":1,\"internalNextHopActiveNum\":1,\"uptime\":\"15w5d02h\",\"nexthops\":[{\"flags\":3,\"fib\":true,\"directlyConnected\":true,\"interfaceIndex\":27,\"interfaceName\":\"ethernet14\",\"active\":true}]}],\"fdbd:dc00:46::6462:2358/127\":[{\"prefix\":\"fdbd:dc00:46::6462:2358/127\",\"protocol\":\"connected\",\"vrfId\":0,\"vrfName\":\"default\",\"selected\":true,\"destSelected\":true,\"distance\":0,\"metric\":0,\"installed\":true,\"table\":254,\"internalStatus\":16,\"internalFlags\":8,\"internalNextHopNum\":1,\"internalNextHopActiveNum\":1,\"uptime\":\"15w5d02h\",\"nexthops\":[{\"flags\":3,\"fib\":true,\"directlyConnected\":true,\"interfaceIndex\":28,\"interfaceName\":\"ethernet15\",\"active\":true}]}],\"fdbd:dc00:46::6462:235a/127\":[{\"prefix\":\"fdbd:dc00:46::6462:235a/127\",\"protocol\":\"connected\",\"vrfId\":0,\"vrfName\":\"default\",\"selected\":true,\"destSelected\":true,\"distance\":0,\"metric\":0,\"installed\":true,\"table\":254,\"internalStatus\":16,\"internalFlags\":8,\"internalNextHopNum\":1,\"internalNextHopActiveNum\":1,\"uptime\":\"15w5d02h\",\"nexthops\":[{\"flags\":3,\"fib\":true,\"directlyConnected\":true,\"interfaceIndex\":29,\"interfaceName\":\"ethernet16\",\"active\":true}]}],\"fdbd:dc41:98:ff05::24/128\":[{\"prefix\":\"fdbd:dc41:98:ff05::24/128\",\"protocol\":\"connected\",\"vrfId\":0,\"vrfName\":\"default\",\"selected\":true,\"destSelected\":true,\"distance\":0,\"metric\":0,\"installed\":true,\"table\":254,\"internalStatus\":16,\"internalFlags\":8,\"internalNextHopNum\":1,\"internalNextHopActiveNum\":1,\"uptime\":\"15w5d02h\",\"nexthops\":[{\"flags\":3,\"fib\":true,\"directlyConnected\":true,\"interfaceIndex\":10,\"interfaceName\":\"loopback0\",\"active\":true}]}],\"fdbd:dc41:98:ff06::c/128\":[{\"prefix\":\"fdbd:dc41:98:ff06::c/128\",\"protocol\":\"bgp\",\"vrfId\":0,\"vrfName\":\"default\",\"selected\":true,\"destSelected\":true,\"distance\":20,\"metric\":0,\"installed\":true,\"table\":254,\"internalStatus\":16,\"internalFlags\":8,\"internalNextHopNum\":16,\"internalNextHopActiveNum\":16,\"uptime\":\"15w5d02h\",\"nexthops\":[{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:233c\",\"afi\":\"ipv6\",\"interfaceIndex\":14,\"interfaceName\":\"ethernet1\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:233e\",\"afi\":\"ipv6\",\"interfaceIndex\":15,\"interfaceName\":\"ethernet2\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:2340\",\"afi\":\"ipv6\",\"interfaceIndex\":16,\"interfaceName\":\"ethernet3\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:2342\",\"afi\":\"ipv6\",\"interfaceIndex\":17,\"interfaceName\":\"ethernet4\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:2344\",\"afi\":\"ipv6\",\"interfaceIndex\":18,\"interfaceName\":\"ethernet5\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:2346\",\"afi\":\"ipv6\",\"interfaceIndex\":19,\"interfaceName\":\"ethernet6\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:2348\",\"afi\":\"ipv6\",\"interfaceIndex\":20,\"interfaceName\":\"ethernet7\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:234a\",\"afi\":\"ipv6\",\"interfaceIndex\":21,\"interfaceName\":\"ethernet8\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:234c\",\"afi\":\"ipv6\",\"interfaceIndex\":22,\"interfaceName\":\"ethernet9\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:234e\",\"afi\":\"ipv6\",\"interfaceIndex\":23,\"interfaceName\":\"ethernet10\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:2350\",\"afi\":\"ipv6\",\"interfaceIndex\":24,\"interfaceName\":\"ethernet11\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:2352\",\"afi\":\"ipv6\",\"interfaceIndex\":25,\"interfaceName\":\"ethernet12\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:2354\",\"afi\":\"ipv6\",\"interfaceIndex\":26,\"interfaceName\":\"ethernet13\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:2356\",\"afi\":\"ipv6\",\"interfaceIndex\":27,\"interfaceName\":\"ethernet14\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:2358\",\"afi\":\"ipv6\",\"interfaceIndex\":28,\"interfaceName\":\"ethernet15\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:235a\",\"afi\":\"ipv6\",\"interfaceIndex\":29,\"interfaceName\":\"ethernet16\",\"active\":true,\"weight\":1}]}],\"fdbd:dc41:98:ff06::d/128\":[{\"prefix\":\"fdbd:dc41:98:ff06::d/128\",\"protocol\":\"bgp\",\"vrfId\":0,\"vrfName\":\"default\",\"selected\":true,\"destSelected\":true,\"distance\":20,\"metric\":0,\"installed\":true,\"table\":254,\"internalStatus\":16,\"internalFlags\":8,\"internalNextHopNum\":16,\"internalNextHopActiveNum\":16,\"uptime\":\"15w5d02h\",\"nexthops\":[{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:233c\",\"afi\":\"ipv6\",\"interfaceIndex\":14,\"interfaceName\":\"ethernet1\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:233e\",\"afi\":\"ipv6\",\"interfaceIndex\":15,\"interfaceName\":\"ethernet2\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:2340\",\"afi\":\"ipv6\",\"interfaceIndex\":16,\"interfaceName\":\"ethernet3\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:2342\",\"afi\":\"ipv6\",\"interfaceIndex\":17,\"interfaceName\":\"ethernet4\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:2344\",\"afi\":\"ipv6\",\"interfaceIndex\":18,\"interfaceName\":\"ethernet5\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:2346\",\"afi\":\"ipv6\",\"interfaceIndex\":19,\"interfaceName\":\"ethernet6\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:2348\",\"afi\":\"ipv6\",\"interfaceIndex\":20,\"interfaceName\":\"ethernet7\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:234a\",\"afi\":\"ipv6\",\"interfaceIndex\":21,\"interfaceName\":\"ethernet8\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:234c\",\"afi\":\"ipv6\",\"interfaceIndex\":22,\"interfaceName\":\"ethernet9\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:234e\",\"afi\":\"ipv6\",\"interfaceIndex\":23,\"interfaceName\":\"ethernet10\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:2350\",\"afi\":\"ipv6\",\"interfaceIndex\":24,\"interfaceName\":\"ethernet11\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:2352\",\"afi\":\"ipv6\",\"interfaceIndex\":25,\"interfaceName\":\"ethernet12\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:2354\",\"afi\":\"ipv6\",\"interfaceIndex\":26,\"interfaceName\":\"ethernet13\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:2356\",\"afi\":\"ipv6\",\"interfaceIndex\":27,\"interfaceName\":\"ethernet14\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:2358\",\"afi\":\"ipv6\",\"interfaceIndex\":28,\"interfaceName\":\"ethernet15\",\"active\":true,\"weight\":1},{\"flags\":3,\"fib\":true,\"ip\":\"fdbd:dc00:46::6462:235a\",\"afi\":\"ipv6\",\"interfaceIndex\":29,\"interfaceName\":\"ethernet16\",\"active\":true,\"weight\":1}]}]}")
	v6Map := make(map[string][]HpaRoutesInfo)
	if err := json.Unmarshal(v6Out, &v6Map); err != nil {
		fmt.Printf("unmarshal v6 routes from output of vtysh failed")
	}

	v6RespRoutes := parseRoutesInfo(v6Map)
	if len(v6RespRoutes) > 0 {
		res.Data = append(res.Data, v6RespRoutes...)
		res.Success = true
	}

	fmt.Printf("len of parsed v4Map is: %d", len(v4Map))
}

func parseIpRouteInfo(output []byte) []RespRoutesInfo {
	res := make([]RespRoutesInfo, 0)
	funcTryAdd := func(p *RespRoutesInfo, res *[]RespRoutesInfo) {
		if p == nil {
			return
		}
		if p.NextHop != nil && strings.Contains(p.NextHop[0], IPV4_SEPARATOR) {
			p.IpVersion = RESP_IP_V4_VERSION
		} else {
			p.IpVersion = RESP_IP_V6_VERSION
		}
		if p.IPNet == DEFAULT_ROUTE_PREFIX {
			if p.IpVersion == RESP_IP_V4_VERSION {
				p.IPNet = V4_DEFAULT_ROUTE_PREFIX
			} else {
				p.IPNet = V6_DEFAULT_ROUTE_PREFIX
			}
		}
		*res = append(*res, *p)
	}

	var p *RespRoutesInfo = nil
	var needAddF bool = false
	re, err := regexp.Compile(ROUTE_PREFIX_REGEXP)
	if err != nil || re == nil {
		fmt.Printf("invalid regexp patten")
	}

	lines := bytes.Split(output, []byte("\n"))
	for i := 0; i < len(lines); i++ {
		line := strings.TrimSpace(string(lines[i]))
		if len(line) == 0 {
			continue
		}
		// ignore scope link or proto kernel
		if strings.Contains(line, ATTR_FIELD_SCOPE_LINK) || strings.Contains(line, ATTR_FIELD_PROTO_KERNEL) {
			funcTryAdd(p, &res)
			needAddF = false
			p = nil
			continue
		}

		words := strings.SplitN(line, " ", 2)
		firstWord := words[0]
		behindS := words[1]

		if firstWord == ATTR_KEY_NEXTHOP {
			ipS := re.FindAllString(behindS, 1)
			p.NextHop = append(p.NextHop, ipS[0])
		} else {
			// If not nexthop, means a new route entry
			// try add the last route entry
			if needAddF {
				funcTryAdd(p, &res)
				needAddF = false
				p = nil
			}
			// ipNet
			p = &RespRoutesInfo{
				IPNet: firstWord,
			}
			p.NextHop = make([]string, 0)
			// vni
			// protocol
			if !strings.Contains(line, ATTR_KEY_PROTO) || strings.Contains(line, ATTR_FIELD_STATIC) {
				p.Protocol = RESP_ROUTE_TYPE_STATIC
			} else {
				p.Protocol = RESP_ROUTE_TYPE_BGP
			}
			// only one nexthop
			if strings.Contains(line, ATTR_KEY_VIA) {
				p.NextHop = make([]string, 0)
				ipS := re.FindAllString(behindS, 1)
				p.NextHop = append(p.NextHop, ipS[0])
				funcTryAdd(p, &res)
				needAddF = false
				p = nil
			} else {
				needAddF = true
			}
		}
	}
	// try add the last route entry
	if needAddF {
		funcTryAdd(p, &res)
		p = nil
	}

	return res
}

func testJsonUnmarshal2() {
	//var res *GetRoutesResp = &GetRoutesResp{}
	//res.Data = make([]RespRoutesInfo, 0)

	var v4Out []byte = []byte("default via 10.11.119.65 dev eth0 onlink \n10.11.119.64/26 dev eth0 proto kernel scope link src 10.11.119.78 \n10.250.0.0/24 dev mgmtbr0 proto kernel scope link src 10.250.0.1 \n172.17.0.0/16 dev docker0 proto kernel scope link src 172.17.0.1 \n192.168.122.0/24 dev virbr0 proto kernel scope link src 192.168.122.1 linkdown \n")
	listRespV4RoutesInfo := parseIpRouteInfo(v4Out)

	fmt.Printf("len(res): %d\n", len(listRespV4RoutesInfo))
	fmt.Printf("listRespV4RoutesInfo: %+v\n\n", listRespV4RoutesInfo)

	var v6Out []byte = []byte("fdbd:dcfd:0:14::/64 dev eth0 proto kernel metric 256 pref medium \nfe80::/64 dev eth0 proto kernel metric 256 pref medium \nfe80::/64 dev eth3 proto kernel metric 256 pref medium \nfe80::/64 dev docker0 proto kernel metric 256 pref medium \nfe80::/64 dev mgmtbr0 proto kernel metric 256 pref medium \nfe80::/64 dev ansible_mgmt proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0500-0 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0500-1 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0500-2 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0500-3 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0501-0 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0501-1 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0501-2 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0501-3 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0502-0 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0502-1 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0502-2 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0502-3 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0503-0 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0503-1 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0503-2 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0503-3 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0504-0 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0504-1 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0504-2 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0504-3 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0505-0 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0505-1 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0505-2 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0505-3 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0506-0 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0506-1 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0506-2 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0506-3 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0507-0 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0507-1 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0507-2 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0507-3 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0508-0 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0508-1 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0508-2 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0508-3 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0509-0 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0509-1 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0509-2 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0509-3 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0510-0 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0510-1 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0510-2 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0510-3 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0511-0 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0511-1 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0511-2 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0511-3 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0512-0 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0512-1 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0512-2 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0512-3 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0513-0 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0513-1 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0513-2 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0513-3 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0514-0 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0514-1 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0514-2 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0514-3 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0515-0 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0515-1 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0515-2 proto kernel metric 256 pref medium \nfe80::/64 dev br-VM0515-3 proto kernel metric 256 pref medium \nfe80::/64 dev VM0500-m proto kernel metric 256 pref medium \nfe80::/64 dev VM0500-t0 proto kernel metric 256 pref medium \nfe80::/64 dev VM0500-t1 proto kernel metric 256 pref medium \nfe80::/64 dev VM0500-t2 proto kernel metric 256 pref medium \nfe80::/64 dev VM0500-t3 proto kernel metric 256 pref medium \nfe80::/64 dev VM0500-back proto kernel metric 256 pref medium \nfe80::/64 dev VM0501-m proto kernel metric 256 pref medium \nfe80::/64 dev VM0501-t0 proto kernel metric 256 pref medium \nfe80::/64 dev VM0501-t1 proto kernel metric 256 pref medium \nfe80::/64 dev VM0501-t2 proto kernel metric 256 pref medium \nfe80::/64 dev VM0501-t3 proto kernel metric 256 pref medium \nfe80::/64 dev VM0501-back proto kernel metric 256 pref medium \nfe80::/64 dev VM0502-m proto kernel metric 256 pref medium \nfe80::/64 dev VM0502-t0 proto kernel metric 256 pref medium \nfe80::/64 dev VM0502-t1 proto kernel metric 256 pref medium \nfe80::/64 dev VM0502-t2 proto kernel metric 256 pref medium \nfe80::/64 dev VM0502-t3 proto kernel metric 256 pref medium \nfe80::/64 dev VM0502-back proto kernel metric 256 pref medium \nfe80::/64 dev VM0503-m proto kernel metric 256 pref medium \nfe80::/64 dev VM0503-t0 proto kernel metric 256 pref medium \nfe80::/64 dev VM0503-t1 proto kernel metric 256 pref medium \nfe80::/64 dev VM0503-t2 proto kernel metric 256 pref medium \nfe80::/64 dev VM0503-t3 proto kernel metric 256 pref medium \nfe80::/64 dev VM0503-back proto kernel metric 256 pref medium \nfe80::/64 dev VM0504-m proto kernel metric 256 pref medium \nfe80::/64 dev VM0504-t0 proto kernel metric 256 pref medium \nfe80::/64 dev VM0504-t1 proto kernel metric 256 pref medium \nfe80::/64 dev VM0504-t2 proto kernel metric 256 pref medium \nfe80::/64 dev VM0504-t3 proto kernel metric 256 pref medium \nfe80::/64 dev VM0504-back proto kernel metric 256 pref medium \nfe80::/64 dev VM0505-m proto kernel metric 256 pref medium \nfe80::/64 dev VM0505-t0 proto kernel metric 256 pref medium \nfe80::/64 dev VM0505-t1 proto kernel metric 256 pref medium \nfe80::/64 dev VM0505-t2 proto kernel metric 256 pref medium \nfe80::/64 dev VM0505-t3 proto kernel metric 256 pref medium \nfe80::/64 dev VM0505-back proto kernel metric 256 pref medium \nfe80::/64 dev VM0506-m proto kernel metric 256 pref medium \nfe80::/64 dev VM0506-t0 proto kernel metric 256 pref medium \nfe80::/64 dev VM0506-t1 proto kernel metric 256 pref medium \nfe80::/64 dev VM0506-t2 proto kernel metric 256 pref medium \nfe80::/64 dev VM0506-t3 proto kernel metric 256 pref medium \nfe80::/64 dev VM0506-back proto kernel metric 256 pref medium \nfe80::/64 dev VM0507-m proto kernel metric 256 pref medium \nfe80::/64 dev VM0507-t0 proto kernel metric 256 pref medium \nfe80::/64 dev VM0507-t1 proto kernel metric 256 pref medium \nfe80::/64 dev VM0507-t2 proto kernel metric 256 pref medium \nfe80::/64 dev VM0507-t3 proto kernel metric 256 pref medium \nfe80::/64 dev VM0507-back proto kernel metric 256 pref medium \nfe80::/64 dev VM0508-m proto kernel metric 256 pref medium \nfe80::/64 dev VM0508-t0 proto kernel metric 256 pref medium \nfe80::/64 dev VM0508-t1 proto kernel metric 256 pref medium \nfe80::/64 dev VM0508-t2 proto kernel metric 256 pref medium \nfe80::/64 dev VM0508-t3 proto kernel metric 256 pref medium \nfe80::/64 dev VM0508-back proto kernel metric 256 pref medium \nfe80::/64 dev VM0509-m proto kernel metric 256 pref medium \nfe80::/64 dev VM0509-t0 proto kernel metric 256 pref medium \nfe80::/64 dev VM0509-t1 proto kernel metric 256 pref medium \nfe80::/64 dev VM0509-t2 proto kernel metric 256 pref medium \nfe80::/64 dev VM0509-t3 proto kernel metric 256 pref medium \nfe80::/64 dev VM0509-back proto kernel metric 256 pref medium \nfe80::/64 dev VM0510-m proto kernel metric 256 pref medium \nfe80::/64 dev VM0510-t0 proto kernel metric 256 pref medium \nfe80::/64 dev VM0510-t1 proto kernel metric 256 pref medium \nfe80::/64 dev VM0510-t2 proto kernel metric 256 pref medium \nfe80::/64 dev VM0510-t3 proto kernel metric 256 pref medium \nfe80::/64 dev VM0510-back proto kernel metric 256 pref medium \nfe80::/64 dev VM0511-m proto kernel metric 256 pref medium \nfe80::/64 dev VM0511-t0 proto kernel metric 256 pref medium \nfe80::/64 dev VM0511-t1 proto kernel metric 256 pref medium \nfe80::/64 dev VM0511-t2 proto kernel metric 256 pref medium \nfe80::/64 dev VM0511-t3 proto kernel metric 256 pref medium \nfe80::/64 dev VM0511-back proto kernel metric 256 pref medium \nfe80::/64 dev VM0512-m proto kernel metric 256 pref medium \nfe80::/64 dev VM0512-t0 proto kernel metric 256 pref medium \nfe80::/64 dev VM0512-t1 proto kernel metric 256 pref medium \nfe80::/64 dev VM0512-t2 proto kernel metric 256 pref medium \nfe80::/64 dev VM0512-t3 proto kernel metric 256 pref medium \nfe80::/64 dev VM0512-back proto kernel metric 256 pref medium \nfe80::/64 dev VM0513-m proto kernel metric 256 pref medium \nfe80::/64 dev VM0513-t0 proto kernel metric 256 pref medium \nfe80::/64 dev VM0513-t1 proto kernel metric 256 pref medium \nfe80::/64 dev VM0513-t2 proto kernel metric 256 pref medium \nfe80::/64 dev VM0513-t3 proto kernel metric 256 pref medium \nfe80::/64 dev VM0513-back proto kernel metric 256 pref medium \nfe80::/64 dev VM0514-m proto kernel metric 256 pref medium \nfe80::/64 dev VM0514-t0 proto kernel metric 256 pref medium \nfe80::/64 dev VM0514-t1 proto kernel metric 256 pref medium \nfe80::/64 dev VM0514-t2 proto kernel metric 256 pref medium \nfe80::/64 dev VM0514-t3 proto kernel metric 256 pref medium \nfe80::/64 dev VM0514-back proto kernel metric 256 pref medium \nfe80::/64 dev VM0515-m proto kernel metric 256 pref medium \nfe80::/64 dev VM0515-t0 proto kernel metric 256 pref medium \nfe80::/64 dev VM0515-t1 proto kernel metric 256 pref medium \nfe80::/64 dev VM0515-t2 proto kernel metric 256 pref medium \nfe80::/64 dev VM0515-t3 proto kernel metric 256 pref medium \nfe80::/64 dev VM0515-back proto kernel metric 256 pref medium \nfe80::/64 dev eth3.1940 proto kernel metric 256 pref medium \nfe80::/64 dev eth3.1941 proto kernel metric 256 pref medium \nfe80::/64 dev eth3.1942 proto kernel metric 256 pref medium \nfe80::/64 dev eth3.1943 proto kernel metric 256 pref medium \nfe80::/64 dev eth3.1944 proto kernel metric 256 pref medium \nfe80::/64 dev eth3.1945 proto kernel metric 256 pref medium \nfe80::/64 dev eth3.1946 proto kernel metric 256 pref medium \nfe80::/64 dev eth3.1947 proto kernel metric 256 pref medium \nfe80::/64 dev ptf-p4gw36-m proto kernel metric 256 pref medium \nfe80::/64 dev inje-p4gw36-11 proto kernel metric 256 pref medium \nfe80::/64 dev inje-p4gw36-10 proto kernel metric 256 pref medium \nfe80::/64 dev inje-p4gw36-9 proto kernel metric 256 pref medium \nfe80::/64 dev inje-p4gw36-8 proto kernel metric 256 pref medium \nfe80::/64 dev br-b-p4gw36 proto kernel metric 256 pref medium \nfe80::/64 dev ptf-p4gw36-b proto kernel metric 256 pref medium \nfe80::/64 dev veth1ae60d4 proto kernel metric 256 pref medium \nfe80::/64 dev vethd059654 proto kernel metric 256 pref medium \nfe80::/64 dev veth191c7a8 proto kernel metric 256 pref medium \ndefault via fdbd:dcfd:0:14::1 dev eth0 metric 1024 pref medium \n")
	listRespV6RoutesInfo := parseIpRouteInfo(v6Out)
	fmt.Printf("len(res): %d\n", len(listRespV6RoutesInfo))
	fmt.Printf("listRespV6RoutesInfo: %+v\n\n", listRespV6RoutesInfo)
}

type BGPEVPNRoute struct {
	// Type    BGPEVPNRouteType
	Prefix  string
	VNI     uint32
	Nexthop string
	Rmac    string
	ASPath  [][]uint32
	Mac     string
	L2VNI   uint32
}

const ExpendAsSet = false

// const ExpendAsSet = true

const (
	AsSetLeftSep     string = "{"
	AsSetRightSep    string = "}"
	AsSetInternalSep string = " "
	AsPathSep        string = ","
)

func formatUploadAsPath(asPath [][]uint32) string {
	res := ""
	var lenAs, lenSubAs int = len(asPath), 0
	for i := 0; i < lenAs; i++ {
		lenSubAs = len(asPath[i])
		if !ExpendAsSet && lenSubAs > 1 {
			res += AsSetLeftSep
		}
		for j := 0; j < lenSubAs; j++ {
			res += strconv.Itoa(int(asPath[i][j]))
			if j < lenSubAs-1 {
				res += AsSetInternalSep
			}
		}
		if !ExpendAsSet && lenSubAs > 1 {
			res += AsSetRightSep
		}
		if i < lenAs-1 {
			res += AsPathSep
		}
	}
	return res
}

type GetRoutesResp struct {
	ErrCode   string           `json:"errCode"`
	ErrMsg    string           `json:"errMsg"`
	Success   bool             `json:"success"`
	Data      []RespRoutesInfo `json:"data"`
	RequestID string           `json:"requestID"`
}

func HexDumpBytes(b []byte) string {
	dumpStr := ""
	for i := 0; i < len(b); i++ {
		if i%16 == 0 {
			dumpStr += fmt.Sprintf("\n%.4x  ", i)
		}
		dumpStr += fmt.Sprintf(" %.2x", b[i])
	}

	return dumpStr
}

func IsIpv4UnicastAfi(afiSafis string) bool {
	return strings.Contains(afiSafis, "AFI_IP_SAFI_UNICAST")
}

type ControlerAPIConf struct {
	APIDomain                string
	Queryparams              map[string]string
	APIheaders               map[string]string
	PrependASN               string
	AlwaysFullUpdate         bool
	FullUpdateAPIAction      string
	FullUpdateRetrytimes     uint
	UpperLimitRetryTimes     uint
	FullUpdateTimeout        uint
	FullUpdateInterval       uint
	TotalBurstSize           uint
	TotalConcurrent          uint
	TotalRate                uint
	TotalInterval            uint
	DCGWBurstSize            uint
	DCGWRate                 uint
	DCGWInterval             uint
	Resolution               uint
	Maxbacklog               uint
	APImerge                 []string
	GCDuration               uint
	MaxIdleTime              uint
	ElectionKey              string
	Name                     string
	GetVNIFromEtcd           bool
	DCGWRouteLimit           uint
	WaitSessReady            bool
	WaitSessReadyWithTimeout uint
	WaitSessReadyExclusion   []string
	WorkWaitSessReady        bool
	WorkWaitSessReadyTimeout uint
	EtcdSyncTimeout          uint
	RetryInterval            uint
	EtcdReWatchTimes         uint
	EtcdReWatchDelay         uint
	SkipElection             bool
	// TopAuth                  topAuthConf
	SchedAlg              uint
	EnBgpSessDiscWithdraw bool
	ErrCodeActions        map[string][]string
}

type RouteSyncConf struct {
	Controlerapi ControlerAPIConf
}

func readYamlConfTest(confpath string) map[string]string {
	fmt.Printf("NewRouteSyncConfFromFile with %v", confpath)
	var conf RouteSyncConf
	ErrCodeActionMap := make(map[string]string)
	ba, err := ioutil.ReadFile(confpath)
	if err != nil {
		fmt.Printf("routesync failed to init from file %v: %v", confpath, err)
		return nil
	}
	if err = yaml.Unmarshal(ba, &conf); err != nil {
		fmt.Printf("routesync failed to init from file %v: %v", confpath, err)
		return nil
	}

	fmt.Printf("RouteSyncConf %#v", conf)
	fmt.Printf("NewRouteSyncConfFromFile done")

	for action, errCodes := range conf.Controlerapi.ErrCodeActions {
		for _, errCode := range errCodes {
			ErrCodeActionMap[errCode] = action
		}
	}
	fmt.Printf("\n\n\n===print conf.Controlerapi.ErrCodeActions map: %v\n\n", ErrCodeActionMap)

	return ErrCodeActionMap
}

var RetryFewTimesIgnoreStr = "retryFewTimesIgnore"
var RetryUpperLimitTimesEndStr = "retryUpperLimitTimesEnd"
var RetryFewTimesIgnoreErr = errors.New(RetryFewTimesIgnoreStr)
var RetryUpperLimitTimesEndErr = errors.New(RetryUpperLimitTimesEndStr)

type vegaRespErr struct {
	CodeN   int    `json:"CodeN"`
	Code    string `json:"Code"`
	Message string `json:"Message"`
}

type vegaResponseMetadata struct {
	RequestId string      `json:"RequestId"`
	Action    string      `json:"Action"`
	Version   string      `json:"Version"`
	Service   string      `json:"Service"`
	Region    string      `json:"Region"`
	Error     vegaRespErr `json:"Error"`
}

type vegaRespBody struct {
	ResponseMetadata vegaResponseMetadata `json:"ResponseMetadata"`
}

func prsRespErrCodeToErr(resp *http.Response, ErrCodeActionMap map[string]string) error {
	if resp == nil || resp.ContentLength == 0 || resp.Body == nil || resp.Body == http.NoBody {
		return nil
	}

	bodyBytes, err := io.ReadAll(resp.Body)
	if err != nil {
		return nil
	}
	if err := resp.Body.Close(); err != nil {
		return nil
	}

	// reset resp.Body as it can only be read once
	resp.Body = io.NopCloser(bytes.NewBuffer(bodyBytes))

	var vegaRespBody vegaRespBody
	if err := json.NewDecoder(bytes.NewBuffer(bodyBytes)).Decode(&vegaRespBody); err != nil {
		return nil
	}

	//fmt.Printf("\n===DEBUG=== parse resp body success, body: %+v\n", vegaRespBody)
	//fmt.Printf("\n===DEBUG=== vega error Code: '%s'\n", vegaRespBody.ResponseMetadata.Error.Code)

	if _, existed := ErrCodeActionMap[vegaRespBody.ResponseMetadata.Error.Code]; existed {
		return errors.New(vegaRespBody.ResponseMetadata.Error.Code)
	}

	return nil
}

func parseHttpRespRetErrAction(bodyStr string, ErrCodeActionMap map[string]string) {
	b := []byte(bodyStr)
	resp := &http.Response{
		ContentLength: int64(len(bodyStr)),
		Body:          io.NopCloser(bytes.NewBuffer(b)),
	}
	err := prsRespErrCodeToErr(resp, ErrCodeActionMap)
	if err == nil {
		fmt.Printf("prsRespErrCodeToErr: %s\n", "<nil>")
		return
	}
	if action, existed := ErrCodeActionMap[err.Error()]; existed {
		fmt.Printf("prsRespErrCodeToErr: %s, \t action: %s\n", err.Error(), action)
	} else {
		fmt.Printf("prsRespErrCodeToErr: %s, \t action: Not Found\n", err.Error())
	}
}

func parseHttpRespRetErrActionTest() {
	ErrCodeActionMap := readYamlConfTest("/Users/haoleeson/go/src/routesyncd_dev/files/routesyncd.yml")

	errCode400Body := "{\"ResponseMetadata\":{\"RequestId\":\"20250114172117D4C2D54F656F458B2FD9\",\"Action\":\"InnerPostReportDirectConnectGatewayBgpRoutes\",\"Version\":\"2020-04-01\",\"Service\":\"directconnect\",\"Region\":\"cn-beijing\",\"Error\":{\"Code\":\"InvalidDirectConnectGatewayBgpRoute.InvalidStatus\",\"Message\":\"The specified direct connect gateway BGP route is not in the correct status for the request.\"}}}"
	errCode404Body := "{\"ResponseMetadata\":{\"RequestId\":\"2025011015455370F0A5E9EB56F83D77CE\",\"Action\":\"InnerPostReportDirectConnectGatewayBgpRoutes\",\"Version\":\"2020-04-01\",\"Service\":\"directconnect\",\"Region\":\"cn-chongqing-sdv\",\"Error\":{\"Code\":\"InvalidDirectConnectGateway.NotFound\",\"Message\":\"The specified direct connect gateway does not exist.\"}}}"
	errCode429Body := "{\"ResponseMetadata\":{\"RequestId\":\"20250114173332859B189089A6E268A0AC\",\"Action\":\"InnerPostReportDirectConnectGatewayBgpRoutes\",\"Version\":\"2020-04-01\",\"Service\":\"directconnect\",\"Region\":\"cn-beijing\",\"Error\":{\"Code\":\"RateLimited\",\"Message\":\"Too many requests, please try again later.\"}}}"
	errCode500Body := "{\"ResponseMetadata\":{\"RequestId\":\"20250114172028B0DBE316BDA30BA075C9\",\"Action\":\"InnerPostReportDirectConnectGatewayBgpRoutes\",\"Version\":\"2020-04-01\",\"Service\":\"directconnect\",\"Region\":\"cn-beijing\",\"Error\":{\"Code\":\"InternalError\",\"Message\":\"An internal error has occurred.\"}}}"
	errCode502Body := "{\"ResponseMetadata\":{\"RequestId\":\"202501142241140E89D985E788EE631F20\",\"Action\":\"InnerPostReportDirectConnectGatewayBgpRoutes\",\"Version\":\"2020-04-01\",\"Service\":\"directconnect\",\"Region\":\"cn-shanghai\",\"Error\":{\"CodeN\":100023,\"Code\":\"InternalServiceError\",\"Message\":\"Service has some internal Error. Pls Contact With Admin.\"}}}"
	errCode503Body := "{\"ResponseMetadata\":{\"RequestId\":\"2025010715501857EAE6EDD64737B06064\",\"Action\":\"InnerPostReportDirectConnectGatewayBgpRoutes\",\"Version\":\"2020-04-01\",\"Service\":\"directconnect\",\"Region\":\"cn-chengdu-sdv\",\"Error\":{\"CodeN\":100035,\"Code\":\"ServiceOverloadTemp\",\"Message\":\"Service is busy, please try again later.\"}}}"
	errCode504Body := "{\"ResponseMetadata\":{\"RequestId\":\"202501141721139A163A1B2A9A018ABC0A\",\"Action\":\"InnerPostReportDirectConnectGatewayBgpRoutes\",\"Version\":\"2020-04-01\",\"Service\":\"directconnect\",\"Region\":\"cn-beijing\",\"Error\":{\"CodeN\":100016,\"Code\":\"InternalServiceTimeout\",\"Message\":\"Internal Service is timeout. Pls Contact With Admin\"}}}"

	noErrCodeBody := "{\"ResponseMetadata\":{\"RequestId\":\"202501141721139A163A1B2A9A018ABC0A\",\"Action\":\"InnerPostReportDirectConnectGatewayBgpRoutes\",\"Version\":\"2020-04-01\",\"Service\":\"directconnect\",\"Region\":\"cn-beijing\"}}"
	noCodeBody := "{\"ResponseMetadata\":{\"RequestId\":\"202501141721139A163A1B2A9A018ABC0A\",\"Action\":\"InnerPostReportDirectConnectGatewayBgpRoutes\"}}"

	parseHttpRespRetErrAction(errCode400Body, ErrCodeActionMap)
	parseHttpRespRetErrAction(errCode404Body, ErrCodeActionMap)
	parseHttpRespRetErrAction(errCode429Body, ErrCodeActionMap)
	parseHttpRespRetErrAction(errCode500Body, ErrCodeActionMap)
	parseHttpRespRetErrAction(errCode502Body, ErrCodeActionMap)
	parseHttpRespRetErrAction(errCode503Body, ErrCodeActionMap)
	parseHttpRespRetErrAction(errCode504Body, ErrCodeActionMap)
	parseHttpRespRetErrAction(noErrCodeBody, ErrCodeActionMap)
	parseHttpRespRetErrAction(noCodeBody, ErrCodeActionMap)
}

func main() {
	fmt.Print("hello world!")
	parseHttpRespRetErrActionTest()
}
