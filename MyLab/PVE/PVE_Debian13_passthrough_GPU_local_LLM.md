# PVE显卡直通Debian13虚拟机并安装本地大模型

**注意事项**
- PVE BIOS设置：进入 BIOS/UEFI 设置，启用 AMD IOMMU （对于 Intel 平台，启用 Intel VT-d）
- 建议在安装过程中禁用 Secure Boot，以避免后续安装 NVIDIA 和 CUDA 驱动时出现签名认证失败或系统启动问题
- 建议选择简体中文作为系统语言，以避免后续安装和修改语言包的额外步骤
- 建议分配 128GB 以上的磁盘空间，因为后续安装本地大模型及相关工具将占用较大存储空间


# PVE直通GPU设置
详见[PVE 主机配置](./MyLab/PVE/PVE_passthrough_GPU_with_CPU_AMD5600X_GPU_Nvdia4070.md)

# 安装Debian13系统
参考博文： https://blog.csdn.net/m0_69493559/article/details/151297885 ， https://osgeo.cn/post/140d7/


## 配置Debian 13 国内镜像源
1. 修改 /etc/apt/sources.list
```shell
deb https://mirrors.ustc.edu.cn/debian/ trixie main contrib non-free non-free-firmware
deb-src https://mirrors.ustc.edu.cn/debian/ trixie main contrib non-free non-free-firmware
deb https://mirrors.ustc.edu.cn/debian/ trixie-updates main contrib non-free non-free-firmware
deb-src https://mirrors.ustc.edu.cn/debian/ trixie-updates main contrib non-free non-free-firmware
deb https://mirrors.ustc.edu.cn/debian/ trixie-backports main contrib non-free non-free-firmware
deb-src https://mirrors.ustc.edu.cn/debian/ trixie-backports main contrib non-free non-free-firmware
# 安全更新源
deb https://mirrors.ustc.edu.cn/debian-security trixie-security main contrib non-free non-free-firmware
deb-src https://mirrors.ustc.edu.cn/debian-security trixie-security main contrib non-free non-free-firmware
```

2. 确保系统已安装 apt-transport-https 和 ca-certificates 包
```shell
sudo apt update
sudo apt install apt-transport-https ca-certificates
```

## PVE中Debian13虚拟机配置示例
root@pve:~# cat /etc/pve/qemu-server/100.conf 
```shell
bios: ovmf
boot: order=virtio0;net0
cores: 8
cpu: host
efidisk0: local:100/vm-100-disk-1.qcow2,efitype=4m,pre-enrolled-keys=1,size=528K
hostpci0: 0000:08:00.0,pcie=1,x-vga=1
hostpci1: 0000:08:00.1
machine: pc-q35-9.2+pve1
memory: 16384
meta: creation-qemu=9.2.0,ctime=1773932671
name: Debian13-GPU
net0: virtio=BC:24:11:D1:CB:12,bridge=vmbr0
numa: 0
onboot: 1
ostype: l26
scsihw: virtio-scsi-single
smbios1: uuid=a13d97aa-9743-4db7-9be3-ff9b1f345289
sockets: 1
startup: order=1,up=10,down=10
tags: 172.21.213.138
usb0: host=3-3
usb1: host=1-7
usb2: host=3-1
usb3: host=3-1.1
usb4: host=3-1.2
virtio0: local:100/vm-100-disk-0.qcow2,iothread=1,size=128G
vmgenid: 521a4240-2c5a-485c-a6bb-638c9da1f1c8
```

## 修复CD-ROM报错
方式1：禁用CD-ROM源（推荐）
```bash
# 编辑 sources list
sudo nano /etc/apt/sources.list
```

找到并注释掉包含 cdrom: 的行，例如：
```bash
# deb cdrom:[Debian GNU/Linux 13.4.0 _Trixie_ ...]/ bookworm main
```

保存文件（Ctrl+O，然后回车），退出（Ctrl+X），并更新：
```bash
sudo apt update
```

方式2：使用 apt-cdrom 移除 CD-ROM 源
```bash
# Remove the CD-ROM from sources
sudo apt-cdrom --no-mount -m remove

# Update package lists
sudo apt update
```

验证修复
```bash
grep -r "cdrom" /etc/apt/sources.list*
sudo apt update
```

## 卸载过时ibus-pinyinj拼音宝并重装新的ibus智能拼音包
注：搜狗输入法在 Debian 13 上安装后可能无法正常使用，建议使用 IBus 输入法框架，安装完成后重启系统即可使用。

1. 卸载过时的拼音包
```bash
sudo apt purge ibus-pinyin
sudo apt autoremove --purge -y
```

2. 安装新的智能拼音包
```bash
sudo apt update
sudo apt install ibus-libpinyin
```

3. 重新配置 IBus
- 重启 IBus 守护进程，让改动生效：
```bash
ibus restart
```

- 打开 IBus 首选项，添加新的输入法：
```bash
ibus-setup
```

在弹出的窗口中，切换到 “输入法” (Input Method) 选项卡。

点击 “添加” (Add) 按钮。

在列表中，选择 “中文” (Chinese)，然后在其子项中选择 “智能拼音” (Intelligent Pinyin)，最后点击“添加”。

4. 在系统设置中启用
这是较为关键的一步，许多用户可能在此处遇到困难。仅在 ibus-setup 中添加输入法并不充分，还需在系统设置中启用。

打开 GNOME 的 “设置” (Settings) 应用。

进入 “键盘” (Keyboard) 设置。

找到 “输入源” (Input Sources) 部分。

点击下方的 “+” 号，添加一个新的输入源。

在弹出的对话框中，将语言选为 “汉语” (Chinese)，然后在列表中应该能看到 “中文（智能拼音）” 或类似的选项，选择它并点击“添加”。

5. 验证
现在，您应能在系统右上角的菜单栏看到新添加的输入法图标。使用 Win 键 + 空格（Super+Space）或自定义快捷键，即可切换至中文输入法进行测试。

若仍有问题，可尝试重启系统，以确保所有配置完全生效。




# 安装本地大模型 (via Ollama)
随着 Ollama 等工具的普及，本地部署大模型的门槛已显著降低。8bit 量化是一种平衡性能与资源消耗的常用方法。通过当前流行的 Ollama 官网，可快速部署本地大模型，几乎实现开箱即用，其中 8bit 量化有助于平衡性能与资源消耗。

## 安装 NVIDIA 驱动和 CUDA 工具包
1. 查看当前已安装的 NVIDIA 包并彻底清理
```bash
# 查看所有已安装的 nvidia 相关包
dpkg -l | grep -E "nvidia|cuda" | grep ^ii

# 彻底清理所有 nvidia 包（包括配置文件）
sudo apt purge *nvidia* *cuda* *cudnn*
sudo apt autoremove --purge -y

# 清理可能残留的 dkms 模块
sudo dkms remove nvidia/$(dkms status | grep nvidia | cut -d',' -f1 | cut -d'/' -f2) --all 2>/dev/null
```

2. 清理 apt 缓存并更新源
```bash
sudo apt clean
sudo apt update
```

3. 安装匹配版本的驱动
```bash
# 只安装传统的闭源驱动包（会自动处理内核模块）
sudo apt install -y nvidia-driver firmware-misc-nonfree
```

4. 为 NVIDIA 驱动签名（推荐，保持系统安全）
```bash
sudo apt update
sudo apt install -y openssl mokutil dkms linux-headers-$(uname -r)
```

生成并注册 MOK 密钥
```bash
# 生成密钥对 (此操作在 /var/lib/dkms/ 目录下创建 mok.pub 和 mok.priv)
sudo dkms generate_mok
# 将生成的公钥导入到 Secure Boot
sudo mokutil --import /var/lib/dkms/mok.pub
```

重启并注册 MOK
```bash
sudo reboot
```
重启时，系统会自动进入 MOK 管理界面（蓝色背景）：
- 选择 "Enroll MOK" → Continue → Yes。
- 输入你上一步设置的一次性密码。
- 完成注册后，系统会继续启动。

验证并重装驱动：重新登录后，签名过程应已完成。如果 nvidia-smi 仍提示命令未找到，可能是之前的清理步骤影响了驱动。此时需要重新安装驱动（签名已在上述步骤中自动处理）:
```bash
sudo apt install -y nvidia-driver firmware-misc-nonfree
```

重启后验证：若能显示 RTX 4070 信息及 CUDA 版本，则表示驱动安装成功
```bash
nvidia-smi
```

RTX4070安装驱动示例
```bash
dpkg -l | grep -E "nvidia|cuda" | grep ^ii
ii  cuda-cccl-13-2                          13.2.27-1                            amd64        CUDA CCCL
ii  cuda-command-line-tools-13-2            13.2.0-1                             amd64        CUDA command-line tools
ii  cuda-compiler-13-2                      13.2.0-1                             amd64        CUDA compiler
ii  cuda-crt-13-2                           13.2.51-1                            amd64        CUDA crt
ii  cuda-cudart-13-2                        13.2.51-1                            amd64        CUDA Runtime native Libraries
ii  cuda-cudart-dev-13-2                    13.2.51-1                            amd64        CUDA Runtime native dev links, headers
ii  cuda-culibos-dev-13-2                   13.2.51-1                            amd64        CUDA DEV culibos is a Math Libraries fork of the cuos library
ii  cuda-cuobjdump-13-2                     13.2.51-1                            amd64        CUDA cuobjdump
ii  cuda-cupti-13-2                         13.2.23-1                            amd64        CUDA profiling tools runtime libs.
ii  cuda-cupti-dev-13-2                     13.2.23-1                            amd64        CUDA profiling tools interface.
ii  cuda-cuxxfilt-13-2                      13.2.51-1                            amd64        CUDA cuxxfilt
ii  cuda-documentation-13-2                 13.2.51-1                            amd64        CUDA documentation
ii  cuda-driver-dev-13-2                    13.2.51-1                            amd64        CUDA Driver native dev stub library
ii  cuda-drivers                            595.58.03-1                          amd64        CUDA Driver meta-package, branch-specific
ii  cuda-gdb-13-2                           13.2.20-1                            amd64        CUDA-GDB
ii  cuda-keyring                            1.1-1                                all          GPG keyring for the CUDA repository
ii  cuda-libraries-13-2                     13.2.0-1                             amd64        CUDA Libraries 13.2 meta-package
ii  cuda-libraries-dev-13-2                 13.2.0-1                             amd64        CUDA Libraries 13.2 development meta-package
ii  cuda-nsight-13-2                        13.2.20-1                            amd64        CUDA nsight
ii  cuda-nsight-compute-13-2                13.2.0-1                             amd64        NVIDIA Nsight Compute
ii  cuda-nsight-systems-13-2                13.2.0-1                             amd64        NVIDIA Nsight Systems
ii  cuda-nvcc-13-2                          13.2.51-1                            amd64        CUDA nvcc
ii  cuda-nvdisasm-13-2                      13.2.51-1                            amd64        CUDA disassembler
ii  cuda-nvml-dev-13-2                      13.2.51-1                            amd64        NVML native dev links, headers
ii  cuda-nvprune-13-2                       13.2.51-1                            amd64        CUDA nvprune
ii  cuda-nvrtc-13-2                         13.2.51-1                            amd64        NVRTC native runtime libraries
ii  cuda-nvrtc-dev-13-2                     13.2.51-1                            amd64        NVRTC native dev links, headers
ii  cuda-nvtx-13-2                          13.2.20-1                            amd64        NVIDIA Tools Extension
ii  cuda-opencl-13-2                        13.2.51-1                            amd64        CUDA OpenCL native Libraries
ii  cuda-profiler-api-13-2                  13.2.20-1                            amd64        CUDA Profiler API
ii  cuda-sandbox-dev-13-2                   13.2.51-1                            amd64        nvsandboxutils native dev links, headers
ii  cuda-sanitizer-13-2                     13.2.23-1                            amd64        CUDA Sanitizer
ii  cuda-tileiras-13-2                      13.2.51-1                            amd64        JIT compilation feature for TileIR.
ii  cuda-toolkit                            13.2.0-1                             amd64        CUDA Toolkit meta-package
ii  cuda-toolkit-13-2                       13.2.0-1                             amd64        CUDA Toolkit 13.2 meta-package
ii  cuda-toolkit-13-2-config-common         13.2.51-1                            all          Common config package for CUDA Toolkit 13.2.
ii  cuda-toolkit-13-config-common           13.2.51-1                            all          Common config package for CUDA Toolkit 13.
ii  cuda-toolkit-config-common              13.2.51-1                            all          Common config package for CUDA Toolkit.
ii  cuda-tools-13-2                         13.2.0-1                             amd64        CUDA Tools meta-package
ii  cuda-visual-tools-13-2                  13.2.0-1                             amd64        CUDA visual tools
ii  firmware-nvidia-gsp                     595.58.03-1                          amd64        NVIDIA GSP firmware
ii  libcuda1:amd64                          595.58.03-1                          amd64        NVIDIA CUDA Driver Library
ii  libcudadebugger1:amd64                  595.58.03-1                          amd64        NVIDIA CUDA Debugger Library
ii  libegl-nvidia0:amd64                    595.58.03-1                          amd64        NVIDIA binary EGL library
ii  libgles-nvidia1:amd64                   595.58.03-1                          amd64        NVIDIA binary OpenGL|ES 1.x library
ii  libgles-nvidia2:amd64                   595.58.03-1                          amd64        NVIDIA binary OpenGL|ES 2.x library
ii  libglx-nvidia0:amd64                    595.58.03-1                          amd64        NVIDIA binary GLX library
ii  libnvidia-allocator1:amd64              595.58.03-1                          amd64        NVIDIA allocator runtime library
ii  libnvidia-api1:amd64                    595.58.03-1                          amd64        NVAPI runtime library
ii  libnvidia-cfg1:amd64                    595.58.03-1                          amd64        NVIDIA binary OpenGL/GLX configuration library
ii  libnvidia-container-tools               1.19.0-1                             amd64        NVIDIA container runtime library (command-line tools)
ii  libnvidia-container1:amd64              1.19.0-1                             amd64        NVIDIA container runtime library
ii  libnvidia-egl-gbm1:amd64                1.1.3-1                              amd64        GBM EGL external platform library for NVIDIA
ii  libnvidia-egl-wayland21:amd64           1.0.1-1                              amd64        Wayland EGL External Platform library, Version 2 -- shared library
ii  libnvidia-egl-xcb1:amd64                1:1.0.5-1                            amd64        This is an EGL platform library for the NVIDIA driver to support
ii  libnvidia-egl-xlib1:amd64               1:1.0.5-1                            amd64        This is an EGL platform library for the NVIDIA driver to support
ii  libnvidia-eglcore:amd64                 595.58.03-1                          amd64        NVIDIA binary EGL core libraries
ii  libnvidia-encode1:amd64                 595.58.03-1                          amd64        NVENC Video Encoding runtime library
ii  libnvidia-fbc1:amd64                    595.58.03-1                          amd64        NVIDIA OpenGL-based Framebuffer Capture runtime library
ii  libnvidia-glcore:amd64                  595.58.03-1                          amd64        NVIDIA binary OpenGL/GLX core libraries
ii  libnvidia-glvkspirv:amd64               595.58.03-1                          amd64        NVIDIA binary Vulkan Spir-V compiler library
ii  libnvidia-gpucomp:amd64                 595.58.03-1                          amd64        NVIDIA binary GPU compiler library
ii  libnvidia-ml1:amd64                     595.58.03-1                          amd64        NVIDIA Management Library (NVML) runtime library
ii  libnvidia-ngx1                          595.58.03-1                          amd64        NVIDIA NGX runtime library
ii  libnvidia-nvvm4:amd64                   595.58.03-1                          amd64        NVIDIA NVVM Compiler library
ii  libnvidia-nvvm704:amd64                 595.58.03-1                          amd64        NVIDIA NVVM Compiler library
ii  libnvidia-opticalflow1:amd64            595.58.03-1                          amd64        NVIDIA Optical Flow runtime library
ii  libnvidia-pkcs11-openssl3:amd64         595.58.03-1                          amd64        NVIDIA PKCS #11 Library (OpenSSL 3)
ii  libnvidia-present:amd64                 595.58.03-1                          amd64        NVIDIA FGX and postprocessing library
ii  libnvidia-ptxjitcompiler1:amd64         595.58.03-1                          amd64        NVIDIA PTX JIT Compiler library
ii  libnvidia-rtcore:amd64                  595.58.03-1                          amd64        NVIDIA binary Vulkan ray tracing (rtcore) library
ii  libnvidia-sandboxutils:amd64            595.58.03-1                          amd64        NVIDIA driver and GPU information for containers
ii  libnvidia-tileiras:amd64                595.58.03-1                          amd64        NVIDIA Tile IR Compiler library
ii  libnvidia-vksc-core                     595.58.03-1                          amd64        NVIDIA binary Vulkan Safety Critical library
ii  nvidia-container-toolkit                1.19.0-1                             amd64        NVIDIA Container toolkit
ii  nvidia-container-toolkit-base           1.19.0-1                             amd64        NVIDIA Container Toolkit Base
ii  nvidia-driver                           595.58.03-1                          amd64        NVIDIA metapackage
ii  nvidia-driver-cuda                      595.58.03-1                          amd64        NVIDIA driver CUDA integration components
ii  nvidia-driver-libs:amd64                595.58.03-1                          amd64        NVIDIA metapackage (OpenGL/GLX/EGL/GLES libraries)
ii  nvidia-egl-icd                          595.58.03-1                          amd64        NVIDIA EGL installable client driver (ICD)
ii  nvidia-kernel-dkms                      595.58.03-1                          amd64        NVIDIA binary kernel module DKMS source
ii  nvidia-kernel-support                   595.58.03-1                          amd64        NVIDIA binary kernel module support files
ii  nvidia-modprobe                         595.58.03-1                          amd64        utility to load NVIDIA kernel modules and create device nodes
ii  nvidia-opencl-icd:amd64                 595.58.03-1                          amd64        NVIDIA OpenCL installable client driver (ICD)
ii  nvidia-persistenced                     595.58.03-1                          amd64        daemon to maintain persistent software state in the NVIDIA driver
ii  nvidia-settings                         595.58.03-1                          amd64        Tool for configuring the NVIDIA graphics driver
ii  nvidia-vdpau-driver:amd64               595.58.03-1                          amd64        Video Decode and Presentation API for Unix - NVIDIA driver
ii  nvidia-vulkan-icd:amd64                 595.58.03-1                          amd64        NVIDIA Vulkan installable client driver (ICD)
ii  nvidia-xconfig                          595.58.03-1                          amd64        deprecated X configuration tool for non-free NVIDIA drivers
ii  xserver-xorg-video-nvidia               595.58.03-1                          amd64        NVIDIA binary Xorg driver
```




## 安装Ollama
1. 安装Ollama
```bash
# 官方一键安装脚本
curl -fsSL https://ollama.com/install.sh | sh

# 验证安装
ollama --version
```

2. 配置Ollama服务
```bash
# 编辑Ollama服务文件
sudo vim /etc/systemd/system/ollama.service

# 在[Service]部分添加环境变量
Environment="OLLAMA_HOST=0.0.0.0:11434"

# 重启服务
sudo systemctl daemon-reload
sudo systemctl restart ollama

# 验证服务状态
sudo systemctl status ollama
```

3. 拉取模型
```bash
# 运行 Llama 3.1 8B（4bit 量化版本，约 5GB）
ollama run llama3.1:8b-instruct-q4_K_M

# 或运行 Phi-4 14B（4bit 量化版本，约 8.5GB）
ollama run phi4:14b-q4_K_M

# 或运行 Qwen2.5 7B
ollama run qwen2.5:7b-instruct-q4_K_M
```

4. 验证模型运行
```bash
# 测试模型推理
ollama run phi4:14b-q4_K_M "解释一下什么是GPU直通技术"

# 按Ctrl+D退出
```

# 安装Open WebUI
1. 安装Docker
```bash
# 安装Docker依赖
sudo apt install ca-certificates curl gnupg

# 添加Docker官方GPG密钥
sudo install -m 0755 -d /etc/apt/keyrings
curl -fsSL https://download.docker.com/linux/debian/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg

# 添加Docker仓库
echo "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/debian bookworm stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null

# 安装Docker
sudo apt update
sudo apt install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
```

2. 安装NVIDIA Container Toolkit（GPU加速关键步骤）
```bash
# 添加NVIDIA Container Toolkit仓库
curl -fsSL https://nvidia.github.io/libnvidia-container/gpgkey | sudo gpg --dearmor -o /usr/share/keyrings/nvidia-container-toolkit-keyring.gpg

curl -s -L https://nvidia.github.io/libnvidia-container/stable/deb/nvidia-container-toolkit.list | \
  sed 's#deb https://#deb [signed-by=/usr/share/keyrings/nvidia-container-toolkit-keyring.gpg] https://#g' | \
  sudo tee /etc/apt/sources.list.d/nvidia-container-toolkit.list

# 安装
sudo apt update
sudo apt install nvidia-container-toolkit

# 配置Docker使用NVIDIA运行时
sudo nvidia-ctk runtime configure --runtime=docker
sudo systemctl restart docker
```

3. 部署Open WebUI容器
```bash
sudo docker run -d \
  --network=host \
  --gpus all \
  -v open-webui:/app/backend/data \
  -e OLLAMA_BASE_URL=http://localhost:11434 \
  --name open-webui \
  --restart always \
  ghcr.io/open-webui/open-webui:main
```

4. 验证容器运行
```bash
# 查看容器状态
sudo docker ps -a

# 查看容器日志
sudo docker logs open-webui --tail 50
```

## 配置Open WebUI连接Ollama
1 首次访问
打开浏览器，访问 http://<你的Debian虚拟机IP>:3000

host网络模式：使用 http://<虚拟机IP>:3000

桥接模式：使用 http://<虚拟机IP>:3000

2 注册管理员账号
首次访问会进入注册页面，设置你的邮箱和密码（所有数据存储在本地，不会上传到云端）。

3 配置Ollama连接
如果模型没有自动出现，手动配置连接：

点击左下角用户名 → 管理员面板（Admin Panel）

进入设置（Settings）→ 外部连接（External Connections）

找到Ollama配置，点击编辑：

基础URL：http://localhost:11434

点击验证连接（Verify Connection）

验证成功后，返回聊天界面，点击左上角模型下拉菜单，应该能看到 phi4:14b-q4_K_M 或你下载的其他模型。

4 开始对话
选择模型后，即可与本地模型进行对话，类似于使用 ChatGPT 的体验。


