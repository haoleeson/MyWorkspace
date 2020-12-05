layout: post
title: Java进程执行Shell命令问题总结
date: 2020/06/15 22:17:44
updated: 2020/06/15 22:17:45
comments: true
tags:

- Java
categories:
- 技术

---
<img src="https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/execShellCMD.jpg" class="full-image" />
在大部分Java开发过程中需要调用一些Shell脚本命令来实现某些功能，如：文本处理过程中调脚本使开发更便捷、其他组件只提供了Shell脚本调用方式或调脚本与系统直接交互等场景。
博主总结了一些Java进程执行Shell命令的常见问题及解决方法，或能在大家开发过程中避坑有积极作用。

关键词: Java调Shell、问题总结
<!-- more -->

## “No such file or directory”问题的原因分析及解决方法
### 1.若执行的是Shell脚本文件，可能是由于执行脚本的换行符不正确导致的
**原因分析：**文件明明存在但Java仍然报“No such file or directory”，可能由于Linux与Windows系统字符差异（主要是换行符\n,\r\n）导致的，即待执行脚本文件的换行符为\r\n，导致win下编写的脚本文件无法被在Linux环境中Java执行，而报“No such file or directory”IO异常。

**解决方法：**

* 重新在Windows上用文本编辑器改好格式后上传到Linux服务器再执行（简单直观）
在Windows上用文本编辑器(eg.VS code、Notepad++)打开脚本，更改右下角的行位序列: CRLF –> LF，保存。将改好的脚本文件Sftp上传到Linux后重新执行。

* 若觉得从Windows到Linux上传太折腾，也可通过vim更改字符格式（dos -> unix），在Linux环境上用vim去掉多出的'\r'
```Shell
# vim查看文本格式，确定脚本文档格式（dos(Windows)--\r\n; unix(Linux)--\n）
:set ff
# vim查看不可见字符，确认脚本结尾字符问题
:set invlist

# 方式1：命令行模式set fileformat(推荐)
:set fileformat=unix
:wq

## 方式2：删除多的\r字符（下方替换命令没写错，用/r）
:%s//r//g
```

* 若需要修改多个脚本文件格式，也可通过dos2unix命令批量修改
```Shell
sudo find YourScriptsDir/ -name "*.sh" | xargs dos2unix
可选参数备注：
-k：保持输出文件的日期不变 
-q：安静模式，不提示任何警告信息
-V：查看版本
-c：转换模式，模式有：ASCII, 7bit, ISO, Mac, 默认是：ASCII
-o：写入到源文件
-n：写入到新文件
```

### 2.手动在bash中能够执行，但Java中调用Shell却报“No such file or directory”
**原因分析：**Java在调用Shell的时候，默认是用在系统的/bin/目录下的指令（不加载环境变量），可能是找不到命令的路径。如：要用Java执行Shell命令为”node helloworld.js”，可能是不能识别”node”这个命令。
**解决方法：**在/bin/目录下创所调用命令软链接 或 用命令全路径
```Shell
# 创建所调用命令软链接到/bin/目录
ln -s /home/admin/node/bin/node node;

#  或调用时用node的绝对地址
/home/admin/node/bin/node helloworld.js
```

### 3.若脚本文件换行符正确、有脚本执行权限，无命令识别问题，但依然无法执行shell
**原因分析：**推测可能是在调用Runtime.getRuntime().exec(“CMD”)时，传递Shell命令字符串的某个实现环节出了问题。
**解决方法：**实例化一个数据输出流，通过dataoutputstream对象的写字节方法往process写待执行的Shell命令字符串
```Java
int resultValue = 0;
Process process = null;
DataOutputStream dataOutputStream = null;

try {
    process = Runtime.getRuntime().exec("/bin/bash");
    dataOutputStream = new DataOutputStream(process.getOutputStream());
    dataOutputStream.writeBytes(command + "\n");
    dataOutputStream.writeBytes("exit\n");
    dataOutputStream.flush();
    readStdStream(process);
    resultValue = process.waitFor();
    System.out.println("resultValue = " + resultValue);
} catch (IOException e) {
    e.printStackTrace();
} catch (InterruptedException e) {
    e.printStackTrace();
} catch (IllegalMonitorStateException e) {
    e.printStackTrace();
} finally {
    try {
        dataOutputStream.close();
        process.destroy();
    } catch (IOException e) {
        e.printStackTrace();
    }
}
```

## 脚本无执行权限问题及解决方法
**原因分析：**Java执行某些程序解压的脚本，因没及时赋权限导致无法执行
**解决方法：**Java中调用shell命令赋权
```Java
ProcessBuilder processBuilder = new ProcessBuilder("/bin/chmod", "a+x", shFile.getPath());
Process process = processBuilder.start();
int exitValue = process.waitFor();
```

## Java进程阻塞(一直等待Shell返回)问题及解决方法
**原因分析：**调用Shell命令后Java业务进程阻塞，根因是在执行的Shell脚本中含print或echo输出，未能读取缓存区导致缓存区用尽。
**解决方法：**及时将标准输出流和错误流读取出来，也方便后续问题定位
```Java
String readLine;
BufferedReader stdInput = null;
BufferedReader stdError = null;
try {
    // 读取Shell进程标准输出流
    stdInput = new BufferedReader(new InputStreamReader(process.getInputStream()));
    while ((readLine = stdInput.readLine()) != null) {
        System.out.println("[stdInputStream]:" + readLine);
    }
    // 读取Shell进程标准错误流
    stdError = new BufferedReader(new InputStreamReader(process.getErrorStream()));
    while ((readLine = stdError.readLine()) != null) {
        System.out.println("[stdErrorStream]:" + readLine);
    }
} catch (IOException e) {
    e.printStackTrace();
} finally {
    try {
        stdInput.close();
        stdError.close();
    } catch (IOException e) {
        e.printStackTrace();
    }
}
```

## 附录：简易的Java执行Shell命令类
```Java
import java.io.*;
public class ExecShellCMD {
    /**
     * Java执行shell命令
     * @param command
     * @return
     */
    public static int execShellCommand(final String command) {
        int resultValue = 0;
        Process process = null;
        DataOutputStream dataOutputStream = null;
        try {
            process = Runtime.getRuntime().exec("/bin/bash");
            dataOutputStream = new DataOutputStream(process.getOutputStream());
            dataOutputStream.writeBytes(command + "\n");
            dataOutputStream.writeBytes("exit\n");
            dataOutputStream.flush();
            readStdStream(process);
            resultValue = process.waitFor();
            System.out.println("resultValue = " + resultValue);
        } catch (IOException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            e.printStackTrace();
        } catch (IllegalMonitorStateException e) {
            e.printStackTrace();
        } finally {
            try {
                dataOutputStream.close();
                process.destroy();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        return resultValue;
    }

    /**
     * 读取Shell进程标准输出流和错误流
     * @param process
     */
    private static void readStdStream(final Process process) {
        String readLine;
        BufferedReader stdInput = null;
        BufferedReader stdError = null;
        try {
            // 读取Shell进程标准输出流
            stdInput = new BufferedReader(new InputStreamReader(process.getInputStream()));
            while ((readLine = stdInput.readLine()) != null) {
                System.out.println("[stdInputStream]:" + readLine);
            }
            // 读取Shell进程标准错误流
            stdError = new BufferedReader(new InputStreamReader(process.getErrorStream()));
            while ((readLine = stdError.readLine()) != null) {
                System.out.println("[stdErrorStream]:" + readLine);
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                System.out.println("close std stream");
                stdInput.close();
                stdError.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    // 简单测试代码
    public static void main(String[] args) {
        System.out.println("Java exec shell command running...");
        String command = "/home/admin/node/bin/node helloworld.js";
        int times = 0;

        while (true) {
            if (times > 100) {
                times = 0;
            }
            System.out.println("\nNo." + (++times) + " times to exec shell command...");
            execShellCommand(command);
            // 进程等待10s
            try {
                Thread.sleep(10000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
```
