#!/opt/homebrew/bin/python3

import ast
# import sys
# import paramiko
import ipaddress
import json
import math
import string
import re
import os
import logging
import ipaddress
import random
import struct
from typing import List



logger = logging.getLogger(__name__)


# 怀来 lab 群布线请求
def print_hl_lab_connect():
    for i in range(0, 16):
        # print("HBHL_D3_311-02-04-39.S0-124-89-LAB HGE1/0/%d <--> Dut2 Ethernet%d" % (33 + i, 1 + i))
        # print("HBHL_D3_311-02-03-39 HGE1/0/%d <--> HBHL_D3_311-02-05-44 Ethernet%d" % (33 + i, 33 + i))
        print("HBHLJD_D1_405-02-15-05 HGE1/0/%d <--> HBHLJD_D1_405-02-09-38 Ethernet%d" % (33 + i, 1 + i))


# H3C Vlan 配置
def print_h3c_add_vlan():
    baseVlan = 1900
    basePort = 1
    size = 64
    for i in range(0, size):
        print("interface HundredGigE 1/0/%d" % (basePort + i))
        print("port trunk pvid vlan %d" % (baseVlan + i))
        print("port trunk permit vlan %d" % (baseVlan + i))
        print("no port trunk permit vlan 1")
        print("exit\n")


# sonic-mgmt lab_connection_graph.xml 配置
def print_stronic_mgmt_lab_connection_graph_xml():
    baseVlan = 1932
    basePort = 33
    size = 32

    print("\n\nansible/files/lab_connection_graph.xml :\n")
    baseEth = 33
    for i in range(0, size):
        print("      <DeviceInterfaceLink BandWidth=\"100000\" EndDevice=\"fanout-10-32-124-89-dup\" EndPort=\"HGE1/0/%d\" StartDevice=\"sonic-DUT-5\" StartPort=\"Ethernet%d\"/>" % (basePort + i, baseEth + i))

    print("\n\nansible/files/lab_connection_graph.xml :\n")
    for i in range(0, size):
        print("      <InterfaceVlan mode=\"Access\" portname=\"HGE1/0/%d\" vlanids=\"%d\"/>" % (basePort + i, baseVlan + i))

    print("\n\nansible/files/sonic_lab_links.csv :\n")
    baseSonicEth = 33
    for i in range(0, size):
        print("sonic-DUT-5,Ethernet%d,fanout-10-32-124-89-dup,HGE1/0/%d,100000,%d,Access" % (baseSonicEth + i, basePort + i, baseVlan + i))


# sonic-mgmt debug 添加子接口
def print_stronic_mgmt_add_sub_port_debug():
    for i in range(0, 32):
        # ovs-vsctl add-port br-VM0502-0 eth3.1934
        print("ovs-vsctl add-port br-VM0%d-0 eth3.19%d\n" % (500 + i, 32 + i))


# sonic-mgmt debug 删除子接口
def print_stronic_mgmt_del_sub_port_debug():
    for i in range(0, 32):
        # ovs-vsctl del-port br-VM0527-0 eth3.1939
        print("ovs-vsctl del-port br-VM0%d-0 eth3.19%d\n" % (500 + i, 32 + i))


def print_ipaddress_obj(o):
    print(o.with_prefixlen)


def test_print_ipaddress_obj():
    o = ipaddress.ip_network(u"10.134.11.0/24")
    print_ipaddress_obj(o)


def print_stronic_config_add_vlan():
    for i in range(0, 16):
        print("\"Vlan%d|Ethernet%d\": { " % (i + 100, 2 * i + 1))
        print("    \"tagging_mode\": \"untagged\" ")
        print("}, ")
        print("\"Vlan%d|Ethernet%d\": { " % (i + 100, 2 * i + 2))
        print("    \"tagging_mode\": \"untagged\" ")
        print("}, ")

def gen_rand_ip():
    randomlist = random.sample(range(1, 254), 4)
    rand_ip = "%d.%d.%d.%d" % (randomlist[0], randomlist[1], randomlist[2], randomlist[3])
    return rand_ip


def test_ten2hex(num_list):
    hex_list = []
    for num in num_list:
        hex_list.append(hex(num))
    return hex_list


# def check_syslog():
#     duthost_hostname = 'sonic-DUT-5'
#     test_message = 'Basic Test Message'
#     print('==Debug hostname:%s, test_message:%s' % (duthost_hostname, test_message))
#     print("grep {} /var/log/syslog | grep -v ansible | grep \"{}\"".format(duthost_hostname, test_message))
#     # result = ptfhost.shell("grep {} /var/log/syslog | grep -v ansible | grep \"{}\"".format(duthost_hostname, test_message))["stdout"]
#     result = "<174>Jan  6 12:11:03 sonic-DUT-5 sonic-DUT-5 INFO admin: Basic Test Message"
#     print("result:%s" % result)
#     regex = re.compile('<[0-9]*>[a-zA-Z]*\s*\d{1,2}\s\d{1,2}:\d{1,2}:\d{1,2}\s%s\s%s\sINFO\s.*?%s' % (duthost_hostname, duthost_hostname, test_message))
#     print("regex :%s" % regex)
#     match_result = regex.match(str(result))
#     print("match :%s" % match_result)

#     return match_result is not None


# 截取范围：左闭右开
def str_cut_test():
    str = 'abcdefg'
    print("str = %s\n" % str)
 
    print("str[1] = ", str[1])
    print("str[-1] = ", str[-1])
    print("str[-2] = ", str[-2])
    
    print("")

    print("str[1:] = ", str[1:])
    print("str[2:] = ", str[2:])
    print("str[:-1] = ", str[:-1])
    print("str[:-2] = ", str[:-2])
    print("str[-1:] = ", str[-1:])
    print("str[-2:] = ", str[-2:])
    print("str[::-1] = ", str[::-1])
    print("str[::-2] = ", str[::-2])
    print("str[:] = ", str[:])


def compare_str(str1, str2) -> bool:
    return bool(str1 == str2)


def empty_str_test():
    str1 = None
    str2 = ""
    str3 = str(None)

    print("is str1 empty: ", not str1)
    print("is str2 empty: ", not str2)
    print("is str3 empty: ", not str3)

    print("type of str3", type(str3))

    print("compare str1 and str2: ", str1 == str2)
    print("compare str1 and str3: ", str1 == str3)
    print("compare str2 and str3: ", str2 == str3)


def get_call_trace(n: int) -> list:
    chain_list = []
    if n <= 0:
        return list(reversed(chain_list))
    for i in range(n):
        chain_list.append("L_%s" % str(i + 1))
    list1 = list(chain_list)
    return list1


def get_call_trace_str(n: int, depth=4):
    traces = get_call_trace(n)
    print("debug traces:", traces)
    # if len(traces) > 1:
    #     traces = traces[:-2]
    # print("debug traces:", traces)

    if len(traces) > depth:
        return "-->".join(traces[-depth:])
    return "-->".join(traces)


def printRealPath():
    WORK_DIR = os.path.dirname(os.path.dirname(os.path.dirname(os.path.realpath(__file__))))
    print("1. os.path.realpath(__file__) :", os.path.realpath(__file__))
    print("2. os.path.dirname(os.path.realpath(__file__)) :", os.path.dirname(os.path.realpath(__file__)))
    print("3. os.path.dirname(os.path.dirname(os.path.realpath(__file__))) :", os.path.dirname(os.path.dirname(os.path.realpath(__file__))))
    print("4. os.path.dirname(os.path.dirname(os.path.dirname(os.path.realpath(__file__)))) :", os.path.dirname(os.path.dirname(os.path.dirname(os.path.realpath(__file__)))))
    print("WORK_DIR : ", WORK_DIR)


class BaseConfig:
    env = ""


def check_in_list():
    list_1 = ["a", "b", "c"]
    element1 = "a"
    element2 = "d"
    if element1 in list_1:
        print("element: %s is in list" % element1)
    else:
        print("element: %s is not in list" % element1)
    if element2 in list_1:
        print("element: %s is in list" % element2)
    else:
        print("element: %s is not in list" % element2)


def dict_test():
    b_replace = False
    Config_next_version = {"A": '123'}
    dict_next_versions = {"A": "aaa", "B": "bbb", "C": ""}
    for k, v in dict_next_versions.items():
        if not str(v).strip():
            continue
        if not b_replace and k in Config_next_version:
            continue
        Config_next_version[k] = v

    print("Config_next_version:", Config_next_version)


def fix_single_quote_dict_to_double(d: dict) -> dict:
    if not d:
        return {}
    str_json_dat = str(ast.literal_eval(json.dumps(d)))
    fix_dict = json.loads(str_json_dat)
    return fix_dict


def json_load_test(str_json: str):
    d = json.loads(str_json)
    print("d json value: \n%s\n" % json.dumps(d))
    # print("json dumps value: %s" % json.dumps(d))
    # print("json json.dumps(json.dumps(d)) value: %s" % json.dumps(json.dumps(d)))
    dd = fix_single_quote_dict_to_double(d)
    print("dd json value: \n%s\n" % json.dumps(dd))


def dump_string_contains_curly_braces(v: str):
    d = {}
    print("origin value str is:\n%s\n" % v)
    d["it's dump value is:"] = v
    print("result\n%s\n" % json.dumps(d))


def hex2dec(str_hex: str):
    if str_hex.startswith("0x"):
        str_hex = str_hex[2:]
    str_dec = str(int(str_hex.upper(), 16))
    print("0x%s (%s)" % (str_hex, str_dec))


# def reboot_remote_host(host_ip, username, password, timeout=10):
#     client = paramiko.SSHClient()
#     client.set_missing_host_key_policy(paramiko.client.WarningPolicy)
#     client.connect(host_ip, username=username, password=password, timeout=timeout)
#     try:
#         stdin, stdout, stderr = client.exec_command("/sbin/reboot -f > /dev/null 2>&1 &")
#         # .........
#         # some code
#         # .........
#     except Exception as e:
#         print("execute command on remote host(%s) failed, Exception: %s" % (host_ip, str(e)))
#     finally:
#         client.close()


def test_link():
    import itertools
    range1 = range(1, 14 + 1)
    range2 = range(33, 64 + 1)
    for i in itertools.chain(range1, range2):
        print("======", i, "======")
        print("sonic:")
        print("sudo config interface shutdown ethernet%s" % str(i))
        # print("show interfaces status | grep 'ethernet%s '" % str(i))
        print("h3c:")
        print("display interface HundredGigE 1/0/%s brief" % str(i))
        # print("sudo config interface startup ethernet%s" % str(i))
        print("")


def print_lambda_bgp_peer():
    for i in range(0, 32, 1):
        # print("        \"10.0.0.%s\": {" % (2 * i + 65))
        # print("            \"group\": \"A%sT0_4\"" % str(i + 1).zfill(2))
        # print("        },")
        # print("        \"fc00::%s\": {" % str(hex(4 * i + 2))[2:])
        # print("            \"group\": \"A00T2_6\"")
        # print("        },")
        print("        \"fc00::%s\": {" % str(hex(4 * i + 2))[2:])
        print("            \"group\": \"A00T2_6\"")
        print("        },")


def print_lambda_bgp_peer_group():
    for i in range(0, 32, 1):
        print("        \"A%sT0_4\": {" % str(i + 1).zfill(2))
        print("            \"adv_interval\": \"0\",")
        print("            \"remote_as\": \"%s\"," % (64001 + i))
        print("            \"v4_active\": \"true\",")
        print("            \"v4_route_map_in\": \"FROM_A%sT0_4\"," % (str(i + 1).zfill(2)))
        print("            \"v4_route_map_out\": \"TO_A%sT0_4\"" % (str(i + 1).zfill(2)))
        print("        },")


def print_lambda_interface():
    for i in range(0, 40, 1):
        print("        \"ethernet%s|10.0.0.%s/31\": {" % (1 + i, 2 * i + 0))
        print("            \"type\": \"primary\"")
        print("        },")
        print("        \"ethernet%s|fc00::%s/126\": {" % (1 + i, str(hex(4 * i + 1))[2:]))
        print("            \"type\": \"primary\"")
        print("        },")


def print_lambda_route_map():
    for i in range(0, 32, 1):
        print("        \"FROM_A%sT0_4|10\": {" % (str(i + 1).zfill(2)))
        print("            \"action\": \"permit\"")
        print("        },")
        print("        \"TO_A%sT0_4|10\": {" % (str(i + 1).zfill(2)))
        print("            \"action\": \"permit\"")
        print("        },")


def print_lambda_port():
    for i in range(0, 32, 1):
        print("        \"ethernet%s\": {" % (i + 33))
        print("            \"admin_status\": \"up\",")
        print("            \"description\": \"ARISTA%sT2:ethernet1\"," % (i + 1))
        print("            \"fec\": \"rs\",")
        print("            \"mtu\": \"9100\",")
        print("            \"speed\": \"100000\"")
        print("        },")


def re_test():
    output_lines = [ "TRANSCEIVER_INFO|Ethernet38",
                    "TRANSCEIVER_INFO|ethernet40",
                    "TRANSCEIVER_INFO|ethernet45" ]
    result = []
    p = re.compile(r"TRANSCEIVER_INFO\|([E|e]thernet\d+)")
    for line in output_lines:
        print("line: %s" % line)
        m = p.match(line)
        # assert m, "Unexpected line %s" % line
        print(m.group(1))
        result.append(m.group(1))
    return result


def test_startswith():
    list_intfInfo = ["Ethernet1", "ethernet2", "Ethernet3"]
    portList = [port for port in list_intfInfo if port.startswith(('Ethernet', 'ethernet'))]
    print("portList: %s" % ' '.join(portList))


def dict_test2():
    interface_facts = {
        "ethernet48": {
            "prefixlen": 31,
            "index": 47,
            "peer_ip": "10.0.0.95",
            "name": "ethernet48",
            "local_ip": "10.0.0.94"
        },
        "ethernet47": {
            "prefixlen": 31,
            "index": 46,
            "peer_ip": "10.0.0.93",
            "name": "ethernet47",
            "local_ip": "10.0.0.92"
        }
    }
    ethernet_prefix = list(interface_facts.keys())[0][:8] if interface_facts and len(interface_facts) > 0 else "Ethernet"
    print("ethernet_prefix: %s" % ethernet_prefix)


def test_list2():
    keyArr = [u'eth0|fdbd:dcff:0:ff:290:fbff:fe78:e33b/64', u'eth0|10.32.124.41/24']

    # ignore ipv6 mgmt ip
    for keyTmp in keyArr:
        logger.info(keyTmp)
        arr1 = keyTmp.split("|")
        if len(arr1) < 2:
            continue
        keyTmp1 = arr1[1]
        arr2 = keyTmp1.split("/")
        if len(arr2) < 2 or ":" in arr2[0]:
            continue
        return arr2[0]
    return ""


def parse_eth_prefix_from_facts(interface_facts):
    """
    Parse ethernet prefixe from minigraph_facts
    """
    ETH_PREFIX_LEN = 8
    if interface_facts and len(interface_facts) > 0:
        for k in interface_facts.keys():
            if not k.startswith(('Ethernet', 'ethernet')):
                print("skip '", k, "'")
                continue
            return k[:ETH_PREFIX_LEN]
    return "Ethernet"


def test_logging():
    ifaddresses = ["a", "b", "c"]
    logging.error("====DEBUG==== ifaddresses: %s" % ' '.join(ifaddresses))


def test_logger():
    logger = logging.getLogger(__name__)
    logger.setLevel(logging.INFO)
    # handler = logging.handlers.SysLogHandler(address = '/dev/log')
    # logger.addHandler(handler)
    ifaddresses = ["a", "b", "c"]
    logger.error("====DEBUG==== ifaddresses: %s" % ' '.join(ifaddresses))


# helper methods for bgp
def get_local_address(peer):
    print("====DEBUG==== 1. peer:")
    print(peer)
    # Here we suppose use /31 for ipv4
    if ':' in peer:
        ip_tokens = peer.split(':')
    else:
        ip_tokens = peer.split('.')
    print("====DEBUG==== 2. ip_tokens:")
    print(ip_tokens)
    last_token_int = int(ip_tokens[-1])
    print("====DEBUG==== 3. last_token_int:")
    print(last_token_int)
    if last_token_int % 2 == 0:
        local_last = last_token_int + 1
    else:
        local_last = last_token_int - 1
    print("====DEBUG==== 4. local_last:")
    print(local_last)
    print("print zero: '%s'" % str(0))
    # ip_tokens = ip_tokens.append(str(local_last))
    ip_tokens.append(str(local_last))
    print("====DEBUG==== 5. ip_tokens:")
    print(ip_tokens)
    if ':' in peer:
        return ':'.join(ip_tokens)
    else:
        return '.'.join(ip_tokens)


def cover_change_routes_to_curl(operation: str, prefix: str, eth_name: str,
                                nexthop: str = '10.10.246.254',
                                ptfip: str = '10.250.0.100') -> str:
    # operation = "announce"
    # prefix = "10.134.22.0/24"
    # nexthop = '10.10.246.254"
    # ptfip = "10.250.0.100"
    # port = 5001
    def eth_name_2_port(name: str, is_v6: bool) -> int:
        base = 6000 if is_v6 else 5000
        return base + int(name[8:]) - 33

    port = eth_name_2_port(eth_name, ":" in prefix)

    messages = []
    messages.append("{} route {} next-hop {}".format(operation, prefix, nexthop))
    url = "http://%s:%d" % (ptfip, port)
    data = {"commands": ";".join(messages)}
    # print("messages has %s" % messages)
    # print("url: %s" % url)
    # print("data = %s" % json.dumps(data))
    # print("turn to CURL string\n")

    # import requests
    # response = requests.post(url, data=data)
    # import curlify
    # curl_str = curlify.to_curl(response.request)

    import urllib.parse
    # curl -X POST -H 'Accept: */*' -H 'Accept-Encoding: gzip, deflate' -H 'Connection: keep-alive' -H 'Content-Length: 63' -H 'Content-Type: application/x-www-form-urlencoded' -H 'User-Agent: python-requests/2.24.0' -d commands=withdraw+route+10.134.11.0%2F24+next-hop+10.10.246.254 http://10.250.0.100:5001
    curl_str = "curl -X POST -H 'Accept: */*' -H 'Accept-Encoding: gzip, deflate' -H 'Connection: keep-alive' -H 'Content-Length: 63' -H 'Content-Type: application/x-www-form-urlencoded' -H 'User-Agent: python-requests/2.24.0' -d %s %s" % (urllib.parse.urlencode(data), url)
    return curl_str


def check_re_search_image(filepath: str, image: str):
    config = open(filepath, 'r')
    config_content = config.read()
    menuentry = re.search("menuentry '" + image + "' {[^}]*}", config_content).group()
    return menuentry


def search_dict(platform: str) -> str:
    dict_platform_sts_conf = {
        "x86_64-accton_wedge100bf_65x-r0": "/usr/share/sonic/device/x86_64-accton_wedge100bf_65x-r0/mavericks/switch-tna-sai.conf",
        "x86_64-accton_wedge100bf_32x-r0": "/usr/share/sonic/device/x86_64-accton_wedge100bf_32x-r0/montara/switch-tna-sai.conf",
        "x86_64-lambda_hpa1-r0": "/usr/share/sonic/device/x86_64-lambda_hpa1-r0/HPA1/switch-tna-sai.conf"
    }
    if platform not in dict_platform_sts_conf:
        print("platform:%s is not support" % platform)
        return ""
    return dict_platform_sts_conf[platform]


def test_set_update():
    total_down_ports = set()
    ports_down = ["ethernet1", "ethernet3", "ethernet5", "ethernet6", "ethernet10"]
    db_ports_down = ["ethernet2", "ethernet4", "ethernet6", "ethernet8", "ethernet10"]
    total_down_ports.update(ports_down)
    total_down_ports.update(db_ports_down)
    print("__get_down_ports# ports_down:%d, db_ports_down:%d, ret: total_down_ports:%d" % (len(ports_down), len(db_ports_down), len(total_down_ports)))
    print("total_down_ports:", total_down_ports)


def run_command(cmd, allow_raise=True):
    print("cmd: ", cmd)
    code = 1
    if code != 0 and allow_raise:
        print("raise Exception run command failed:  + p.stderr")


def test_join(ips):
    print("Input:")
    print(ips)
    hosts_v4 = ips[0] if len(ips) == 1 else ",".join(ips)
    if not hosts_v4:
        print("hosts: NULL")
    else:
        print("hosts: '%s'" % hosts_v4)


def split_subnet(cidr, prefix_len):
    subnets = []
    n = ipaddress.ip_network(cidr)
    if n.prefixlen >= prefix_len:
        return [cidr]
    for i in range(1, (1 << (prefix_len - n.prefixlen)) - 1):
        if n.version == 4:
            offset = 32 - prefix_len
        else:
            offset = 128 - prefix_len
        new = n.network_address + (i << offset)
        new = ipaddress.ip_network(str(new) + "/" + str(prefix_len))
        subnets.append(str(new))
    return subnets


# def extra_ping_res(res: str):
#     match_obj = re.match('^([^-]*)-{3}[a-zA-Z0-9:.\s]+-{3}([\s\S]*)$', res)
#     if match_obj is None:
#         raise Exception("ping failed: re match failed")
    
#     rules = match_obj.group(1).split('\n')[1:-2]
#     tmp = match_obj.group(2).strip().split(',')
#     statics = ['', '', '', '']

#     if len(tmp[-1].split('ms')) == 3:
#         statics = tmp[-1].split('ms')[1].strip().split('=')[1].split('/')

#     res = {
#         'statistics':{
#             'send': re.match('^(\\d+)\d+$', tmp[0].strip()).group(1),
#             'received': re.match('^(\\d+)\d+$', tmp[1].strip()).group(1),
#             'min': statics[0],
#             'avg': statics[1],
#             'max': statics[2],
#             'stddev': statics[3],
#         },
#         'rules':[]
#     }
#     for rule in rules:
#         match_obj = re.match('^\d+\d+([a-zA-Z0-9:\.]+)\d+(\d+)\d+(\d+)\D+([\d\.]+)\d+$', rule)
#         if match_obj is not None:
#             res['rules'].append({
#                 'dst_ip': match_obj.group(1),
#                 'seq': match_obj.group(2),
#                 'ttl': match_obj.group(3),
#                 'time': match_obj.group(4)
#             })
#     return res


def gen_vtysh_announce_cmd_str(bgp_asn: int, v4_ips: list, v6_ips: list):
    configs = ["config terminal", "router bgp %s" % bgp_asn]
    if len(v4_ips) > 0:
        configs.append("  address-family ipv4 unicast")
        for ip in v4_ips:
            configs.append("   network " + ip)
    if len(v6_ips) > 0:
        configs.append(" address-family ipv6 unicast")
        for ip in v6_ips:
            configs.append("   network " + ip)
    config = "\n".join(configs)
    str_cmd = "docker exec -it bgp vtysh -c '%s'" % config
    return str_cmd


def gen_vtysh_withdraw_cmd_str(bgp_asn: int, v4_ips: list, v6_ips: list):
    configs = ["config terminal", "router bgp %s" % bgp_asn]
    if len(v4_ips) > 0:
        configs.append("  address-family ipv4 unicast")
        for ip in v4_ips:
            configs.append("   no network " + ip)
    if len(v6_ips) > 0:
        configs.append(" address-family ipv6 unicast")
        for ip in v6_ips:
            configs.append("   no network " + ip)
    config = "\n".join(configs)
    str_cmd = "docker exec -it bgp vtysh -c '%s'" % config
    return str_cmd


def ipintfadd(intf, addend):
    # TODO: 超过 256 的 IP 是否还能生成
    return ipaddress.ip_interface("{}/{}".format(intf.ip + addend*intf.network.num_addresses, intf.network.prefixlen))


def test_ipintfadd():
    loipintf = ipaddress.ip_interface("20.10.0.2/32")
    for i in range(1000,1005):
        loip = ipintfadd(loipintf, i*2+1).with_prefixlen
        print(i, loip)

def combineHexBytes(strList: List[str]) -> bytes:
    s = ""
    for val in strList:
        if val.startswith("0x"):
            val = val[2:]
        s += val
    return bytes.fromhex(s)


def combineHex(hexList: List[hex]):
    combined_hex_bytes = b''.join([struct.pack("!I", val)[-((val.bit_length() + 7) // 8):] for val in hexList])
    return combined_hex_bytes


def test_gen_dcg_flink_sinks():
    pair_list = [
        ["out_bytes", "ifOutBytes"],
        ["qosq_drp_pps0", "intfQosQDrpPps0"],
        ["qosq_drp_pps1", "intfQosQDrpPps1"],
        ["qosq_drp_pps2", "intfQosQDrpPps2"],
        ["qosq_drp_pps3", "intfQosQDrpPps3"],
        ["qosq_drp_pps4", "intfQosQDrpPps4"],
        ["qosq_drp_pps5", "intfQosQDrpPps5"],
        ["qosq_fwd_bps0", "intfQosQFwdBps0"],
        ["qosq_fwd_bps1", "intfQosQFwdBps1"],
        ["qosq_fwd_bps2", "intfQosQFwdBps2"],
        ["qosq_fwd_bps3", "intfQosQFwdBps3"],
        ["qosq_fwd_bps4", "intfQosQFwdBps4"],
        ["qosq_fwd_bps5", "intfQosQFwdBps5"],
        ["qosq_fwd_ratio", "intfQosQFwdRatio"]
    ]

    for pair in pair_list:
        print("\nINSERT INTO sink\nSELECT 'STORE', '%s', %s,\nCONCAT('{',\n'dcgw_id=', direct_connect_gateway_id,\n',',\n'account_id=',account_id,\n',',\n'switch_id=',switch_id,\n',',\n'region=','@{region}',\n',',\n'access_point=', direct_connect_access_point_id,\n',',\n'route_type=',route_type,\n','\n'account_scope=',account_scope,\n'}'\n)\nfrom dcgw_metric_aggregation  WHERE direct_connect_gateway_id IS NOT NULL;\n" % (pair[0], pair[1]))


def test_gen_dcc_flink_sinks():
    pair_list = [
        ["in_bps", "ifHCInOctets"],
        ["qosq_drp_pps0", "intfQosQDrpPps0"],
        ["qosq_drp_pps1", "intfQosQDrpPps1"],
        ["qosq_drp_pps2", "intfQosQDrpPps2"],
        ["qosq_drp_pps3", "intfQosQDrpPps3"],
        ["qosq_drp_pps4", "intfQosQDrpPps4"],
        ["qosq_drp_pps5", "intfQosQDrpPps5"],
        ["qosq_fwd_bps0", "intfQosQFwdBps0"],
        ["qosq_fwd_bps1", "intfQosQFwdBps1"],
        ["qosq_fwd_bps2", "intfQosQFwdBps2"],
        ["qosq_fwd_bps3", "intfQosQFwdBps3"],
        ["qosq_fwd_bps4", "intfQosQFwdBps4"],
        ["qosq_fwd_bps5", "intfQosQFwdBps5"],
        ["qosq_fwd_ratio", "intfQosQFwdRatio"]
    ]

    for pair in pair_list:
        print("\nINSERT INTO sink\nSELECT 'STORE', '%s', %s,\nCONCAT('{',\n'dcc_id=', direct_connect_connection_id,\n',',\n'account_id=',account_id,\n','\n'account_scope=',account_scope,\n',',\n'switch_id=',switch_id,\n',',\n'region=','cn-chengdu-sdv',\n','\n'access_point=', direct_connect_access_point_id,\n','\n'connection_type=', connection_type,\n'}'\n)\nfrom dcc_metric_aggregation WHERE direct_connect_connection_id IS NOT NULL;\n" % (pair[0], pair[1]))


def test_for_list():
    interface_info = [{"ifIndex": "oid1"},{"ifIndex": "oid2"},{"ifIndex": "oid3"},{"ifIndex": "oid4"}]
    if_idx_list = []
    for i in range(len(interface_info)):
        if interface_info[i].get('ifIndex', ''):
            if_idx_list.append(interface_info[i].get('ifIndex', ''))
    print(if_idx_list)



def main():
    test_for_list()


if __name__ == '__main__':
    main()
