layout: post
title: Go pprof性能分析工具
date: 2024/6/26 19:53:45
updated: 2024/6/26 19:53:45
comments: true
tags:
- Go
categories:
- 技术

---

Go 的 pprof 是一个内置的性能分析工具，用于帮助开发者诊断程序的性能问题，如 CPU 占用、内存泄漏、协程阻塞等。它通过采样和生成报告，定位代码中的性能瓶颈。pprof 结合简洁的命令和可视化工具，显著提升了 Go 程序的调优效率，是性能优化的必备工具。

<!-- more -->

# 1. 核心功能
- CPU分析：识别消耗最多 CPU 时间的函数。
- 内存分析：检测内存分配和泄漏。
- 阻塞分析：查找导致协程（goroutine）阻塞的代码。
- 协程分析：查看当前所有协程的堆栈信息。

# 2. 启用 pprof
在程序中导入 net/http/pprof 包，并启动 HTTP 服务（如监听:9381）：

```go
import _ "net/http/pprof"

func main() {
    go func() {
        log.Println(http.ListenAndServe("localhost:9381", nil))
    }()
    // 程序逻辑...
}
```

访问 http://localhost:9381/debug/pprof/ 可查看分析入口。

# 3. 常用分析类型及端点
- CPU 分析：/debug/pprof/profile（默认采样 30 秒）。
- 内存分析：/debug/pprof/heap。
- 协程阻塞分析：/debug/pprof/block。
- 当前协程状态：/debug/pprof/goroutine。

# 4. 使用 go tool pprof
通过命令行工具抓取数据并分析：

1. 实时分析：
```shell
# gobgpd 中的 pprof 服务端口, 一般为 9381
PPROF_PORT=9381

# CPU 分析
go tool pprof http://localhost:$PPROF_PORT/debug/pprof/profile

# 内存分析
go tool pprof http://localhost:$PPROF_PORT/debug/pprof/heap

# 查看当前内存使用最多的 10 个函数
echo -e "top 10\nexit" | go tool pprof -inuse_space http://localhost:${PPROF_PORT}/debug/pprof/heap

# 查看当前内存使用最多的 20 个函数调用链 (子函数的值会累加到父函数)
echo -e "top 20 -cum\nexit" | go tool pprof -inuse_space http://localhost:${PPROF_PORT}/debug/pprof/heap

# 查看累积分配内存较多的 20 个函数
echo -e "top 20\nexit" | go tool pprof -alloc_space http://localhost:${PPROF_PORT}/debug/pprof/heap

# 查看累积分配内存较多的 20 个函数调用链 (子函数的值会累加到父函数)
echo -e "top 20 -cum\nexit" | go tool pprof -alloc_space http://localhost:${PPROF_PORT}/debug/pprof/heap
```

交互命令示例：
- top 10：查看前 10 耗时/内存分配的函数。
- web：生成调用关系图（需安装 Graphviz）。
```shell
bash -c 'command -v dot >/dev/null 2>&1 || apt install -y graphviz'
```

2. 生成火焰图：
```shell
# 生成火焰图
go tool pprof -http=:${PPROF_PORT} profile.pprof
go tool pprof -alloc_space -cum -svg http://localhost:${PPROF_PORT}/debug/pprof/heap
```

浏览器打开后，选择 Flame Graph 视图即可。

# 5. 应用场景
- 优化 CPU 使用：定位高耗时函数。
- 排查内存泄漏：分析堆内存分配趋势。
- 解决协程阻塞：发现锁竞争或 I/O 等待问题。
- 并发调试：查看协程堆栈状态。

# 6. 其他方式
- 测试中生成 Profile：使用 go test -cpuprofile 或 -memprofile。
- 手动采集数据：通过 runtime/pprof 包写入文件（适用于非 HTTP 服务）。

