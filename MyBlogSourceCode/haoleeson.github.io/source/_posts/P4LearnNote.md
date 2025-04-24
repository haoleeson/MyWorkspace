layout: post
title: P4学习笔记
date: 2023/4/24 9:21:45
updated: 2023/4/24 9:21:45
comments: true
tags: 
- Network
- P4
categories:
- 技术

---

intel 收购 Barefoot 后推出的可编程交换机芯片 Tofino 所采用的编程语言为P4，本文记录P4基础及常用抓包方法等笔记。

<!-- more -->



# 1. P4基础语法


## 1.1. 变量类型
> P4 是一种静态类型的语言

### 1.1.1. 常用类型
void、error、string、match_kind、bool、int、Bit-strings、Fixed-width

### 1.1.2. 派生类型
enum、header、header stacks、struct、header_union、tuple、type specialization 、extern、parser、control、package

### 1.1.3. 参数方向
每个参数都需要标记方向：
- in， 只读
- out， 未标记、视作无方法或函数体的值
- inout， both in and out
- 'No direction' 
  - 编译阶段值
  - 只能在控制平台设置的“行为参数”
  - 能被其他“调用行为”直接设置的值，如同局部变量


### 1.1.4. L-values vs I-values
- L-values: 出现在赋值操作左侧、或作为 out 和 inout 函数参数（代表“存储”）




## 1.2. 基本语法
### 1.2.1. 支持运算类型
- 算术运算（arithmetic operations）：+, -, *
- 逻辑运算（logical operations）：~, &, |, ^, >>, <<
- 特殊运算（non-standard operations）：
- 数列的切割（bit slicing）：[m;l]
- 比特的叠加（bit concatenation）：++

### 1.2.2. 支持语法逻辑
- if-else
```c++
if (x == 123) {
    ...
} else {
    ...
}
```

- switch
```c++
switch (t.apply().action_run) {
	action1: {...}
	action2: {...}
}
```

### 1.2.3. P4 查看 VLAN subinterface 表项
```shell
docker exec -it syncd /opt/bfn/install/bin/bfshell
bf_switch
show hostif handle 2

```

# 2. PTF查看switchd表项
## 2.1. PTF测试查看 switchd 表项

```shell

bfshell> bf_switch
bf_switch:0> show hostif all
bf_switch:0> show route all
bf_switch:0> show neighbor all
bf_switch:0> show nexthop all
bf_switch:0> show rif all
bf_switch:0> show vrf all
bf_switch:0> show rmac_group all
bf_switch:0> show mtu all
```

## 2.2. PTF 查看表项
```shell
bfshell> bfrt_python
bfrt_root>bfrt
bfrt> switch
bfrt.switch> pipe
bfrt.switch.pipe> SwitchEgress

#...
```

bfrt.switch.pipe.SwitchEgress.rewrite.egress_bd.bd_mapping

bfrt.switch.pipe.SwitchEgress.mtu

bfrt.switch.pipe.SwitchIngress.smac

switch_bridged_metadata_h



# 3. snapshot抓包示例

control: 类
table： 函数 （if else）
key: 入参（需关注参数）
action: 子函数 （一般在 table 上实现/被调用）


entry 中删表：


## 3.1. 在 table 中添加表（执行逻辑: 条件 + action）
### 3.1.1. 删表
delete(表名)

### 3.1.2. 添加表
add_with_<function>()

添加表项（添加执行逻辑）

gw: get way 硬件

Inhibited 抑制（硬件匹配，但代码逻辑抑制gw ）



entry 中删表：


## 3.2. 在 table 中添加表（执行逻辑: 条件 + action）
当前是 "agent" 来「替人为添加这些 逻辑」

### 3.2.1. 删表
delete(表名)

### 3.2.2. 添加表
add_with_<function>()

添加表项（添加执行逻辑）


## 3.3. snapshort 抓包
> 两个方向
> 1. 看进出口，有无丢包
> 2. 看 Table info **哪些 hit** 哪些没 hit，关心的哪张表

/opt/bfn/install/bin/bfshell

进入 pipe_mgr
```shell
ucli
pipe_mgr

bf-sde.pipe_mgr > 
```

### 3.3.1. 删除旧 snapshort 句柄
```shell
# 删除旧 snapshort （若有）
snap-delete -h 0x581
snap-delete -h 0x1583
## pipe2 Ingress
snap-delete -h 0x2581
## pipe2 Egress
snap-delete -h 0x2583
## pipe3 Ingress
snap-delete -h 0x3581
## pipe3 Egress
snap-delete -h 0x3583
```

### 3.3.2. 创建 snapshot（获取返回句柄）
```shell

# -i 0 是 Ingress, 1 是 Egress
snap-create -d 0 -p 0 -s 0 -e 11 -i 0
snap-create -d 0 -p 1 -s 0 -e 11 -i 1
## pipe2 Ingress
snap-create -d 0 -p 2 -s 0 -e 11 -i 0
## pipe2 Egress
snap-create -d 0 -p 2 -s 0 -e 11 -i 1
## pipe3 Ingress
snap-create -d 0 -p 3 -s 0 -e 11 -i 0
## pipe3 Egress
snap-create -d 0 -p 3 -s 0 -e 11 -i 1
```

### 3.3.3. 创建抓包触发器 (设置触发条件)
#### 3.3.3.1. 查看有哪些字段可抓
```shell
# PS 可通过 查看可用哪些「PHV 资源」 **可抓**
# -i 0 是 Ingress, 1 是 Egress
phv-dump -d 0 -p 1 -s 0 -i 1
## pipe2 Ingress
phv-dump -d 0 -p 2 -s 0 -i 0
## pipe2 Egress
phv-dump -d 0 -p 2 -s 0 -i 1
## pipe3 Ingress
phv-dump -d 0 -p 3 -s 0 -i 0
## pipe3 Egress
phv-dump -d 0 -p 3 -s 0 -i 1
```


```shell
# 抓特定 DIP 10.0.0.32（0xA000020）
snap-trig-add -h 0x581 -n hdr_ipv4_dst_addr  -v 0xA000020 -m 0xffffffff
# 抓特定 DIP 1.0.0.100 (0x1000064)
snap-trig-add -h 0x2581 -n hdr_ipv4_dst_addr  -v 0x1000064 -m 0xffffffff
snap-trig-add -h 0x2581 -n hdr_ipv4_dst_addr  -v 0xAE3C384 -m 0xffffffff
#   172.20.0.1  0xAC140001
snap-trig-add -h 0x2581 -n hdr_ipv4_dst_addr  -v 0xAC140001 -m 0xffffffff
# 抓特定 DIP 1.0.0.100 (0x1000064)
snap-trig-add -h 0x1583 -n hdr_inner_ipv4_dst_addr  -v 0x1000064 -m 0xffffffff
# pipe2 Ingress 抓特定 DIP 100.106.182.121 (0x646AB679)
snap-trig-add -h 0x2581 -n hdr_inner_ipv4_dst_addr  -v 0x646AB679 -m 0xffffffff
# pipe2 Egress 抓特定 DIP 100.106.182.121 (0x646AB679)
snap-trig-add -h 0x2583 -n hdr_ipv4_dst_addr  -v 0x646AB679 -m 0xffffffff
# pipe3 Ingress 抓特定 DIP 100.106.182.121 (0x646AB679)
snap-trig-add -h 0x3581 -n hdr_ipv4_dst_addr  -v 0x646AB679 -m 0xffffffff
# pipe3 Egress 抓特定 DIP 100.106.182.121 (0x646AB679)
snap-trig-add -h 0x3583 -n hdr_inner_ipv4_dst_addr  -v 0x646AB679 -m 0xffffffff
# pipe3 Egress 抓特定 DIP 100.106.182.121 (0x646AB679)
snap-trig-add -h 0x3583 -n hdr_ipv4_dst_addr  -v 0xC0A81E01 -m 0xffffffff

# 抓特定端口
snap-trig-add -h 0x1583 -n local_md_ingress_port -v 0x144 -m 0x1ff
# 抓送往 FPGA 33 口报文
snap-trig-add -h 0x2583 -n local_md_egress_port -v 0x134 -m 0x1ff
# 抓特定状态
snap-trig-add -h 0x1583 -n hdr_table_1_result_valid  -v 0x1 -m 0xf


```

### 3.3.4. 开启抓包
```shell
# check 当前抓包配置
snap-cfg-dump -h 0x2581

snap-state-set -h 0x581 -e 1
snap-state-set -h 0x1583 -e 1
## pipe2 Ingress
snap-state-set -h 0x2581 -e 1
## pipe2 Egress
snap-state-set -h 0x2583 -e 1
## pipe3 Ingress
snap-state-set -h 0x3581 -e 1
## pipe3 Egress
snap-state-set -h 0x3583 -e 1
```
### 3.3.5. 查看抓包结果
```shell
snap-capture-get -h 0x581
snap-capture-get -h 0x1583
## pipe2 Ingress
snap-capture-get -h 0x2581
## pipe2 Egress
snap-capture-get -h 0x2583
## pipe3 Ingress
snap-capture-get -h 0x3581
## pipe3 Egress
snap-capture-get -h 0x3583
```
### 3.3.6. 停止抓包
```shell
snap-state-set -h 0x1583 -e 0
snap-state-set -h 0x581 -e 0
## pipe2 Ingress
snap-state-set -h 0x2581 -e ~~0~~
## pipe2 Egress
snap-state-set -h 0x2583 -e 0
## pipe3 Ingress
snap-state-set -h 0x3581 -e 0
## pipe3 Egress
snap-state-set -h 0x3583 -e 0
```




# 4. 为什么编译器 flexible 很重要

flexible 加在哪儿？ （PHV、ALU、ALC 实现）
变量初始化
 
编译宏 -- 结构体

注解  @flexible 自动优化变量结构/字节序/panding

编译器优化，两个结构体的不同变量（同大小），编译器放到了同一个存储空间

修饰符：让编译器不做优化

（pa_mutually_exclusive("ingress", "lkp.mpls_lookup_label", "lkp.ip_src_addr")）



# 5. P4编译中常见PHV、ALU资源分配错误问题解决思路
P4编译遇到PHV和ALU资源冲突问题解决思路

1. struct 中尽量小 bit 成员变量在前
2. 拆 action。拆解有多个 key、parameter 的 action 到多个子 action（一个赋值对应一个 ALU）
3. 通过 in hash 降维？