layout: post
title: gRPC简介
date: 2022/1/17 15:39:45
updated: 2022/1/17 16:34:45
comments: true
tags:
- gRPC
categories:
- 技术

---

# 1. RPC 回顾
> RPC 简介：https://en.wikipedia.org/wiki/Remote_procedure_call
Remote procedure call, RPC：远程程序调用

## 1.1. 需求场景
- 分布式计算场景中，一台计算机产生一个“需要在不同网络地址下的计算机中执行的”子程序，希望：
  - 像调用本地程序一样调用这些需在远程执行的子程序
  - 无需编写远程交互的详细代码
  - 且编码时只需完成简单的“调用方式选择”编码，即选择需调用的一个子程序的方式为：本地调用 or 远程调用

<!-- more -->

## 1.2. 简介

- **一种请求响应协议（模式、机制）**
  - 支持本地计算机远程调用其他计算机中的程序。
  - 基于目标导向编程范式，RPC 通常又表现为**远程方法调用**(remote method invocation, RMI)

- **CS架构**：
  - 调用“执行某远程程序”的计算机为客户端（caller is client）
  - 远程真正执行该程序的计算机为服务端（executor is server）
- **调用方式**：
  - 基于请求-响应协议的消息传递方式调用
  - 通过进程间通信(inter-process communication, IPC)实现，客户端/服务端程序位于不同的地址空间（若在同一物理机，也分别位于不同的虚拟地址空间中）
- **备注**：
  - RPC 模型隐含了（对需远程调用子程序的）“位置暴露”的级别（划分）
  - 相比于本地调用子程序，远程调用子程序的常见特征：响应及时性要求低、与本地主程序依赖程度低

## 1.3. 发展历史
- 1960s早期，请求响应模式最早出现在早期的分布式计算中
- 1970s，“将远程程序调用RPC作为网络操作的模型”的理论被提出
  - 1978，Per Brinch Hansen提出分布式程序，是基于大量进程间的“外部请求”子程序调用构成的
- 1980s早期，RPC 才实际应用于实践
  - 1982，Brian Randell和同事们将 RPC 实际应用于支持多台 UNIX 设备构建分布式系统所需的 Newcastle Connection 程序。
- 1990s，随着（object-oriented programming，OOP）的普及，多种远程方法调用（RMI）的模型相继出现：
  - 1991，Common Object Request Broker Architecture，CORBA
  - Java remote method invocation
- 2000s，随着因特网的崛起，远程方法调用模型（RMI）也被广泛应用
- 2015年，谷歌开源了一款精简而强大的 RPC 协议（Google Remote Procedure Call, gRPC）

# 2. gRPC
> 2015年，谷歌开源的一款精简而强大的下一代 RPC 协议（Google Remote Procedure Call, gRPC）。
>  - 一款性能强大的开源通用 RPC 框架
>
> 传输方式：[HTTP/2.0](https://http2.github.io/)
>
> [gRPC官网](https://grpc.io/)
>
> [grpc官方github文档](https://github.com/grpc/grpc/tree/master/doc)

## 2.1. gRPC 诞生原因（解决什么问题）

提升数据交换性能：
- 提升网络传输速率和带宽
- 提升编解码效率
- 精简传输数据

主流的数据交换格式有两种（可扩展标记语言）：XML、JSON

### 2.1.1. XML优缺点

- 优势：
  - 格式统一：使用DTD(document type definition)文档类型定义来组织数据，格式统一，跨平台和语言，已成为业界公认的标准
  - 与其他系统进行远程交互较容易，数据共享较方便。
- 缺点：
  - XML 文件庞大，格式复杂，传输占用带宽较高
  - XML解析代码冗长且复杂、不易维护
  - 不同客户端浏览器之间解析XML的方式不一致，需要重复编写很多适配代码；
  - 解析 XML 耗费较多资源及时间

### 2.1.2. JSON 优缺点
- 优势：
  - 格式简单：数据格式比较简单，易于读写，格式中空格换行能被压缩
  - 易解析：
  - 易于维护：
- 缺点：
  - 描述性不及 XML
  - 普及程度与通用性不及 XML

## 2.2. gRPC 优势
- 基于 [Protobuf](https://developers.google.com/protocol-buffers) 序列化协议的接口定义：
  - 提升安全性。通过Protobuf来提供严格的接口约束（[Google Protobuf简明教程](https://www.jianshu.com/p/b723053a86a6)）
  - 更提升一致性。客户端服务端使用同一份原文件生成接口定义，双方接口完全相同，结构直观精确，便于管理维护
  - 提高传输性能。可以将数据序列化并压缩为二进制编码，大幅减少传输数据量，易于实现更高的吞吐性能
- 基于 http2.0 传输协议的网络通信：
  - 支持流式通信。可以非常便捷地支持双向流、流控等
  - 提升通信效率。通过 http2.0可实现异步请求、头部压缩、单 TCP 连接上的多复用请求，从而大幅提升通信效率
  - 支持在浏览器中实现一个 gRPC 客户端

<!-- 优点：客户端充分利用高级流和链接功能，从而有助于节省带宽、降低的TCP链接次数、节省CPU使用、和电池寿命。 -->

<!-- ## 4. gRPC 发展情况（发展现状，6年，gRPC-web） -->

## 2.3. gRPC 如何使用、demo

1. Define a service in a .proto file.
  - 定义服务：在 .proto 后缀的文件中定义要建立的服务以及可以远程调用的基本参数和返回类型。
2. Generate the gRPC code from the .proto file.
  - 从 .proto 文件生成 gRPC 代码：gRPC 的编译器 protoc 按照 .proto 文件中定义的服务及数据结构生成目标语言的接口代码
3. Implementation of the server in the chosen language.
  - 以目标语言编码实现服务器端业务功能。
4. Creation of the client stub that calls the service.
  - 创建（目标语言）进行远程调用的 “代理对象”client stub。

## 2.4. 安装 grpc-go
```shell
# 设置env proxy
go env -w GOPROXY=https://goproxy.cn,direct
# 安装 gRPC-go 方式1（go 一键安装）
go install google.golang.org/grpc@latest
# 安装 gRPC-go 方式2 (go get)
go get -u google.golang.org/grpc
# 安装 gRPC-go 方式3（GitHub）
git clone https://github.com/grpc/grpc-go.git ./google.golang.org/grpc; cd google.golang.org/grpc; go install; cd ../../

# 安装 Protobuf
brew install protobuf
# 验证命令
protoc --version

# 安装 go net 包
git clone https://github.com/golang/net.git ./google.golang.org/x/net

# 安装 go genproto 包
git clone https://github.com/google/go-genproto.git ./google.golang.org/genproto

# 安装 go text 包
git clone https://github.com/golang/text.git ./google.golang.org/x/text
```

## 2.5. 安装 Python gRPC 插件
```shell
python3 -m pip install grpcio
pip3 install grpcio-tools
```

## 2.6. 利用 grpc-go 中提供的 helloworld example 实验
```shell
# 启动 server 端
cd google.golang.org/grpc
go get google.golang.org/grpc/examples/helloworld/helloworld
go run examples/helloworld/greeter_server/main.go

# 然后启动 client 端
examples/helloworld/greeter_client/main.go

# 执行结果（服务端）
$ go run examples/helloworld/greeter_server/main.go

2021/12/24 20:09:20 server listening at 127.0.0.1:50051
2021/12/24 20:10:37 Received: world

# 执行结果（客户端）
$ go run examples/helloworld/greeter_client/main.go
2021/12/24 20:10:37 Greeting: Hello world
```

## 2.7. Quick start 记录
> [官网 Quick Start 教程](https://grpc.io/docs/languages/go/quickstart/)
```shell
# 安装 protocol compiler
go install google.golang.org/protobuf/cmd/protoc-gen-go@v1.26
go install google.golang.org/grpc/cmd/protoc-gen-go-grpc@v1.1
# 更新 PATH 以能够发现上述安装插件后的
export PATH="$PATH:$(go env GOPATH)/bin"

# 下载 gRPC 示例代码
git clone -b v1.41.0 https://github.com/grpc/grpc-go
# 跳转到 helloworld 实例路径
cd grpc-go/examples/helloworld

# 运行示例，启动服务端
go run greeter_server/main.go
# 在另一窗口启动客户端
go run greeter_client/main.go
# done. 完成一次 简单的 基于 gRPC 的远程程序调用
```

## 2.8. 备注
- gRPC 服务压测工具：
  - [ghz](https://github.com/bojand/ghz)
- [Protobuf 的 proto2 与 proto3 的区别](https://blog.csdn.net/huanggang982/article/details/77944174)
- gRPC 在 SONIC 中的应用（sonic-sairedis、sonic-mgmt-framework、sonic-telemetry、sonic-frr）

# 3. 参考文档
- [gRPC官网](https://grpc.io/)
- [grpc官方github文档](https://github.com/grpc/grpc/tree/master/doc)
- [Google Protobuf简明教程](https://www.jianshu.com/p/b723053a86a6)
- [了解grpc](https://www.modb.pro/db/78814)

