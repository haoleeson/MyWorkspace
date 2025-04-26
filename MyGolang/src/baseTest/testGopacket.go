package main

import (
	"encoding/binary"
	"fmt"
	"log"
	"net"
	"strings"

	"github.com/google/gopacket"
	"github.com/google/gopacket/layers"
	"github.com/google/gopacket/pcap"
)

const (
	DefOuterSMac    = "aa:bb:cc:dd:ee:ff"
	DefOuterDMac    = "00:01:00:01:01:00"
	DefInnerSMac    = "00:03:00:03:03:03"
	DefInnerDMac    = "00:01:00:01:01:00"
	DefIpv4Addr     = "0.0.0.0"
	DefIpv6Addr     = "::"
	Ipv4Separator   = "."
	VxLANPort       = uint16(4789)
	DefPort         = uint16(0)
	DefIPId         = uint16(1)
	DefTTL          = uint8(64)
	DefTos          = uint8(0)
	DefEtherHdrLen  = uint16(14)
	DefIPv4HdrLen   = uint16(20)
	DefIPv6HdrLen   = uint16(40)
	DefUDPHdrLen    = uint16(8)
	DefVxLANHdrLen  = uint16(8)
	DefFlowLabel    = uint32(1)
	DefOAMVxLANFlag = byte(0x0D)
	UDPProtoCode    = byte(0x11)
	TCPProtoCode    = byte(0x06)
)

type IPType uint

const (
	IPTypeUNKNOWN IPType = iota
	IPType4
	IPType6
)

/**
 * MyVxLAN :
 * @Desc: Support OAM Flag, VxLAN-GPE Header, RFC7348
 * 0                   1                   2                   3
 * 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |R|R|Ver|I|P|B|O|       Reserved                |Next Protocol  |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                VxLAN Network Identifier (VNI) |   Reserved    |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
type MyVxLAN struct {
	layers.VXLAN
	Proto byte
}

func NewMyVxLAN(vni uint32, proto_optional ...byte) *MyVxLAN {
	pc := UDPProtoCode
	if len(proto_optional) > 0 {
		pc = proto_optional[0]
	}
	return &MyVxLAN{
		layers.VXLAN{
			VNI: vni,
		},
		pc,
	}
}

func (vx *MyVxLAN) SerializeTo(b gopacket.SerializeBuffer, opts gopacket.SerializeOptions) error {
	bytes, err := b.PrependBytes(8)
	if err != nil {
		return err
	}
	i := 0

	// FLAGs
	bytes[0] = DefOAMVxLANFlag // with VNI, Next Protocol, OAM bit, 0x0D, 00001101
	i += 1

	// Reserved
	i += 2

	// Next Protocol
	bytes[i] = vx.Proto
	i += 1

	// VNI (write uint32 value(4 Bytes) into 3 Bytes buffer)
	binary.BigEndian.PutUint32(bytes[i:], vx.VNI<<8)

	return nil
}

func PrintBytesHexDump(b []byte) {
	for i := 0; i < len(b); i++ {
		if i%16 == 0 {
			fmt.Printf("\n%.4x   ", i)
		}
		fmt.Printf("%.2x ", b[i])
	}
	fmt.Println()
}

func checkAndParseIp(ipStr string) (net.IP, IPType, error) {
	var ipType IPType
	var netIP net.IP

	if len(ipStr) == 0 {
		return nil, IPTypeUNKNOWN, fmt.Errorf("invalid empty ip param")
	}

	netIP = net.ParseIP(ipStr)
	if strings.Contains(ipStr, Ipv4Separator) {
		ipType = IPType4
		if netIP == nil || netIP.To4() == nil {
			return nil, IPTypeUNKNOWN, fmt.Errorf("invalid ip param '%s'", ipStr)
		}
	} else {
		ipType = IPType6
		if netIP == nil || netIP.To16() == nil {
			return nil, IPTypeUNKNOWN, fmt.Errorf("invalid ip param '%s'", ipStr)
		}
	}

	return netIP, ipType, nil
}

type PktGenerator struct {
	OuterSMac  string `json:"outer_smac"`
	OuterDMac  string `json:"outer_dmac"`
	OuterSIP   string `json:"outer_sip"`
	OuterDIP   string `json:"outer_dip"`
	OuterDscp  uint8  `json:"outer_dscp"`
	OuterSPort uint16 `json:"outer_sport"`
	OuterDPort uint16 `json:"outer_dport"`
	Vni        uint32 `json:"vni"`
	InnerSMac  string `json:"inner_smac"`
	InnerDMac  string `json:"inner_dmac"`
	InnerSIP   string `json:"inner_sip"`
	InnerDIP   string `json:"inner_dip"`
	InnerDscp  uint8  `json:"inner_dscp"`
	InnerSPort uint16 `json:"inner_sport"`
	InnerDPort uint16 `json:"inner_dport"`
}

func NewPktGenerator() *PktGenerator {
	return &PktGenerator{
		OuterSMac:  DefOuterSMac,
		OuterDMac:  DefOuterDMac,
		OuterSIP:   DefIpv4Addr,
		OuterDIP:   DefIpv4Addr,
		OuterDscp:  DefTos,
		OuterSPort: DefPort,
		OuterDPort: VxLANPort,
		Vni:        0,
		InnerSMac:  DefInnerSMac,
		InnerDMac:  DefInnerDMac,
		InnerSIP:   DefIpv4Addr,
		InnerDIP:   DefIpv4Addr,
		InnerDscp:  DefTos,
		InnerSPort: DefPort,
		InnerDPort: DefPort,
	}
}

func (param *PktGenerator) GenVxLanUdpPkt(payload []byte) (gopacket.SerializeBuffer, error) {
	var totalLen uint16 = 0
	var err error

	var innerSrcIp, innerDstIp, outerSrcIp, outerDstIp net.IP
	var innerIPType, outerIPType, innerSrcIpType, innerDstIpType, outerSrcIpType, outerDstIpType IPType
	var innerIPv4, outerIPv4 *layers.IPv4 = nil, nil
	var innerIPv6, outerIPv6 *layers.IPv6 = nil, nil
	var innerEthType, outerEthType layers.EthernetType

	// check and parse ip addr
	if innerSrcIp, innerSrcIpType, err = checkAndParseIp(param.InnerSIP); err != nil {
		return nil, err
	}
	if innerDstIp, innerDstIpType, err = checkAndParseIp(param.InnerDIP); err != nil {
		return nil, err
	}
	if outerSrcIp, outerSrcIpType, err = checkAndParseIp(param.OuterSIP); err != nil {
		return nil, err
	}
	if outerDstIp, outerDstIpType, err = checkAndParseIp(param.OuterDIP); err != nil {
		return nil, err
	}
	if innerSrcIpType != innerDstIpType {
		return nil, fmt.Errorf("inner dip(%s) and sip(%s) are not the same ip type", param.InnerDIP, param.InnerSIP)
	}
	if outerSrcIpType != outerDstIpType {
		return nil, fmt.Errorf("outer dip(%s) and sip(%s) are not the same ip type", param.OuterDIP, param.OuterSIP)
	}

	innerIPType, outerIPType = innerSrcIpType, outerSrcIpType

	switch innerIPType {
	case IPType4:
		innerEthType = layers.EthernetTypeIPv4
	case IPType6:
		innerEthType = layers.EthernetTypeIPv6
	}

	switch outerIPType {
	case IPType4:
		outerEthType = layers.EthernetTypeIPv4
	case IPType6:
		outerEthType = layers.EthernetTypeIPv6
	}

	// Inner Packet: Ether(smac, dmac) / IP(sip, dip, dscp) / UDP(sport, dport) / Payload

	// Inner payload
	innerPayload := gopacket.Payload(payload)
	totalLen += uint16(len(innerPayload))

	// Inner UDP
	totalLen += DefUDPHdrLen
	innerUDP := &layers.UDP{
		SrcPort: layers.UDPPort(param.InnerSPort),
		DstPort: layers.UDPPort(param.InnerDPort),
		Length:  totalLen,
	}

	// Inner IP
	switch innerIPType {
	case IPType4:
		totalLen += DefIPv4HdrLen
		innerIPv4 = &layers.IPv4{
			Version:  4,
			IHL:      5,
			TOS:      param.InnerDscp << 2,
			Length:   totalLen,
			Id:       DefIPId,
			Flags:    layers.IPv4DontFragment,
			TTL:      DefTTL,
			Protocol: layers.IPProtocolUDP,
			SrcIP:    innerSrcIp,
			DstIP:    innerDstIp,
		}
		// set checksum layer
		innerUDP.SetNetworkLayerForChecksum(innerIPv4)
	case IPType6:
		totalLen += DefIPv6HdrLen
		innerIPv6 = &layers.IPv6{
			Version:      6,
			TrafficClass: param.InnerDscp << 2,
			FlowLabel:    DefFlowLabel,
			Length:       totalLen,
			NextHeader:   layers.IPProtocolUDP,
			HopLimit:     DefTTL,
			SrcIP:        innerSrcIp,
			DstIP:        innerDstIp,
		}
		// set checksum layer
		innerUDP.SetNetworkLayerForChecksum(innerIPv6)
	}

	// Inner Ether
	totalLen += DefEtherHdrLen
	innerEth := &layers.Ethernet{
		EthernetType: innerEthType,
	}
	innerEth.SrcMAC, err = net.ParseMAC(param.InnerSMac)
	if err != nil {
		fmt.Printf("Invalid inner ether source MAC '%s'\n", param.InnerSMac)
	}
	innerEth.DstMAC, err = net.ParseMAC(param.InnerDMac)
	if err != nil {
		fmt.Printf("Invalid inner ether destination MAC '%s'\n", param.InnerDMac)
	}

	// Outer Packet: Ether(smac, dmac) / IP(sip, dip, dscp) / UDP(sport, dport) / VxLAN(flags, vni)

	// VxLAN
	totalLen += DefVxLANHdrLen
	vxLan := NewMyVxLAN(param.Vni)

	// Outer UDP
	totalLen += DefUDPHdrLen
	outerUDP := &layers.UDP{
		SrcPort: layers.UDPPort(param.OuterSPort),
		DstPort: layers.UDPPort(param.OuterDPort),
		Length:  totalLen,
	}

	// Outer IP
	switch outerIPType {
	case IPType4:
		totalLen += DefIPv4HdrLen
		outerIPv4 = &layers.IPv4{
			Version:  4,
			IHL:      5,
			TOS:      param.OuterDscp << 2,
			Length:   totalLen,
			Id:       DefIPId,
			Flags:    layers.IPv4DontFragment,
			TTL:      DefTTL,
			Protocol: layers.IPProtocolUDP,
			SrcIP:    outerSrcIp,
			DstIP:    outerDstIp,
		}
		// set checksum layer
		outerUDP.SetNetworkLayerForChecksum(outerIPv4)
	case IPType6:
		totalLen += DefIPv6HdrLen
		outerIPv6 = &layers.IPv6{
			Version:      6,
			TrafficClass: param.OuterDscp << 2,
			FlowLabel:    DefFlowLabel,
			Length:       totalLen,
			NextHeader:   layers.IPProtocolUDP,
			HopLimit:     DefTTL,
			SrcIP:        outerSrcIp,
			DstIP:        outerDstIp,
		}
		// set checksum layer
		outerUDP.SetNetworkLayerForChecksum(outerIPv6)
	}

	// Outer Ether
	totalLen += DefEtherHdrLen
	outerEth := &layers.Ethernet{
		EthernetType: outerEthType,
	}
	outerEth.SrcMAC, err = net.ParseMAC(param.OuterSMac)
	if err != nil {
		fmt.Printf("Invalid outer ether source MAC '%s'\n", param.OuterSMac)
	}
	outerEth.DstMAC, err = net.ParseMAC(param.OuterDMac)
	if err != nil {
		fmt.Printf("Invalid outer ether destination MAC '%s'\n", param.OuterDMac)
	}

	// Serialize Buffer
	buf := gopacket.NewSerializeBuffer()
	opts := gopacket.SerializeOptions{FixLengths: true, ComputeChecksums: true}
	switch innerIPType | outerIPType<<2 {
	case (IPType4 | IPType4<<2):
		// 4 in 4
		err = gopacket.SerializeLayers(buf, opts, outerEth, outerIPv4, outerUDP, vxLan,
			innerEth, innerIPv4, innerUDP, innerPayload)
	case (IPType6 | IPType4<<2):
		// 6 in 4
		err = gopacket.SerializeLayers(buf, opts, outerEth, outerIPv4, outerUDP, vxLan,
			innerEth, innerIPv6, innerUDP, innerPayload)
	case (IPType4 | IPType6<<2):
		// 4 in 6
		err = gopacket.SerializeLayers(buf, opts, outerEth, outerIPv6, outerUDP, vxLan,
			innerEth, innerIPv4, innerUDP, innerPayload)
	case (IPType6 | IPType6<<2):
		// 6 in 6
		err = gopacket.SerializeLayers(buf, opts, outerEth, outerIPv6, outerUDP, vxLan,
			innerEth, innerIPv6, innerUDP, innerPayload)
	}
	if err != nil {
		fmt.Printf("Serialize layers failed, error: '%s'\n", err.Error())
	}
	return buf, nil
}

func SendPkt(port string, mtu int32, buf gopacket.SerializeBuffer) {
	// Open Network Interface
	handle, err := pcap.OpenLive(port, mtu, true, pcap.BlockForever)
	if err != nil {
		log.Fatal(err)
	}
	defer handle.Close()

	// Send Pkt
	err = handle.WritePacketData(buf.Bytes())
	if err != nil {
		log.Fatal(err)
	}

	log.Println("VxLAN packet sent successfully")
}

func main() {
	fmt.Println("hello world")

	// payload := []byte("This is the inner payload")
	// payload := []byte{0xAB, 0xCD, 0xEF}
	payload := []byte{}

	pg1 := NewPktGenerator()
	pg1.OuterSMac = "08:c0:eb:64:e5:ec"
	pg1.OuterDMac = "10:70:fd:c6:04:c2"
	pg1.OuterSIP = "10.11.115.104"
	pg1.OuterDIP = "10.11.114.32"
	pg1.OuterDscp = 56
	pg1.OuterSPort = 1234
	pg1.Vni = 500
	pg1.InnerSMac = "00:03:00:03:03:03"
	pg1.InnerDMac = "00:01:00:01:01:00"
	pg1.InnerSIP = "10.0.1.2"
	pg1.InnerDIP = "172.16.2.2"
	pg1.InnerDscp = 0
	pg1.InnerSPort = 1024
	pg1.InnerDPort = 80
	pktBuf1, err := pg1.GenVxLanUdpPkt(payload)
	if err != nil {
		fmt.Printf("GenVxLanUdpPkt Error: '%s'\n", err.Error())
	}
	PrintBytesHexDump(pktBuf1.Bytes())

	pg2 := NewPktGenerator()
	pg2.OuterSMac = "08:c0:eb:64:e5:ec"
	pg2.OuterDMac = "10:70:fd:c6:04:c2"
	pg2.OuterSIP = "10:11::115:104"
	pg2.OuterDIP = "10:11::114:32"
	pg2.OuterDscp = 56
	pg2.OuterSPort = 1234
	pg2.Vni = 500
	pg2.InnerSMac = "00:03:00:03:03:03"
	pg2.InnerDMac = "00:01:00:01:01:00"
	pg2.InnerSIP = "10:0::1:2"
	pg2.InnerDIP = "172:16::2:2"
	pg2.InnerDscp = 0
	pg2.InnerSPort = 1024
	pg2.InnerDPort = 80
	pktBuf2, err := pg2.GenVxLanUdpPkt(payload)
	if err != nil {
		fmt.Printf("GenVxLanUdpPkt Error: '%s'\n", err.Error())
	}
	PrintBytesHexDump(pktBuf2.Bytes())

	fmt.Println("start send pkt...")
	// SendPkt("eth0", 1500, pktBuf1)
	fmt.Println("Send pkt Finish")
}
